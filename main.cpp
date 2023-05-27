#include <iostream>
#include "Graph.h"
#include "MaxHeap.h"
#include "Kruskal.h"
#include "Dijkstra.h"
#include<chrono>
#include <random>


int main(){
	// --- Initialize the random generator
	int seed2 = 0;
	int seed = 0;

	std::mt19937 generator(seed2);
	std::uniform_int_distribution<int> sourceDesti(0, 5000 - 1);

	// --- Pick at random the source and destination vertices
	int source = sourceDesti(generator);
	int target = sourceDesti(generator);
	std::cout << "Problem MaxBandwidth from: " << source << " to " << target << ", using seed: " << seed << std::endl;

	// --- Creater Graph, Dijkstra's and Kruskal's objects
	Graph G(0, seed);
	Dijkstra dAlgo;
	Kruskal kAlgo(G);

	// --- Kruskal 
	std::cout << "\n=== Kruskal ===";
	auto start = std::chrono::high_resolution_clock::now();
	kAlgo.maxBandwidth(G.adj, source, target);
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << "\nTotal Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms";

	// --- Dijkstra, array based
	std::cout << "\n\n=== Simple ===\n";
	start = std::chrono::high_resolution_clock::now();
	dAlgo.arrayBased(source, target, G.adj);
	end = std::chrono::high_resolution_clock::now();
	std::cout << "Total Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms";

	// --- Dijkstra, heap based
	std::cout << "\n\n=== Heap based ===\n";
	start = std::chrono::high_resolution_clock::now();
	dAlgo.heapBased(source, target, G.adj);
	end = std::chrono::high_resolution_clock::now();
	std::cout << "Total Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
	
	// now we try with type = 1
	Graph G1(1, seed);
	Dijkstra dAlgo1;
	Kruskal kAlgo1(G1);

	std::cout << "Problem MaxBandwidth from: " << source << " to " << target << ", using seed: " << seed << std::endl;

	//// --- Dijkstra, heap based
	std::cout << "\n\n=== Heap based ===\n";
	auto start2 = std::chrono::high_resolution_clock::now();
	dAlgo1.heapBased(source, target, G1.adj);
	auto end2 = std::chrono::high_resolution_clock::now();
	std::cout << "Total Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count() << "ms" << std::endl;

	//// --- Dijkstra, array baseds
	std::cout << "\n\n=== Simple ===\n";
	auto start1 = std::chrono::high_resolution_clock::now();
	dAlgo1.arrayBased(source, target, G1.adj);
	auto end1 = std::chrono::high_resolution_clock::now();
	std::cout << "Total Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1).count() << "ms";

	// --- Kruskal 
	std::cout << "\n=== Kruskal ===";
	auto start3 = std::chrono::high_resolution_clock::now();
	kAlgo1.maxBandwidth(G1.adj, source, target);
	auto end3 = std::chrono::high_resolution_clock::now();
	std::cout << "\nTotal Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end3 - start3).count() << "ms";	

	return 0;
}



