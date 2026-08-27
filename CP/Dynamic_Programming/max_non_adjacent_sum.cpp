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

ll n;
ll ans[MAXN];
ll val[MAXN];

ll calc(ll v)  {
    if (v >= n) return 0;
    if(ans[v] != -INF) return ans[v];
    ans[v] = max(val[v] + calc(v+2), calc(v+1));
    return ans[v];
}

void solve() {
    memset(ans, -INF, sizeof(ans));
    cin >> n;

    for(ll i = 0; i < n; i++) {
        ll x;
        cin >> x;
        val[i] = x;
    }

    ans[n] = 0;
    cout << calc(0) << "\n";
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
}
