#include "mainwindow.h"
#include "stadiummanager.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    StadiumManager sm;

    Trip trip = sm.shortestPath("Marlins Park", "Kauffman Stadium");
//    Trip trip = sm.DFS("Marlins Park");
//    Trip trip = sm.BFS("Marlins Park");

    for (auto& stadium : trip.path)
    {
        qDebug() << stadium->getStadiumName() << "   "
                 << stadium->getLocation();

        for (auto& souvenir : stadium->getSouvenirs())
        {
            qDebug() << souvenir.name << souvenir.price;
        }

        qDebug () << "\n";
    }

    qDebug() << "Distance Traveled: " << trip.distanceTraveled;


    w.show();
    return a.exec();
}
