#include "Dijkstra.h"
#include <iostream>

Dijkstra::Dijkstra() {
	for (size_t i = 0; i < nNodes; i++) {
		status[i] = 0;
		daddy[i] = -1;
		bw[i] = 0;
	}
}

void Dijkstra::arrayBased(int s, int t, vertex* adj[]) {

	// Step 1: Initialize all arrays
	for (size_t i = 0; i < nNodes; i++) {
		status[i] = 0;
		daddy[i] = -1;
		bw[i] = 0;
	}

	// Step 2: Set the status of the s node to be in-tree (2)
	status[s] = 2;

	// Step 3: For all neighbors of s, add them as fringes
	vertex* temp = adj[s];
	int nFringes = 0;
	while(temp != NULL){
		status[temp->id] = 1;
		daddy[temp->id] = s;
		bw[temp->id] = temp->weight;
		temp = temp->next;
		nFringes++;
	}

	// Step 4: for all fringes
	int v;
	while (nFringes != 0) {
		// Step 4.1:	pick the fringe v with the largest bw
		v = nodeMaxBw(); 
		status[v] = 2;
		nFringes--;

		// Step 4.2: For all neighbors of w
		temp = adj[v];
		while(temp != NULL){
			if (status[temp->id] == 0) {
				status[temp->id] = 1;
				bw[temp->id] = std::min(bw[v], temp->weight);
				daddy[temp->id] = v;
				nFringes++;
			}
			else if (status[temp->id] == 1 && bw[temp->id] < std::min(bw[v], temp->weight)) {
				bw[temp->id] = std::min(bw[v], temp->weight);
				daddy[temp->id] = v;
			}
			temp = temp->next;
		}

	}

	std::cout << "Maximum Bandwidth is: " << bw[t] << std::endl;
}


int Dijkstra::nodeMaxBw() {
	int maxBw = 0;
	int node;
	for (size_t i = 0; i < nNodes; i++)
		// If the status of the node is fringe check the bw
		if (status[i] == 1)
			if (bw[i] > maxBw) {
				maxBw = bw[i];
				node = i;
			}

	return node;
}






// === The code is roughly the same, we highlight the differences
void Dijkstra::heapBased(int s, int t,  vertex *adj[]) {

	// Step 1: Initialize all arrays
	for (size_t i = 0; i < nNodes; i++) {
		status[i] = 0;
		daddy[i] = 0;
		bw[i] = 0;
	}

	// Step 1.1 Create heap
	DijkstraHeap heap;

	// Step 2: Set the status of the s node to be in-tree (2)
	status[s] = 2;

	// Step 3: For all neighbors of s
	int nFringes = 0;
	vertex* temp = adj[s];
	while(temp != NULL) {
		status[temp->id] = 1;
		daddy[temp->id] = s;
		bw[temp->id] = temp->weight;
		
		// ============================== Change{
		heap.insertNode(temp->id, temp->weight);
		// ============================== Change}

		temp = temp->next;
		nFringes++;
	}

	// Step 4: for all fringes
	int v;
	while (nFringes != 0) {

		// ============================== Changes{
		// Step 4.1: pick the fringe v of the largest bw
		v = heap.nodeID[0];
		// Step 4.2:  delete this node from the heap
		heap.deleteNode(v);
		// ============================== Changes}

		status[v] = 2;
		nFringes--;

		// Step 4.2: For all neighbors of w
		temp = adj[v];
		while(temp != NULL) {
			if (status[temp->id] == 0) {
				status[temp->id] = 1;
				bw[temp->id] = std::min(bw[v], temp->weight);
				daddy[temp->id] = v;
				nFringes++;
				// ============================== Changes{
				heap.insertNode(temp->id, bw[temp->id]);
				// ============================== Changes}
			}
			else if (status[temp->id] == 1 && bw[temp->id] < std::min(bw[v], temp->weight)) {
				bw[temp->id] = std::min(bw[v], temp->weight);
				daddy[temp->id] = v;
				// ============================== Changes{
				heap.deleteNode(temp->id);
				heap.insertNode(temp->id, bw[temp->id]);
				// ============================== Changes}
			}
			temp = temp->next;
		}

	}

	std::cout << "Maximum Bandwidth is: " << bw[t] << std::endl;
}
