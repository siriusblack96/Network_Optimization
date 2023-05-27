#include "Graph.h"
#include "Kruskal.h"
#include <random>
#include <iostream>


Graph::Graph(bool type, int seed) {
	lastElementPos = -1;
	collectorArray = new edge[3000000];
	
	// Initialization of the randomness of RNG
	std::mt19937 generator(seed);
	std::uniform_int_distribution<int> genNeighbors(0, nNodes - 1);
	std::uniform_int_distribution<int> genCapacity(1, 10000);


	// Initialize the three arrays
	for (size_t i = 0; i < nNodes; i++) {
		numNeighbors[i] = 0;
		connections[i] = 0;
		color[i] = 0;
		adj[i] = NULL;
	}

	nEdges = 0;

	std::cout << "\n=== Create Graph ===\n\n";
	if (!type) {
		maxNeighbors = 6;
		// Since the graph is sparse, we create a cycle contain all nodes to make sure that the graph will be connected
		// Create a cycle
		for (size_t i = 0; i < nNodes - 1; i++) {
			addPair(i, i + 1, genCapacity(generator));
		}

		// Connect the last node with the first node
		addPair(nNodes - 1, 0, genCapacity(generator));
	}
	else {
		// maxNeighbors for each node (Approximately)
		maxNeighbors = 1000;
	}

	std::queue<int> q;
	// === Construct the graph
	// For all nodes
	int aveDegre = 0;
	int i = 0;
	while (aveDegre / (nNodes) < maxNeighbors) {
		// Step 0: Set that i node is "connected" to itself, and push it into the queue
		connections[i] = 1;
		q.push(i);

		// Step 1: Check who is neighbor with i
		node* temp = adj[i];
		while(temp != NULL){
			connections[temp->id] = 1;
			q.push(temp->id);
			temp = temp->next;
		}

	
		// Step 2: Add neighbors to this node
		if (numNeighbors[i] < maxNeighbors){
			int neighbor;
			for (size_t j = 0; j < maxNeighbors - numNeighbors[i]; j++) {
				// Step 2.1: Create a new Neighbor
				do {
					neighbor = genNeighbors(generator);
				} while (connections[neighbor] || numNeighbors[neighbor]>= maxNeighbors );

				q.push(neighbor);
				connections[neighbor] = 1;
				// Step 2.2: Generate the capacity between this two nodes and add the pair to the graph
				addPair(i, neighbor, genCapacity(generator));
			}
		}

		// Step 3: Empty queue and initialize the connections with all zeros
		while (!q.empty()) {
			connections[q.front()] = 0;
			q.pop();
		}
		
		aveDegre += numNeighbors[i];
		i = (i + 1) % nNodes;
	}


	// Compute the average degree of a node
	std::cout << "\nAverage Degree = " << aveDegre / (nNodes) << std::endl;
	isConnected();
}


void Graph::addPair(int node1, int node2, int weight) {
	//change#4 now inserting in heap
	lastElementPos++;
	edge newEdge;
	std::pair<int, int> p;
	p.first = node1;
	p.second = node2;
	newEdge.nodes = p;
	newEdge.weight = weight;
	newEdge.position = lastElementPos;

	// Insert the edge struct to the heap
	collectorArray[lastElementPos] = newEdge;

	// Initialize nodes
	vertex *v1 = initNode(node1, weight);
	vertex *v2 = initNode(node2, weight);

	//Connect node1 -> node2
	vertex *temp = adj[node1];
	v2->next = temp;
	adj[node1] = v2;

	//Connect node2 -> node1
	vertex *temp2 = adj[node2];
	v1->next = temp2;
	adj[node2] = v1;

	numNeighbors[node2]++;
	numNeighbors[node1]++;
	nEdges++;

}

vertex* Graph::initNode(int node, int weight) {

	vertex *newNode = new vertex();
	newNode->id = node;
	newNode->weight = weight;
	newNode->next = NULL;
	return newNode;

}


void Graph::bfs(int node) {
	// Step 1: Create a queue and push node to queue
	std::queue<int> q;
	q.push(node);

	// Step 2: set the value of the node to be black
	color[node] = 2;

	int u;
	// Iterate
	while (!q.empty()) {
		u = q.front();
		q.pop();

		vertex *temp = adj[u];
		while (temp != NULL) {
			if (color[temp->id] == 0) {
				q.push(temp->id);
				color[temp->id] = 2;
			}
			temp = temp->next;
		}

	}


}


void Graph::isConnected() {

	for (size_t i = 0; i < nNodes; i++)
		color[i] = 0;

	bfs(0);

	for (size_t i = 0; i < nNodes; i++) {
		if (color[i] == 0) {
			std::cout << "Graph is not connected\n";
			return;
		}
	}

	std::cout << "Graph is connected\n";

}



void Graph::printGraph() {
	for (size_t i = 0; i < nNodes; i++) {
		std::cout << "\n\n====== Neighbors of " << i << " are the following ======\n";
		printNeighbors(i);
	}
}



void Graph::printNeighbors(int node) {
	vertex* temp = adj[node];
	while (temp != NULL) {
		std::cout << "Node: " << temp->id << " with Capacity: " << temp->weight << std::endl;
		temp = temp->next;
	}
}

void Graph::printNeigh(int node) {
	vertex* temp = adj[node];
	int cnt = 0;
	while (temp != NULL) {
		cnt++;
		temp = temp->next;
	}
	std::cout << cnt << std::endl;
	if (cnt == 6)std::cout << "Yes";
	else std::cout << "No";
	std::cout << std::endl;
}
