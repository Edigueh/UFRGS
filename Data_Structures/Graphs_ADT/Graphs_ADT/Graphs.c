#include <limits.h>
#include <stdlib.h>

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

// Helper function to find the vertex with the minimum distance value
// from the set of vertices not yet included in the shortest path tree
int minDistance(int *dist, int *visited) {
    int min = INT_MAX; 
    int min_index = -1;

    for (int v = 0; v < N; v++) {
        if (visited[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

void dijkstra(int graph[N][N], int startNode) {
    int *dist = (int *)malloc(N * sizeof(int));
    int *visited = (int *)calloc(N, sizeof(int));
    
    if (!dist || !visited) {
        printf("Memory allocation failed\n");
        return;
    }

    for (int i = 0; i < N; i++) {
        dist[i] = INT_MAX; // Set all distances to Infinity
    }
    dist[startNode] = 0;   // Distance to self is 0

    // 3. Main Loop
    // Iterate for all vertices except the last one (automatically handled)
    for (int count = 0; count < N - 1; count++) {
        
        // Pick the minimum distance vertex from the set of unvisited vertices
        int u = minDistance(dist, visited);

        // If u is -1, remaining nodes are unreachable
        if (u == -1) break;

        // Mark the picked vertex as processed
        visited[u] = 1;

        // Relax: Update dist value of the adjacent vertices of the picked vertex
        for (int v = 0; v < N; v++) {
            // Check if:
            // 1. 'v' is not visited
            // 2. There is an edge from u to v (graph[u][v] != 0)
            // 3. Total weight is smaller than current dist[v]
            // 4. Check for overflow (dist[u] != INT_MAX)
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX 
                && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printf("Vertex \t Distance from Source %d\n", startNode);
    for (int i = 0; i < N; i++) {
        if (dist[i] == INT_MAX) {
            printf("%d \t INF\n", i);
        } else {
            printf("%d \t %d\n", i, dist[i]);
        }
    }

    free(dist);
    free(visited);
}

void printSolution(int *colors) {
    printf("Vertex Coloring Result:\n");
    int maxColor = 0;
    for (int i = 0; i < N; i++) {
        printf("Vertex %d -> Color %d\n", i, colors[i]);
        if (colors[i] > maxColor) maxColor = colors[i];
    }
    // Chromatic number found by this heuristic
    printf("Total colors used (Chromatic Number approximation): %d\n", maxColor + 1); 
}

// greedyColoring tries to assign the lowest possible color index to the current vertex.
// 'order' allows you to pass vertices in BFS or DFS order.
void greedyColoring(int graph[N][N], int *order) {
    int *colors = malloc(N * sizeof(int));
    bool *available = malloc(N * sizeof(bool)); // Tracks available colors

    // Initialize all vertices as uncolored (-1)
    for (int i = 0; i < N; i++) {
        colors[i] = -1;
    }

    // Assign color to the first vertex in the specified order
    colors[order[0]] = 0;

    // Process remaining vertices
    for (int i = 1; i < N; i++) {
        int u = order[i]; // Get the actual vertex index from the order array

        // 1. Reset available colors to true
        for (int cr = 0; cr < N; cr++) {
            available[cr] = true;
        }

        // 2. Mark colors used by adjacent neighbors as unavailable
        for (int v = 0; v < N; v++) {
            // If there is an edge and 'v' is already colored
            if (graph[u][v] && colors[v] != -1) {
                available[colors[v]] = false;
            }
        }

        // 3. Find the first available color
        int cr;
        for (cr = 0; cr < N; cr++) {
            if (available[cr]) {
                break;
            }
        }

        colors[u] = cr; // Assign the found color
    }

    printSolution(colors);

    free(colors);
    free(available);
}

// Find One Maximal Independent Set.
void findCVIM(int graph[N][N]) {
    bool *inSet = calloc(N, sizeof(bool)); // 0 = false
    
    // Greedy approach to find a maximal independent set
    for (int u = 0; u < N; u++) {
        bool canAdd = true;
        
        // Check if 'u' connects to anyone currently in the Set
        for (int v = 0; v < N; v++) {
            if (inSet[v] && graph[u][v]) {
                canAdd = false;
                break;
            }
        }
        
        if (canAdd) {
            inSet[u] = true;
        }
    }

    printf("\nMaximal Independent Set (CVIM) found: { ");
    for (int i = 0; i < N; i++) {
        if (inSet[i]) printf("%d ", i);
    }
    printf("}\n");
    
    free(inSet);
}
