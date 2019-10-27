#ifndef SERVICEBATTERY_H
#define SERVICEBATTERY_H
#include <QObject>
#include <battery.h>
#include <windows.h>
#include <QDebug>
#include <QThread>

class ServiceBattery : public QObject {
    Q_OBJECT
public:
    explicit ServiceBattery() {}
    ~ServiceBattery() {}

public slots:
    void controlBattery();
    void updateBatteryStatus();

    Battery getBatteryStatus();
    void setRunning(bool);

signals:
    void changedBatteryInformation();
    void updateBatteryStatusIsStopped();

private:
    Battery battery;

    bool m_running = false;
};

#endif // SERVICEBATTERY_H
