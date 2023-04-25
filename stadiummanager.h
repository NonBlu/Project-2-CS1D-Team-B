#pragma once

#include <QSqlDatabase>
#include "Containers/Map.h"
#include "Containers/Graph.h"
#include "mlb.h"

using Iterator = Map<QString, MLB>::Iterator;


class StadiumManager
{
  public:
    StadiumManager();

    MLB* getStadium(const QString& stadiumName);
    MLB* getTeam(const QString& teamName);


    // For Testing:
    void printEntrys();
    void printSouvenirs();
    void printGraph();

//  private:
    void setDB(const QString& fileName);
    void readDB();

    void parseMLBTable(QSqlQuery& query);
    void parseSouvenirTable(QSqlQuery& query);
    void parseDistanceTable(QSqlQuery& query);

    QSqlDatabase        db;
    Map  <QString, MLB> map;
    Graph<QString, int> graph;
};
