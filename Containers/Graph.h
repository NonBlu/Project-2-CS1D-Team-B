#pragma once

#include <list>
#include <vector>
#include <iostream>
#include <QDebug>

using std::list;
using std::vector;

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
        int destV;
        T2  weight;
    };

    Graph();

    Vertex* insertVertex(const T1& v);
    Edge*   insertEdge(const T1& v1, const T1& v2, const T2& weight);

    void DFS(const T1& value);
//	void BFS(const T1& value);

    bool hasVertex(const T1& value);

    void printEdge(int v1, int v2, EdgeType type);
    void printGraph();

  private:
    int _find(const T1& value);

    vector<Vertex> vertices;
};



template<class T1, class T2>
Graph<T1, T2>::Graph() { }


template <class T1, class T2>
typename Graph<T1, T2>::Vertex*
Graph<T1, T2>::insertVertex(const T1& value)
{
    vertices.push_back(Vertex { value, {} });

    return &vertices.back();
}


template <class T1, class T2>
typename Graph<T1, T2>::Edge*
Graph<T1, T2>::insertEdge(const T1& v1, const T1& v2, const T2& weight)
{
    int   origV  {   -1    };
    int   destV  {   -1    };
    Edge* edge   { nullptr };

    for (int i {}; i < vertices.size(); ++i)
    {
        if      (vertices[i].value == v1) origV = i;
        else if (vertices[i].value == v2) destV = i;
    }

    if ((origV != -1) && (destV != -1))
    {
        vertices[origV].edges.push_front(Edge { destV, weight });

        edge = &vertices[destV].edges.front();
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
int Graph<T1, T2>::_find(const T1& value)
{
    int v { -1 };

    for (int i {}; i < vertices.size(); ++i)
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
void Graph<T1, T2>::DFS(const T1& value)
{
    int vertex { _find(value) };

    if (vertex != -1)
    {
        Edge*         edge            { };
        list<Edge*>   edges           { };
        unsigned long totalDistance   { };
        unsigned long visitedVertices { };

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
             //   printEdge(vertex, edge->destV, EdgeType::Discovery);

                visitedVertices |= 1 << edge->destV;

                totalDistance += edge->weight;
            }
            else
            {
             //   printEdge(vertex, edge->destV, EdgeType::Back);
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

        qDebug() << "Total Distance Traveled:  " << totalDistance;
    }
}


template <class T1, class T2>
void Graph<T1, T2>::printEdge(int v1, int v2, EdgeType type)
{
    QDebug output = qDebug();

    switch (type)
    {
        case EdgeType::Discovery  : output << "Discovery Edge:  ";
                                    break;
        case EdgeType::Back       : output << "Back      Edge:  ";
                                    break;
        case EdgeType::Cross      : output << "Cross     Edge:  ";
                                    break;
        case EdgeType::Unexplored : output << "";
    }

    output << vertices[v1].value
           << (QString(" ").repeated(34 - vertices[v1].value.size()) )
           <<   " -> "
           << vertices[v2].value;
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




