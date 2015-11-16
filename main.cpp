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
#include "Graph.h"

using namespace std;

int main() {

	// Get graph from output file
	cout << "Enter the name of an input file: ";
	string inputFileName;
	cin >> inputFileName;
	graph g = graph::generateFromFile(inputFileName);

	// Get starting vertex name
	cout << "Enter a valid vertex name for the starting vertex: ";
	string startingVertexName;
	cin >> startingVertexName;

	// Execute Dijkstra's Algorithm
	g.shortestPathDijkstra(startingVertexName);

	// Write graph to output file
	cout << "Enter the name of an output file: ";
	string outputFileName;
	cin >> outputFileName;
	g.writeToFile(outputFileName);

	system("pause");
	return 0;
}