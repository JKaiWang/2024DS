#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
#define INF -1 // For the maximum spanning tree, we'll treat -1 as infinity.

// Function to read input
void readInput(int *n, int adjacencyMatrix[MAX_N][MAX_N]) {
    int i, j;
    // Read the number of nodes
    scanf("%d", n);
    // Read the adjacency matrix
    for (i = 0; i < *n; i++) {
        for (j = 0; j < *n; j++) {
            scanf("%d", &adjacencyMatrix[i][j]);
        }
    }
}

// Function to output results
void outputResult(int cost, int edgeCount, int edges[MAX_N][2]) {
    int i;
    // Output total weight
    printf("%d\n", cost);

    // Output edges
    for (i = 0; i < edgeCount; i++) {
        printf("(%d,%d) ", edges[i][0], edges[i][1]);
    }
    printf("\n");
}

// Prim's algorithm to find the maximum cost spanning tree
void findMaxSpanningTree(int n, int adjacencyMatrix[MAX_N][MAX_N], int *cost, int *edgeCount, int edges[MAX_N][2]) {
    int inMST[MAX_N] = {0};       // Tracks nodes included in MST
    int maxWeight[MAX_N];         // Maximum weight edge for each node
    int parent[MAX_N];            // Parent of each node in MST
    int i, j;

    // Initialize all nodes with maxWeight = -1 (unreachable) and parent = -1
    for (i = 0; i < n; i++) {
        maxWeight[i] = INF;
        parent[i] = -1;
    }

    // Start from node 0
    maxWeight[3] = 0;
    *cost = 0;
    *edgeCount = 0;

    // Process n nodes
    for (i = 0; i < n; i++) {
        int maxW = INF;
        int u = -1;

        // Find the node with the maximum weight edge that is not in the MST
        for (j = 0; j < n; j++) {
            if (!inMST[j] && maxWeight[j] > maxW) {
                maxW = maxWeight[j];
                u = j;
            }
        }

        // Add the selected node to the MST
        inMST[u] = 1;
        *cost += maxW;

        // Record the edge (parent[u], u)
        if (parent[u] != -1) {
            edges[*edgeCount][0] = parent[u];
            edges[*edgeCount][1] = u;
            (*edgeCount)++;
        }

        // Update the maxWeight array for neighbors of the selected node
        for (j = 0; j < n; j++) {
            if (!inMST[j] && adjacencyMatrix[u][j] > maxWeight[j]) {
                maxWeight[j] = adjacencyMatrix[u][j];
                parent[j] = u;
            }
        }
    }
    for(i=0;i<n;i++){
        printf("%d ",parent[i]);
    }printf("\n");
    for(i=0;i<n;i++){
        printf("%d ",maxWeight[i]);
    }printf("\n");
}

int main() {
    int n;
    int adjacencyMatrix[MAX_N][MAX_N];
    int edges[MAX_N][2];     // Stores the selected edges
    int edgeCount = 0;
    int cost = 0;

    readInput(&n, adjacencyMatrix);
    findMaxSpanningTree(n, adjacencyMatrix, &cost, &edgeCount, edges);
    outputResult(cost, edgeCount, edges);

    return 0;
}