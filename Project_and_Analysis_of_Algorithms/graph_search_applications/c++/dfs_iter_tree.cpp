#include "graphs.h"

#define antecessorTree(type) map<type, type>

// Iterative depth first search from the starting node using an iterative tree.
// This returns a dict mapping each node to its parent in the search.
antecessorTree(string) dfsIterTree(adjacencyMap(string) graph, string startNode) {
    visitedMap(string) visited = initVisited(graph);
    antecessorTree(string) antTree;
    for (auto const&[node, _] : graph) antTree[node] = node;
    visited[startNode] = true;
    stack<string> s;
    s.push(startNode);

    while(s.size() > 0) {
        string curNode = s.top(); s.pop();
        for (string neighbour: graph[curNode]) {
            if (!visited[neighbour]) {
                s.push(neighbour);
                antTree[neighbour] = curNode;
                visited[neighbour] = true;
            }
        }
    }

    return antTree;
}

int main(void) {
    for (auto const& [node, parent] : dfsIterTree(G1, "A")) {
        cout << node << " : " << parent << "\n";
    }
    return EXIT_SUCCESS;
}
