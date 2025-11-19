#include <stdio.h>

#include "Graphs.h"

int main(void) {
    int graph[N][N] = {
        {0, 1, 1, 0, 0, 0}, // Node 1 connects to 2, 3
        {1, 0, 0, 0, 1, 1}, // Node 2 connects to 1, 5, 6
        {1, 0, 0, 1, 0, 1}, // Node 3 connects to 1, 4, 6
        {0, 0, 1, 0, 0, 1}, // Node 4 connects to 3, 6
        {0, 1, 0, 0, 0, 0}, // Node 5 connects to 2
        {0, 1, 1, 1, 0, 0}  // Node 6 connects to 2, 3, 4
    };

    printf("DFS traversal\n");
    DFS(graph, 0);
    printf("\n");

    printf("BFS traversal\n");
    BFS(graph, 0);
    printf("\n");
}
