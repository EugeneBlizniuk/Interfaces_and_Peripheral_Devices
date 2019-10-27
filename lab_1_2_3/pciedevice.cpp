#include "pciedevice.h"


QString PCIeDevice::getDeviceName() {
    return this->deviceName;
}

QString PCIeDevice::getDeviceID() {
    return this->deviceID;
}

QString PCIeDevice::getDeviceVendorID() {
    return this->deviceVendorID;
}

//setters

void PCIeDevice::setDeviceName(const QString deviceName) {
    this->deviceName = deviceName;
}

void PCIeDevice::setDeviceID(const QString deviceID) {
    this->deviceID = deviceID;
}

void PCIeDevice::setDeviceVendorID(const QString deviceVendorID) {
    this->deviceVendorID = deviceVendorID;
}
