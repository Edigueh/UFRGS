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
    int n, m;
    cin >> n >> m;
    vector<vector<ll>> g(m, vector<ll>(n));

    // Create rotated matrix.
    // Rows = m, Columns = n.
    for(int c = 0; c < n; c++)
        for (int r = 0; r < m; r++)
            cin >> g[r][c];

    // Sort each row (as the matrix is rotated, sorts the columns of the original input).
    for (int i = 0; i < m; i++) {
        sort(all(g[i]));
    }

    // Sums up each time a number appears with positive and negative signs in that row
    // (column of the original matrix).
    ll sum = 0L;
    for (int r = 0; r < m; r++) {
        for (int c = 0; c < n; c++) {
            int pos = c;
            int neg = (n - c - 1);
            sum -= (g[r][c] * neg);
            sum += (g[r][c] * pos);
        }
    }

    cout << sum << "\n";
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int tc;
    cin >> tc;
    while(tc--) solve();
}
