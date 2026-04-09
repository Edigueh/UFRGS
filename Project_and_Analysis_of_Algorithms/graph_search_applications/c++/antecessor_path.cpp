#include "graphs.h"

#define antecessorTree(type) map<type, type>


// initVisited maps all nodes as unvisited.
visitedMap(string) initVisited(adjacencyMap(string) graph) {
    visitedMap(string) visited;
    for (auto const&[node, neighbous] : graph) {
        visited[node] = false;
    }
    return visited;
}

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

// antecessorPath returns the path from the target until its ultimate antecessor.
vector<string> antecessorPath(antecessorTree(string) tree, string target) {
    string node = target;
    vector<string> path = {target};

    while (node != tree[node]) {
        node = tree[node];
        path.push_back(node);
    }

    reverse(path.begin(), path.end());

    return path;
}

int main(void) {
    for(string node : antecessorPath(dfsIterTree(G1, "A"), "G")) {
        cout << node << "\n";
    }
    return EXIT_SUCCESS;
}
