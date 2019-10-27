#ifndef SERVICEDISKS_H
#define SERVICEDISKS_H

#include <QObject>
#include <QList>
#include <QDebug>
#include <QSettings>
#include <QThread>

#include <logicaldisk.h>
#include <physicaldisk.h>

#include <enumbustype.h>
#include <windows.h>

#define BUFFER_SIZE 1024
#define BITS_AMOUNT 26
#define BITS_MASK 0x00000001
#define DISK_IS_EXISTED 1

class ServiceDisks : public QObject
{
    Q_OBJECT
public:
    explicit ServiceDisks(QObject *parent = nullptr) {}
    ~ServiceDisks() {}

public slots:
    void mainWork();
    QList<LogicalDisk> getLogicalDisks();
    PhysicalDisk getPhysicalDisk();

    void updateDiskData();
    void setRunning(bool);

signals:
    void changedDiskData();
    void updateIsStoped();

private slots:
    void readLogicalDiskInfo();
    void readPhysicalDiskInfo();

    void setBusType(const int);
private:
    QList<LogicalDisk> logicalDisks;
    PhysicalDisk physicalDisk;

    bool m_running = false;
};

#endif // SERVICEDISKS_H
