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
    // Have to calculate the unique numbers we have there.
    // This is why we use a set for this.
    set<ll> ans;

    for (ll a = 2; a <= n; a++) {
        ll num = a * a;
        if (num > n) break;
        for (ll b = 2; b <= n; b++) {
            if (num <= n) ans.insert(num); else break;
            num *= a;
        }
    }

    cout << n - ans.size() << "\n";
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    solve();
}
