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

#ifndef ANIMATEDLEDSTRIP_ANIMATIONDATA_H
#define ANIMATEDLEDSTRIP_ANIMATIONDATA_H

#include <string>
#include <nlohmann/json.hpp>
#include "ColorContainer.h"

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


    AnimationData & setAnimation(std::string & a) {
        animation.assign(a);
        return *this;
    }

    AnimationData & setAnimation(const char * a) {
        animation.assign(a);
        return *this;
    }

    AnimationData & addColor(struct ColorContainer & c) {
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

    AnimationData & setId(std::string & i) {
        id.assign(i);
        return *this;
    }

    AnimationData & setId(const char * i) {
        id.assign(i);
        return *this;
    }

    AnimationData & setSection(std::string & s) {
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

    AnimationData() {}

    AnimationData(nlohmann::json data) {
        if (data["animation"] != nullptr) setAnimation(((std::string) data["animation"]).c_str());

        if (data["colors"] != nullptr)
            for (auto c : data["colors"]) {
                ColorContainer cc;
                for (int col : c["colors"])
                    cc.addColor(col);
                addColor(cc);
            }

        if (data["center"] != nullptr) setCenter(data["center"]);

        if (data["continuous"] == nullptr) setContinuous(DEFAULT);
        else if (data["continuous"] == true) setContinuous(CONTINUOUS);
        else if (data["continuous"] == false) setContinuous(NONCONTINUOUS);

        if (data["delay"] != nullptr) setDelay(data["delay"]);

        if (data["delayMod"] != nullptr) setDelayMod(data["delayMod"]);

        if (data["direction"] != nullptr) {
            if (std::strcmp(((std::string) data["direction"]).c_str(), "FORWARD") == 0)
                setDirection(FORWARD);
            else if (std::strcmp(((std::string) data["direction"]).c_str(), "BACKWARD") == 0)
                setDirection(BACKWARD);
            else setDirection(FORWARD);
        }

        if (data["distance"] != nullptr) setDistance(data["distance"]);

        if (data["id"] != nullptr) setId(((std::string) data["id"]).c_str());

        if (data["section"] != nullptr) setSection(((std::string) data["section"]).c_str());

        if (data["spacing"] != nullptr) setSpacing(data["spacing"]);
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
        switch (continuous) {
            case CONTINUOUS:
                data.append("true");
                break;
            case NONCONTINUOUS:
                data.append("false");
                break;
            case DEFAULT:
                data.append("null");
                break;
        }

        data.append(R"(,"delay":)");
        data.append(std::to_string(delay));

        data.append(R"(,"delayMod":)");
        data.append(std::to_string(delay_mod));

        data.append(R"(,"direction":")");
        switch (direction) {
            case FORWARD:
                data.append("FORWARD");
                break;
            case BACKWARD:
                data.append("BACKWARD");
                break;
        }

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


#endif  // ANIMATEDLEDSTRIP_ANIMATIONDATA_H
