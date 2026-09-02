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
#define MAXN 100100

int c[MAXN], v[MAXN];

void solve() {
    int n;
    cin >> n;
    
    for (int i = 1; i <= n; i++) {
        cin >> c[i] >> v[i];
        c[i] += c[i-1];
        v[i] += v[i-1];
    }

    int q, j;
    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> j;
        if(c[j] == v[j])
            cout << "NEUTRO\n";
        else
            cout << (c[j] < v[j] ? "VENDA" : "COMPRA") << '\n';
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
}
