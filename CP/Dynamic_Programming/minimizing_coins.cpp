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
const ll INF = INT32_MAX;
const ll MAXN = 1e6+5;

vector<ll> coins;
ll qnt[MAXN];

ll calc(ll v) {
    if (v <= 0) return 0;
    if(qnt[v] != -1) return qnt[v];
    qnt[v] = INF;
    for(auto c : coins) {
        if (v >= c) qnt[v] = min(qnt[v], calc(v-c)+1);
    }

    return qnt[v];
}

void solve() {
    memset(qnt, -1, sizeof(qnt));
    ll n, sum;
    cin >> n >> sum;

    for(ll i = 0; i < n; i++) {
        int x;
        cin >> x;
        coins.push_back(x);
    }

    qnt[0] = 0;
    ll ans = calc(sum);

    if (ans == INF) {
        cout << -1 << "\n";
        return;
    }

    cout << ans << "\n";
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
}
