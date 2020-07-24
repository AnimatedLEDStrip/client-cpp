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

#ifndef ANIMATEDLEDSTRIP_ANIMATIONINFOTEST_H
#define ANIMATEDLEDSTRIP_ANIMATIONINFOTEST_H

#include "AnimationInfo.hpp"
#include "nlohmann/json.hpp"
#include "gtest/gtest.h"


namespace {

    TEST(AnimationInfo, DefaultConstructor) {
        const AnimationInfo info = AnimationInfo();

        EXPECT_STREQ(info.name.c_str(), "");
        EXPECT_STREQ(info.abbr.c_str(), "");
        EXPECT_STREQ(info.description.c_str(), "");
        EXPECT_STREQ(info.signatureFile.c_str(), "");
        EXPECT_FALSE(info.repetitive);
        EXPECT_EQ(info.minimumColors, 0);
        EXPECT_FALSE(info.unlimitedColors);
        EXPECT_EQ(info.center, NOTUSED);
        EXPECT_EQ(info.delay, NOTUSED);
        EXPECT_EQ(info.direction, NOTUSED);
        EXPECT_EQ(info.distance, NOTUSED);
        EXPECT_EQ(info.spacing, NOTUSED);
        EXPECT_EQ(info.delayDefault, 50);
        EXPECT_EQ(info.distanceDefault, -1);
        EXPECT_EQ(info.spacingDefault, 3);
    }

    TEST(AnimationInfo, SetName) {
        AnimationInfo info = AnimationInfo();
        EXPECT_STREQ(info.name.c_str(), "");
        char test[7];
        strcpy(test, "Meteor");
        info.setName(test);
        EXPECT_STREQ(info.name.c_str(), "Meteor");
        std::string test2 = "Multi Pixel Run";
        info.setName(test2);
        EXPECT_STREQ(info.name.c_str(), "Multi Pixel Run");
    }

    TEST(AnimationInfo, SetAbbr) {
        AnimationInfo info = AnimationInfo();
        EXPECT_STREQ(info.abbr.c_str(), "");
        char test[4];
        strcpy(test, "MET");
        info.setAbbr(test);
        EXPECT_STREQ(info.abbr.c_str(), "MET");
        std::string test2 = "MPR";
        info.setAbbr(test2);
        EXPECT_STREQ(info.abbr.c_str(), "MPR");
    }

    TEST(AnimationInfo, SetDescription) {
        AnimationInfo info = AnimationInfo();
        EXPECT_STREQ(info.description.c_str(), "");
        char test[14];
        strcpy(test, "A description");
        info.setDescription(test);
        EXPECT_STREQ(info.description.c_str(), "A description");
        std::string test2 = "Another description";
        info.setDescription(test2);
        EXPECT_STREQ(info.description.c_str(), "Another description");
    }

    TEST(AnimationInfo, SetSignatureFile) {
        AnimationInfo info = AnimationInfo();
        EXPECT_STREQ(info.signatureFile.c_str(), "");
        char test[9];
        strcpy(test, "file.csv");
        info.setSignatureFile(test);
        EXPECT_STREQ(info.signatureFile.c_str(), "file.csv");
        std::string test2 = "file2.csv";
        info.setSignatureFile(test2);
        EXPECT_STREQ(info.signatureFile.c_str(), "file2.csv");
    }

    TEST(AnimationInfo, SetRepetitive) {
        AnimationInfo info = AnimationInfo();
        EXPECT_FALSE(info.repetitive);
        info.setRepetitive(true);
        EXPECT_TRUE(info.repetitive);
        info.setRepetitive(false);
        EXPECT_FALSE(info.repetitive);
    }

    TEST(AnimationInfo, SetMinimumColors) {
        AnimationInfo info = AnimationInfo();
        EXPECT_EQ(info.minimumColors, 0);
        info.setMinimumColors(4);
        EXPECT_EQ(info.minimumColors, 4);
    }

    TEST(AnimationInfo, SetUnlimitedColors) {
        AnimationInfo info = AnimationInfo();
        EXPECT_FALSE(info.unlimitedColors);
        info.setUnlimitedColors(true);
        EXPECT_TRUE(info.unlimitedColors);
        info.setUnlimitedColors(false);
        EXPECT_FALSE(info.unlimitedColors);
    }

    TEST(AnimationInfo, SetCenter) {
        AnimationInfo info = AnimationInfo();
        EXPECT_EQ(info.center, NOTUSED);
        info.setCenter(USED);
        EXPECT_EQ(info.center, USED);
        info.setCenter(NOTUSED);
        EXPECT_EQ(info.center, NOTUSED);
    }

    TEST(AnimationInfo, SetDelay) {
        AnimationInfo info = AnimationInfo();
        EXPECT_EQ(info.delay, NOTUSED);
        info.setDelay(USED);
        EXPECT_EQ(info.delay, USED);
        info.setDelay(NOTUSED);
        EXPECT_EQ(info.delay, NOTUSED);
    }

    TEST(AnimationInfo, SetDirection) {
        AnimationInfo info = AnimationInfo();
        EXPECT_EQ(info.direction, NOTUSED);
        info.setDirection(USED);
        EXPECT_EQ(info.direction, USED);
        info.setDirection(NOTUSED);
        EXPECT_EQ(info.direction, NOTUSED);
    }

    TEST(AnimationInfo, SetDistance) {
        AnimationInfo info = AnimationInfo();
        EXPECT_EQ(info.distance, NOTUSED);
        info.setDistance(USED);
        EXPECT_EQ(info.distance, USED);
        info.setDistance(NOTUSED);
        EXPECT_EQ(info.distance, NOTUSED);
    }

    TEST(AnimationInfo, SetSpacing) {
        AnimationInfo info = AnimationInfo();
        EXPECT_EQ(info.spacing, NOTUSED);
        info.setSpacing(USED);
        EXPECT_EQ(info.spacing, USED);
        info.setSpacing(NOTUSED);
        EXPECT_EQ(info.spacing, NOTUSED);
    }

    TEST(AnimationInfo, SetDelayDefault) {
        AnimationInfo info = AnimationInfo();
        EXPECT_EQ(info.delayDefault, 50);
        info.setDelayDefault(4);
        EXPECT_EQ(info.delayDefault, 4);
        info.setDelayDefault(8L);
        EXPECT_EQ(info.delayDefault, 8);
    }

    TEST(AnimationInfo, SetDistanceDefault) {
        AnimationInfo info = AnimationInfo();
        EXPECT_EQ(info.distanceDefault, -1);
        info.setDistanceDefault(4);
        EXPECT_EQ(info.distanceDefault, 4);
    }

    TEST(AnimationInfo, SetSpacingDefault) {
        AnimationInfo info = AnimationInfo();
        EXPECT_EQ(info.spacingDefault, 3);
        info.setSpacingDefault(4);
        EXPECT_EQ(info.spacingDefault, 4);
    }

    TEST(AnimationInfo, FromJSON) {
        std::string data_str = R"({"name":"Wipe","abbr":"WIP","description":"A description","signatureFile":"wipe.png","repetitive":false,"minimumColors":1,"unlimitedColors":false,"center":"NOTUSED","delay":"USED","direction":"USED","distance":"NOTUSED","spacing":"NOTUSED","delayDefault":10,"distanceDefault":3,"spacingDefault":15})";

        nlohmann::json data_json = nlohmann::json::parse(data_str);
        AnimationInfo info = AnimationInfo(data_json);

        EXPECT_STREQ(info.name.c_str(), "Wipe");
        EXPECT_STREQ(info.abbr.c_str(), "WIP");
        EXPECT_STREQ(info.description.c_str(), "A description");
        EXPECT_STREQ(info.signatureFile.c_str(), "wipe.png");
        EXPECT_FALSE(info.repetitive);
        EXPECT_EQ(info.minimumColors, 1);
        EXPECT_FALSE(info.unlimitedColors);
        EXPECT_EQ(info.center, NOTUSED);
        EXPECT_EQ(info.delay, USED);
        EXPECT_EQ(info.direction, USED);
        EXPECT_EQ(info.distance, NOTUSED);
        EXPECT_EQ(info.spacing, NOTUSED);
        EXPECT_EQ(info.delayDefault, 10);
        EXPECT_EQ(info.distanceDefault, 3);
        EXPECT_EQ(info.spacingDefault, 15);
    }

    TEST(AnimationInfo, FromBadJSON) {
        std::string data_str = "{}";

        nlohmann::json data_json = nlohmann::json::parse(data_str);
        AnimationInfo info = AnimationInfo(data_json);

        EXPECT_STREQ(info.name.c_str(), "");
        EXPECT_STREQ(info.abbr.c_str(), "");
        EXPECT_STREQ(info.description.c_str(), "");
        EXPECT_STREQ(info.signatureFile.c_str(), "");
        EXPECT_FALSE(info.repetitive);
        EXPECT_EQ(info.minimumColors, 0);
        EXPECT_FALSE(info.unlimitedColors);
        EXPECT_EQ(info.center, NOTUSED);
        EXPECT_EQ(info.delay, NOTUSED);
        EXPECT_EQ(info.direction, NOTUSED);
        EXPECT_EQ(info.distance, NOTUSED);
        EXPECT_EQ(info.spacing, NOTUSED);
        EXPECT_EQ(info.delayDefault, 50);
        EXPECT_EQ(info.distanceDefault, -1);
        EXPECT_EQ(info.spacingDefault, 3);
    }
}

#endif //ANIMATEDLEDSTRIP_ANIMATIONINFOTEST_H
