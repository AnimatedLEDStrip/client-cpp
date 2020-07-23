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

#include "Animation.h"

const char *animation_string(Animation a) {
    switch (a) {
        case COLOR:
            return "COLOR";
        case CUSTOMANIMATION:
            return "CUSTOMANIMATION";
        case CUSTOMREPETITIVEANIMATION:
            return "CUSTOMREPETITIVEANIMATION";
        case ALTERNATE:
            return "ALTERNATE";
        case BOUNCE:
            return "BOUNCE";
        case BOUNCETOCOLOR:
            return "BOUNCETOCOLOR";
        case CATTOY:
            return "CATTOY";
        case METEOR:
            return "METEOR";
        case MULTIPIXELRUN:
            return "MULTIPIXELRUN";
        case MULTIPIXELRUNTOCOLOR:
            return "MULTIPIXELRUNTOCOLOR";
        case RIPPLE:
            return "RIPPLE";
        case PIXELMARATHON:
            return "PIXELMARATHON";
        case PIXELRUN:
            return "PIXELRUN";
        case SMOOTHCHASE:
            return "SMOOTHCHASE";
        case SMOOTHFADE:
            return "SMOOTHFADE";
        case SPARKLE:
            return "SPARKLE";
        case SPARKLEFADE:
            return "SPARKLEFADE";
        case SPARKLETOCOLOR:
            return "SPARKLETOCOLOR";
        case SPLAT:
            return "SPLAT";
        case STACK:
            return "STACK";
        case STACKOVERFLOW:
            return "STACKOVERFLOW";
        case WIPE:
            return "WIPE";
        case ENDANIMATION:
            return "ENDANIMATION";
    }
}

Animation animation_from_string(const char *anim) {
    if (std::strcmp(anim, "COLOR") == 0)
        return COLOR;
    else if (std::strcmp(anim, "CUSTOMANIMATION") == 0)
        return CUSTOMANIMATION;
    else if (std::strcmp(anim, "CUSTOMREPETITIVEANIMATION") == 0)
        return CUSTOMREPETITIVEANIMATION;
    else if (std::strcmp(anim, "ALTERNATE") == 0)
        return ALTERNATE;
    else if (std::strcmp(anim, "BOUNCE") == 0)
        return BOUNCE;
    else if (std::strcmp(anim, "BOUNCETOCOLOR") == 0)
        return BOUNCETOCOLOR;
    else if (std::strcmp(anim, "CATTOY") == 0)
        return CATTOY;
    else if (std::strcmp(anim, "METEOR") == 0)
        return METEOR;
    else if (std::strcmp(anim, "MULTIPIXELRUN") == 0)
        return MULTIPIXELRUN;
    else if (std::strcmp(anim, "MULTIPIXELRUNTOCOLOR") == 0)
        return MULTIPIXELRUNTOCOLOR;
    else if (std::strcmp(anim, "RIPPLE") == 0)
        return RIPPLE;
    else if (std::strcmp(anim, "PIXELMARATHON") == 0)
        return PIXELMARATHON;
    else if (std::strcmp(anim, "PIXELRUN") == 0)
        return PIXELRUN;
    else if (std::strcmp(anim, "SMOOTHCHASE") == 0)
        return SMOOTHCHASE;
    else if (std::strcmp(anim, "SMOOTHFADE") == 0)
        return SMOOTHFADE;
    else if (std::strcmp(anim, "SPARKLE") == 0)
        return SPARKLE;
    else if (std::strcmp(anim, "SPARKLEFADE") == 0)
        return SPARKLEFADE;
    else if (std::strcmp(anim, "SPARKLETOCOLOR") == 0)
        return SPARKLETOCOLOR;
    else if (std::strcmp(anim, "SPLAT") == 0)
        return SPLAT;
    else if (std::strcmp(anim, "STACK") == 0)
        return STACK;
    else if (std::strcmp(anim, "STACKOVERFLOW") == 0)
        return STACKOVERFLOW;
    else if (std::strcmp(anim, "WIPE") == 0)
        return WIPE;
    else if (std::strcmp(anim, "ENDANIMATION") == 0)
        return ENDANIMATION;
    else return COLOR;
}