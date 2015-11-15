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

graph::vertex::vertex(std::string name) {
	id = name;
	adjacentEdges = std::list<edge>();
}

graph::vertex::edge::edge(vertex * pv, int c) {
	destinaion = pv;
	cost = c;
}