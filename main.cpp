#include <iostream>
#include <vector>
#include "graph.h"
#include "utils.h"

using namespace std;



void validNnumber(int n);
void validVertexID(int n, int v);

void fillEdges(Graph& graph, int m, int n) {
	int a, b, c;
	Vertex &v = graph.vertexes[0];
	for (int i = 0; i < m; i++)
	{
		cin >> a;
		cin >> b;
		cin >> c;
		validVertexID(n, a);
		validVertexID(n, b);
		validNnumber(c);

		graph.vertexes[a - 1].edges.push_back(Edge(graph.vertexes[a - 1], graph.vertexes[b-1], c));
	}
}

void validNnumber(int n) {
	if (n < 1)
	{
		cout << "invalid input" << endl;
		exit(1);
	}
}

void validVertexID(int n, int v) {
	if (v < 1 || v > n)
	{
		cout << "invalid input" << endl;
		exit(1);
	}
}

int main() {
	int n, m, s,t;


	cin >> n;
	Graph graph(n);

	cin >> m;
	cin >> s;
	cin >> t;

	validNnumber(n);
	validNnumber(m);
	validVertexID(n, s);
	validVertexID(n, t);


	fillEdges(graph, m, n);

	fordFulkerson(graph, graph.getVertexById(s), graph.getVertexById(t), true);
	fordFulkerson(graph, graph.getVertexById(s), graph.getVertexById(t), false);
	Graph rGraph = createResidualGraph(graph);
}