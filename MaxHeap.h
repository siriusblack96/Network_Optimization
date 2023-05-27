#pragma once
#include <utility>
#include <iostream>
#include "Graph.h"

class MaxHeap
{
public:

	MaxHeap();
	void printIdxNodes();
	void printValuesNodes();
	void printposInTheHeap();
	void print();


	int nCurrNodes = 0;
	int nodeID[nNodes];
	int valueNodes[nNodes];
	int posInHeap[nNodes];

	void heapify(bool up, int node);
	void deleteNode(int node);
	void insertNode(int node, int value);
	void swapAll(int node1, int node2);



};

