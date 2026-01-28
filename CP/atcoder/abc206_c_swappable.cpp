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
    ll n, x, len, ans = 0LL;
    multiset<ll> s;

    cin >> n;
    while (n--) {
        cin >> x;
        s.insert(x);
    }

    x = 0LL;
    len = s.size();
    for (set<ll>::iterator it = s.begin(); next(it) != s.end(); ++it) {
        x++;
        len--;
        if (*next(it) != *it) {
            ans += x * len;
            x = 0LL;
        }
    }

    cout << ans << "\n";
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    solve();
}
