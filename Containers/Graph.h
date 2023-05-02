#pragma once

#include <list>
#include <queue>
#include <vector>
#include <iostream>
#include <QDebug>
#include <QString>

using std::string;
using std::list;
using std::vector;
using std::priority_queue;


template <typename T>
struct Trip
{
    list<T>      path;
    unsigned int distanceTraveled;

    Trip() : path { }, distanceTraveled { } { }
};


template <typename T>
struct MinTree
{
    struct Edge
    {
        T orig;
        T dest;
    };

    list<Edge> edges;
    int        totalDistance;

    MinTree() : edges { }, totalDistance { } { }
};


template <typename T1, typename T2>
class Graph
{
  public:
    struct Edge;

    enum EdgeType { Unexplored, Discovery, Back, Cross };

    struct Vertex
    {
        T1         value;
        list<Edge> edges;
    };

    struct Edge
    {
        int origV;
        int destV;
        T2  weight;
    };

    Graph(int size = 0);

    Vertex* insertVertex(const T1& v);
    Edge*   insertEdge(const T1& v1, const T1& v2, const T2& weight);

    MinTree<T1> prims(const T1& startVertex);

    Trip<T1> DFS(const T1& startVertex);
    Trip<T1> BFS(const T1& startVertex);
    Trip<T1> Dijkstras(const T1& startVertex, const T1& destVertex);
    Trip<T1> closestVertexPath(const vector<T1>& vertexes);

    void printGraph();
    void printVertexes();
    bool hasVertex(const T1& value);

    void updateVertexValue(const T1& oldValue, const T1& newValue);

  private:
    int _find(const T1& value);

    vector<Vertex> vertices;
    unsigned int   vertexCount;
};



template<class T1, class T2>
Graph<T1, T2>::Graph(int size) : vertexCount { }
{
    vertices.reserve(size);
 }


template <class T1, class T2>
typename Graph<T1, T2>::Vertex*
Graph<T1, T2>::insertVertex(const T1& value)
{
    vertices.push_back(Vertex { value, { } });

    ++vertexCount;

    return &vertices.back();
}


template <class T1, class T2>
typename Graph<T1, T2>::Edge*
Graph<T1, T2>::insertEdge(const T1& v1, const T1& v2, const T2& weight)
{
    int   origV  {   -1    };
    int   destV  {   -1    };
    Edge* edge   { nullptr };

    for (unsigned int i {}; i < vertices.size(); ++i)
    {
        if      (vertices[i].value == v1) origV = i;
        else if (vertices[i].value == v2) destV = i;
    }

    if ((origV != -1) && (destV != -1))
    {
        vertices[origV].edges.push_front(Edge { origV, destV, weight });

        edge = &vertices[origV].edges.front();
    }

    return edge;
}


template <class T1, class T2>
bool Graph<T1, T2>::hasVertex(const T1& value)
{
    bool found { false };

    for (auto& vertex : vertices)
    {
        if (vertex.value == value)
        {
            found = true;

            break;
        }
    }

    return found;
}


template <class T1, class T2>
void Graph<T1, T2>::updateVertexValue(const T1& oldValue, const T1& newValue)
{
    for (auto& vertex : vertices)
    {
        if (vertex.value == oldValue)
        {
            vertex.value = newValue;

            break;
        }
    }
}


template <class T1, class T2>
int Graph<T1, T2>::_find(const T1& value)
{
    int v { -1 };

    for (unsigned int i {}; i < vertices.size(); ++i)
    {
        if (vertices[i].value == value)
        {
            v = i;

            break;
        }
    }

    return v;
}



template <class T1, class T2>
Trip<T1> Graph<T1, T2>::DFS(const T1& startVertex)
{
    Trip<T1> trip;

    int vertex { _find(startVertex) };

    if (vertex != -1)
    {
        Edge*         edge;
        list<Edge*>   edges;
        unsigned long visitedVertices { };

        trip.path.push_back(vertices[vertex].value);

        visitedVertices |= 1 << vertex;

        vertices[vertex].edges.sort( [] (const Edge& a, const Edge& b)
                                        { return a.weight > b.weight; } );

        for (auto& edge : vertices[vertex].edges)
        {
            edges.push_front(&edge);
        }

        while (!edges.empty())
        {
            edge = edges.front();

            edges.pop_front();

            if (!(visitedVertices & (1 << edge->destV)))
            {
                trip.path.push_back((vertices[edge->destV].value));

                visitedVertices |= 1 << edge->destV;

                trip.distanceTraveled += edge->weight;
            }

            vertex = edge->destV;

            vertices[vertex].edges.sort( [] (const Edge& a, const Edge& b)
                                            { return a.weight > b.weight; } );

            for (auto& edge : vertices[vertex].edges)
            {
                if (!(visitedVertices & (1 << edge.destV)))
                {
                    edges.push_front(&edge);
                }
            }
        }
    }
    else
    {
        qDebug() << "Invalid Start Vertex";
    }

    return trip;
}


template <class T1, class T2>
Trip<T1>Graph<T1, T2>::BFS(const T1& startVertex)
{
    Trip<T1> trip;

    int vertex { _find(startVertex) };

    if (vertex != -1)
    {
        auto comp = [] (const Edge& a, const Edge& b) { return b.weight < a.weight; };
        priority_queue<Edge, vector<Edge>, decltype( comp )> priorityQ(comp);

        list<int>    vertexes;
        unsigned int visitedVertices { };

        vertexes.push_front(vertex);

        visitedVertices |= 1 << vertex;

        while (!vertexes.empty())
        {
            vertex = vertexes.front();

            vertexes.pop_front();

            trip.path.push_back(vertices[vertex].value);

            for (auto& edge : vertices[vertex].edges)
            {
                if (!(visitedVertices & (1 << edge.destV)))
                {
                    priorityQ.push(edge);

                    visitedVertices |= 1 << edge.destV;

                    trip.distanceTraveled += edge.weight;
                }
            }

            while (!priorityQ.empty())
            {
                vertex = priorityQ.top().destV;

                vertexes.push_back(vertex);

                priorityQ.pop();
            }
        }
    }
    else
    {
        qDebug() << "Invalid start Vertex";
    }

    return trip;
}


template <class T1, class T2>
MinTree<T1> Graph<T1, T2>::prims(const T1& startVertex)
{
    MinTree<T1> tree;

    int vertex { _find(startVertex) };

    if (vertex != -1)
    {
        auto comp = [] (const Edge& a, const Edge& b) { return b.weight < a.weight; };
        priority_queue<Edge, vector<Edge>, decltype( comp )> priorityQ(comp);

        Edge         minEdge          { };
        unsigned int visitedVertices  { };
        unsigned int count            { };

        priorityQ.push(Edge { vertex, vertex, 0 });

        while (!priorityQ.empty() && (count < vertexCount))
        {
            minEdge = priorityQ.top();

            priorityQ.pop();

            if (!(visitedVertices & (1 << minEdge.destV)))
            {
                tree.edges.push_back({ vertices[minEdge.origV].value,
                                       vertices[minEdge.destV].value});

                visitedVertices |= 1 << minEdge.destV;

                ++count;

                tree.totalDistance += minEdge.weight;
            }

            for (auto& edge : vertices[minEdge.destV].edges)
            {
                if (!(visitedVertices & (1 << edge.destV)))
                {
                    priorityQ.push(edge);
                }
            }
        }

        tree.edges.pop_front();
    }
    else
    {
        qDebug() << "Invalid start Vertex for Prim's Algorithm";
    }

    return tree;
}


template <class T1, class T2>
Trip<T1> Graph<T1, T2>::Dijkstras(const T1& startVertex, const T1& destVertex)
{
    Trip<T1> trip;

    int startV { _find(startVertex) };
    int destV  { _find(destVertex ) };

    if (startV != -1 && destV != -1)
    {
        auto comp = [] (const Edge& a, const Edge& b) { return b.weight < a.weight; };
        priority_queue<Edge, vector<Edge>, decltype( comp )> priorityQ(comp);

        vector<unsigned int> costs(vertexCount, 0 - 1);
        vector<int>          parents(vertexCount);
        Edge                 minEdge;
        int                  parent;

        costs[startV]   =  0;
        parents[startV] = -1;

        priorityQ.push(Edge { startV, startV, 0 });

        while (!priorityQ.empty())
        {
            minEdge = priorityQ.top();

            priorityQ.pop();

            for (auto& edge : vertices[minEdge.destV].edges)
            {
                if ((unsigned int)(minEdge.weight + edge.weight) < costs[edge.destV])
                {
                    costs[edge.destV]   = minEdge.weight + edge.weight;
                    parents[edge.destV] = minEdge.destV;

                    priorityQ.push(Edge { edge.origV, edge.destV, minEdge.weight + edge.weight });
                }
            }
        }

        // Collect the desired path from origin -> destination

        parent = destV;

        trip.distanceTraveled = costs[destV];

        trip.path.push_front(vertices[parent].value);

        while (parent != startV)
        {
            parent = parents[parent];

            trip.path.push_front(vertices[parent].value);
        }
    }
    else
    {
        qDebug() << "Graph does not contain the provided vertexes";
    }

    return trip;
}



template <class T1, class T2>
Trip<T1> Graph<T1, T2>::closestVertexPath(const vector<T1>& vertexes)
{
    Trip<T1> trip;

    int vertex { _find(vertexes[0]) };

    auto comp = [] (const Edge& a, const Edge& b) { return b.weight < a.weight; };
    priority_queue<Edge, vector<Edge>, decltype( comp )> priorityQ(comp);

    vector<unsigned int> costs(vertexCount, 0 - 1);
    vector<int>          parents(vertexCount);
    Edge                 minEdge;
    unsigned int         minCost = 0 - 1;
    int                  parent;

    costs[vertex]   =  0;
    parents[vertex] = -1;

    priorityQ.push(Edge { vertex, vertex, 0 });

    while (!priorityQ.empty())
    {
        minEdge = priorityQ.top();

        priorityQ.pop();

        for (auto& edge : vertices[minEdge.destV].edges)
        {
            if ((unsigned int)(minEdge.weight + edge.weight) < costs[edge.destV])
            {
                costs[edge.destV]   = minEdge.weight + edge.weight;
                parents[edge.destV] = minEdge.destV;

                priorityQ.push(Edge { edge.origV, edge.destV, minEdge.weight + edge.weight });
            }
        }
    }

    // Find path to vertex with minimal cost (from vertexes argument)

    unsigned int index { 1 };

    do
    {
        vertex = _find(vertexes[index]);

        if (costs[vertex] < minCost)
        {
            minCost = costs[vertex];

            parent = vertex;
        }

        ++index;

    } while (index < vertexes.size());

    trip.distanceTraveled = costs[parent];

    trip.path.push_front(vertices[parent].value);

    vertex = _find(vertexes[0]);

    while (parent != vertex)
    {
        parent = parents[parent];

        trip.path.push_front(vertices[parent].value);
    }

    return trip;
}




// ----- For Testing ---------

template <class T1, class T2>
void Graph<T1, T2>::printVertexes()
{
    for (auto& vertex : vertices)
    {
        qDebug() << vertex.value;
    }
}


template <class T1, class T2>
void Graph<T1, T2>::printGraph()
{
    QDebug out { qDebug() };

    for (auto& vertex : vertices)
    {
        out << vertex.value << ':';

        for (auto& edge : vertex.edges)
        {
            out << vertices[edge.destV].value << " ";
        }

        out << '\n';
    }
}

