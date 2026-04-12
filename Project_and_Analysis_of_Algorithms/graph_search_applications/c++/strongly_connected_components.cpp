#include "graphs.h"

void dfsRec(adjacencyMap(int) g, int startNode, visitedMap(int) &visited, vector<int> &order) {
    visited[startNode] = true;
    for (int neighbour : g[startNode]) {
        if (!visited[neighbour]) {
            dfsRec(g, neighbour, visited, order);
        }
    }
    order.push_back(startNode);
}

// initVisited maps all nodes as unvisited.
visitedMap(int) initVisitedInt(adjacencyMap(int) graph) {
    visitedMap(int) visited;
    for (auto const&[node, neighbous] : graph) {
        visited[node] = false;
    }
    return visited;
}

// Topological sorting using DFS.
vector<int> dfsTopoSort(adjacencyMap(int) g){
    visitedMap(int) visited = initVisitedInt(g);
    vector<int> order = {};

    for (auto const&[node, _] : g) {
        if (!visited[node]) {
            dfsRec(g, node, visited, order);
        }
    }

    reverse(order.begin(), order.end());
    return order;
}

// Given a digraph, returns a digraph with the direction of all edges inverted.
adjacencyMap(int) reverseGraph(adjacencyMap(int) g) {
    adjacencyMap(int) revGraph; for(auto const&[node, _] : g) revGraph[node] = {};
    for(auto const&[node, neighbours] : g) {
        for (int neighbour : neighbours) {
            revGraph[neighbour].push_back(node);
        }
    }

    return revGraph;
}

void compDfs(adjacencyMap(int) g, int startNode, visitedMap(int) &visited, unordered_map<int, int> &components, int &c) {
    visited[startNode] = true;
    components[startNode] = c;

    for(int neighbour : g[startNode]) {
        if (!visited[neighbour]) {
            compDfs(g, neighbour, visited, components, c);
        }
    }
}

// Kosaraju-Shamir algorithm to find strongly connected components in a Digraph.
unordered_map<int, int> kosarajuShamir(adjacencyMap(int) g) {
    adjacencyMap(int) revGraph = reverseGraph(g);
    vector<int> order = dfsTopoSort(revGraph);

    visitedMap(int) visited = initVisitedInt(g);
    unordered_map<int, int> components = {};
    int c = 0;

    for(int node : order) {
        if (!visited[node]) {
            compDfs(g, node, visited, components, c);
            c++;
        }
    }

    return components;
} 

int main(void) {
    for (auto const&[node, comp] : kosarajuShamir(G4)) cout << node << ": " << comp << "\n";
    return EXIT_SUCCESS;
}
