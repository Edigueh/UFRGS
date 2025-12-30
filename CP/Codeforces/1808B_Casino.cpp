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
    int n, m, sum = 0;
    cin >> n >> m;
    int g[n][m];

    for(int r = 0; r < n; r++)
        for (int c = 0; c < m; c++)
            cin >> g[r][c];

    for (int c = 0; c < m; c++) {
        for (int r = 0; r < n; r++) {
            for (int j = r + 1; j < n; j++) {
                sum += abs(g[r][c] - g[j][c]);
            }
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
