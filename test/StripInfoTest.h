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

#ifndef ANIMATEDLEDSTRIP_STRIPINFOTEST_H
#define ANIMATEDLEDSTRIP_STRIPINFOTEST_H

#include "StripInfo.h"
#include "gtest/gtest.h"

namespace {

    TEST(StripInfo, Constructor) {
        StripInfo s = StripInfo();
        EXPECT_EQ(s.numLEDs, 0);
        EXPECT_EQ(s.pin, -1);
        EXPECT_FALSE(s.imageDebugging);
        EXPECT_STREQ(s.fileName.c_str(), "");
        EXPECT_EQ(s.rendersBeforeSave, -1);
        EXPECT_EQ(s.threadCount, 100);
    }

    TEST(StripInfo, SetNumLEDs) {
        StripInfo s = StripInfo();
        EXPECT_EQ(s.numLEDs, 0);
        s.setNumLEDs(5);
        EXPECT_EQ(s.numLEDs, 5);
    }

    TEST(StripInfo, SetPin) {
        StripInfo s = StripInfo();
        EXPECT_EQ(s.pin, -1);
        s.setPin(3);
        EXPECT_EQ(s.pin, 3);
    }

    TEST(StripInfo, SetImageDebugging) {
        StripInfo s = StripInfo();
        EXPECT_FALSE(s.imageDebugging);
        s.setImageDebugging(true);
        EXPECT_TRUE(s.imageDebugging);
    }

    TEST(StripInfo, SetFileName) {
        StripInfo s = StripInfo();
        EXPECT_STREQ(s.fileName.c_str(), "");
        char test[9];
        strcpy(test, "file.csv");
        s.setFileName(test);
        EXPECT_STREQ(s.fileName.c_str(), "file.csv");
        std::string test2 = "file2.csv";
        s.setFileName(test2);
        EXPECT_STREQ(s.fileName.c_str(), "file2.csv");
    }

    TEST(StripInfo, SetRendersBeforeSave) {
        StripInfo s = StripInfo();
        EXPECT_EQ(s.rendersBeforeSave, -1);
        s.setRendersBeforeSave(500);
        EXPECT_EQ(s.rendersBeforeSave, 500);
    }

    TEST(StripInfo, SetThreadCount) {
        StripInfo s = StripInfo();
        EXPECT_EQ(s.threadCount, 100);
        s.setThreadCount(200);
        EXPECT_EQ(s.threadCount, 200);
    }

    TEST(StripInfo, FromJSON) {
        std::string info_str = R"({"numLEDs":240,"pin":12,"imageDebugging":false,"fileName":"file.csv","rendersBeforeSave":1000,"threadCount":200})";

        nlohmann::json info_json = nlohmann::json::parse(info_str);
        StripInfo info = StripInfo(info_json);

        EXPECT_EQ(info.numLEDs, 240);
        EXPECT_EQ(info.pin, 12);
        EXPECT_FALSE(info.imageDebugging);
        EXPECT_STREQ(info.fileName.c_str(), "file.csv");
        EXPECT_EQ(info.rendersBeforeSave, 1000);
        EXPECT_EQ(info.threadCount, 200);
    }

    TEST(StripInfo, FromBadJSON) {
        std::string info_str = "{}";

        nlohmann::json info_json = nlohmann::json::parse(info_str);
        StripInfo info = StripInfo(info_json);

        EXPECT_EQ(info.numLEDs, 0);
        EXPECT_EQ(info.pin, -1);
        EXPECT_FALSE(info.imageDebugging);
        EXPECT_STREQ(info.fileName.c_str(), "");
        EXPECT_EQ(info.rendersBeforeSave, -1);
        EXPECT_EQ(info.threadCount, 100);
    }

}

#endif //ANIMATEDLEDSTRIP_STRIPINFOTEST_H
