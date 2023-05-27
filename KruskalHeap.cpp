#include "KruskalHeap.h"
#include<chrono>
#include<unordered_map>

KruskalHeap::KruskalHeap(int nEdges) {

	lastElementPos = -1;
	countDuplEdges = -1;
	int temp = 2 * nEdges;
	enEdges = nEdges;

	heapArray = new edge[nEdges];
	sortedArray = new edge[nEdges];
	collectorArray = new edge[temp];
}

void KruskalHeap::insertEdge(int node1, int node2, int weight) {

	// Increase the counter
	countDuplEdges++;

	// Create an edge
	edge newEdge;
	std::pair<int, int> p;
	p.first = node1;
	p.second = node2;
	newEdge.nodes = p;
	newEdge.weight = weight;
	newEdge.position = -1;
	
	// Insert the edge struct to the heap
	collectorArray[countDuplEdges] = newEdge;

	
}

void KruskalHeap::deleteDuplicates() {
	for (size_t i = 0; i < 2*enEdges; i++){

		// Keep only the edges where the id of the source is smaller than the id of the destination
		if (collectorArray[i].nodes.first < collectorArray[i].nodes.second) {
			lastElementPos++;
			collectorArray[i].position = lastElementPos;
			heapArray[lastElementPos] = collectorArray[i];
			heapify(1, heapArray[lastElementPos]);
		}
			
	}

	delete[] collectorArray;
}

void KruskalHeap::deleteDuplicates2() {
	int cnt = lastElementPos;
	lastElementPos = -1;
	int count = 0;
	for (size_t i = 0; i <= cnt; i++) {
		lastElementPos++;
		collectorArray[i].position = lastElementPos;
		heapArray[i] = collectorArray[i];
		heapify(1, heapArray[i]);
	}
	delete[] collectorArray;
}


void KruskalHeap::heapify(bool up, edge node){

	int pos = node.position;
	int parent = (pos - 1) / 2;

	int l = 2 * pos + 1;
	int r = 2 * pos + 2;

	if (up) {
		// Go up
		// Check if the node is the root
		if (pos == 0)
			return;
		else {
			// Check the parent
			if (heapArray[pos].weight > heapArray[parent].weight) {

				// Swap
				heapArray[pos].position = parent;
				heapArray[parent].position = pos;
				edge temp = heapArray[pos];
				heapArray[pos] = heapArray[parent];
				heapArray[parent] = temp;

				heapify(1, heapArray[parent]);
			}
			else
				// The node is at the correct position 
				return;
		}
	}
	else {
		//  Go down
		int child;

		if (r > lastElementPos) {

			if (l > lastElementPos)
				// The node is a leaf => done
				return;

			// Only one child
			else if (heapArray[l].weight > heapArray[pos].weight)
				child = l;
			else
				return;
		}
		// Two children
		else if (heapArray[l].weight >= heapArray[r].weight && heapArray[l].weight > heapArray[pos].weight)
			child = l;
		else if (heapArray[r].weight > heapArray[l].weight && heapArray[r].weight > heapArray[pos].weight)
			child = r;
		else
			return;

		// Swap
		heapArray[pos].position = child;
		heapArray[child].position = pos;
		edge temp = heapArray[pos];
		heapArray[pos] = heapArray[child];
		heapArray[child] = temp;
		heapify(0, heapArray[child]);
	}


}

void KruskalHeap::deleteRoot(){

	// Find the location  of the node in the heap
	int pos = 0;


	if (lastElementPos != pos) {

		// Swap
		heapArray[lastElementPos].position = 0;
		heapArray[0] = heapArray[lastElementPos];

		// Decrease the number of current nodes
		lastElementPos--;
		
		
		// Call heapify to fix everthing
		heapify(0, heapArray[pos]);
	}

}

void KruskalHeap::heapSort() {
	edge root;
	auto start5 = std::chrono::high_resolution_clock::now();
	for (size_t i = 0; i < enEdges; i++){

		// Step 1: Pick and remove the root
		root = heapArray[0];
		
		// Step 2: Insert this node to the sortedArray
		sortedArray[i] = root;

		// Step 3: Delete root
		deleteRoot();
	}
	auto end5 = std::chrono::high_resolution_clock::now();
	std::cout << "\nSort Time in K: " << std::chrono::duration_cast<std::chrono::milliseconds>(end5 - start5).count();
	delete[] heapArray;
}


// ======== Functions for Debugging
void KruskalHeap::printHeap() {
	for (size_t i = 0; i < enEdges ; i++) {
		std::cout << "\nEdge: " << i << " Node: " << heapArray[i].nodes.first << " to Node: " << heapArray[i].nodes.second << " Weight: " << heapArray[i].weight<< std::endl;
	}
}

void KruskalHeap::printColle() {
	std::cout << enEdges;
	for (size_t i = 0; i < enEdges; i++) {
		std::cout << "Edge: " << i << " Node: " << collectorArray[i].nodes.first << " to Node: " << collectorArray[i].nodes.second << std::endl;
	}
}
bool KruskalHeap::isSorted() {

	for (size_t i = 0; i < enEdges-1; i++){
		if (sortedArray[i].weight < sortedArray[i + 1].weight) {
			return 0;
		}
	}

	return 1;
}