// Brief: beecrowd 1774 - Roteadores. Classical MST via Kruskal.
//
// Format: R C, then C lines (V W P). Prints the minimum total cost.
// Algorithm: Kruskal with Union-Find (path compression + union by rank).

#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct DSU {
    vector<int> parent, rnk;
    DSU(int n) : parent(n + 1), rnk(n + 1, 0) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        int root = x;
        while (parent[root] != root) root = parent[root];
        while (parent[x] != root) {
            int nxt = parent[x];
            parent[x] = root;
            x = nxt;
        }
        return root;
    }
    bool unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return false;
        if (rnk[rx] < rnk[ry]) swap(rx, ry);
        parent[ry] = rx;
        if (rnk[rx] == rnk[ry]) rnk[rx]++;
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int R, C;
    while (cin >> R >> C) {
        vector<tuple<int,int,int>> edges(C); // (weight, u, v)
        for (int i = 0; i < C; i++) {
            int v, w, p;
            cin >> v >> w >> p;
            edges[i] = make_tuple(p, v, w);
        }
        sort(edges.begin(), edges.end());
        DSU dsu(R);
        ll total = 0;
        int used = 0;
        for (auto& e : edges) {
            int p, u, v;
            tie(p, u, v) = e;
            if (dsu.unite(u, v)) {
                total += p;
                if (++used == R - 1) break;
            }
        }
        cout << total << '\n';
    }
    return 0;
}
