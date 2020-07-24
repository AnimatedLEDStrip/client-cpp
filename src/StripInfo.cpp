#include "StripInfo.h"

StripInfo & StripInfo::setNumLEDs(int n) {
    numLEDs = n;
    return *this;
}

StripInfo & StripInfo::setPin(int p) {
    pin = p;
    return *this;
}

StripInfo & StripInfo::setImageDebugging(bool i) {
    imageDebugging = i;
    return *this;
}

StripInfo & StripInfo::setFileName(std::string f) {
    fileName.assign(f);
    return *this;
}

StripInfo & StripInfo::setFileName(const char * f) {
    fileName.assign(f);
    return *this;
}

StripInfo & StripInfo::setRendersBeforeSave(int r) {
    rendersBeforeSave = r;
    return *this;
}

StripInfo & StripInfo::setThreadCount(int t) {
    threadCount = t;
    return *this;
}
