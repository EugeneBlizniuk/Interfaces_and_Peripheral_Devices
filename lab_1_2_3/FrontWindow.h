#ifndef FRONTWINDOW_H
#define FRONTWINDOW_H

#include <QMainWindow>
#include <QListView>
#include <QThread>
#include "servicepcie.h"
#include "servicedisks.h"
#include <servicebattery.h>
#include <QDebug>

namespace Ui {
class FrontWindow;
}

class FrontWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FrontWindow(QWidget *parent = nullptr);
    ~FrontWindow();

public slots:
    void rewriteDiskData();
    void rewriteBatteryStatus();

private slots:
    void on_printInfoOfPCIe_clicked();
    void on_clearInfo_clicked();

    void on_printDiskInfo_clicked();
    void loadDiskInformation();

    void on_printBatteryInfo_clicked();
    void loadBatteryInformation();

private:
    Ui::FrontWindow *ui;
    QListView *mainList;
    bool isRead = false;

    ServicePCIe reader;
    ServiceDisks diskReader;
    ServiceBattery batteryService;

    QThread readPCIeT;
    QThread readDisksT;
    QThread readBatteryT;
};

#endif // FRONTWINDOW_H
