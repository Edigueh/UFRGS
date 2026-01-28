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

void solve() {
    int n;
    cin >> n;
    ll len = 401, offset = 200;
    vector<ll> cnt(len, 0);

    for (ll i = 0; i < n; i++) {
        int a;
        cin >> a;
        cnt[a + offset]++;
    }
    
    ll ans = 0LL;
    for (int i = 0; i < len; i++) {
        if (cnt[i] == 0) continue;
        for (int j = i + 1; j < len; j++) {
            if (cnt[j] == 0) continue;
            ll val_i = i - offset;
            ll val_j = j - offset;
            ll diff = val_i - val_j;

            ans += cnt[i] * cnt[j] * (diff * diff);
        }
    }

    cout << ans << "\n";
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    solve();
}
