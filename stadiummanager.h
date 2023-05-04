
#pragma once

#include <QtSql>
#include <QSqlDatabase>
#include "Containers/Map.h"
#include "Containers/Graph.h"
#include "mlb.h"

using Iterator = Map<QString, MLB>::Iterator;


class StadiumManager
{
    friend class AdminPage;

  public:

    using Map   = Map<QString, MLB>;
    using Graph = Graph<QString, int>;

    StadiumManager();

    ~StadiumManager();

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

    void parseExpansionTables();

    void addSouvenirToDB(const QString& stadium, const QString& souvenir, float price);
    void modSouvenirNameInDB(const QString& stadium, const QString& oldName, const QString& newName);
    void modSouvenirPriceInDB(const QString& stadium, const QString& souvenir, float price);
    void deleteSouvenirFromDB(const QString& stadium, const QString& souvenir);
    void updateStadiumForSouvenir(const QString& oldName, const QString& newName);

    void updateStadiumNameInDB(const QString& oldName, const QString& newName);
    void updateTeamNameInDB(const QString& stadium, const QString& teamName);
    void updateSeatingInDB(const QString& stadium, int capacity);
    void updateLocationInDB(const QString& stadium, const QString& location);
    void updateSurfaceInDB(const QString& stadium, const QString& surface);
    void updateLeagueInDB(const QString& stadium, const QString& league);
    void updateDateInDB(const QString& stadium, int date);
    void updateFeetToCenterInDB(const QString& stadium, int feet);
    void updateMetersToCenterInDB(const QString& stadium, int meters);
    void updateTypologyInDB(const QString& stadium, const QString& typology);
    void updateRoofTypeInDB(const QString& stadium, const QString& roofType);

    // For Testing:
    void printEntrys();
    void printSouvenirs();
    void printGraph();
    void printVertices();

    Map map;  // put back to private

  private:
    void setDB(const QString& fileName);

    void parseTables();
    void parseMLBTable(QSqlQuery* query);
    void parseSouvenirTable(QSqlQuery* query);
    void parseDistanceTable(QSqlQuery* query);

    void parseMLBXTable(QSqlQuery* query);
    void parseSouvenirXTable(QSqlQuery* query);
    void parseDistanceXTable(QSqlQuery* query);

    // Recursive calls for custom trip
    void _customTrip(vector<QString>& stadiums,
                     Trip<QString>&   shortestPath, int count = 0);

    static int distance;

    QSqlDatabase  db;
    QSqlQuery*    query;
 //   Map           map;
    Graph         graph;
};
