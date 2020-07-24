//
// Created by mnmax on 7/23/2020.
//

#ifndef ANIMATEDLEDSTRIP_ENDANIMATIONTEST_H
#define ANIMATEDLEDSTRIP_ENDANIMATIONTEST_H

#include "EndAnimation.h"
#include "gtest/gtest.h"

namespace {
    TEST(EndAnimation, Constructor) {
        EndAnimation e = EndAnimation();
        EXPECT_STREQ(e.id.c_str(), "");
    }

    TEST(EndAnimation, SetFileName) {
        EndAnimation e = EndAnimation();
        EXPECT_STREQ(e.id.c_str(), "");
        char test[9];
        strcpy(test, "test");
        e.setId(test);
        EXPECT_STREQ(e.id.c_str(), "test");
        std::string test2 = "test2";
        e.setId(test2);
        EXPECT_STREQ(e.id.c_str(), "test2");
    }

    TEST(EndAnimation, FromJSON) {
        std::string data_str = R"({"id":"test_id"})";

        nlohmann::json data_json = nlohmann::json::parse(data_str);
        EndAnimation e = EndAnimation(data_json);

        EXPECT_STREQ(e.id.c_str(), "test_id");
    }

    TEST(EndAnimation, FromBadJSON) {
        std::string data_str = "{}";

        nlohmann::json data_json = nlohmann::json::parse(data_str);
        EndAnimation e = EndAnimation(data_json);

        EXPECT_STREQ(e.id.c_str(), "");
    }
}

#endif //ANIMATEDLEDSTRIP_ENDANIMATIONTEST_H
