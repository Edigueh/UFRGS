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
#define graph(type) vector<vector<type>>

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    // city -> product
    vector<int> city_to_product(n+1);
    graph(int) g(n+1);
    for(int i = 1; i <= n; i++) {
        int p;
        cin >> p;
        city_to_product[i] = p;
        g[i] = {};
    }

    // for(auto const&[k, v] : prod) {
    //     cout << "City " << k << " produces " << v << endl;
    // }

    while(m--) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    // city -> dist
    queue<int> q;
    q.push(1);

    vector<int> max_min_dist(n+1);
    vector<int> distances(n+1);
    for (int i = 1; i <= n; i++)
        distances[i] = -1;
    distances[1] = 0;
    while (!q.empty()) {
        int curNode = q.front(); q.pop();
        for (int neighbour : g[curNode]) {
            if(distances[neighbour] == -1) {
                q.push(neighbour);
                distances[neighbour] = distances[curNode] + 1;
            }
        }
        max_min_dist[city_to_product[curNode]] = max(distances[curNode], max_min_dist[city_to_product[curNode]]);
    }

    // for(auto const&[k, v] : distances) {
    //     cout << "Distance to " << k << " is " << v << endl;
    // }

    // prod_type -> max_min_dist

    // prod_type -> max_min_dist
    for(int i = 1; i <= k; i++) {
        cout << max_min_dist[i];
        if (i < k){
            cout << " ";
        }
    }
    cout << endl;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
}
