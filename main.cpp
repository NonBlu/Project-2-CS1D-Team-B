#include "mainwindow.h"
#include "stadiummanager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    StadiumManager sm;

    sm.printEntrys();
    sm.printSouvenirs();
    sm.printGraph();


    return a.exec();
}
