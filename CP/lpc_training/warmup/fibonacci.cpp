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
#define MOD 1000007

void solve() {
    int k, n;
    cin >> k >> n;

    vector<ll> dp(max(k, n + 1));
    ll window_sum = 0;

    // Build fibonnac^ki sequence.
    for(int i = 0; i < k; i++) {
        dp[i] = i;
        window_sum = (window_sum + dp[i]) % MOD;
    }

    for(int i = k; i <= n; i++) {
        dp[i] = window_sum;

        // Adds the new created element and removes the oldest one left behind.
        window_sum = (window_sum + dp[i] - dp[i - k] + MOD) % MOD;
    }

    // (n - 1) as problem is 1-indexed.
    cout << dp[n - 1] << "\n";
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int tc;
    cin >> tc;
    while(tc--) solve();
}
