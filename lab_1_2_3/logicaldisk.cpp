#include "logicaldisk.h"

LogicalDisk::LogicalDisk(QString diskName, unsigned int freeBytes, unsigned int busyBytes, unsigned int totalBytes) {
    this->diskName = diskName;
    this->freeMemory = freeBytes;
    this->totalMemory = totalBytes;
    this->busyMemory = busyBytes;
}

unsigned int LogicalDisk::getFreeMemory() {
    return freeMemory;
}

unsigned int LogicalDisk::getBusyMemory() {
    return busyMemory;
}

unsigned int LogicalDisk::getTotalMemory() {
    return totalMemory;
}

QString LogicalDisk::getDiskName() {
    return diskName;
}
