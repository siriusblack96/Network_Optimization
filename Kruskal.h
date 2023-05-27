#pragma once
#include<utility>
#include "KruskalHeap.h"
#include "Graph.h"

class Kruskal{
	
	int  numEdges;
	bool type;

public:
	KruskalHeap *maxHeap;
	Kruskal(Graph  g);

	vertex *maxTree[nNodes];
	
	int lastElement = 0;
	int *color = new int[nNodes];
	int *parent = new int[nNodes];
	int *rank = new int[nNodes];
	int *daddy = new int[nNodes];
	int *capacityInTree = new int[nNodes];


	// Function to find the Maximum Spanning Tree using Kruskal's
	void maxBandwidth(vertex* adj[], int s, int t);

	// For collecting and Sorting the edges
	void collectAndSort(vertex* adj[]);
	void collect(vertex* adj[]);
	void addPair(int node1, int node2, int weight);
	vertex* initNode(int node, int weight);
	
	// For disjoint sets
	int find(int node);
	void unionFuc(int r1, int r2);
	void makeSet(int node);

	// To find the maximum bandwidth in the maximum spanning tree	
	void findMaxAndPath(int s, int t);
	void bfs(int node);

};

