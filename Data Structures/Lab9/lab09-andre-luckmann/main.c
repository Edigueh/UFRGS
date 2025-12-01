#include "include/Graphs.h"

#define LEN 1

int main(void) {
    int graph[N][N] = {
//       1  2  3  4  5  6
        {0, 1, 0, 0, 0, 1}, // Node 1 connects to 2, 6
        {1, 0, 1, 1, 0, 0}, // Node 2 connects to 1, 3, 4 
        {0, 1, 0, 1, 1, 0}, // Node 3 connects to 2, 4, 5
        {0, 1, 1, 0, 1, 1}, // Node 4 connects to 2, 3, 5, 6
        {0, 0, 1, 1, 0, 1}, // Node 5 connects to 3, 4, 6
        {1, 0, 0, 1, 1, 0}, // Node 6 connects to 1, 4, 5
    };


    greedyColoringDFS(graph, 3);
    printf("\n\n");

    greedyColoringBFS(graph, 3);
}
