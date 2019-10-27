#include "servicebattery.h"

void ServiceBattery::controlBattery() {
    SYSTEM_POWER_STATUS status;
    GetSystemPowerStatus(&status);

    battery.setPercentage((unsigned int)status.BatteryLifePercent);
    battery.setIsOnline((bool)status.ACLineStatus);
    battery.setIsSaverOn((bool)status.Reserved1);
}

void ServiceBattery::updateBatteryStatus() {
    while(m_running) {
        QThread::msleep(50);

        controlBattery();

        if(m_running) {
            emit changedBatteryInformation();
        }
    }

    emit updateBatteryStatusIsStopped();
}

Battery ServiceBattery::getBatteryStatus() {
    return battery;
}

void ServiceBattery::setRunning(bool running) {
    this->m_running = running;
}
