#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <list>
#include "Hash.h"

class graph {

public:

	// Default constructor
	// Initializes graph with no nodes or edges
	graph();

	// Checks if the graph contains specified vertex
	bool contains(std::string);

	// Inserts vertex into the graph
	// Returns 0 on success
	// 1 if the vertex already exists in the graph
	// 2 if there is some other error
	int insertVertex(std::string);

	// Execute Dijkstra's algorithm on the graph
	// Rearranges the state of the graph according to the algorithm
	void dijkstra(std::string);

private:

	// vertex class
	// Represents a vertex in the graph
	class vertex {
	public:
		// edge struct
		// Represents an edge in the graph with a destination and a cost
		class edge {
		public:
			edge(vertex *, int);

			vertex * destinaion;
			int cost;
		};

		vertex(std::string);
		
		std::string id;
		std::list<edge> adjacentEdges;
	};

	hashTable vertexLookup;
	std::list<vertex *> vertexList;

};

#endif