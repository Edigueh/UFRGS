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
    int n, i, j;
    cin >> n;

    vector<pii> vt;

    while(n--) {
        cin >> i >> j;
        vt.push_back(mp(i, j));
    }

    int sol = 0;
    sort(all(vt), [](const pii& a, const pii& b) {
        return a.first < b.second;
    });

    
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
}
