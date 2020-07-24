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

#ifndef ANIMATEDLEDSTRIP_STRIPINFO_HPP
#define ANIMATEDLEDSTRIP_STRIPINFO_HPP

class StripInfo {
public:
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

    StripInfo & setFileName(const std::string f) {
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

    StripInfo() = default;

    explicit StripInfo(nlohmann::json data) {
        if (data["numLEDs"].is_number_integer())
            setNumLEDs(data["numLEDs"].get<int>());
        else if (!data["numLEDs"].is_null())
            std::cerr << "Bad type for numLEDs" << data["numLEDs"].type_name() << std::endl;

        if (data["pin"].is_number_integer())
            setPin(data["pin"].get<int>());
        else if (!data["pin"].is_null())
            std::cerr << "Bad type for pin" << data["pin"].type_name() << std::endl;

        if (data["imageDebugging"].is_boolean())
            setImageDebugging(data["imageDebugging"].get<bool>());
        else if (!data["imageDebugging"].is_null())
            std::cerr << "Bad type for imageDebugging" << data["imageDebugging"].type_name() << std::endl;

        if (data["fileName"].is_string())
            setFileName(data["fileName"].get<std::string>());
        else if (!data["fileName"].is_null())
            std::cerr << "Bad type for fileName" << data["fileName"].type_name() << std::endl;

        if (data["rendersBeforeSave"].is_number_integer())
            setRendersBeforeSave(data["rendersBeforeSave"].get<int>());
        else if (!data["rendersBeforeSave"].is_null())
            std::cerr << "Bad type for rendersBeforeSave" << data["rendersBeforeSave"].type_name() << std::endl;

        if (data["threadCount"].is_number_integer())
            setThreadCount(data["threadCount"].get<int>());
        else if (!data["threadCount"].is_null())
            std::cerr << "Bad type for threadCount" << data["threadCount"].type_name() << std::endl;
    }

};

#endif //ANIMATEDLEDSTRIP_STRIPINFO_HPP
