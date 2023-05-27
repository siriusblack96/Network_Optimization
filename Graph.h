#pragma once
#include<queue>


const int nNodes = 5000;

// Struct to create the Neigbors of each node
typedef struct node {

	int id;
	int weight;
	node* next;

}vertex;
// change#1 imported from kheap.h
#ifndef EDGES
#define EDGES
typedef struct edge {
	std::pair<int, int> nodes;
	int weight;
	int position;
}edge;
#endif
class Graph{

	bool type;
	int seed;
public:
	// change#2 imported from kheap.h
	int lastElementPos;
	//int countDuplEdges;

	//edge* heapArray; // heap array
	//edge* sortedArray; // sorted array, we can use the heap array to reduce the space complexity
	edge* collectorArray; // Two times the heap array since we collect an edge two times
	// Constructor
	Graph(bool type, int seed);
	int nEdges;
	
	// Adjecency List
	vertex *adj[nNodes];

	// Use During the Graph construction
	int maxNeighbors; // Depends on the type of the graph
	int *numNeighbors = new int[nNodes];
	bool *connections = new bool[nNodes];
	
	// Add the edge on the graph
	void addPair(int node1, int node2, int weight);
	vertex* initNode(int node, int weight);

	// --- BFS
	int color[nNodes];
	void bfs(int node);

	// --- To check if the graph is connected
	void isConnected();

	// --- Print the graph (Recomendend only for graphs with small number of vertices)
	void printGraph();
	void printNeighbors(int node);

	void printNeigh(int node);

};

