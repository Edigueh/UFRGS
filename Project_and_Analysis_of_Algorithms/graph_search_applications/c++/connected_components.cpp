#include "graphs.h"

void dfs(adjacencyMap(string) graph, string startNode, visitedMap(string) &visited, map<string, int> &comp, int c) {
    visited[startNode] = true;
    comp[startNode] = c;
    for (string neighbour : graph[startNode]) {
        if (!visited[neighbour]) {
            dfs(graph, neighbour, visited, comp, c);
        }
    }
}

// Returns the connected components in a simple graph.
map<string, int> components(adjacencyMap(string) graph) {
    map<string, int> comp = {};
    int c = 0;
    visitedMap(string) visited = initVisited(graph);

    for (auto const&[node, _] : graph) {
        if (!visited[node]) {
            dfs(graph, node, visited, comp, c);
            c++;
        }
    }

    return comp;
}

int main(void) {
    for (auto const&[node, val] : components(G2)) {
        cout << node << ": " << val << "\n";
    }
    return EXIT_SUCCESS;
}
