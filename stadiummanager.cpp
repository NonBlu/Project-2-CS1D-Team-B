#include "stadiummanager.h"
#include <QtSql>


StadiumManager::StadiumManager()
{
    setDB("/Volumes/USB1/ProjectOld/Balls.db");

    query = new QSqlQuery(db);

    db.open();

    parseTables();
}


StadiumManager::~StadiumManager()
{
    db.close();

    delete query;
}


void StadiumManager::setDB(const QString& fileName)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(fileName);
}



void StadiumManager::parseTables()
{

    parseMLBTable(query);

    parseSouvenirTable(query);

    parseDistanceTable(query);
}



void StadiumManager::parseMLBTable(QSqlQuery* query)
{
    MLB mlb;

    query->exec("SELECT * FROM MLB;");

    while(query->next())
    {
        mlb.setTeamName(query->value(0).toString());
        mlb.setStadiumName(query->value(1).toString());
        mlb.setSeatingCapacity(query->value(2).toInt());
        mlb.setLocation(query->value(3).toString());
        mlb.setSurface(query->value(4).toString());
        mlb.setLeague(query->value(5).toString());
        mlb.setDateOpened(query->value(6).toInt());
        mlb.setDistanceToCenterFT(query->value(7).toInt());
        mlb.setDistanceToCenterM((query->value(8).toInt()));
        mlb.setTypology(query->value(9).toString());
        mlb.setRoofType(query->value(10).toString());

        map.put( { mlb.getStadiumName(), mlb } );
    }

    query->clear();

}



void StadiumManager::parseSouvenirTable(QSqlQuery* query)
{
    MLB* mlb { nullptr };

    query->exec("SELECT Stadium, Name, Price FROM Souvenirs ORDER BY Stadium;");

    while (query->next())
    {
        mlb = &(*(map.find(query->value(0).toString())));

        mlb->addSouvenir(query->value(1).toString(), query->value(2).toFloat());
    }

    query->clear();
}



void StadiumManager::parseDistanceTable(QSqlQuery* query)
{
    QString origStadium;
    QString destStadium;
    int     distance;

    query->exec("SELECT OrigStadium, DestStadium, Distance FROM Distances ORDER BY OrigStadium;");

    while (query->next())
    {
        origStadium = query->value(0).toString();
        destStadium = query->value(1).toString();
        distance    = query->value(2).toInt();

        if (!graph.hasVertex(origStadium))
        {
            graph.insertVertex(origStadium);
        }

        if (!graph.hasVertex(destStadium))
        {
            graph.insertVertex(destStadium);
        }

        graph.insertEdge(origStadium, destStadium, distance);
    }

    query->clear();
}


// Read from expansion tables - write to main tables.
void StadiumManager::parseExpansionTables()
{
    parseMLBXTable(query);

    parseSouvenirXTable(query);

    parseDistanceXTable(query);
}


void StadiumManager::parseMLBXTable(QSqlQuery* query)
{
    MLB mlb;

    query->exec("SELECT * FROM MLBX;");

    query->next();

    mlb.setTeamName(query->value(0).toString());
    mlb.setStadiumName(query->value(1).toString());
    mlb.setSeatingCapacity(query->value(2).toInt());
    mlb.setLocation(query->value(3).toString());
    mlb.setSurface(query->value(4).toString());
    mlb.setLeague(query->value(5).toString());
    mlb.setDateOpened(query->value(6).toInt());
    mlb.setDistanceToCenterFT(query->value(7).toInt());
    mlb.setDistanceToCenterM((query->value(8).toInt()));
    mlb.setTypology(query->value(9).toString());
    mlb.setRoofType(query->value(10).toString());

    query->clear();

    map.put( { mlb.stadiumName, mlb } );

    query->prepare("INSERT INTO MLB (TeamName, StadiumName, SeatingCapacity, Location, "
                  "PlayingSurface, League, DateOpened, DistanceToCenterFT, DistanceToCenterM, "
                  "BallparkTypology, RoofType) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);"      );

    query->bindValue(0,  mlb.getTeamName());
    query->bindValue(1,  mlb.getStadiumName());
    query->bindValue(2,  mlb.getSeatingCapacity());
    query->bindValue(3,  mlb.getLocation());
    query->bindValue(4,  mlb.getSurface());
    query->bindValue(5,  mlb.getLeague());
    query->bindValue(6,  mlb.getDateOpened());
    query->bindValue(7,  mlb.getFeetToCenter());
    query->bindValue(8,  mlb.getMetersToCenter());
    query->bindValue(9,  mlb.getTypology());
    query->bindValue(10, mlb.getRoofType());

    query->exec();
}


void StadiumManager::parseSouvenirXTable(QSqlQuery* query)
{
    MLB* mlb { nullptr };

    query->exec("SELECT Stadium, Name, Price FROM SouvenirsX ORDER BY Stadium;");

    while (query->next())
    {
        mlb = &(*map.find(query->value(0).toString()));
        mlb->addSouvenir(query->value(1).toString(),
                         query->value(2).toFloat());
    }

    query->clear();

    if (mlb)
    {
        for (auto& souvenir : mlb->souvenirs)
        {
            query->prepare("INSERT INTO Souvenirs (Stadium, Name, Price) "
                          "VALUES (?, ?, ?);"                             );

            query->bindValue(0, mlb->getStadiumName());
            query->bindValue(1, souvenir.name);
            query->bindValue(2, souvenir.price);

            query->exec();
        }
    }

}


void StadiumManager::parseDistanceXTable(QSqlQuery* query)
{
    QString         origStadium;
    vector<QString> destStadiums;
    vector<int>     distances;

    query->exec("SELECT * FROM DistancesX");

    query->next();

    origStadium = query->value(0).toString();
    destStadiums.push_back(query->value(1).toString());
    distances.push_back(query->value(2).toInt());

    graph.insertEdge(origStadium, destStadiums.back(), distances.back());
    graph.insertEdge(destStadiums.back(), origStadium, distances.back());

    while (query->next())
    {
        destStadiums.push_back(query->value(1).toString());
        distances.push_back(query->value(2).toInt());

        graph.insertEdge(origStadium, destStadiums.back(), distances.back());
        graph.insertEdge(destStadiums.back(), origStadium, distances.back());
    }

    query->clear();


    for (unsigned int i { }; i < distances.size(); ++i)
    {
        query->prepare("INSERT INTO DISTANCES (OrigStadium, destStadium, Distance) "
                      "VALUES (?, ?, ?);"                                          );

        query->bindValue(0, origStadium    );
        query->bindValue(1, destStadiums[i]);
        query->bindValue(2, distances[i]   );

        query->exec();
    }

    for (unsigned int i { }; i < distances.size(); ++i)
    {
        query->prepare("INSERT INTO DISTANCES (OrigStadium, destStadium, Distance) "
                      "VALUES (?, ?, ?);"                                          );

        query->bindValue(0, destStadiums[i]);
        query->bindValue(1, origStadium    );
        query->bindValue(2, distances[i]   );

        query->exec();
    }
}


void StadiumManager::updateStadiumNameInDB(const QString& oldName, const QString& newName)
{
    query->prepare("UPDATE MLB SET StadiumName = ? WHERE StadiumName = ?; ");

    query->bindValue(0, newName);
    query->bindValue(1, oldName);

    query->exec();


    query->prepare("UPDATE Distances SET OrigStadium = ? WHERE OrigStadium = ?; ");

    query->bindValue(0, newName);
    query->bindValue(1, oldName);

    query->exec();


    query->prepare("UPDATE Distances SET DestStadium = ? WHERE DestStadium = ?; ");

    query->bindValue(0, newName);
    query->bindValue(1, oldName);

    query->exec();
}


void StadiumManager::updateTeamNameInDB(const QString& stadiumName, const QString& teamName)
{
    query->prepare("UPDATE MLB SET TeamName = ? WHERE StadiumName = ?; ");

    query->bindValue(0, teamName);
    query->bindValue(1, stadiumName);

    query->exec();

}


void StadiumManager::updateSeatingInDB(const QString& stadium, int capacity)
{
    query->prepare("UPDATE MLB SET SeatingCapacity = ? WHERE StadiumName = ?; ");

    query->bindValue(0, capacity);
    query->bindValue(1, stadium);

    query->exec();
}


void StadiumManager::updateLocationInDB(const QString& stadium, const QString& location)
{
    query->prepare("UPDATE MLB SET Location = ? WHERE StadiumName = ?; ");

    query->bindValue(0, location);
    query->bindValue(1, stadium);

    query->exec();
}


void StadiumManager::updateSurfaceInDB(const QString& stadium, const QString& surface)
{
    query->prepare("UPDATE MLB SET PlayingSurface = ? WHERE StadiumName = ?; ");

    query->bindValue(0, surface);
    query->bindValue(1, stadium);

    query->exec();
}


void StadiumManager::updateLeagueInDB(const QString& stadium, const QString& league)
{
    query->prepare("UPDATE MLB SET League = ? WHERE StadiumName = ?; ");

    query->bindValue(0, league);
    query->bindValue(1, stadium);

    query->exec();
}


void StadiumManager::updateDateInDB(const QString& stadium, int date)
{
    query->prepare("UPDATE MLB SET DateOpened = ? WHERE StadiumName = ?; ");

    query->bindValue(0, date);
    query->bindValue(1, stadium);

    query->exec();
}


void StadiumManager::updateFeetToCenterInDB(const QString& stadium, int feet)
{
    query->prepare("UPDATE MLB SET DistanceToCenterFT = ? WHERE StadiumName = ?; ");

    query->bindValue(0, feet);
    query->bindValue(1, stadium);

    query->exec();
}


void StadiumManager::updateMetersToCenterInDB(const QString& stadium, int meters)
{
    query->prepare("UPDATE MLB SET DistanceToCenterM = ? WHERE StadiumName = ?; ");

    query->bindValue(0, meters);
    query->bindValue(1, stadium);

    query->exec();
}


void StadiumManager::updateTypologyInDB(const QString& stadium, const QString& typology)
{
    query->prepare("UPDATE MLB SET BallparkTypology = ? WHERE StadiumName = ?; ");

    query->bindValue(0, typology);
    query->bindValue(1, stadium);

    query->exec();
}


void StadiumManager::updateRoofTypeInDB(const QString& stadium, const QString& roofType)
{
    query->prepare("UPDATE MLB SET RoofType = ? WHERE StadiumName = ?; ");

    query->bindValue(0, roofType);
    query->bindValue(1, stadium);

    query->exec();
}


void StadiumManager::addSouvenirToDB(const QString& stadium,
                                     const QString& souvenir,
                                     float price             )
{
    QSqlQuery query(db);

    db.open();

   if (!db.isOpen())
   {
       qDebug() << "Database did not open to add a Souvenir";
   }
   else
   {
       query.prepare("INSERT INTO Souvenirs (Stadium, Name, Price) "
                     "VALUES (?, ?, ?);"                             );

       query.bindValue(0, stadium  );
       query.bindValue(1, souvenir );
       query.bindValue(2, price    );

       query.exec();

       db.close();
   }
}



void StadiumManager::modSouvenirNameInDB(const QString& stadium,
                                         const QString& oldName,
                                         const QString& newName )
{
    QSqlQuery query(db);

    db.open();

   if (!db.isOpen())
   {
       qDebug() << "Database did not open to modify a souvenir name";
   }
   else
   {
       query.prepare("UPDATE Souvenirs "
                     "SET Name = ? "
                     "WHERE Stadium = ? AND Name = ?;");

       query.bindValue(0, newName);
       query.bindValue(1, stadium);
       query.bindValue(2, oldName);

       query.exec();

       db.close();
   }
}



void StadiumManager::modSouvenirPriceInDB(const QString& stadium,
                                          const QString& souvenir,
                                                float    price    )
{
    QSqlQuery query(db);

    db.open();

   if (!db.isOpen())
   {
       qDebug() << "Database did not open to modify a souvnirs price";
   }
   else
   {
       query.prepare("UPDATE Souvenirs "
                     "SET Price = ? "
                     "WHERE Stadium = ? AND Name = ?;");

       query.bindValue(0, price   );
       query.bindValue(1, stadium );
       query.bindValue(2, souvenir);

       query.exec();

       db.close();
   }
}



void StadiumManager::deleteSouvenirFromDB(const QString& stadium, const QString& souvenir)
{
    QSqlQuery query(db);

    db.open();

   if (!db.isOpen())
   {
       qDebug() << "Database did not open to delete a souvenir";
   }
   else
   {
        query.prepare("DELETE FROM Souvenirs "
                      "WHERE Stadium = ? AND Name = ?; "      );

        query.bindValue(0, stadium);
        query.bindValue(1, souvenir);

        query.exec();

        db.close();
   }
}



Map<QString, MLB>& StadiumManager::getStadiums()
{
    return map;
}



MLB* StadiumManager::getStadium(const QString& stadiumName)
{
    return &(*map.find(stadiumName));
}



MLB* StadiumManager::getTeam(const QString& teamName)
{
    MLB* mlb { nullptr };

    for (auto& entry : map)
    {
        if (entry.getTeamName() == teamName)
        {
            mlb = &entry;

            break;
        }
    }

    return mlb;
}



MinTree<QString> StadiumManager::MST(const QString& origin)
{
    return graph.prims(origin);
}



Trip<MLB*> StadiumManager::DFS(const QString& start)
{
    Trip<MLB*> trip;

    Trip<QString> dfs { graph.DFS(start) };

    for (auto& vertex : dfs.path)
    {
            trip.path.push_back((&(*map.find(vertex))));
    }

    trip.distanceTraveled = dfs.distanceTraveled;

    return trip;
}



Trip<MLB*> StadiumManager::BFS(const QString& start)
{
    Trip<MLB*> trip;

    Trip<QString> bfs { graph.BFS(start) };

    for (auto& vertex : bfs.path)
    {
            trip.path.push_back((&(*map.find(vertex))));
    }

    trip.distanceTraveled = bfs.distanceTraveled;

    return trip;
}



Trip<MLB*> StadiumManager::shortestPath(const QString& start, const QString& end)
{
    Trip<MLB*> trip;

    Trip<QString> dijkstras { graph.Dijkstras(start, end) };

    for (auto& vertex : dijkstras.path)
    {
            trip.path.push_back((&(*map.find(vertex))));
    }

    trip.distanceTraveled = dijkstras.distanceTraveled;

    return trip;
}



Trip<MLB*> StadiumManager::customOrderTrip(const vector<QString>& stadiums)
{
    Trip<MLB*> trip;

    Trip<QString> shortestPath;

    for (unsigned int i { }; i < stadiums.size() - 1; ++i)
    {
        shortestPath = graph.Dijkstras(stadiums[i], stadiums[i + 1]);

        if (i && shortestPath.path.front() == trip.path.back()->getStadiumName())
        {
            shortestPath.path.pop_front();
        }

        for (auto& stadium : shortestPath.path)
        {
            trip.path.push_back(&(*map.find(stadium)));
        }

        trip.distanceTraveled += shortestPath.distanceTraveled;
    }

    return trip;
}



Trip<MLB*> StadiumManager::customTrip(vector<QString>& stadiums)
{
    Trip<MLB*> trip;

    Trip<QString> shortestPath;

    _customTrip(stadiums, shortestPath);

    for (auto& stadium : shortestPath.path)
    {
        trip.path.push_back(&(*map.find(stadium)));
    }

    trip.distanceTraveled = shortestPath.distanceTraveled;

    return trip;
}



void StadiumManager::_customTrip(vector<QString>& stadiums, Trip<QString>& shortestPath, int count)
{
   if (stadiums.size() == 1)
   {
       return;
   }
   else
   {
       Trip<QString> trip { graph.closestVertexPath(stadiums) };

       for (unsigned int i { }; i < stadiums.size(); ++i)
       {
           if (stadiums[i] == trip.path.back())
           {
               std::swap(stadiums[0], stadiums[i]);

               stadiums.erase(stadiums.begin() + i);
           }
       }

       if (count)
       {
           trip.path.pop_front();
       }

       shortestPath.path.splice(shortestPath.path.end(), trip.path);

       shortestPath.distanceTraveled += trip.distanceTraveled;

       _customTrip(stadiums, shortestPath, ++count);
   }
}




// ----------------------  For Testing ---------------------------

void StadiumManager::printEntrys()
{
    for (auto& mlb : map)
    {
        qDebug() << mlb.getTeamName()   << "  " << mlb.getStadiumName()  << "  " << mlb.getSeatingCapacity() << "  "
                 << mlb.getLocation()   << "  " << mlb.getSurface()      << "  " << mlb.getLeague()          << "  "
                 << mlb.getDateOpened() << "  " << mlb.getFeetToCenter() << "  " << mlb.getMetersToCenter()  << "  "
                 << mlb.getTypology()   << "  " << mlb.getRoofType();

    }
}


void StadiumManager::printSouvenirs()
{

    for (auto& mlb : map)
    {
        qDebug() << mlb.getStadiumName();

        for (auto& souvenir : mlb.souvenirs)
        {
            qDebug() << souvenir.name << "    " << souvenir.price;
        }

        qDebug() << "\n";
    }
}


void StadiumManager::printGraph()
{
    graph.printGraph();
}


void StadiumManager::printVertices()
{
    graph.printVertexes();
}
