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

#include "AnimationData.h"


AnimationData & AnimationData::setAnimation(std::string & a) {
    animation.assign(a);
    return *this;
}

AnimationData & AnimationData::setAnimation(const char * a) {
    animation.assign(a);
    return *this;
}

AnimationData & AnimationData::addColor(struct ColorContainer & c) {
    colors.push_back(c);
    return *this;
}

AnimationData & AnimationData::setCenter(int c) {
    center = c;
    return *this;
}

AnimationData & AnimationData::setContinuous(enum Continuous c) {
    continuous = c;
    return *this;
}

AnimationData & AnimationData::setDelay(long d) {
    delay = d;
    return *this;
}

AnimationData & AnimationData::setDelayMod(double d) {
    delay_mod = d;
    return *this;
}

AnimationData & AnimationData::setDirection(enum Direction d) {
    direction = d;
    return *this;
}

AnimationData & AnimationData::setDistance(int d) {
    distance = d;
    return *this;
}

AnimationData & AnimationData::setId(std::string & i) {
    id.assign(i);
    return *this;
}

AnimationData & AnimationData::setId(const char * i) {
    id.assign(i);
    return *this;
}

AnimationData & AnimationData::setSection(std::string & s) {
    section.assign(s);
    return *this;
}

AnimationData & AnimationData::setSection(const char * s) {
    section.assign(s);
    return *this;
}

AnimationData & AnimationData::setSpacing(int s) {
    spacing = s;
    return *this;
}
