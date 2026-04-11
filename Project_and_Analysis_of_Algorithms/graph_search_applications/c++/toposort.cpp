#include "graphs.h"

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

void dfsRec(adjacencyMap(string) g, string startNode, visitedMap(string) &visited, vector<string> &order) {
    visited[startNode] = true;
    for (string neighbour : g[startNode]) {
        if (!visited[neighbour]) {
            dfsRec(g, neighbour, visited, order);
        }
    }
    order.push_back(startNode);
}

// Topological sorting using DFS.
vector<string> dfsTopoSort(adjacencyMap(string) g){
    visitedMap(string) visited = initVisited(g);
    vector<string> order = {};

    for (auto const&[node, _] : g) {
        if (!visited[node]) {
            dfsRec(g, node, visited, order);
        }
    }

    reverse(order.begin(), order.end());
    return order;
}

int main(void) {
    for (string node : topoSortKahn(G1)) cout << node << "\n";
    cout << "--------------\n";
    for (string node : dfsTopoSort(G1)) cout << node << "\n";
    return EXIT_SUCCESS;
}
