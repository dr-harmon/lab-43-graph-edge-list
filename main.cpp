#include "graph.h"

#include <cstdlib>
#include <iostream>

using namespace std;

int main()
{
	Graph<char,char> graph;
	auto u = graph.insertVertex('u');
	auto v = graph.insertVertex('v');
	auto w = graph.insertVertex('w');
	auto z = graph.insertVertex('z');
	auto a = graph.insertEdge(u, v, 'a');
	auto b = graph.insertEdge(v, w, 'b');
	auto c = graph.insertEdge(u, w, 'c');
	auto d = graph.insertEdge(w, z, 'd');

	cout << "Vertices:" << endl;
	auto vertices = graph.vertices();
    for (auto it = vertices.begin(); it != vertices.end(); ++it) {
		cout << **it << endl;
	}

	cout << "Edge:" << endl;
	auto edges = graph.edges();
    for (auto it = edges.begin(); it != edges.end(); ++it) {
		cout << **it << endl;
	}

	cout << "u vertices:" << endl;
    for (auto it = vertices.begin(); it != vertices.end(); ++it) {
		if (u.isAdjacentTo(*it)) {
			cout << **it << endl;
		}
	}

	cout << "w edges:" << endl;
    for (auto it = edges.begin(); it != edges.end(); ++it) {
		if ((*it).isIncidentOn(w)) {
			cout << **it << endl;
		}
	}

	graph.eraseVertex(z);

	cout << "w edges without z:" << endl;
	auto newEdges = graph.edges();
    for (auto it = newEdges.begin(); it != newEdges.end(); ++it) {
		if ((*it).isIncidentOn(w)) {
			cout << **it << endl;
		}
	}

	return EXIT_SUCCESS;
}
