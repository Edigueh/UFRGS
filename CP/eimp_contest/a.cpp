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
#define adjList(type) vector<vector<type>>


void solve() {
    int n, m;
    cin >> n >> m;

    adjList(int) graph(n+1);

    while(m--) {
        int u, v;
        cin >> u >> v;

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int x = INT_MIN;
    int y = INT_MIN;

    int start = -1;
    for(int i = 1; i <= n; i++) {
        if(graph[i].size() == 1) {
            start = i;
        }
    }
    int lvl = 0;
    queue<int> q;
    q.push(start);
    vector<int> max_min_dist(n+1);
    vector<bool> visited(n+1);
    for (int i = 1; i <= n; i++)
        visited[i] = false;
    visited[start] = true;

    while (!q.empty()) {
        int curNode = q.front(); q.pop();
        for (int neighbour : graph[curNode]) {
            if(!visited[neighbour] && lvl < 2) {
                q.push(neighbour);
                visited[neighbour] = true;
                if (lvl == 0) {
                    y = graph[neighbour].size() - 1;
                    lvl++;
                } else if(lvl == 1 && graph[neighbour].size() != 1) {
                    x = graph[neighbour].size();
                    lvl++;
                }
            }
        }
    }

    cout << x << " " << y << endl;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int tc;
    cin >> tc;
    while(tc--) solve();
}
