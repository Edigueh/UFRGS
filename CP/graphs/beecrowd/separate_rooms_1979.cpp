#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ar array
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define F first
#define S second
#define all(x) x.begin(), x.end()
#define loop(it, start, end) for(int it = start; it < end; it++)
#define adjacencyMap(type) map<type, set<type>>
#define visitedMap(type) map<type, bool>

void readAndFillGraph(int tc, adjacencyMap(int) *graph) {
    for (int i = 1; i <= tc; i++) (*graph)[i] = {};
    while(tc--) {
        int node;
        cin >> node;
        cin.ignore();
        string line;
        set<int> nodeneighbours;
        if(getline(cin, line)) {
            istringstream iss(line);
            int neighbour;

            while(iss >> neighbour) {
                nodeneighbours.insert(neighbour);
            }
        }

        (*graph)[node] = nodeneighbours;
        for(int neighbour : nodeneighbours) {
            (*graph)[neighbour].insert(node);
        }

        nodeneighbours.clear();
    }
}

// initVisited maps all nodes as unvisited.
visitedMap(int) initVisited(adjacencyMap(int) graph) {
    visitedMap(int) visited;
    for (auto const&[node, neighbous] : graph) {
        visited[node] = false;
    }
    return visited;
}

bool isBipartite(adjacencyMap(int) graph) {
    visitedMap(int) visited = initVisited(graph);
    map<int, bool> color = visited;
    
    // Choses a node for each component.
    for(auto const&[node, neighbours] : graph) {
        if (visited[node]) continue;

        // Starts a search queue for a specific node. 
        queue<int> q; q.push(node);

        // Attribute color 1 to the node,
        color[node] = true;
        visited[node] = true;
        while(!q.empty()) {
            int curNode = q.front(); q.pop();
            for (int neighbour : graph[curNode]) {
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

void solve(int tc) {
    adjacencyMap(int) graph;
    
    readAndFillGraph(tc, &graph);
    
    if (isBipartite(graph)) {
        cout << "SIM\n";
    } else {
        cout << "NAO\n";
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int tc;
    cin >> tc;
    while(tc != 0){
        solve(tc);
        cin >> tc;
    }
}
