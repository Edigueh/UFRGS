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

const int maxn = 2e5 + 5;

int n, dp[maxn], diam;
vector<int> graph[maxn];

void dfs(int src, int parent) {
    dp[src] = 0;
    for(auto ngb : graph[src]) {
        if (ngb == parent) continue;
        dfs(ngb, src);
        diam = max(diam, dp[ngb] + dp[src] + 1);
        dp[src] = max(dp[src], dp[ngb] + 1);
    }
}

void solve() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        int node, ngb;
        cin >> node >> ngb;
        graph[node].push_back(ngb);
        graph[ngb].push_back(node);
    }

    dfs(1, 1);

    cout << diam << "\n";
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
}
