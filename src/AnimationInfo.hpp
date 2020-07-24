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

#ifndef ANIMATEDLEDSTRIP_ANIMATIONINFO_HPP
#define ANIMATEDLEDSTRIP_ANIMATIONINFO_HPP

#include <iostream>

enum ParamUsage {
    USED,
    NOTUSED
};

class AnimationInfo {
public:
    std::string name = "";
    std::string abbr = "";
    std::string description = "";
    std::string signatureFile = "";
    bool repetitive = false;
    int minimumColors = 0;
    bool unlimitedColors = false;
    ParamUsage center = NOTUSED;
    ParamUsage delay = NOTUSED;
    ParamUsage direction = NOTUSED;
    ParamUsage distance = NOTUSED;
    ParamUsage spacing = NOTUSED;
    long delayDefault = 50;
    int distanceDefault = -1;
    int spacingDefault = 3;

    // setters

    AnimationInfo & setName(const std::string & n) {
        name.assign(n);
        return *this;
    }

    AnimationInfo & setName(const char * n) {
        name.assign(n);
        return *this;
    }

    AnimationInfo & setAbbr(const std::string & a) {
        abbr.assign(a);
        return *this;
    }

    AnimationInfo & setAbbr(const char * a) {
        abbr.assign(a);
        return *this;
    }

    AnimationInfo & setDescription(const std::string & d) {
        description.assign(d);
        return *this;
    }

    AnimationInfo & setDescription(const char * d) {
        description.assign(d);
        return *this;
    }

    AnimationInfo & setSignatureFile(const std::string & s) {
        signatureFile.assign(s);
        return *this;
    }

    AnimationInfo & setSignatureFile(const char * s) {
        signatureFile.assign(s);
        return *this;
    }

    AnimationInfo & setRepetitive(bool r) {
        repetitive = r;
        return *this;
    }

    AnimationInfo & setMinimumColors(int m) {
        minimumColors = m;
        return *this;
    }

    AnimationInfo & setUnlimitedColors(bool u) {
        unlimitedColors = u;
        return *this;
    }

    AnimationInfo & setCenter(enum ParamUsage c) {
        center = c;
        return *this;
    }

    AnimationInfo & setDelay(enum ParamUsage d) {
        delay = d;
        return *this;
    }

    AnimationInfo & setDirection(enum ParamUsage d) {
        direction = d;
        return *this;
    }

    AnimationInfo & setDistance(enum ParamUsage d) {
        distance = d;
        return *this;
    }

    AnimationInfo & setSpacing(enum ParamUsage s) {
        spacing = s;
        return *this;
    }

    AnimationInfo & setDelayDefault(long d) {
        delayDefault = d;
        return *this;
    }

    AnimationInfo & setDelayDefault(int d) {
        delayDefault = (long) d;
        return *this;
    }

    AnimationInfo & setDistanceDefault(int d) {
        distanceDefault = d;
        return *this;
    }

    AnimationInfo & setSpacingDefault(int s) {
        spacingDefault = s;
        return *this;
    }

    static ParamUsage paramUsageString(const std::string & p) {
        if (std::strcmp(p.c_str(), "USED") == 0) return USED;
        else if (std::strcmp(p.c_str(), "NOTUSED") == 0) return NOTUSED;
        else return NOTUSED;
    }


    AnimationInfo() = default;

    explicit AnimationInfo(nlohmann::json data) {
        if (data["name"].is_string())
            setName(data["name"].get<std::string>());
        else if (!data["name"].is_null())
            std::cerr << "Bad type for name" << data["name"].type_name() << std::endl;

        if (data["abbr"].is_string())
            setAbbr(data["abbr"].get<std::string>());
        else if (!data["abbr"].is_null())
            std::cerr << "Bad type for abbr" << data["abbr"].type_name() << std::endl;

        if (data["description"].is_string())
            setDescription(data["description"].get<std::string>());
        else if (!data["description"].is_null())
            std::cerr << "Bad type for description" << data["description"].type_name() << std::endl;

        if (data["signatureFile"].is_string())
            setSignatureFile(data["signature_file"].get<std::string>());
        else if (!data["signatureFile"].is_null())
            std::cerr << "Bad type for signatureFile" << data["signatureFile"].type_name() << std::endl;

        if (data["repetitive"].is_boolean())
            setRepetitive(data["repetitive"].get<bool>());
        else if (!data["repetitive"].is_null())
            std::cerr << "Bad type for repetitive" << data["repetitive"].type_name() << std::endl;

        if (data["minimumColors"].is_number_integer())
            setMinimumColors(data["minimumColors"].get<int>());
        else if (!data["minimumColors"].is_null())
            std::cerr << "Bad type for minimumColors" << data["minimumColors"].type_name() << std::endl;

        if (data["unlimitedColors"].is_boolean())
            setUnlimitedColors(data["unlimitedColors"].get<bool>());
        else if (!data["unlimitedColors"].is_null())
            std::cerr << "Bad type for unlimitedColors" << data["unlimitedColors"].type_name() << std::endl;

        if (data["center"].is_string())
            setCenter(paramUsageString(data["center"].get<std::string>()));
        else if (!data["center"].is_null())
            std::cerr << "Bad type for center" << data["center"].type_name() << std::endl;

        if (data["delay"].is_string())
            setDelay(paramUsageString(data["delay"].get<std::string>()));
        else if (!data["delay"].is_null())
            std::cerr << "Bad type for delay" << data["delay"].type_name() << std::endl;

        if (data["direction"].is_string())
            setDirection(paramUsageString(data["direction"].get<std::string>()));
        else if (!data["direction"].is_null())
            std::cerr << "Bad type for direction" << data["direction"].type_name() << std::endl;

        if (data["distance"].is_string())
            setDistance(paramUsageString(data["distance"].get<std::string>()));
        else if (!data["distance"].is_null())
            std::cerr << "Bad type for distance" << data["distance"].type_name() << std::endl;

        if (data["spacing"].is_string())
            setSpacing(paramUsageString(data["spacing"].get<std::string>()));
        else if (!data["spacing"].is_null())
            std::cerr << "Bad type for spacing" << data["spacing"].type_name() << std::endl;

        if (data["delayDefault"].is_number_integer())
            setDelayDefault(data["delayDefault"].get<int>());
        else if (!data["delayDefault"].is_null())
            std::cerr << "Bad type for delayDefault" << data["delayDefault"].type_name() << std::endl;

        if (data["distanceDefault"].is_number_integer())
            setDistanceDefault(data["distanceDefault"].get<int>());
        else if (!data["distanceDefault"].is_null())
            std::cerr << "Bad type for distanceDefault" << data["distanceDefault"].type_name() << std::endl;

        if (data["spacingDefault"].is_number_integer())
            setSpacingDefault(data["spacingDefault"].get<int>());
        else if (!data["spacingDefault"].is_null())
            std::cerr << "Bad type for spacingDefault" << data["spacingDefault"].type_name() << std::endl;
    }


};

#endif //ANIMATEDLEDSTRIP_ANIMATIONINFO_HPP
