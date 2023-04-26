#pragma once

#include <QSqlDatabase>
#include "Containers/Map.h"
#include "Containers/Graph.h"
#include "mlb.h"

using Iterator = Map<QString, MLB>::Iterator;


class StadiumManager
{
  public:

    using Map   = Map<QString, MLB>;
    using Graph = Graph<QString, int>;

    StadiumManager();

    // mark the copy/move constructors and assignment operators as deleted

    Map& getStadiums();

    MLB* getStadium(const QString& stadiumName);
    MLB* getTeam(const QString& teamName);

    MinTree<QString> MST(const QString& origin);

    Trip<MLB*> DFS(const QString& start);
    Trip<MLB*> BFS(const QString& start);
    Trip<MLB*> shortestPath(const QString& start, const QString& end);
    Trip<MLB*> customTrip(vector<QString>& stadiums);
    Trip<MLB*> customOrderTrip(const vector<QString>& stadiums);
  

    // For Testing:
    void printEntrys();
    void printSouvenirs();
    void printGraph();

    Map map;  // put back to private

  private:
    void setDB(const QString& fileName);
    void readDB();

    void parseMLBTable(QSqlQuery& query);
    void parseSouvenirTable(QSqlQuery& query);
    void parseDistanceTable(QSqlQuery& query);

    // Recursive calls for custom trip
    void _customTrip(vector<QString>& stadiums, Trip<QString>& shortestPath, int count = 0);

    static int distance;

    QSqlDatabase  db;
  //  Map           map;
    Graph         graph;
};
