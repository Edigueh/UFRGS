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

int get_sum(vector<vector<int>> &graph, int src, int n) {
    vector<bool> vis(n+1, false);
    queue<int> q;
    q.push(src);

    vector<int> dist(n+1);
    dist[src] = 0;

    while(!q.empty()) {
        int cur = q.front(); q.pop();
        vis[cur] = true;

        for(int ngb : graph[cur]) {
            if(!vis[ngb]) {
                dist[ngb] = dist[cur] + 1;
                q.push(ngb);
            }
        }
    }

    return accumulate(all(dist), 0);
}

void solve() {
    int n;
    cin >> n;
    
    vector<vector<int>> graph(n+1);

    for (int i = 0; i < n-1; i++) {
        int node, ngb;
        cin >> node >> ngb;
        graph[node].push_back(ngb);
        graph[ngb].push_back(node);
    }

    for(int i = 1; i <= n; i++) cout << get_sum(graph, i, n) << ' ';
    cout << endl;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
}
