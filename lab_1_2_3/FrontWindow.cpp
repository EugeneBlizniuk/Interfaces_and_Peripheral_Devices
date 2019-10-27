#include "FrontWindow.h"
#include "ui_FrontWindow.h"

FrontWindow::FrontWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FrontWindow) {
    ui->setupUi(this);

    this->mainList = new QListView();

    //PCIe's thread
    connect(&readPCIeT, &QThread::started, &reader, &ServicePCIe::read);
    connect(&reader, &ServicePCIe::finished, &readPCIeT, &QThread::terminate);

    reader.moveToThread(&readPCIeT);

    //Disk's thread
    connect(&readDisksT, &QThread::started, &diskReader, &ServiceDisks::updateDiskData);
    connect(&diskReader, &ServiceDisks::updateIsStoped, &readDisksT, &QThread::terminate); //I'm not sure
    connect(&diskReader, SIGNAL(changedDiskData()), this, SLOT(rewriteDiskData()));

    diskReader.moveToThread(&readDisksT);

    //Battery's thread
    connect(&readBatteryT, &QThread::started, &batteryService, &ServiceBattery::updateBatteryStatus);
    connect(&batteryService, &ServiceBattery::updateBatteryStatusIsStopped, &readBatteryT, &QThread::terminate);
    connect(&batteryService, SIGNAL(changedBatteryInformation()), this, SLOT(rewriteBatteryStatus()));

    batteryService.moveToThread(&readBatteryT);
}

FrontWindow::~FrontWindow() {
    delete ui;
}

void FrontWindow::rewriteDiskData() {
    ui->listWidget->clear();
    loadDiskInformation();
}

void FrontWindow::rewriteBatteryStatus() {
    ui->listWidget->clear();
    loadBatteryInformation();
}

void FrontWindow::on_printInfoOfPCIe_clicked() {
    if(isRead) {
        return;
    }

    unsigned int deviceAmount = 0;

    readPCIeT.start();

    //reader.read();
    QThread::msleep(5); // I have to imagine out how to put the connection between this instance & the instance of ServicePCIe cause the line is useless

    foreach(PCIeDevice device, reader.getDevices()) {
        QString currentString = "*** Device: ";
        deviceAmount++;

        ui->listWidget->addItem(currentString + QString::number(deviceAmount));
        ui->listWidget->addItem("Device name: " + device.getDeviceName());
        ui->listWidget->addItem("Device ID: " + device.getDeviceID());
        ui->listWidget->addItem("Vendor ID: " + device.getDeviceVendorID());
        ui->listWidget->addItem("");
    }

    isRead = true;
}

void FrontWindow::on_clearInfo_clicked() {
    diskReader.setRunning(false);
    batteryService.setRunning(false);

    readDisksT.terminate();
    if(isRead) {
        ui->listWidget->clear();
        isRead = false;
    }
}

void FrontWindow::on_printDiskInfo_clicked() {
    if(isRead) {
        return;
    }

    diskReader.mainWork();
    loadDiskInformation();

    readDisksT.start();
    diskReader.setRunning(true);

    isRead = true;
}

void FrontWindow::loadDiskInformation() {
    PhysicalDisk physicalDisk = diskReader.getPhysicalDisk();
    QList<LogicalDisk> logicalDisks = diskReader.getLogicalDisks();

    ui->listWidget->addItem("Vendor: " + physicalDisk.getVendor());
    ui->listWidget->addItem("Model: " + physicalDisk.getModel());
    ui->listWidget->addItem("Serial Number: " + physicalDisk.getSerialNumber());
    ui->listWidget->addItem("Type of Interface: " + physicalDisk.getInterfaceType());
    ui->listWidget->addItem("Memory information: " + physicalDisk.getMemoryInformation());
    ui->listWidget->addItem("Firmware: " + physicalDisk.getFirmware());
    ui->listWidget->addItem("");

    foreach(LogicalDisk logicalDisk, logicalDisks) {
        ui->listWidget->addItem("Logical disk: " + logicalDisk.getDiskName());
        ui->listWidget->addItem("Memory:");
        ui->listWidget->addItem("Total: " + QString::number(logicalDisk.getTotalMemory()) + " MBytes");
        ui->listWidget->addItem("Busy: " + QString::number(logicalDisk.getBusyMemory()) + " MBytes");
        ui->listWidget->addItem("Free: " + QString::number(logicalDisk.getFreeMemory()) + " MBytes");
        ui->listWidget->addItem("");
    }
}

void FrontWindow::on_printBatteryInfo_clicked() {
    if(isRead) {
        return;
    }

    batteryService.controlBattery();
    loadBatteryInformation();

    readBatteryT.start();
    batteryService.setRunning(true);

    isRead = true;
}

void FrontWindow::loadBatteryInformation() {
    Battery batteryStatus = batteryService.getBatteryStatus();

    ui->listWidget->addItem("Percentage: " + QString::number(batteryStatus.getPercentage()));

    if(batteryStatus.getIsOnline() == 1) {
        ui->listWidget->addItem("Device is ONLINE");
    } else {
        ui->listWidget->addItem("Device is OFFLINE");
    }

    if(batteryStatus.getIsSaverOn() == 1) {
        ui->listWidget->addItem("Battery saver is ON");
    } else {
        ui->listWidget->addItem("Battery saver is OFF");
    }
}
