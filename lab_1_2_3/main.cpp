#include "FrontWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FrontWindow w;
    w.show();

    return a.exec();
}
