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

#ifndef ANIMATEDLEDSTRIPCLIENT_ANIMATIONTEST_H
#define ANIMATEDLEDSTRIPCLIENT_ANIMATIONTEST_H

#include "Animation.h"
#include "gtest/gtest.h"

namespace {

    TEST(Animation, AnimationString) {
        Animation a = COLOR;
        EXPECT_STREQ(animation_string(a), "COLOR");

        a = CUSTOMANIMATION;
        EXPECT_STREQ(animation_string(a), "CUSTOMANIMATION");

        a = CUSTOMREPETITIVEANIMATION;
        EXPECT_STREQ(animation_string(a), "CUSTOMREPETITIVEANIMATION");

        a = ALTERNATE;
        EXPECT_STREQ(animation_string(a), "ALTERNATE");

        a = BOUNCE;
        EXPECT_STREQ(animation_string(a), "BOUNCE");

        a = BOUNCETOCOLOR;
        EXPECT_STREQ(animation_string(a), "BOUNCETOCOLOR");

        a = CATTOY;
        EXPECT_STREQ(animation_string(a), "CATTOY");

        a = METEOR;
        EXPECT_STREQ(animation_string(a), "METEOR");

        a = MULTIPIXELRUN;
        EXPECT_STREQ(animation_string(a), "MULTIPIXELRUN");

        a = MULTIPIXELRUNTOCOLOR;
        EXPECT_STREQ(animation_string(a), "MULTIPIXELRUNTOCOLOR");

        a = RIPPLE;
        EXPECT_STREQ(animation_string(a), "RIPPLE");

        a = PIXELMARATHON;
        EXPECT_STREQ(animation_string(a), "PIXELMARATHON");

        a = PIXELRUN;
        EXPECT_STREQ(animation_string(a), "PIXELRUN");

        a = SMOOTHCHASE;
        EXPECT_STREQ(animation_string(a), "SMOOTHCHASE");

        a = SMOOTHFADE;
        EXPECT_STREQ(animation_string(a), "SMOOTHFADE");

        a = SPARKLE;
        EXPECT_STREQ(animation_string(a), "SPARKLE");

        a = SPARKLEFADE;
        EXPECT_STREQ(animation_string(a), "SPARKLEFADE");

        a = SPARKLETOCOLOR;
        EXPECT_STREQ(animation_string(a), "SPARKLETOCOLOR");

        a = SPLAT;
        EXPECT_STREQ(animation_string(a), "SPLAT");

        a = STACK;
        EXPECT_STREQ(animation_string(a), "STACK");

        a = STACKOVERFLOW;
        EXPECT_STREQ(animation_string(a), "STACKOVERFLOW");

        a = WIPE;
        EXPECT_STREQ(animation_string(a), "WIPE");

        a = ENDANIMATION;
        EXPECT_STREQ(animation_string(a), "ENDANIMATION");
    }

    TEST(Animation, AnimationFromString) {
        std::string anim_color = "COLOR";
        std::string anim_custom = "CUSTOMANIMATION";
        std::string anim_custom_r = "CUSTOMREPETITIVEANIMATION";
        std::string anim_alt = "ALTERNATE";
        std::string anim_bounce = "BOUNCE";
        std::string anim_bounce_tc = "BOUNCETOCOLOR";
        std::string anim_cat = "CATTOY";
        std::string anim_meteor = "METEOR";
        std::string anim_mpr = "MULTIPIXELRUN";
        std::string anim_mpr_tc = "MULTIPIXELRUNTOCOLOR";
        std::string anim_ripple = "RIPPLE";
        std::string anim_pixel_mar = "PIXELMARATHON";
        std::string anim_pixel_run = "PIXELRUN";
        std::string anim_smooth_c = "SMOOTHCHASE";
        std::string anim_smooth_f = "SMOOTHFADE";
        std::string anim_sparkle = "SPARKLE";
        std::string anim_sparkle_f = "SPARKLEFADE";
        std::string anim_sparkle_tc = "SPARKLETOCOLOR";
        std::string anim_splat = "SPLAT";
        std::string anim_stack = "STACK";
        std::string anim_stack_of = "STACKOVERFLOW";
        std::string anim_wipe = "WIPE";
        std::string anim_end = "ENDANIMATION";
        std::string anim_non_anim = "TEST";

        EXPECT_EQ(animation_from_string(anim_color.c_str()), COLOR);
        EXPECT_EQ(animation_from_string(anim_custom.c_str()), CUSTOMANIMATION);
        EXPECT_EQ(animation_from_string(anim_custom_r.c_str()), CUSTOMREPETITIVEANIMATION);
        EXPECT_EQ(animation_from_string(anim_alt.c_str()), ALTERNATE);
        EXPECT_EQ(animation_from_string(anim_bounce.c_str()), BOUNCE);
        EXPECT_EQ(animation_from_string(anim_bounce_tc.c_str()), BOUNCETOCOLOR);
        EXPECT_EQ(animation_from_string(anim_cat.c_str()), CATTOY);
        EXPECT_EQ(animation_from_string(anim_meteor.c_str()), METEOR);
        EXPECT_EQ(animation_from_string(anim_mpr.c_str()), MULTIPIXELRUN);
        EXPECT_EQ(animation_from_string(anim_mpr_tc.c_str()), MULTIPIXELRUNTOCOLOR);
        EXPECT_EQ(animation_from_string(anim_ripple.c_str()), RIPPLE);
        EXPECT_EQ(animation_from_string(anim_pixel_mar.c_str()), PIXELMARATHON);
        EXPECT_EQ(animation_from_string(anim_pixel_run.c_str()), PIXELRUN);
        EXPECT_EQ(animation_from_string(anim_smooth_c.c_str()), SMOOTHCHASE);
        EXPECT_EQ(animation_from_string(anim_smooth_f.c_str()), SMOOTHFADE);
        EXPECT_EQ(animation_from_string(anim_sparkle.c_str()), SPARKLE);
        EXPECT_EQ(animation_from_string(anim_sparkle_f.c_str()), SPARKLEFADE);
        EXPECT_EQ(animation_from_string(anim_sparkle_tc.c_str()), SPARKLETOCOLOR);
        EXPECT_EQ(animation_from_string(anim_splat.c_str()), SPLAT);
        EXPECT_EQ(animation_from_string(anim_stack.c_str()), STACK);
        EXPECT_EQ(animation_from_string(anim_stack_of.c_str()), STACKOVERFLOW);
        EXPECT_EQ(animation_from_string(anim_wipe.c_str()), WIPE);
        EXPECT_EQ(animation_from_string(anim_end.c_str()), ENDANIMATION);
        EXPECT_EQ(animation_from_string(anim_non_anim.c_str()), COLOR);
    }

}

#endif //ANIMATEDLEDSTRIPCLIENT_ANIMATIONTEST_H
