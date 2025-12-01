#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Graphs.h"

void dfs(int graph[N][N], int visited[N], int node) {
    visited[node] = 1;

    printf("%d ", node);

    for (int adj = 0; adj < N; adj++) {
        if (!visited[adj] && graph[node][adj]) {
            dfs(graph, visited, adj);
        }
    }
}

void bfs(int graph[N][N], int visited[N], Queue *queue, int startNode) {
    visited[startNode] = 1;
    enqueue(&queue, startNode);

    while(!isEmpty(queue)) {
        int currentNode;
        dequeue(&queue, &currentNode);
        printf("%d ", currentNode);
        for (int adj = 0; adj < N; adj++) {
            if (!visited[adj] && graph[currentNode][adj]) {
                enqueue(&queue, adj);
                visited[adj] = 1;
            }
        }
    }
}

void DFS(int graph[N][N], int node) {
    int visited[N] = {0};
    dfs(graph, visited, node);
}

void BFS(int graph[N][N], int startNode) {
    int visited[N] = {0};
    bfs(graph, visited, initQueue(), startNode);
}

// Helper function to color a single vertex
int colorVertex(int graph[N][N], int *colors, int vertex) {
    bool available[N];
    
    // Initialize all colors as available
    for (int i = 0; i < N; i++) {
        available[i] = true;
    }
    
    // Mark colors of adjacent vertices as unavailable
    for (int adj = 0; adj < N; adj++) {
        if (graph[vertex][adj] && colors[adj] != -1) {
            available[colors[adj]] = false;
        }
    }
    
    // Find the first available color
    for (int color = 0; color < N; color++) {
        if (available[color]) {
            return color;
        }
    }
    
    return 0;
}

// DFS helper with inline coloring
void dfsColoring(int graph[N][N], int *visited, int *colors, int node, int *order, int *index) {
    visited[node] = 1;
    
    // Color the current vertex
    colors[node] = colorVertex(graph, colors, node);
    printf("Visiting Vertex %d -> Color %d\n", node+1, colors[node]+1);
    
    // Add to visit order
    order[(*index)++] = node;
    
    // Visit adjacent vertices
    for (int adj = 0; adj < N; adj++) {
        if (!visited[adj] && graph[node][adj]) {
            dfsColoring(graph, visited, colors, adj, order, index);
        }
    }
}

// BFS helper with inline coloring
void bfsColoring(int graph[N][N], int *visited, int *colors, Queue *queue, int startNode, int *order, int *index) {
    visited[startNode] = 1;
    colors[startNode] = colorVertex(graph, colors, startNode);
    printf("Visiting Vertex %d -> Color %d\n", startNode+1, colors[startNode]+1);
    order[(*index)++] = startNode;
    enqueue(&queue, startNode);
    
    while (!isEmpty(queue)) {
        int currentNode;
        dequeue(&queue, &currentNode);
        
        for (int adj = 0; adj < N; adj++) {
            if (!visited[adj] && graph[currentNode][adj]) {
                visited[adj] = 1;
                colors[adj] = colorVertex(graph, colors, adj);
                printf("Visiting Vertex %d -> Color %d\n", adj+1, colors[adj]+1);
                order[(*index)++] = adj;
                enqueue(&queue, adj);
            }
        }
    }
}

void greedyColoringDFS(int graph[N][N], int startNode) {
    int visited[N] = {0};
    int colors[N];
    int order[N];
    int index = 0;
    
    // Initialize all colors as -1 (uncolored)
    for (int i = 0; i < N; i++) {
        colors[i] = -1;
    }
    
    printf("DFS Greedy Coloring starting from node %d:\n", startNode);
    dfsColoring(graph, visited, colors, startNode, order, &index);
    
    // Color disconnected vertices
    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            dfsColoring(graph, visited, colors, i, order, &index);
        }
    }
    
    int maxColor = 0;
    for (int i = 0; i < N; i++) {
        if (colors[i] > maxColor) maxColor = colors[i];
    }
    printf("Total colors used: %d\n\n", maxColor + 1);
}

// Greedy coloring with BFS
void greedyColoringBFS(int graph[N][N], int startNode) {
    int visited[N] = {0};
    int colors[N];
    int order[N];
    int index = 0;
    
    // Initialize all colors as -1 (uncolored)
    for (int i = 0; i < N; i++) {
        colors[i] = -1;
    }
    
    printf("BFS Greedy Coloring starting from node %d:\n", startNode);
    bfsColoring(graph, visited, colors, initQueue(), startNode, order, &index);
    
    // Color disconnected vertices
    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            bfsColoring(graph, visited, colors, initQueue(), i, order, &index);
        }
    }
    
    int maxColor = 0;
    for (int i = 0; i < N; i++) {
        if (colors[i] > maxColor) maxColor = colors[i];
    }
    printf("Total colors used: %d\n\n", maxColor + 1);
}
