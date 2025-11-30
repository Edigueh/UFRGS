#include <stdio.h>

#include "Queue.h"

#define N 8
// DFS is a Depth First Search.
void DFS(int graph[N][N], int node);

// BFS is a Breadth First Search.
void BFS(int graph[N][N], int node);

// dijkstra prints the shortst distance from the startNode to all other nodes in the graph.
void dijkstra(int graph[N][N], int startNode);

// greedyColoring tries to assign the lowest possible color index to the current vertex.
// 'order' allows you to pass vertices in BFS or DFS order.
void greedyColoring(int graph[N][N], int *order);

// findCVIM prints a Maximal Independent Set in the given graph.
void findCVIM(int graph[N][N]);