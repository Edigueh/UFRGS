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

void solve() {
   int n;
   cin >> n;

    vector<ll> apples(n);
    for(int i = 0; i < n; i++) cin >> apples[i];

    ll ans = INT_MAX;
    for(int mask = 0; mask < (1<<n); mask++) {
        ll g0 = 0, g1 = 0;
        for (int i = 0; i < n; i++) {
            if(mask & (1<<i)) {
                g1 += apples[i];
            } else {
                g0 += apples[i];
            }
        }
        ans = min(ans, abs(g1 - g0));
    }

    cout << ans << "\n";
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
}
