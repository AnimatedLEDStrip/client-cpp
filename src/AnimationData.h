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

#ifndef ANIMATEDLEDSTRIPCLIENT_ANIMATIONDATA_H
#define ANIMATEDLEDSTRIPCLIENT_ANIMATIONDATA_H

#include <string>
#include <nlohmann/json.hpp>
#include "Animation.h"
#include "ColorContainer.h"
#include "Continuous.h"
#include "Direction.h"

#define MAX_LEN 10000

class AnimationData {
public:
    Animation animation = COLOR;
    std::vector<ColorContainer> colors;
    int center = -1;
    Continuous continuous = DEFAULT;
    long delay = -1;
    double delay_mod = 1.0;
    Direction direction = FORWARD;
    int distance = -1;
    int end_pixel = -1;
    std::string id = "";
    int spacing = -1;
    int start_pixel = 0;


    AnimationData &setAnimation(enum Animation a);

    AnimationData &addColor(struct ColorContainer &c);

    AnimationData &setCenter(int c);

    AnimationData &setContinuous(enum Continuous c);

    AnimationData &setDelay(long d);

    AnimationData &setDelayMod(double d);

    AnimationData &setDirection(enum Direction d);

    AnimationData &setDistance(int d);

    AnimationData &setEndPixel(int p);

    AnimationData &setId(std::string &i);

    AnimationData &setId(char *i);

    AnimationData &setSpacing(int s);

    AnimationData &setStartPixel(int p);


    int json(char **buff) const {
        std::string data = "DATA:{";

        data.append(R"("animation":")");
        data.append(animation_string(animation));

        data.append(R"(","colors":[)");

        char *cBuff = new char[MAX_LEN];
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
        data.append(continuous_string(continuous));

        data.append(R"(,"delay":)");
        data.append(std::to_string(delay));

        data.append(R"(,"delayMod":)");
        data.append(std::to_string(delay_mod));

        data.append(R"(,"direction":")");
        data.append(direction_string(direction));

        data.append(R"(","distance":)");
        data.append(std::to_string(distance));

        data.append(R"(,"endPixel":)");
        data.append(std::to_string(end_pixel));

        data.append(R"(,"id":")");
        data.append(id);

        data.append(R"(","spacing":)");
        data.append(std::to_string(spacing));

        data.append(R"(,"startPixel":)");
        data.append(std::to_string(start_pixel));

        data.append("}");

        std::strcpy(*buff, data.c_str());
        return data.size();
    }

    static AnimationData &get_data_from_json(nlohmann::json data) {
        auto *d = new AnimationData();
        d->setAnimation(animation_from_string(((std::string) data["animation"]).c_str()));
        for (auto c : data["colors"]) {
            ColorContainer cc;
            for (int col : c["colors"])
                cc.addColor(col);
            d->addColor(cc);
        }
        d->setCenter(data["center"]);
        if (data["continuous"] == nullptr)
            d->setContinuous(DEFAULT);
        else
            d->setContinuous(continuous_from_bool(data["continuous"]));
        d->setDelay(data["delay"]);
        d->setDelayMod(data["delayMod"]);
        d->setDirection(direction_from_string(((std::string) data["direction"]).c_str()));
        d->setDistance(data["distance"]);
        d->setEndPixel(data["endPixel"]);
        d->id = data["id"];
        d->setSpacing(data["spacing"]);
        d->setStartPixel(data["startPixel"]);
        return *d;
    }
};


#endif  // ANIMATEDLEDSTRIPCLIENT_ANIMATIONDATA_H
