#include "servicepcie.h"

void ServicePCIe::read() {
    QSettings path("HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Enum\\PCI", QSettings::NativeFormat);
    QStringList information = path.childGroups();

    int counter = 0;
    foreach(QString deviceID, information) {
        PCIeDevice newDevice;

        path.beginGroup(deviceID);
        QString property = path.childGroups()[0];
        QString name = path.value(property.append("/DeviceDesc")).toString();
        QStringList list = name.split(QRegExp("[%;,]+"));
        QStringList otherOptionsList = information.at(counter).split(QRegExp("[&]+"));

        path.endGroup();

        newDevice.setDeviceVendorID(otherOptionsList.at(0));
        newDevice.setDeviceID(otherOptionsList.at(1));
        newDevice.setDeviceName(list.at(2));

        this->devices.push_back(newDevice);
    }

    emit finished();
}

void ServicePCIe::setDevices(const QList<PCIeDevice>& devices) {
    this->devices = devices;
}

QList<PCIeDevice> ServicePCIe::getDevices() {
    return this->devices;
}
