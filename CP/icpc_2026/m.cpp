#include <bits/stdc++.h>
using namespace std;

#define int long long
#define ar array
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define F first
#define S second
#define all(x) x.begin(), x.end()
#define loop(it, start, end) for(int it = start; it < end; it++)
#define MAXN 100100
#define MAXK 12
#define INF 1000000000000000000LL
#define piii pair<int, pii>

int n, m, k;
vector<pii> graph[MAXN];

int d[MAXN][MAXK];

priority_queue<piii, vector<piii>, greater<piii>> q;

int dijkstra() {
    for(int i = 1; i <= n; i++)
        for(int j = 0; j <= k; j++)
            d[i][j] = INF;

    // For node 1, using 0 microwaves edges, we reach with 0.
    d[1][0] = 0;

    // distance, node, used microwaves edges.
    q.push({0, {1, 0}});

    while(!q.empty()) {
       pii cur = q.top().second;
       int dist = q.top().first;
       q.pop();

       // Reached target?
       if (cur.first == n)
           return dist;

       // Dist is greater than current?
       if (dist > d[cur.first][cur.second])
           continue;

       for(pii edge : graph[cur.first]) {
           pii ngb;
           // if edge.second < 0 -> microwaves, then have to use the current number of microwaves + 1.
           if (edge.second < 0)
               ngb = {edge.first, cur.second + 1};
           else
               ngb = {edge.first, cur.second};

           int new_dist = abs(edge.second);

           // limits at k microwaves
           if (ngb.second <= k && d[ngb.first][ngb.second] > dist + new_dist) {
               d[ngb.first][ngb.second] = dist + new_dist;
               q.push({d[ngb.first][ngb.second], ngb});
           }
       }
    }

    // Not found.
    return -1;
}

void solve() {
    cin >> n >> m >> k;
    int node, ngb, dist, microwaves;

    // Build graph.
    for(int i = 0; i < m; i++) {
        cin >> node >> ngb >> dist >> microwaves;
        graph[node].push_back({ngb, dist});
        graph[ngb].push_back({node, dist});
        if (microwaves != -1) {
            graph[node].push_back({ngb, -microwaves});
            graph[ngb].push_back({node, -microwaves});
        }
    }

    cout << dijkstra() << '\n';
}

int32_t main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
}
