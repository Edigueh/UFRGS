#include "graphs.h"

// bfsDistance returns the distance from the startNode to every other node in the given graph.
map<string, int> bfsDistance(adjacencyMap(string) graph, string startNode, visitedMap(string) visited){
    queue<string> q;
    q.push(startNode);
    visited[startNode] = true;

    map<string, int> distances; for (auto const&[node, _] : visited) distances[node] = -1;
    distances[startNode] = 0;

    while (!q.empty()) {
        string curNode = q.front(); q.pop();
        for (string neighbour : graph[curNode]) {
            if(!visited[neighbour]) {
                q.push(neighbour);
                visited[neighbour] = true;

                distances[neighbour] = distances[curNode] + 1;
            }
        }
    }

    return distances;
}

int main(void) {
    for(auto const&[node, distance] : bfsDistance(G1, "B", initVisited(G1))) cout << node << " : " << distance << "\n";
    return EXIT_SUCCESS;
}
