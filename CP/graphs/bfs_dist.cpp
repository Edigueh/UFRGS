#include <bits/stdc++.h>
using namespace std;

#define MAX 1000
int dist[MAX];
bool visited[MAX];
vector<int> graph[MAX];
queue<int> q;

void bfs(int src) {
    dist[src] = 0;
    visited[src] = true;
    q.push(src);

    while(!q.empty()) {
        int cur = q.front();
        q.pop();
        visited[cur] = true;

        for(int ngb : graph[cur]) {
            if (!visited[ngb]) {
                dist[ngb] = dist[cur] + 1;
                q.push(ngb);
            }
        }
    }
}
