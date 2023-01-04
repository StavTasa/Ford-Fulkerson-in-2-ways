#pragma once
#include <iostream>
#include <vector>
#include "graph.h"

using namespace std;


Graph::Graph(int n)
{
    _verNumber = n;
    for (int i = 0; i < n; i++)
        vertexes.push_back(Vertex(i+1));
}

Graph::Graph(const Graph& G)
{
    _verNumber = G._verNumber;
    Vertex * source, *target;
    for (auto u = G.vertexes.begin(); u < G.vertexes.end(); u++)
        vertexes.push_back(Vertex(u->id));

    for (auto u = G.vertexes.begin(); u < G.vertexes.end(); u++)
    {
        for (auto e = u->edges.begin(); e < u->edges.end(); e++)
        {
            source = &vertexes[u->id - 1];
            target = &vertexes[e->target.id - 1];
            source->edges.push_back(Edge(*source, *target, e->capacity));
        }
    }
}


Vertex& Graph::getVertexById(int id)
{
    for (auto i = vertexes.begin(); i < vertexes.end(); i++)
        if (i->id == id)
            return *i;

}

vector<Vertex> Graph::getAdjList(Graph &graph, int i)
{
    vector<Vertex> res;
    Vertex v = graph.vertexes[i+1];
    for (auto i = v.edges.begin(); i < v.edges.end(); i++)
    {
        res.push_back(i->target);
    }
    return res;
}

void Graph::sortVertexesEdges()
{
    for (auto i = vertexes.begin(); i < vertexes.end(); i++)
    {
        i->sortEdges();
    }
}

vector<int> Graph::getIDs()
{
    vector<int> vec;
     for (auto i : vertexes)
         vec.push_back(i.id);
     return vec;
}
