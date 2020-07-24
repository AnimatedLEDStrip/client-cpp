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

class AnimationSender {

    std::string host_name;
    int socket_desc;    // socket descriptor
    int port_num;
    struct sockaddr_in sa{};
    bool running = false;

    pthread_t receiver_handle{};

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


    int start();

    int end();


    int sendAnimation(const AnimationData & d);

    int endAnimation(const std::string & id);

    int endAnimation(const AnimationData & d);

private:
    int connect();

    static void * receiverLoop(void *);
};

#endif // ANIMATEDLEDSTRIP_ANIMATIONSENDER_H
