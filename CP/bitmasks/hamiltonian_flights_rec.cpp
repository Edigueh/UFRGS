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
#define MAXN (int)(1e6 + 10)
#define MOD (int)(1e9 + 7)

int n, m, a, b, routes[25][MAXN];
vector<int> graph[MAXN];

int tsp(int cur, int visited_mask) {
    // __builtin_popcount counts how many bits are set in the mask.
    // -> Everyone is already visited?
    if (__builtin_popcount(visited_mask) == n) return (cur == n-1);
    if (routes[cur][visited_mask] != -1) return routes[cur][visited_mask];

    int ans = 0;
    for (int ngb : graph[cur]) {
        // If ngb is visited, go to the next one.
        if (visited_mask&(1<<ngb)) continue;
        // Else, add the value of that node to the cost memo.
        // By making the OR operation with the visited mask, we will insert it into the mask (marking it as visited).
        else ans = (ans + tsp(ngb, visited_mask|(1<<ngb))) % MOD;
    }

    // Return the number of paths to the current node.
    return routes[cur][visited_mask] = ans;
}

void solve() {
    cin >> n >> m;
    
    while(m--) {
        cin >> a >> b;        
        graph[a-1].push_back(b-1);
    }

    memset(routes, -1, sizeof routes);

    cout << tsp(0, 1) << '\n';
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
}
