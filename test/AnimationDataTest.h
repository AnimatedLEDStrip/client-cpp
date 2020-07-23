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

#ifndef ANIMATEDLEDSTRIPCLIENT_ANIMATIONDATATEST_H
#define ANIMATEDLEDSTRIPCLIENT_ANIMATIONDATATEST_H

#include "AnimationData.h"
#include "AnimationSender.h"
#include "nlohmann/json.hpp"
#include "gtest/gtest.h"


namespace {

    TEST(AnimationData, DefaultConstructor) {
        const AnimationData data = AnimationData();

        EXPECT_STREQ(data.animation.c_str(), "Color");
        EXPECT_EQ(data.center, -1);
        EXPECT_EQ(data.continuous, DEFAULT);
        EXPECT_EQ(data.delay, -1);
        EXPECT_EQ(data.delay_mod, 1.0);
        EXPECT_EQ(data.direction, FORWARD);
        EXPECT_EQ(data.distance, -1);
        EXPECT_STREQ(data.id.c_str(), "");
        EXPECT_STREQ(data.section.c_str(), "");
        EXPECT_EQ(data.spacing, -1);
    }

    TEST(AnimationData, SetAnimation) {
        AnimationData data = AnimationData();
        EXPECT_STREQ(data.animation.c_str(), "Color");
        char test[5];
        strcpy(test, "Meteor");
        data.setAnimation(test);
        EXPECT_STREQ(data.animation.c_str(), "Meteor");
        std::string test2 = "Multi Pixel Run";
        data.setAnimation(test2);
        EXPECT_STREQ(data.animation.c_str(), "Multi Pixel Run");
    }

    TEST(AnimationData, AddColor) {
        AnimationData data = AnimationData();
        ColorContainer cc = ColorContainer();
        cc.addColor(0xFFFF);
        data.addColor(cc);
        EXPECT_TRUE(data.colors.size() == 1);
    }

    TEST(AnimationData, SetCenter) {
        AnimationData data = AnimationData();
        EXPECT_EQ(data.center, -1);
        data.setCenter(50);
        EXPECT_EQ(data.center, 50);
    }

    TEST(AnimationData, SetContinuous) {
        AnimationData data = AnimationData();
        EXPECT_EQ(data.continuous, DEFAULT);
        data.setContinuous(CONTINUOUS);
        EXPECT_EQ(data.continuous, CONTINUOUS);
        data.setContinuous(NONCONTINUOUS);
        EXPECT_EQ(data.continuous, NONCONTINUOUS);
        data.setContinuous(DEFAULT);
        EXPECT_EQ(data.continuous, DEFAULT);
    }

    TEST(AnimationData, SetDelay) {
        AnimationData data = AnimationData();
        EXPECT_EQ(data.delay, -1);
        data.setDelay(30);
        EXPECT_EQ(data.delay, 30);
    }

    TEST(AnimationData, SetDelayMod) {
        AnimationData data = AnimationData();
        EXPECT_EQ(data.delay_mod, 1.0);
        data.setDelayMod(3.0);
        EXPECT_EQ(data.delay_mod, 3.0);
    }

    TEST(AnimationData, SetDirection) {
        AnimationData data = AnimationData();
        EXPECT_EQ(data.direction, FORWARD);
        data.setDirection(BACKWARD);
        EXPECT_EQ(data.direction, BACKWARD);
        data.setDirection(FORWARD);
        EXPECT_EQ(data.direction, FORWARD);
    }

    TEST(AnimationData, SetDistance) {
        AnimationData data = AnimationData();
        EXPECT_EQ(data.distance, -1);
        data.setDistance(50);
        EXPECT_EQ(data.distance, 50);
    }

    TEST(AnimationData, SetId) {
        AnimationData data = AnimationData();
        EXPECT_STREQ(data.id.c_str(), "");
        char test[5];
        strcpy(test, "TEST");
        data.setId(test);
        EXPECT_STREQ(data.id.c_str(), "TEST");
        std::string test2 = "TEST2";
        data.setId(test2);
        EXPECT_STREQ(data.id.c_str(), "TEST2");
    }

    TEST(AnimationData, SetSection) {
        AnimationData data = AnimationData();
        EXPECT_STREQ(data.section.c_str(), "");
        char test[5];
        strcpy(test, "TEST");
        data.setSection(test);
        EXPECT_STREQ(data.section.c_str(), "TEST");
        std::string test2 = "TEST2";
        data.setSection(test2);
        EXPECT_STREQ(data.section.c_str(), "TEST2");
    }

    TEST(AnimationData, SetSpacing) {
        AnimationData data = AnimationData();
        EXPECT_EQ(data.spacing, -1);
        data.setSpacing(5);
        EXPECT_EQ(data.spacing, 5);
    }

    TEST(AnimationData, JSON) {
        AnimationData data = AnimationData();

        data.setAnimation("Meteor");

        ColorContainer cc = ColorContainer();
        cc.addColor(0xFF);
        cc.addColor(0xFF00);

        ColorContainer cc2 = ColorContainer();
        cc2.addColor(0xFF0000);

        data.addColor(cc);
        data.addColor(cc2);
        data.setCenter(50);
        data.setContinuous(NONCONTINUOUS);
        data.setDelay(10);
        data.setDelayMod(1.5);
        data.setDirection(BACKWARD);
        data.setDistance(45);
        std::string test_str = "TEST";
        data.setId(test_str);
        data.setSection("SECT");
        data.setSpacing(5);

        char * data_str = new char[1000];
        data.json(&data_str);
        EXPECT_STREQ(data_str,
                     "DATA:{\"animation\":\"Meteor\",\"colors\":[{\"colors\":[255,65280]},{\"colors\":[16711680]}],\"center\":50,\"continuous\":false,\"delay\":10,\"delayMod\":1.500000,\"direction\":\"BACKWARD\",\"distance\":45,\"id\":\"TEST\",\"section\":\"SECT\",\"spacing\":5}");
    }

    TEST(AnimationData, FromJSON) {
        std::string data_str = R"({"animation":"Meteor","colors":[{"colors":[255,65280]},{"colors":[16711680]}],"center":50,"continuous":false,"delay":10,"delayMod":1.500000,"direction":"BACKWARD","distance":45,"id":"TEST","section":"SECT","spacing":5})";

        nlohmann::json data_json = nlohmann::json::parse(data_str);
        AnimationData data = AnimationData::get_data_from_json(data_json);

        EXPECT_STREQ(data.animation.c_str(), "Meteor");
        EXPECT_TRUE(data.colors.size() == 2);
        EXPECT_TRUE(data.colors[0].colors.size() == 2);
        EXPECT_EQ(data.colors[0].colors[0], 0xFF);
        EXPECT_EQ(data.colors[0].colors[1], 0xFF00);
        EXPECT_TRUE(data.colors[1].colors.size() == 1);
        EXPECT_EQ(data.colors[1].colors[0], 0xFF0000);
        EXPECT_EQ(data.center, 50);
        EXPECT_EQ(data.continuous, NONCONTINUOUS);
        EXPECT_EQ(data.delay, 10);
        EXPECT_EQ(data.delay_mod, 1.5);
        EXPECT_EQ(data.direction, BACKWARD);
        EXPECT_EQ(data.distance, 45);
        EXPECT_STREQ(data.id.c_str(), "TEST");
        EXPECT_STREQ(data.section.c_str(), "SECT");
        EXPECT_EQ(data.spacing, 5);

        // Test when continuous is null, as this is handled separately from true/false
        std::string data_str2 = R"({"animation":"METEOR","colors":[],"center":50,"continuous":null,"delay":10,"delayMod":1.500000,"direction":"BACKWARD","distance":45,"endPixel":200,"id":"TEST","spacing":5,"startPixel":15})";
        nlohmann::json data_json2 = nlohmann::json::parse(data_str2);
        AnimationData data2 = AnimationData::get_data_from_json(data_json2);

        EXPECT_EQ(data2.continuous, DEFAULT);
    }
}

#endif
