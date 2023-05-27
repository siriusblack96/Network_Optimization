#pragma once
#include "DijkstraHeap.h"
class Dijkstra {



public:

	// Constructor
	Dijkstra();

	// To store the status, daddy and bandwidth of a node
	int status[nNodes];
	int daddy[nNodes];
	int bw[nNodes];

	// Dijkstra Implementation with O(n^2) complexity
	void arrayBased(int s, int t, vertex* adj[]);
	int nodeMaxBw();

	// Dijkstra Implementation with O(mlogn) complexity, using heap
	void heapBased(int s, int t, vertex* adj[]);

};
