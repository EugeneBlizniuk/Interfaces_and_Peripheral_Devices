#ifndef SERVICEPCIE_H
#define SERVICEPCIE_H
#include "pciedevice.h"
#include <QObject>
#include <QSettings>

class ServicePCIe : public QObject {
    Q_OBJECT
public:
    explicit ServicePCIe() {}
    ~ServicePCIe() {}

public slots:
    void setDevices(const QList<PCIeDevice>& device);
    QList<PCIeDevice> getDevices();

    void read();

signals:
    void finished();

private:
    QList<PCIeDevice> devices;
};

#endif // SERVICEPCIE_H
