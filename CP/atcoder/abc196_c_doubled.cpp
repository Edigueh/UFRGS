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

bool is_palindrome(ll i, ll n) {
    string s = to_string(i);
    string ds = s + s;
    ll v = stoll(ds);
    return v <= n;
}

void solve() {
    ll n, ans = 0LL;

    cin >> n;

    for (ll i = 1; i <= 1000000; i++) {
        if (is_palindrome(i, n)) ans++; else break;
    }

    cout << ans << "\n";
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    solve();
}
