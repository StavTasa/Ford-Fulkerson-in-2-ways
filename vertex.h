#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Vertex;

class Edge {
public:
    Vertex& source;
    Vertex& target;
    int capacity;
    int flow;
    Edge(Vertex& _s, Vertex& _t, int _c) : source(_s), target(_t), capacity(_c), flow(0) {}
    Edge(const Edge& e);
    bool isImprove();

    void operator=(const Edge& e);
    bool operator!=(const Edge& e);
};

class Vertex {

    public:
        int id;
        int d=100000;
        int p = -1;
        vector<Edge> edges;
        Vertex(int i) : id(i) {}
        Vertex(const Vertex& v) {
            id = v.id;
        }

        bool operator== (const Vertex& v);
        void operator= (const Vertex& v);
        Edge* getEdgeBySource(Vertex& s);
        Edge* getEdgeByTarget(Vertex& t);
        Edge* getEdgeByTargetId(int t_id);
        void sortEdges();
};

