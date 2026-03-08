#include "include/Graphs.h"

#define LEN 3

int main(void) {
    int graph[N][N] = {
//       0  1  2  3  4  5  6  7
        {0, 1, 1, 0, 0, 0, 0, 0}, // Node 0 connects to 1, 2
        {0, 0, 0, 1, 0, 0, 0, 0}, // Node 1 connects to 3
        {0, 0, 0, 1, 1, 0, 0, 0}, // Node 2 connects to 3, 4 
        {0, 0, 0, 0, 1, 1, 0, 1}, // Node 3 connects to 4, 5, 7
        {0, 0, 0, 0, 0, 0, 0, 0}, // Node 4 has no connections
        {0, 0, 0, 0, 1, 0, 0, 0}, // Node 5 connects to 2, 3, 4
        {0, 1, 0, 0, 0, 0, 0, 0}, // Node 6 connects to 1
        {0, 0, 0, 0, 0, 0, 1, 0}  // Node 7 connects to 6
    };

    int test[LEN] = {0, 2, 4};

    for (int i = 0; i < LEN; i++) {
        printf("DFS traversal starting from %d\n", test[i]);
        DFS(graph, test[i]);
        printf("\n\n");
    }

    printf("================================\n\n");
    for (int i = 0; i < LEN; i++) {
        printf("BFS traversal starting from %d\n", test[i]);
        BFS(graph, test[i]);
        printf("\n\n");
    }
}
