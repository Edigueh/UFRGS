#include <stdio.h>

#include "Queue.h"

#define N 6
// DFS is a Depth First Search.
void DFS(int graph[N][N], int node);

// BFS is a Breadth First Search.
void BFS(int graph[N][N], int node);

// greedyColoringDFS tries to assign the lowest possible color index to the current vertex with DFS.
void greedyColoringDFS(int graph[N][N], int startNode);

// greedyColoringBFS tries to assign the lowest possible color index to the current vertex with BFS.
void greedyColoringBFS(int graph[N][N], int startNode);
