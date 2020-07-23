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

#ifndef ANIMATEDLEDSTRIPCLIENT_COLORCONTAINERTEST_H
#define ANIMATEDLEDSTRIPCLIENT_COLORCONTAINERTEST_H

#include "ColorContainer.h"
#include "gtest/gtest.h"

namespace {

    TEST(ColorContainer, DefaultConstructor) {
        const ColorContainer cc = ColorContainer();

        EXPECT_TRUE(cc.colors.empty());
    }

    TEST(ColorContainer, AddColor) {
        ColorContainer cc = ColorContainer();

        cc.addColor(0xFF);

        EXPECT_FALSE(cc.colors.empty());
        EXPECT_TRUE(cc.colors.size() == 1);
        EXPECT_EQ(cc.colors[0], 0xFF);

        cc.addColor(0xFF00);

        EXPECT_FALSE(cc.colors.empty());
        EXPECT_TRUE(cc.colors.size() == 2);
        EXPECT_EQ(cc.colors[0], 0xFF);
        EXPECT_EQ(cc.colors[1], 0xFF00);
    }
}

#endif //ANIMATEDLEDSTRIPCLIENT_COLORCONTAINERTEST_H
