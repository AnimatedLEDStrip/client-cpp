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


#ifndef ANIMATEDLEDSTRIP_SECTIONTEST_HPP
#define ANIMATEDLEDSTRIP_SECTIONTEST_HPP

#include "Section.hpp"
#include "nlohmann/json.hpp"
#include "gtest/gtest.h"


namespace {

    TEST(Section, DefaultConstructor) {
        const Section sect = Section();

        EXPECT_STREQ(sect.name.c_str(), "");
        EXPECT_EQ(sect.startPixel, -1);
        EXPECT_EQ(sect.endPixel, -1);
        EXPECT_EQ(sect.physicalStart, -1);
        EXPECT_EQ(sect.numLEDs, 0);
    }

    TEST(Section, SetName) {
        Section sect = Section();
        EXPECT_STREQ(sect.name.c_str(), "");
        char test[5];
        strcpy(test, "Sect");
        sect.setName(test);
        EXPECT_STREQ(sect.name.c_str(), "Sect");
        std::string test2 = "TestSect";
        sect.setName(test2);
        EXPECT_STREQ(sect.name.c_str(), "TestSect");
    }

    TEST(Section, SetStartPixel) {
        Section sect = Section();
        EXPECT_EQ(sect.startPixel, -1);
        sect.setStartPixel(5);
        EXPECT_EQ(sect.startPixel, 5);
    }

    TEST(Section, SetEndPixel) {
        Section sect = Section();
        EXPECT_EQ(sect.endPixel, -1);
        sect.setEndPixel(5);
        EXPECT_EQ(sect.endPixel, 5);
    }

    TEST(Section, SetPhysicalStart) {
        Section sect = Section();
        EXPECT_EQ(sect.physicalStart, -1);
        sect.setPhysicalStart(5);
        EXPECT_EQ(sect.physicalStart, 5);
    }

    TEST(Section, SetNumLEDs) {
        Section sect = Section();
        EXPECT_EQ(sect.numLEDs, 0);
        sect.setNumLEDs(5);
        EXPECT_EQ(sect.numLEDs, 5);
    }

    TEST(Section, JSON) {
        Section sect = Section();

        sect.setName("Section");
        sect.setStartPixel(15);
        sect.setEndPixel(30);

        char * data_str = new char[1000];
        sect.json(&data_str);
        EXPECT_STREQ(data_str, "SECT:{\"name\":\"Section\",\"startPixel\":15,\"endPixel\":30}");
        delete[] data_str;
    }

    TEST(Section, FromJSON) {
        std::string data_str = R"({"name":"NewSection","startPixel":20,"endPixel":55,"physicalStart":40,"numLEDs":36})";

        nlohmann::json data_json = nlohmann::json::parse(data_str);
        Section sect = Section(data_json);

        EXPECT_STREQ(sect.name.c_str(), "NewSection");
        EXPECT_EQ(sect.startPixel, 20);
        EXPECT_EQ(sect.endPixel, 55);
        EXPECT_EQ(sect.physicalStart, 40);
        EXPECT_EQ(sect.numLEDs, 36);
    }

    TEST(Section, FromBadJSON) {
        std::string data_str = "{}";

        nlohmann::json data_json = nlohmann::json::parse(data_str);
        Section sect = Section(data_json);

        EXPECT_STREQ(sect.name.c_str(), "");
        EXPECT_EQ(sect.startPixel, -1);
        EXPECT_EQ(sect.endPixel, -1);
        EXPECT_EQ(sect.physicalStart, -1);
        EXPECT_EQ(sect.numLEDs, 0);
    }

}

#endif //ANIMATEDLEDSTRIP_SECTIONTEST_HPP
