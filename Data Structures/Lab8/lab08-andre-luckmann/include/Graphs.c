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
