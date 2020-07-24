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

#ifndef ANIMATEDLEDSTRIP_ANIMATIONSENDER_H
#define ANIMATEDLEDSTRIP_ANIMATIONSENDER_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
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
#include "AnimationData.h"
#include "StripInfo.h"

using json = nlohmann::json;
#define DEBUG true

class AnimationSender {

    std::string host_name;
    int socket_desc;    // socket descriptor
    int port_num;
    struct sockaddr_in sa{};
    bool running = false;

    pthread_t receiver_handle{};

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

            std::stringstream ss(buff);
            std::string token;
            tokens.clear();

            while (std::getline(ss, token, ';'))
                tokens.push_back(token);

            for (const auto & s : tokens) {
                auto t = s.substr(0, 4);
                const char * type = t.c_str();
                auto remainingData = s.substr(5);

                if (strcmp(type, "AINF")) {
                    // TODO
                } else if (strcmp(type, "DATA")) {
                    AnimationData d = AnimationData(json::parse(remainingData));
                    sender.running_animations.insert(std::pair<std::string, AnimationData>(d.id, d));
                } else if (strcmp(type, "END ")) {
                    // TODO
                } else if (strcmp(type, "SECT")) {
                    // TODO
                } else if (strcmp(type, "SINF")) {
                    StripInfo i = StripInfo(json::parse(remainingData));
                    sender.info = &i;
                } else {

                }


                if (strcmp(s.substr(0, 4).c_str(), "INFO") == 0) {
                    json data = json::parse(s.substr(5));
                    int num = data["numLEDs"];
                    sender.info = new StripInfo();
                } else if (strcmp(s.substr(0, 4).c_str(), "DATA") == 0) {
                    json data = json::parse(s.substr(5));
                    AnimationData d = AnimationData(data);
//                if (d.animation == ENDANIMATION)
//                    sender.running_animations.erase(d.id);
//                else
                    sender.running_animations.insert(std::pair<std::string, AnimationData>(d.id, d));
                }
            }
            for (int i = 0; i < MAX_LEN; i++) buff[i] = 0;
        }
        return nullptr;
    }

    int connect() {
        if (::connect(socket_desc, (struct sockaddr *) &sa, sizeof(sa)) < 0) {
            perror("connect()");
            return -1;
        }
        printf("Connected\n");
        return 0;
    }

public:
    StripInfo * info{};

    safe::map<std::string, AnimationData> running_animations;

    AnimationSender(const std::string & host, int port) {
        host_name = host;
        port_num = port;
        if ((socket_desc = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            perror("socket()");
        }
        struct hostent * hp;
        if ((hp = gethostbyname(host.c_str())) == nullptr) {
            perror("gethostbyname()");
        }
        memset((char *) &sa, '\0', sizeof(sa));
        memcpy((char *) &sa.sin_addr.s_addr, hp->h_addr, hp->h_length);
        sa.sin_family = AF_INET;
        sa.sin_port = htons(port);
    }


    int start() {
        if (connect() < 0) {
            perror("Could not connect");
            return -1;
        }
        running = true;
        pthread_create(
                &receiver_handle,
                nullptr,
                receiverLoop,
                this);
        return 0;
    }

    int end() {
        if (close(socket_desc) < 0) {
            perror("Could not close socket");
            return -1;
        }
        running = false;
        pthread_cancel(receiver_handle);
        return 0;
    }


    int sendAnimation(const AnimationData & d) {
        char * buff = new char[MAX_LEN];
        int size = d.json(&buff);
        int ret;
        if ((ret = write(socket_desc, buff, size)) < 0)
            printf("error %d", ret);
        return 0;
    }

    int endAnimation(const std::string & id) {
        if (running_animations.count(id) == 0)
            return 1;
        else {
//        AnimationData d = running_animations[id];
//        d.setAnimation(ENDANIMATION);
//        char *buff = new char[MAX_LEN];
//
//        int size = d.json(&buff);
//        int ret;
//        if ((ret = write(socket_desc, buff, size)) < 0)
//            printf("error %d", ret);
//        sleep(1);
            return 0;
        }
    }

    int endAnimation(const AnimationData & d) {
        char * buff = new char[MAX_LEN];
        int size = d.json(&buff);
        int ret;
        if ((ret = write(socket_desc, buff, size)) < 0)
            printf("error %d", ret);
        sleep(5);
        return 0;
    }

};

#endif // ANIMATEDLEDSTRIP_ANIMATIONSENDER_H
