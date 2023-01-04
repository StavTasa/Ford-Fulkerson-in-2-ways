#include "vertex.h"

bool Vertex::operator==(const Vertex& v)
{
    if (v.id == id)
        return true;
    return false;
}

void Vertex::operator=(const Vertex& v)
{
    cout << "assign vertex ope";
}

Edge* Vertex::getEdgeBySource(Vertex& s)
{
    for (auto i = edges.begin(); i < edges.end(); i++)
        if (i->source.id == s.id)
            return &(*i);
    return nullptr;
}

Edge* Vertex::getEdgeByTarget(Vertex& t)
{
    for (auto i = edges.begin(); i < edges.end(); i++)
        if ((*i).target == t)
            return &(*i);
    return nullptr;
}

Edge* Vertex::getEdgeByTargetId(int t_id)
{
    for (auto i = edges.begin(); i < edges.end(); i++)
        if ((*i).target.id == t_id)
            return &(*i);
    return nullptr;
}

struct less_than_key
{
    inline bool operator() (const Edge& e1, const Edge& e2)
    {
        return (e1.target.id < e2.target.id);
    }
};

int less_than(const Edge* e1, const Edge* e2) {
    return (e1->target.id < e2->target.id);
}

void Vertex::sortEdges()
{
    int i = 0;
    int size = edges.size();

    //sort(edges.begin(), edges.end(), less_than_key());
    vector<Edge> new_edges;

    
    Edge** tmp = new Edge*[size];
    for (auto e = edges.begin(); e < edges.end(); e++) {
        tmp[i] = &(*e);
        i += 1;
    }

    sort(tmp, tmp + size, less_than);
    edges.clear();

    for (int i = 0; i < size;i++ ) {
        new_edges.push_back(*tmp[i]);
    }
    edges = new_edges;
    delete tmp;
}
