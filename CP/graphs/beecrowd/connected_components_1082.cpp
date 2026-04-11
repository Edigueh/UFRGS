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
const string alpha = "abcdefghijklmnopqrstuvwxyz";

// initVisited maps all nodes as unvisited.
visitedMap(char) initVisited(adjacencyMap(char) graph) {
    visitedMap(char) visited;
    for (auto const&[node, neighbous] : graph) {
        visited[node] = false;
    }
    return visited;
}

adjacencyMap(char) buildGraph() {
    int v, e;
    cin >> v >> e;
    adjacencyMap(char) graph; for(int i = 0; i < v; i++) graph[alpha[i]] = {};

    while(e--) {
        char a, b;
        cin >> a >> b;
        graph[a].insert(b);
        graph[b].insert(a);
    }

    return graph;
}

set<char> bfs(adjacencyMap(char) graph, char startNode, visitedMap(char) *visited) {
    set<char> component;
    queue<char> q;
    q.push(startNode);
    (*visited)[startNode] = true;
    component.insert(startNode);

    while(!q.empty()) {
        char curNode = q.front(); q.pop();
        for(char neighbour : graph[curNode]) {
            if((*visited)[neighbour]) continue;

            q.push(neighbour);
            (*visited)[neighbour] = true;
            component.insert(neighbour);
        }
    }

    return component;
}

void solve(int tc) {
    adjacencyMap(char) graph = buildGraph();
    visitedMap(char) visited = initVisited(graph);
    set<set<char>> components;

    for(auto const&[node, _] : graph) {
        if (!visited[node]) {
            set<char> component = bfs(graph, node, &visited);
            components.insert(component);
        }
    }

    cout << "Case #" << tc << ":\n";
    for(auto component : components) {
        for (char node : component) {
            cout << node << ",";
        }
        cout << "\n";
    }
    cout << components.size() << " connected components\n\n";
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int tc, i = 1;
    cin >> tc;
    while(tc--) {
        solve(i);
        i++;
    }
}
