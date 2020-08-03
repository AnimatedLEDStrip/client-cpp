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

#ifndef ANIMATEDLEDSTRIP_SECTION_HPP
#define ANIMATEDLEDSTRIP_SECTION_HPP

#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

class Section {
public:
    std::string name = "";
    int startPixel = -1;
    int endPixel = -1;
    int physicalStart = -1;
    int numLEDs = 0;

    Section & setName(const std::string & n) {
        name.assign(n);
        return *this;
    }

    Section & setName(const char * n) {
        name.assign(n);
        return *this;
    }

    Section & setStartPixel(int s) {
        startPixel = s;
        return *this;
    }

    Section & setEndPixel(int e) {
        endPixel = e;
        return *this;
    }

    Section & setPhysicalStart(int p) {
        physicalStart = p;
        return *this;
    }

    Section & setNumLEDs(int n) {
        numLEDs = n;
        return *this;
    }

    Section() = default;

    explicit Section(nlohmann::json data) {
        if (data["name"].is_string())
            setName(data["name"].get<std::string>());
        else if (!data["name"].is_null())
            std::cerr << "Bad type for name" << data["name"].type_name() << std::endl;

        if (data["startPixel"].is_number_integer())
            setStartPixel(data["startPixel"].get<int>());
        else if (!data["startPixel"].is_null())
            std::cerr << "Bad type for startPixel" << data["startPixel"].type_name() << std::endl;

        if (data["endPixel"].is_number_integer())
            setEndPixel(data["endPixel"].get<int>());
        else if (!data["endPixel"].is_null())
            std::cerr << "Bad type for endPixel" << data["endPixel"].type_name() << std::endl;

        if (data["physicalStart"].is_number_integer())
            setPhysicalStart(data["physicalStart"].get<int>());
        else if (!data["physicalStart"].is_null())
            std::cerr << "Bad type for physicalStart" << data["physicalStart"].type_name() << std::endl;

        if (data["numLEDs"].is_number_integer())
            setNumLEDs(data["numLEDs"].get<int>());
        else if (!data["numLEDs"].is_null())
            std::cerr << "Bad type for numLEDs" << data["numLEDs"].type_name() << std::endl;
    }

    int json(char ** buff) const {
        std::string data = "SECT:{";

        data.append(R"("name":")");
        data.append(name);

        data.append(R"(","startPixel":)");
        data.append(std::to_string(startPixel));

        data.append(R"(,"endPixel":)");
        data.append(std::to_string(endPixel));

        data.append("}");

        std::strcpy(*buff, data.c_str());
        return data.size();
    }
};

#endif //ANIMATEDLEDSTRIP_SECTION_HPP
