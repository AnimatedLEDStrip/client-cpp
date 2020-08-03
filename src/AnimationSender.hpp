/*
 *  Copyright (c) 2019-2020 AnimatedLEDStrip
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 */

#ifndef ANIMATEDLEDSTRIP_ANIMATIONSENDER_HPP
#define ANIMATEDLEDSTRIP_ANIMATIONSENDER_HPP

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <sstream>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
#include <nlohmann/json.hpp>
#include <safe-map/safemap.h>
#include "AnimationData.hpp"
#include "AnimationInfo.hpp"
#include "EndAnimation.hpp"
#include "Section.hpp"
#include "StripInfo.hpp"

using json = nlohmann::json;
#define DEBUG false

class AnimationSender {

    std::string host_name;
    int socket_desc;    // socket descriptor
    int port_num;
    struct sockaddr_in sa{};
    bool running = false;

    pthread_t receiver_handle{};

    std::string partialData;

    void (* receiveAction)(std::string) = nullptr;

    void (* newAnimationDataAction)(AnimationData) = nullptr;

    void (* newAnimationInfoAction)(AnimationInfo) = nullptr;

    void (* newEndAnimationAction)(EndAnimation) = nullptr;

    void (*newSectionAction)(Section) = nullptr;

    void (* newStripInfoAction)(StripInfo) = nullptr;

    void (* connectAction)(std::string, int) = nullptr;

    void (* disconnectAction)(std::string, int) = nullptr;

    void (* unableToConnectAction)(std::string, int) = nullptr;

    int getDelimitedStringLen(const std::string & buff) {
        int numDelimiters = 0;
        int count = 0;
        while (numDelimiters < 3) {
            if (buff[count] == 0) {
                partialData.assign(buff);
                return -1;
            }
            if (buff[count] == ';') numDelimiters++;
            else if (numDelimiters > 0) numDelimiters = 0;
            count++;
        }

        return count;
    }

    static void * receiverLoop(void * args) {
        AnimationSender sender = *((AnimationSender *) args);
        int ret;
        std::vector<std::string> tokens = std::vector<std::string>();
        char * buff = new char[MAX_LEN];

        while (sender.running) {
            if (DEBUG) printf("Waiting\n");
            if ((ret = recv(sender.socket_desc, buff, MAX_LEN - 1, 0)) < 0)
                printf("error %d", ret);
            if (DEBUG) printf("%s\n", buff);

            tokens.clear();

            int len;
            int start = 0;

            std::string fullStr;
            fullStr.assign(sender.partialData);
            fullStr.append(buff);

            sender.partialData.clear();

            while ((len = sender.getDelimitedStringLen(fullStr.substr(start))) != -1) {
                tokens.push_back(fullStr.substr(start, len - 3));
                start += len;
            }

            for (const auto & s : tokens) {
                auto t = s.substr(0, 4);
                const char * type = t.c_str();
                auto remainingData = s.substr(5);

                if (std::strcmp(type, "DATA") == 0) {
                    AnimationData d = AnimationData(json::parse(remainingData));
                    if (sender.newAnimationDataAction != nullptr) sender.newAnimationDataAction(d);
                    sender.running_animations->insert(std::pair<std::string, AnimationData>(d.id, d));
                } else if (std::strcmp(type, "AINF") == 0) {
                    AnimationInfo i = AnimationInfo(json::parse(remainingData));
                    sender.supported_animations->insert(std::pair<std::string, AnimationInfo>(i.name, i));
                    if (sender.newAnimationInfoAction != nullptr) sender.newAnimationInfoAction(i);
                } else if (std::strcmp(type, "END ") == 0) {
                    EndAnimation e = EndAnimation(json::parse(remainingData));
                    if (sender.newEndAnimationAction != nullptr) sender.newEndAnimationAction(e);
                    sender.running_animations->erase(e.id);
                } else if (std::strcmp(type, "SECT") == 0) {
                    Section sect = Section(json::parse(remainingData));
                    if (sender.newSectionAction != nullptr) sender.newSectionAction(sect);
                    sender.sections->insert(std::pair<std::string, Section>(sect.name, sect));
                } else if (std::strcmp(type, "SINF") == 0) {
                    StripInfo i = StripInfo(json::parse(remainingData));
                    sender.stripInfo = &i;
                    if (sender.newStripInfoAction != nullptr) sender.newStripInfoAction(i);
                } else {

                }

                if (sender.receiveAction != nullptr) sender.receiveAction(s);
            }
            for (int i = 0; i < MAX_LEN; i++) buff[i] = 0;
        }
        return nullptr;
    }

    int connect() {
        if (::connect(socket_desc, (struct sockaddr *) &sa, sizeof(sa)) < 0) {
            perror((host_name + " " + std::to_string(port_num) + " connect()").c_str());
            return -1;
        }
        return 0;
    }

public:
    StripInfo * stripInfo{};

    static const char * delimiter;

    safe::map<std::string, AnimationData> * running_animations;
    safe::map<std::string, AnimationInfo> * supported_animations;
    safe::map<std::string, Section> * sections;

    AnimationSender(const std::string & host, int port) {
        host_name = host;
        port_num = port;
        if ((socket_desc = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            perror("socket()");
        }
        struct hostent * hp;
        if ((hp = gethostbyname(host_name.c_str())) == nullptr) {
            perror("gethostbyname()");
        }
        memset((char *) &sa, '\0', sizeof(sa));
        memcpy((char *) &sa.sin_addr.s_addr, hp->h_addr, hp->h_length);
        sa.sin_family = AF_INET;
        sa.sin_port = htons(port_num);

        running_animations = new safe::map<std::string, AnimationData>;
        supported_animations = new safe::map<std::string, AnimationInfo>;
        sections = new safe::map<std::string, Section>;
    }

    ~AnimationSender() {
        delete running_animations;
        delete supported_animations;
        delete sections;
        delete stripInfo;
    }

    int start() {
        if (connect() < 0) {
            perror("Could not connect");
            if (unableToConnectAction != nullptr) unableToConnectAction(host_name, port_num);
            return -1;
        }
        running = true;
        pthread_create(
                &receiver_handle,
                nullptr,
                receiverLoop,
                this);
        if (connectAction != nullptr) connectAction(host_name, port_num);
        return 0;
    }

    int end() {
        if (close(socket_desc) < 0) {
            perror("Could not close socket");
            return -1;
        }
        running = false;
        pthread_cancel(receiver_handle);
        if (disconnectAction != nullptr) disconnectAction(host_name, port_num);
        supported_animations->clear();
        running_animations->clear();
        sections->clear();
        return 0;
    }

    int send(const char * buff, int size) const {
        char * sendBuff = new char[size + 4];
        std::strcpy(sendBuff, buff);
        std::strcat(sendBuff, delimiter);
        int ret;
        if ((ret = write(socket_desc, sendBuff, size + 3)) < 0)
            printf("error %d", ret);
        return ret;
    }

    int send(const AnimationData & d) const {
        char * buff = new char[MAX_LEN];
        int size = d.json(&buff);
        return send(buff, size);
    }

    int send(const EndAnimation & e) const {
        char * buff = new char[MAX_LEN];
        int size = e.json(&buff);
        return send(buff, size);
    }


    AnimationSender & setOnReceiveCallback(void (* action)(std::string)) {
        receiveAction = action;
        return *this;
    }

    AnimationSender & setOnConnectCallback(void (* action)(std::string, int)) {
        connectAction = action;
        return *this;
    }

    AnimationSender & setOnDisconnectCallback(void (* action)(std::string, int)) {
        disconnectAction = action;
        return *this;
    }

    AnimationSender & setOnUnableToConnectCallback(void (* action)(std::string, int)) {
        unableToConnectAction = action;
        return *this;
    }

    AnimationSender & setOnNewAnimationDataCallback(void (* action)(AnimationData)) {
        newAnimationDataAction = action;
        return *this;
    }

    AnimationSender & setOnNewAnimationInfoCallback(void (* action)(AnimationInfo)) {
        newAnimationInfoAction = action;
        return *this;
    }

    AnimationSender & setOnNewEndAnimationCallback(void (* action)(EndAnimation)) {
        newEndAnimationAction = action;
        return *this;
    }

    AnimationSender & setOnNewSectionCallback(void (*action)(Section)) {
        newSectionAction = action;
        return *this;
    }

    AnimationSender & setOnNewStripInfoCallback(void (* action)(StripInfo)) {
        newStripInfoAction = action;
        return *this;
    }

};

const char * AnimationSender::delimiter = ";;;";

#endif // ANIMATEDLEDSTRIP_ANIMATIONSENDER_HPP
