#include <string>
#include "Graph.h"

using namespace std;

graph::graph() {
	vertexLookup = hashTable();
}

bool graph::contains(string name) {
	return vertexLookup.contains(name);
}

int graph::insertVertex(string name) {
	vertex * pv = new vertex(name);

	// Attempt insert, and if the vertex already exists return that status
	// If there is some other error, report that back
	int status;
	if ((status = vertexLookup.insert(name, pv)) == 1) {
		return 1;
	} else if (status) {
		return 2;
	}

	// On successful insertion, add vertex to list
	vertexList.push_back(pv);
	return 0;
}

int graph::insertEdge(string v1Name, string v2Name, int cost) {
	// Make sure that both vertices are in the graph
	if (!contains(v1Name) || !contains(v2Name)) {
		return 1;
	}

	vertex * v1 = (vertex *) vertexLookup.getPointer(v1Name);
	vertex * v2 = (vertex *) vertexLookup.getPointer(v2Name);

	v1->insertEdge(v2, cost);
	return 0;
}

graph::vertex::vertex(string n) {
	name = n;
	adjacentEdges = list<edge>();

	visited = false;
	distance = INT_MAX;
	lastVertex = NULL;
}

void graph::vertex::insertEdge(vertex * pv, int c) {
	adjacentEdges.push_back(edge(pv, c));
}

graph::vertex::edge::edge(vertex * pv, int c) {
	destinaion = pv;
	cost = c;
}

int graph::dijkstra(string startingVertexName) {
	// Ensure the starting vertex exists in the graph
	if (!contains(startingVertexName)) {
		return 1;
	}

	vertex * startingVertex = (vertex *) vertexLookup.getPointer(startingVertexName);


	return 0;
}