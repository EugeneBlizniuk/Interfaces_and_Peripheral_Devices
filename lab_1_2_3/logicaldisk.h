#ifndef LOGICALDISK_H
#define LOGICALDISK_H
#include <QString>

class LogicalDisk
{
public:
    LogicalDisk() {}
    LogicalDisk(QString, unsigned int, unsigned int, unsigned int);
    ~LogicalDisk() {}

    QString getDiskName();
    unsigned int getFreeMemory();
    unsigned int getBusyMemory();
    unsigned int getTotalMemory();
private:
    QString diskName;
    unsigned int freeMemory;
    unsigned int busyMemory;
    unsigned int totalMemory;
};

#endif // LOGICALDISK_H
