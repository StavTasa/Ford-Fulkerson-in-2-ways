#pragma once
#include "graph.h"
#include <queue>
#include <stack>

using namespace std;

Graph createResidualGraph(Graph &rgraph);
int fordFulkerson(Graph& graph, Vertex &s, Vertex &t, bool isBFS);
class Node;
Node* BFS(Graph G, Vertex& s, Vertex& t);
