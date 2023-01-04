#pragma once
#include <iostream>
#include <vector>
#include "vertex.h"
#include "edge.h"


using namespace std;


class Graph {
public:
    int _verNumber;
    vector<Vertex>vertexes;

    Graph(int n);
    Graph(const Graph& G);
    ~Graph() {};
    Vertex &getVertexById(int id);
    vector<Vertex> getAdjList(Graph &graph, int i);
    void sortVertexesEdges();
    vector<int> getIDs();
};