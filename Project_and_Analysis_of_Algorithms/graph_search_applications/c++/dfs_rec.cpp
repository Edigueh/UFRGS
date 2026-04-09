#include "graphs.h"

// initVisited maps all nodes as unvisited.
visitedMap(string) initVisited(adjacencyMap(string) graph) {
    visitedMap(string) visited;
    for (auto const&[node, neighbous] : graph) {
        visited[node] = false;
    }
    return visited;
}

// Recursive depth first search from the starting node using a queue.
void dfs(adjacencyMap(string) graph, string node, visitedMap(string) *visited) {
    (*visited)[node] = true;
    cout << node << "\n"; // Process Node.

    for (string neighbour: graph[node]){
        if (!(*visited)[neighbour]) {
            dfs(graph, neighbour, visited);
        }
    }
}

int main(void) {
    visitedMap(string) visited = initVisited(G1);
    dfs(G1, "A", &visited);
    return EXIT_SUCCESS;
}
