#include <bits/stdc++.h>
using namespace std;

#define MAX 1000
#define pii pair<int,int>

int dist[MAX], nodes, edges;
bool visited[MAX];

// node -> list of {ngb, weight}.
vector<pii> graph[MAX];

// dist[node], node
priority_queue<pii, vector<pii>, greater<pii>> pq;

void dijkstra(int src) {
    for(int i = 1; i <= nodes; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }

    dist[src] = 0;
    pq.push({0, src});

    while(!pq.empty()) {
        auto [_, cur] = pq.top();
        pq.pop();

        if(visited[cur]) continue;
        visited[cur] = true;

        for(auto[ngb, weight] : graph[cur]) {
            if(visited[cur]) continue;
            if(dist[ngb] > dist[cur] + weight) {
                dist[ngb] = dist[cur] + weight;
                pq.push({dist[ngb], ngb});
            }
        }
    }
}

