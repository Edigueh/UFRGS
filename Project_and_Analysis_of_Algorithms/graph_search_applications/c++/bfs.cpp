#include "graphs.h"

// initVisited maps all nodes as unvisited.
visitedMap(string) initVisited(adjacencyMap(string) graph) {
    visitedMap(string) visited;
    for (auto const&[node, neighbous] : graph) {
        visited[node] = false;
    }
    return visited;
}

// Iterative breadth first search from the starting node using a queue.
void bfs(adjacencyMap(string) graph, string startNode, visitedMap(string) visited) {
    queue<string> q;
    q.push(startNode);
    visited[startNode] = true;

    while(!q.empty()) {
        string curNode = q.front(); q.pop();
        cout << curNode << "\n"; // Process Node.
        for (string neighbour : graph[curNode]) {
            if (!visited[neighbour]){
                q.push(neighbour);
                visited[neighbour] = true;
            }
        }
    }
}

int main(void) {
    bfs(G1, "A", initVisited(G1));
    return EXIT_SUCCESS;
}
