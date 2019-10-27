#ifndef PCIEDEVICE_H
#define PCIEDEVICE_H
#include <QString>

class PCIeDevice {
public:
    explicit PCIeDevice() {}
    ~PCIeDevice() {}

    QString getDeviceName();
    QString getDeviceID();
    QString getDeviceVendorID();

    void setDeviceName(const QString deviceName);
    void setDeviceID(const QString deviceID);
    void setDeviceVendorID(const QString deviceVendorID);

private:
    QString deviceName;
    QString deviceID;
    QString deviceVendorID;
};

#endif // PCIEDEVICE_H
