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
    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;

    int ans = 0, l = 0, r = 0;
    for(r = 0; r < k; r++) {
        if (s[r] == 'W') ans++;
    }

    int cont = ans;
    while (r < n) {
        if(s[l] == 'W') cont--;
        if(s[r] == 'W') cont++;
        ans = min(ans, cont);
        l++;
        r++;
    }

    cout << ans << "\n";
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;
    cin >> t;
    while(t--)
        solve();
}
