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

#ifndef ANIMATEDLEDSTRIP_ANIMATIONDATA_HPP
#define ANIMATEDLEDSTRIP_ANIMATIONDATA_HPP

#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include "ColorContainer.hpp"

#define MAX_LEN 10000

enum Continuous {
    CONTINUOUS,
    NONCONTINUOUS,
    DEFAULT
};

enum Direction {
    FORWARD,
    BACKWARD
};

class AnimationData {
public:
    std::string animation = "Color";
    std::vector<ColorContainer> colors;
    int center = -1;
    Continuous continuous = DEFAULT;
    long delay = -1;
    double delay_mod = 1.0;
    Direction direction = FORWARD;
    int distance = -1;
    std::string id = "";
    std::string section = "";
    int spacing = -1;


    AnimationData & setAnimation(const std::string & a) {
        animation.assign(a);
        return *this;
    }

    AnimationData & setAnimation(const char * a) {
        animation.assign(a);
        return *this;
    }

    AnimationData & addColor(ColorContainer & c) {
        colors.push_back(c);
        return *this;
    }

    AnimationData & setCenter(int c) {
        center = c;
        return *this;
    }

    AnimationData & setContinuous(enum Continuous c) {
        continuous = c;
        return *this;
    }

    AnimationData & setDelay(long d) {
        delay = d;
        return *this;
    }

    AnimationData & setDelayMod(double d) {
        delay_mod = d;
        return *this;
    }

    AnimationData & setDirection(enum Direction d) {
        direction = d;
        return *this;
    }

    AnimationData & setDistance(int d) {
        distance = d;
        return *this;
    }

    AnimationData & setId(const std::string & i) {
        id.assign(i);
        return *this;
    }

    AnimationData & setId(const char * i) {
        id.assign(i);
        return *this;
    }

    AnimationData & setSection(const std::string & s) {
        section.assign(s);
        return *this;
    }

    AnimationData & setSection(const char * s) {
        section.assign(s);
        return *this;
    }

    AnimationData & setSpacing(int s) {
        spacing = s;
        return *this;
    }

    static std::string continuousToString(enum Continuous c) {
        switch (c) {
            case CONTINUOUS:
                return "true";
            case NONCONTINUOUS:
                return "false";
            case DEFAULT:
                return "null";
        }
    }

    static enum Direction directionFromString(const std::string & d) {
        if (std::strcmp(d.c_str(), "BACKWARD") == 0) return BACKWARD;
        else if (std::strcmp(d.c_str(), "FORWARD") == 0) return FORWARD;
        else {
            std::cerr << "Bad direction string " << d << std::endl;
            return FORWARD;
        }
    }

    static std::string directionToString(enum Direction d) {
        switch (d) {
            case FORWARD:
                return "FORWARD";
            case BACKWARD:
                return "BACKWARD";
        }
    }

    AnimationData() = default;

    explicit AnimationData(nlohmann::json data) {
        if (data["animation"].is_string())
            setAnimation(data["animation"].get<std::string>());
        else if (!data["animation"].is_null())
            std::cerr << "Bad type for animation" << data["animation"].type_name() << std::endl;

        if (data["colors"].is_array())
            for (auto & c : data["colors"].items()) {
                if (c.value().is_object()) {
                    ColorContainer cc = ColorContainer(c.value());
                    addColor(cc);
                }
            }
        else if (!data["colors"].is_null())
            std::cerr << "Bad type for colors" << data["colors"].type_name() << std::endl;

        if (data["center"].is_number_integer())
            setCenter(data["center"].get<int>());
        else if (!data["center"].is_null())
            std::cerr << "Bad type for center" << data["center"].type_name() << std::endl;

        if (data["continuous"].is_null())
            setContinuous(DEFAULT);
        else if (data["continuous"].is_boolean() && data["continuous"].get<bool>())
            setContinuous(CONTINUOUS);
        else if (data["continuous"].is_boolean() && !data["continuous"].get<bool>())
            setContinuous(NONCONTINUOUS);
        else
            std::cerr << "Bad type for continuous" << data["continuous"].type_name() << std::endl;

        if (data["delay"].is_number_integer())
            setDelay(data["delay"].get<int>());
        else if (!data["delay"].is_null())
            std::cerr << "Bad type for delay" << data["delay"].type_name() << std::endl;

        if (data["delayMod"].is_number_float())
            setDelayMod(data["delayMod"].get<double>());
        else if (!data["delayMod"].is_null())
            std::cerr << "Bad type for delayMod" << data["delayMod"].type_name() << std::endl;

        if (data["direction"].is_string())
            setDirection(directionFromString(data["direction"].get<std::string>()));
        else if (!data["direction"].is_null())
            std::cerr << "Bad type for direction" << data["direction"].type_name() << std::endl;

        if (data["distance"].is_number_integer())
            setDistance(data["distance"].get<int>());
        else if (!data["distance"].is_null())
            std::cerr << "Bad type for distance" << data["distance"].type_name() << std::endl;

        if (data["id"].is_string())
            setId(data["id"].get<std::string>());
        else if (!data["id"].is_null())
            std::cerr << "Bad type for id" << data["id"].type_name() << std::endl;

        if (data["section"].is_string())
            setSection(data["section"].get<std::string>());
        else if (!data["section"].is_null())
            std::cerr << "Bad type for section" << data["section"].type_name() << std::endl;

        if (data["spacing"].is_number_integer())
            setSpacing(data["spacing"].get<int>());
        else if (!data["spacing"].is_null())
            std::cerr << "Bad type for spacing" << data["spacing"].type_name() << std::endl;
    }

    std::string colorsString() {
        std::string cols = "[";

        for (auto c : colors) {
            cols.append(c.colorsString(true));
            cols.append(",");
        }
        if (!colors.empty())
            cols.pop_back();
        cols.append("]");
        return cols;
    }

    int json(char ** buff) const {
        std::string data = "DATA:{";

        data.append(R"("animation":")");
        data.append(animation);

        data.append(R"(","colors":[)");

        char * cBuff = new char[MAX_LEN];
        for (ColorContainer c : colors) {
            cBuff[0] = 0;
            c.json(&cBuff);
            data.append(cBuff);
            data.append(",");
        }
        if (!colors.empty())
            data.pop_back();

        data.append(R"(],"center":)");
        data.append(std::to_string(center));

        data.append(R"(,"continuous":)");
        data.append(continuousToString(continuous));

        data.append(R"(,"delay":)");
        data.append(std::to_string(delay));

        data.append(R"(,"delayMod":)");
        data.append(std::to_string(delay_mod));

        data.append(R"(,"direction":")");
        data.append(directionToString(direction));

        data.append(R"(","distance":)");
        data.append(std::to_string(distance));

        data.append(R"(,"id":")");
        data.append(id);

        data.append(R"(","section":")");
        data.append(section);

        data.append(R"(","spacing":)");
        data.append(std::to_string(spacing));

        data.append("}");

        std::strcpy(*buff, data.c_str());
        return data.size();
    }

};


#endif  // ANIMATEDLEDSTRIP_ANIMATIONDATA_HPP
