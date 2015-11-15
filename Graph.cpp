#include <string>
#include "Heap.h"
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

graph::vertex::vertex() : vertex("") { }

graph::vertex::vertex(string n) {
	name = n;
	adjacentEdges = list<edge>();

	known = false;
	distance = INT_MAX;
	lastVertex = NULL;
}

void graph::vertex::insertEdge(vertex * pv, int c) {
	adjacentEdges.push_back(edge(pv, c));
}

graph::vertex::edge::edge(vertex * pv, int c) {
	destination = pv;
	cost = c;
}

int graph::shortestPathDijkstra(string startingVertexName) {
	// Ensure the starting vertex exists in the graph
	if (!contains(startingVertexName)) {
		return 1;
	}

	vertex * startingVertex = (vertex *) vertexLookup.getPointer(startingVertexName);

	heap data(vertexList.size());

	// Set start node parameters
	startingVertex->distance = 0;
	startingVertex->known = true;
	startingVertex->lastVertex = NULL;

	// Insert each vertex into the priority queue
	for (list<vertex *>::iterator it = vertexList.begin(); it != vertexList.end(); ++it) {
		data.insert((*it)->name, (*it)->distance, (*it));
	}

	// Vertex container
	vertex * pv = new vertex();

	// Cycle through all vertices that are still in the unknown set (data object)
	while (data.deleteMin(NULL, NULL, pv) == 0) {
		pv->known = true;

		// Loop through all outgoing edges incident upon current vertex
		for (list<vertex::edge>::iterator it = pv->adjacentEdges.begin(); it != pv->adjacentEdges.end(); ++it) {
			// Check if new path is better than old one
			int newCost;
			if ((newCost = pv->distance + (*it).cost) < (*it).destination->distance) {
				// Set key in the priority queue
				data.setKey((*it).destination->name, newCost);
				// Update vertex data
				(*it).destination->distance = newCost;
				(*it).destination->lastVertex = pv;
			}
		}
	}

	return 0;
}