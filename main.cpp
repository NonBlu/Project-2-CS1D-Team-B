#include "mainwindow.h"
#include "stadiummanager.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


    StadiumManager sm;
    Trip<MLB*>     trip;


//  ------- Test #1 - DFS ----------------------------

    trip = sm.DFS("Oracle Park");

//  -------- END: Test #1 ----------------------------



//  ------- Test #2 - BFS ----------------------------

//    trip = sm.BFS("Target Field");

//  -------- END: Test #2 ----------------------------



//  ------- Test #3 Shortest Path --------------------

//    trip = sm.shortestPath("Dodger Stadium", "Nationals Park");

//  -------- END: Test #3 ----------------------------



//  ------- Test #3 Custrom Ordered Trip --------------

//    vector<QString> stadiums;

//    stadiums.push_back("Dodger Stadium");
//    stadiums.push_back("Coors Field");
//    stadiums.push_back("Nationals Park");
//    stadiums.push_back("Marlins Park");

//    trip = sm.customOrderTrip(stadiums);


//  -------- END: Test #3 ----------------------------




//   --------- Test #5 - Custom Trip (Recursive) ------------------

//    vector<QString> stadiums;

//    stadiums.push_back("Marlins Park");
//    stadiums.push_back("Oracle Park");
//    stadiums.push_back("PNC Park");
//    stadiums.push_back("Target Field");

//    trip = sm.customTrip(stadiums);

// ----------------- END: Test #5 ---------------------------------



     // Return from trips:

     for (auto& stadium : trip.path)
     {
         qDebug() << stadium->getStadiumName();

     }

     qDebug() << "\nDistance Traveled: " << trip.distanceTraveled;



//    Minimal Spanning Tree:

//    MinTree tree = sm.MST("Marlins Park");

//    for (auto& edge : tree.edges)
//    {
//        qDebug() << edge.orig << "  ->  "
//                 << edge.dest;
//    }

//    qDebug() << "\nTotal Distance:  " << tree.totalDistance;



    w.show();

    StadiumManager sm;

    sm.printEntrys();
    sm.printSouvenirs();
    sm.printGraph();


    return a.exec();
}
