#pragma once
#include <iostream>


// Struct to be a node of the heap
// change#1: putting edge nodes in graph.h
#ifndef EDGES
#define EDGES
typedef struct edge {

	std::pair<int, int> nodes;
	int weight;
	int position;

}edge;
#endif

class KruskalHeap{

	int enEdges;
public:

	// Constructor
	KruskalHeap(int nEdges);
	
	// chage#2: putting these fields in graph.h
	int lastElementPos;
	int countDuplEdges;

	edge* heapArray; // heap array
	edge* sortedArray; // sorted array, we can use the heap array to reduce the space complexity
	edge* collectorArray; // Two times the heap array since we collect an edge two times
	void deleteDuplicates(); // Delete the duplicates
	void deleteDuplicates2();

	// For the functionalities of the heap
	void insertEdge(int node1, int node2, int capacity);
	void heapify(bool up, edge node);
	void heapSort();
	//void heapify1(size_t n,int i);
	//void heapSort1(); //change
	void deleteRoot();

	// Functions for Debugging
	void printHeap();
	bool isSorted();
	void printColle();

};

