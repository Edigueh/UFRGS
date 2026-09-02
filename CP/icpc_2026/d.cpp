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
#define MAXN 1010

int n, m;
char a[MAXN][MAXN];

int n2, m2;
char b[MAXN][MAXN], c[MAXN][MAXN];

bool equal() {
    if (n2 != n || m2 != m)
        return false;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if (a[i][j] != b[i][j])
                return false;
    return true;
}

void flip() {
    for(int i = 0; i < n2; i++)
        for(int j = 0; j < m2 - 1 - j; j++)
            swap(b[i][j],b[i][m2 - 1 - j]);
}

void rotate() {
    for(int i = 0; i < n2; i++)
        for(int j = 0; j < m2; j++)
            c[j][n2 - 1 - i] = b[i][j];
    swap(n2, m2);
    for(int i = 0; i < n2; i++)
        for(int j = 0; j < m2; j++)
            b[i][j] = c[i][j];
}

void solve() {
    cin >> n >> m;
    
    n2 = n;
    m2 = m;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++) {
            cin >> a[i][j];
            b[i][j] = a[i][j];
        }
    int ans = 0;
    for(int i = 0; i < 4; i++) {
        ans += equal();
        flip();
        ans += equal();
        flip();
        rotate();
    }
    cout << ans << '\n';
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
}
