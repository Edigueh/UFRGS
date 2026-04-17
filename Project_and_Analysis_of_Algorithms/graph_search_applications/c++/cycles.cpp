#include "graphs.h"

bool dfsCycle(adjacencyMap(string) g, string node, string parent, visitedMap(string) &visited) {
    visited[node] = true;
    for(string neighbour : g[node]) {
        if (!visited[neighbour]) {
            if(dfsCycle(g, neighbour, node, visited))
                return true;
        } else if(neighbour != parent)
            return true;
    }
    return false;
}

// Topological sort for DAGs using BGS (Kahn algorithm).
vector<string> topoSortKahn(adjacencyMap(string) g) {
    // Input degrees.
    map<string, int> inDeg; for(auto const&[node, _] : g) inDeg[node] = 0;
    
    // Node inputs at neighbour.
    for(auto const&[node, _] : g) {
        for (string neighbour : g[node]) inDeg[neighbour] += 1;
    }
    // Source nodes list.
    queue<string> q;
    
    //Output nodes order.
    vector<string> order;

    // Inits q with nodes with input degree equals 0.
    for(auto const&[node, _] : g) {
        if (inDeg[node] == 0) q.push(node);
    }

    while(!q.empty()) {
        string curNode = q.front(); q.pop();
        order.push_back(curNode);
        for (string neighbour : g[curNode]) {
            inDeg[neighbour]--;
            // If input degree is 0, it will be a source node.
            if(inDeg[neighbour] == 0) q.push(neighbour);
        }
    }

    return order;
}

// Detects if a given simple undirected graph has a cycle using DFS.
bool hasCycle(adjacencyMap(string) g) {
    visitedMap(string) visited = initVisited(g);
    for(auto const& [node, _] : g) {
        if(!visited[node])
            if (dfsCycle(g, node, "-1", visited))
                return true;
    }
    return false;
}

// Cycle detection in a digraph using Kahn's algorithm.
bool hasCycleKahn(adjacencyMap(string) g) {
    // If the graph has a cycle, the nodes in that cycle will never reach in-degree 0,
    // so they'll never be enqueued and never appear in the output of topoSortKahn.
    // TLDR: Did Kahn's algorithm manage to process all nodes?
    // If not, some nodes were trapped in a cycle.
    if(topoSortKahn(g).size() != g.size())
        return true;
    return false;
}

int main(void) {
    cout << hasCycle(G1) << "\n";
    cout << hasCycleKahn(G1) << "\n";
    cout << hasCycleKahn(G3) << "\n";
    return EXIT_SUCCESS;
}
