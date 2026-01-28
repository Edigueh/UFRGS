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
    ll n;
    cin >> n;
    vector<ll> v(n);

    ll vsum = 0LL;
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        vsum += v[i];
    }

    ll x;
    cin >> x;

    ll fb = x / vsum;
    ll sum = fb * vsum;
    ll ans = fb * n;

    for(int i = 0; i < n; i++) {
        sum += v[i];
        ans++;
        if (sum > x) break;
    }

    cout << ans << "\n";
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    solve();
}
