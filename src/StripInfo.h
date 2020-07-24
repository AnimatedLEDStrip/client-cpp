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

#include <string>
#include <nlohmann/json.hpp>

#ifndef ANIMATEDLEDSTRIP_STRIPINFO_H
#define ANIMATEDLEDSTRIP_STRIPINFO_H

struct StripInfo {
    int numLEDs = 0;
    int pin = -1;
    bool imageDebugging = false;
    std::string fileName = "";
    int rendersBeforeSave = -1;
    int threadCount = 100;

    StripInfo & setNumLEDs(int n) {
        numLEDs = n;
        return *this;
    }

    StripInfo & setPin(int p) {
        pin = p;
        return *this;
    }

    StripInfo & setImageDebugging(bool i) {
        imageDebugging = i;
        return *this;
    }

    StripInfo & setFileName(std::string f) {
        fileName.assign(f);
        return *this;
    }

    StripInfo & setFileName(const char * f) {
        fileName.assign(f);
        return *this;
    }

    StripInfo & setRendersBeforeSave(int r) {
        rendersBeforeSave = r;
        return *this;
    }

    StripInfo & setThreadCount(int t) {
        threadCount = t;
        return *this;
    }

    StripInfo() {}

    StripInfo(nlohmann::json data) {
        if (data["numLEDs"] != nullptr) setNumLEDs(data["numLEDs"]);
        if (data["pin"] != nullptr) setPin(data["pin"]);
        if (data["imageDebugging"] != nullptr) setImageDebugging(data["imageDebugging"]);
        if (data["fileName"] != nullptr) setFileName(((std::string) data["fileName"]).c_str());
        if (data["rendersBeforeSave"] != nullptr) setRendersBeforeSave(data["rendersBeforeSave"]);
        if (data["threadCount"] != nullptr) setThreadCount(data["threadCount"]);
    }

};

#endif //ANIMATEDLEDSTRIP_STRIPINFO_H
