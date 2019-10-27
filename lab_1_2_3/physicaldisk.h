#ifndef PHYSICALDISK_H
#define PHYSICALDISK_H
#include <QString>
#include <QStringList>

class PhysicalDisk
{
public:
    PhysicalDisk() {}
    PhysicalDisk(QString, QString, QString, QString, QString, QString, QStringList);
    ~PhysicalDisk() {}

    void setModel(QString);
    void setVendor(QString);
    void setSerialNumber(QString);
    void setFirmware(QString);
    void setMemoryInformation(QString);
    void setInterfaceType(QString);
    void setSupportedModes(QStringList);

    QString getModel();
    QString getVendor();
    QString getSerialNumber();
    QString getFirmware();
    QString getMemoryInformation();
    QString getInterfaceType();
    QStringList getSupportedModes();
private:
    QString model;
    QString vendor;
    QString serialNumber;
    QString firmware;
    QString memoryInformation;
    QString interfaceType;
    QStringList supportedModes;

};

#endif // PHYSICALDISK_H
