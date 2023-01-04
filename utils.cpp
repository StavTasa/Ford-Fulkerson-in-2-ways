#include "utils.h"
#include <algorithm>
#include <unordered_map>


Graph createResidualGraph(Graph& graph) {
    Graph rgraph = graph;
    for (auto u = graph.vertexes.begin(); u < graph.vertexes.end(); u++)
    {
        for (auto e = u->edges.begin(); e < u->edges.end(); e++)
        {
            if (rgraph.vertexes[e->target.id - 1].getEdgeByTarget(e->source) == nullptr)
                rgraph.vertexes[e->target.id - 1].edges.push_back(Edge(e->target, e->source, 0));
        }
    }

    return rgraph;
}


class Node {
public:
    Vertex& vertex;
    Node* parent;
    Node(Vertex& v, Node* p) : vertex(v), parent(p) {}
};

bool inPath(Node* n, Vertex& v) {

    while (n != nullptr)
    {
        if (n->vertex == v)
            return true;
        n = n->parent;
    }
    return false;
}

// no free nodes
Node* BFS(Graph& G, Vertex& s, Vertex& t, vector<int>& S) {
    queue<Node*> Q;
    unordered_map<int, int> d;
    Vertex& u = s;
    Node* n = new Node(s, nullptr);
    Node* curr;

    for (auto& v : G.vertexes)
        d[v.id] = -1;
    d[s.id] = 0;

    Q.push(n);

    while (!Q.empty()) {
        curr = Q.front();
        Q.pop();
        S.push_back(curr->vertex.id);
        for (auto e = curr->vertex.edges.begin(); e < curr->vertex.edges.end(); e++)
        {
            if (d[e->target.id] == -1 && e->isImprove())
            {
                n = new Node(e->target, curr);
                if (e->target == t)
                    return n;
                Q.push(n);
                d[e->target.id] = d[e->source.id] + 1;
            }
        }

    }


    return nullptr;
}

class Compare
{

public:

    bool operator()(Vertex* v, Vertex* u)
    {
        if (v->d < u->d)
            return true;
        else if (v == u)
            if (v->id > u->id)
                return true;
        return false;
    }
};
bool inPathByParentID(Graph& G, int curr, int id) {
    while (curr != -1)
    {
        if (curr == id)
            return true;
        curr = G.getVertexById(curr).p;
    }
    return false;
}
Node* Dijkstra(Graph& rGraph, Vertex& s, Vertex& t, vector<int>& S) {
    int* d = new int[rGraph._verNumber];
    Vertex** p = new Vertex * [rGraph._verNumber];
    Vertex* u = nullptr, * prev_u;
    for (auto i = rGraph.vertexes.begin(); i < rGraph.vertexes.end(); i++)
        i->d = 0;

    rGraph.vertexes[s.id - 1].d = 0;
    for (auto i = rGraph.vertexes.begin(); i < rGraph.vertexes.end(); i++)
        i->p = -1;

    std::priority_queue<Vertex*, std::vector<Vertex*>, Compare> pq;


    S.push_back(s.id);
    for (auto e : s.edges) {
        if (e.target.d < e.capacity) {
            e.target.d = e.capacity;
            e.target.p = s.id;
            pq.push(&(e.target));
        }
    }    
    for (auto e : s.edges)
        cout << endl << "-- " << e.target.id << " capacity: " << e.capacity << " current d:" << e.target.d << " current p:" << e.target.p << " location: " << &e.target;


    prev_u = &s;
    while (!pq.empty()) {

        u = pq.top();
        pq.pop();
        if (u->id == t.id)
            break;
        if (u->id == 7)
            for (auto e : u->edges)
                cout << endl << "7 -- " << e.target.id;
        if (!inPathByParentID(rGraph, prev_u->id, u->id)) {
            S.push_back(u->id);
            if (u->id == 7)
                for (auto e : u->edges)
                    cout << endl << "7 -- " << e.target.id << " capacity: " << e.capacity << " current d:" << e.target.d << " current p:" << e.target.p << " location: " << &e.target;
            cout << endl;
            for (auto e : (*u).edges)
            {
                if (e.target.id == s.id)
                    continue;
                if (e.target.d < min(e.source.d, e.capacity)) {
                    e.target.d = min(e.source.d, e.capacity);
                    e.target.p = e.source.id;
                    pq.push(&(e.target));
                }
            }
            prev_u = u;
        }
    }

    Node* n = nullptr, * prev, * top;
    queue<Node*> path;
    path.push(new Node(t, nullptr));
    Vertex* curr = &t;
    while (curr->p != -1)
    {
        curr = &(rGraph.getVertexById(curr->p));
        path.push(new Node(*curr, nullptr));
    }

    prev = path.front();
    top = prev;
    path.pop();
    while (!path.empty())
    {
        n = path.front();
        path.pop();
        prev->parent = n;
        prev = n;
    }

    if (prev->vertex.id != s.id)
        return nullptr;
    return top;
}



void improveEdge(Vertex& s, Vertex& t, int path_flow) {
    Edge* e = s.getEdgeByTarget(t);
    e->capacity -= path_flow;

    e = t.getEdgeByTarget(s);
    e->capacity += path_flow;

}

void changeCapacityInRGraph(Node* n, int path_flow) {
    while (n->parent != nullptr)
    {
        improveEdge(n->parent->vertex, n->vertex, path_flow);
        n = n->parent;
    }
}

void increaseFlowInGraph(Graph graph, Node* n, int path_flow) {
    Edge* e;
    int nv, v;
    stack<int> path;
    while (n != nullptr)
    {
        path.push(n->vertex.id);
        n = n->parent;
    }


    nv = path.top();
    path.pop();

    v = nv;
    while (!path.empty())
    {
        nv = path.top();
        path.pop();

        e = graph.getVertexById(v).getEdgeByTargetId(nv);
        if (e == nullptr)
        {
            e = graph.getVertexById(nv).getEdgeByTargetId(v);
            e->flow -= path_flow;
        }
        else
            e->flow += path_flow;
        v = nv;
    }
}

int getMinimalFlow(Node* n) {
    int min_flow = n->parent->vertex.getEdgeByTarget(n->vertex)->capacity;

    while (n->parent != nullptr)
    {
        min_flow = min(min_flow, n->parent->vertex.getEdgeByTarget(n->vertex)->capacity);
        n = n->parent;
    }
    return min_flow;
}

void printPath(Node* p) {
    stack<int> Q;
    cout << "Improve Path: ";
    while (p != nullptr)
    {
        Q.push(p->vertex.id);
        p = p->parent;
    }
    while (!Q.empty())
    {
        cout << Q.top() << " ";
        Q.pop();
    }
    cout << endl;
}

bool comp(int a, int b)
{
    return a != b;
}


int fordFulkerson(Graph& graph, Vertex& s, Vertex& t, bool isBFS)
{
    vector<int> S;
    vector<int> T;

    Graph rGraph = createResidualGraph(graph);
    rGraph.sortVertexesEdges();

    int max_flow = 0;
    int path_flow = 0;

    Node* p2;
    if (isBFS) {
        cout << "BFS Method:" << endl;
        Node* p = BFS(rGraph, rGraph.vertexes[s.id - 1], rGraph.vertexes[t.id - 1], S);
        while (p != nullptr) {
            path_flow = getMinimalFlow(p);
            changeCapacityInRGraph(p, path_flow);
            increaseFlowInGraph(graph, p, path_flow);

            // Add path flow to overall flow
            max_flow += path_flow;
            S.clear();

            p = BFS(rGraph, rGraph.vertexes[s.id - 1], rGraph.vertexes[t.id - 1], S);

        }
    }
    else
    {
        cout << "Greedy Method:" << endl;
        Node* p = Dijkstra(rGraph, rGraph.vertexes[s.id - 1], rGraph.vertexes[t.id - 1], S);
        while (p != nullptr) {
            path_flow = p->vertex.d;
            changeCapacityInRGraph(p, path_flow);
            increaseFlowInGraph(graph, p, path_flow);

            // Add path flow to overall flow
            max_flow += path_flow;
            S.clear();
            cout << "--->" << endl;
            printPath(p);
            cout << endl << "Max Flow: " << max_flow << "Path Flow: " << path_flow << endl << endl;
            p = Dijkstra(rGraph, rGraph.vertexes[s.id - 1], rGraph.vertexes[t.id - 1], S);

        }
    }

    vector<int> all_ids = rGraph.getIDs();
    sort(S.begin(), S.end());
    set_difference(all_ids.begin(), all_ids.end(),
        S.begin(), S.end(), back_inserter(T));



    cout << "Max Flow = " << max_flow << endl;
    cout << "Min cut: S = ";
    auto i = S.begin();
    cout << *i++;
    for (; i < S.end(); i++)
        cout << ", " << *i;

    cout << ". T = ";
    i = T.begin();
    cout << *i++;
    for (; i < T.end(); i++)
        cout << ", " << *i;
    cout << endl;

    // Return the overall flow
    return max_flow;
}