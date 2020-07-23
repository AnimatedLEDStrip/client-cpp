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

#ifndef ANIMATEDLEDSTRIPCLIENT_COLORCONTAINER_H
#define ANIMATEDLEDSTRIPCLIENT_COLORCONTAINER_H

#include <vector>
#include <string>
#include <cstring>
#include <iomanip>
#include <sstream>

struct ColorContainer {
    std::vector<long> colors;

    ColorContainer &addColor(long c) {
        colors.push_back(c);
        return *this;
    }

    int json(char **buff) {
        std::string data = R"({"colors":[)";

        for (auto c : colors) {
            data.append(std::to_string(c));
            data.append(",");
        }
        if (!colors.empty())
            data.pop_back();
        data.append("]}");

        strcpy(*buff, data.c_str());
        return data.size();
    }
};

#endif  // ANIMATEDLEDSTRIPCLIENT_COLORCONTAINER_H
