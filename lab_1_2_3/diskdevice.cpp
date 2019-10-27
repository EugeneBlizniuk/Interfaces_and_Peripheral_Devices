#include "diskdevice.h"

QString DiskDevice::getModel() {
    return model;
}

QString DiskDevice::getVendor() {
    return vendor;
}

QString DiskDevice::getSerialNumber() {
    return serialNumber;
}

QString DiskDevice::getFirmware() {
    return firmware;
}

QStringList DiskDevice::getMemoryInformation() {
    return memoryInformation;
}

QString DiskDevice::getInterfaceType() {
    return interfaceType;
}

QStringList DiskDevice::getSupportedModes() {
    return supportedModes;
}

void DiskDevice::setModel(QString value) {
    this->model = value;
}

void DiskDevice::setVendor(QString value) {
    this->vendor = value;
}

void DiskDevice::setSerialNumber(QString value) {
    this->serialNumber = value;
}

void DiskDevice::setFirmware(QString value) {
    this->firmware = value;
}

void DiskDevice::setMemoryInformation(QStringList value) {
    this->memoryInformation = value;
}

void DiskDevice::setInterfaceType(QString value) {
    this->interfaceType = value;
}

void DiskDevice::setSupportedModes(QStringList value) {
    this->supportedModes = value;
}
