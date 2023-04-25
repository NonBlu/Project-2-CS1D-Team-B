
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

    MLB* getStadium(const QString& stadiumName);
    MLB* getTeam(const QString& teamName);

    Trip<MLB*> DFS(const QString& start);
    Trip<MLB*> BFS(const QString& start);
    Trip<MLB*> shortestPath(const QString& start, const QString& end);
  
    MinTree<QString> MST(const QString& origin);

    // For Testing:
    void printEntrys();
    void printSouvenirs();
    void printGraph();

  private:
    void setDB(const QString& fileName);
    void readDB();

    void parseMLBTable(QSqlQuery& query);
    void parseSouvenirTable(QSqlQuery& query);
    void parseDistanceTable(QSqlQuery& query);

    static int distance;

    QSqlDatabase  db;
    Map           map;
    Graph         graph;
};
