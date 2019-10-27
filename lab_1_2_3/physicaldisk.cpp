#include "physicaldisk.h"

PhysicalDisk::PhysicalDisk(QString model, QString vendor, QString serialNumber,
                            QString firmware, QString memoryAmount, QString interfaceType,
                            QStringList supportedModes) {
    this->model = model;
    this->vendor = vendor;
    this->serialNumber = serialNumber;
    this->firmware = firmware;
    this->memoryInformation = memoryAmount;
    this->interfaceType = interfaceType;
    this->supportedModes = supportedModes;
}

void PhysicalDisk::setVendor(QString vendor) {
    this->vendor = vendor;
}

void PhysicalDisk::setModel(QString model) {
    this->model = model;
}

void PhysicalDisk::setSerialNumber(QString serialNumber) {
    this->serialNumber = serialNumber;
}

void PhysicalDisk::setFirmware(QString firmware) {
    this->firmware = firmware;
}

void PhysicalDisk::setMemoryInformation(QString memoryInformation) {
    this->memoryInformation = memoryInformation;
}

void PhysicalDisk::setInterfaceType(QString interfaceType) {
    this->interfaceType = interfaceType;
}

void PhysicalDisk::setSupportedModes(QStringList modes) {
    this->supportedModes = modes;
}


QString PhysicalDisk::getVendor() {
    return vendor;
}

QString PhysicalDisk::getModel() {
    return model;
}

QString PhysicalDisk::getSerialNumber() {
    return serialNumber;
}

QString PhysicalDisk::getFirmware() {
    return firmware;
}

QString PhysicalDisk::getMemoryInformation() {
    return memoryInformation;
}

QString PhysicalDisk::getInterfaceType() {
    return interfaceType;
}

QStringList PhysicalDisk::getSupportedModes() {
    return supportedModes;
}
