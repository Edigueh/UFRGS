#include "graphs.h"

bool isBipartite(adjacencyMap(string) graph) {
    visitedMap(string) visited = initVisited(graph);
    map<string, bool> color = visited;
    
    // Choses a node for each component.
    for(auto const&[node, neighbours] : graph) {
        if (visited[node]) continue;

        // Starts a search queue for a specific node. 
        queue<string> q; q.push(node);

        // Attribute color 1 to the node,
        color[node] = true;
        visited[node] = true;
        while(!q.empty()) {
            string curNode = q.front(); q.pop();
            for (string neighbour : graph[curNode]) {
                if (visited[neighbour] && color[curNode] == color[neighbour]) {
                    // Found an odd cycle (two neighbours with same color).
                    return false;
                } else if(!visited[neighbour]) {
                    // Inverts the color of the cur node based on the neighbour color.
                    color[neighbour] = !(color[curNode]);
                    visited[neighbour] = true;
                    q.push(neighbour);
                }
            }
        }
    }

    // No odd cycle was found.
    return true;
}

int main(void) {
    cout << isBipartite(G2) << "\n";
    return EXIT_SUCCESS;
}
