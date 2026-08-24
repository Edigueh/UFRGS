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

int n;
vector<vector<int>> graph;
vector<int> subtree_size;
vector<ll> ans;

void calc_subtrees_sizes_from(int src, int parent, int depth) {
    subtree_size[src] = 1;
    ans[1] += depth;

    for(int ngb : graph[src]) {
        if (ngb != parent) {
           calc_subtrees_sizes_from(ngb, src, depth + 1);
           subtree_size[src] += subtree_size[ngb];
        }
    }
}

void reroot(int src, int parent) {
    for(int ngb : graph[src]) {
        if (ngb != parent) {
            // Nós da sub-árvore de 'v' ficam mais perto: -subtree_size[v].
            // O resto da árvore fica mais longe: + (n - subtree_size[v]).
            ans[ngb] = ans[src] + n - 2LL * subtree_size[ngb];
            reroot(ngb, src);
        }
    }
}

void solve() {
    cin >> n;
    graph.assign(n + 1, vector<int>());
    ans.assign(n + 1, 0);
    subtree_size.assign(n + 1, 0);
    for (int i = 0; i < n-1; i++) {
        int node, ngb;
        cin >> node >> ngb;
        graph[node].push_back(ngb);
        graph[ngb].push_back(node);
    }

    calc_subtrees_sizes_from(1, -1, 0);

    reroot(1, -1);

    for(int i = 1; i <= n; i++) cout << ans[i] << ' ';
    cout << endl;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
}
