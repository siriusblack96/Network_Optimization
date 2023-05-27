#pragma once
#include "Graph.h"
class DijkstraHeap
{
public:

	// Constructor
	DijkstraHeap();
	
	// Variables
	int nCurrNodes = 0;
	int nodeID[nNodes];
	int valueNodes[nNodes];
	int posInHeap[nNodes];

	// For the functionalities of the heap
	void insertNode(int node, int value);
	void deleteNode(int node);
	void heapify(bool up, int node);
	void swapAll(int node1, int node2);

	// Functions for Debugging
	void printIdxNodes();
	void printValuesNodes();
	void printposInTheHeap();
	void print();
};

