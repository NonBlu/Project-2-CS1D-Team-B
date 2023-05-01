#include "stadiummanager.h"
#include <QtSql>


StadiumManager::StadiumManager()
{
    setDB("/Users/19494/Documents/GitHub/Project-2-CS1D-Team-B/Balls.db");

    readDB();
}


void StadiumManager::setDB(const QString& fileName)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(fileName);
}


void StadiumManager::readDB()
{
    QSqlQuery query(db);

    db.open();

    if (!db.isOpen())
    {
        qDebug() << "DB did not open";
    }
    {
        parseMLBTable(query);

        parseSouvenirTable(query);

        parseDistanceTable(query);
    }

    db.close();
}


void StadiumManager::parseMLBTable(QSqlQuery& query)
{
    MLB mlb;

    query.exec("SELECT * FROM MLB;");

    while(query.next())
    {
        mlb.setTeamName(query.value(0).toString());
        mlb.setStadiumName(query.value(1).toString());
        mlb.setSeatingCapacity(query.value(2).toInt());
        mlb.setLocation(query.value(3).toString());
        mlb.setSurface(query.value(4).toString());
        mlb.setLeague(query.value(5).toString());
        mlb.setDateOpened(query.value(6).toInt());
        mlb.setDistanceToCenterFT(query.value(7).toInt());
        mlb.setDistanceToCenterM((query.value(8).toInt()));
        mlb.setTypology(query.value(9).toString());
        mlb.setRoofType(query.value(10).toString());

        map.put( { mlb.getStadiumName(), mlb } );
    }

    query.clear();

}


void StadiumManager::parseSouvenirTable(QSqlQuery& query)
{
    MLB* mlb { nullptr };

    query.exec("SELECT Stadium, Name, Price FROM Souvenirs ORDER BY Stadium;");

    while (query.next())
    {
        mlb = &(*(map.find(query.value(0).toString())));

        mlb->addSouvenir(query.value(1).toString(), query.value(2).toFloat());
    }

    query.clear();
}


void StadiumManager::parseDistanceTable(QSqlQuery& query)
{
    QString origStadium;
    QString destStadium;
    int     distance;

    query.exec("SELECT OrigStadium, DestStadium, Distance FROM Distances ORDER BY OrigStadium;");

    while (query.next())
    {
        origStadium = query.value(0).toString();
        destStadium = query.value(1).toString();
        distance    = query.value(2).toInt();

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

    query.clear();
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
