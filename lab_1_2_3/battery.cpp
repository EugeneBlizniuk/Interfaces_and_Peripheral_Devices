#include "battery.h"

void Battery::setPercentage(unsigned int percentage) {
    this->percentage = percentage;
}

void Battery::setIsOnline(bool isOnline) {
    this->isOnline = isOnline;
}

void Battery::setIsSaverOn(bool isSaverOn) {
    this->isSaverOn = isSaverOn;
}

unsigned int Battery::getPercentage() {
    return percentage;
}


bool Battery::getIsOnline() {
    return isOnline;
}


bool Battery::getIsSaverOn() {
    return isSaverOn;
}
