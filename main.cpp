/*
*****************************************
Jason Katz
ECE-165 Project 3: Dijkstra's Algorithm

Graph implementation
with Dijkstra's algorithm built in

File: main.cpp
*****************************************
*/

#include <iostream>
#include <string>
#include <ctime>
#include "Graph.h"

using namespace std;

int main() {

	// Get graph from output file
	cout << "Enter the name of an input file: ";
	string inputFileName;
	cin >> inputFileName;
	graph g = graph::generateFromFile(inputFileName);

	// Get starting vertex name
	string startingVertexName;
	do {
		cout << "Enter a valid vertex name for the starting vertex: ";
		cin >> startingVertexName;
	} while (!g.contains(startingVertexName));

	// Set up timer
	clock_t startTime = clock();

	// Execute Dijkstra's Algorithm
	g.shortestPathDijkstra(startingVertexName);

	cout << "Total time spent executing Dijkstra's Algorithm: " << (double) (clock() - startTime) / 1000 << " seconds" << endl;

	// Write graph to output file
	cout << "Enter the name of an output file: ";
	string outputFileName;
	cin >> outputFileName;
	g.writeToFile(outputFileName);

	return 0;
}