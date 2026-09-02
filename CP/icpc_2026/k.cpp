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
#define MAXN 200100


int n, sumc;
int c[MAXN], k[MAXN];

int worstcase() {
    int ret = 0;
    for(int i = 0; i < n; i++)
        ret = max(ret, sumc - c[i] + k[i]);

    return ret;
}

void solve() {
    cin >> n;
    sumc = 0;
    for(int i = 0; i < n; i++){
        cin >> c[i];
        sumc += c[i];
    }
    for(int i = 0; i < n; i++) {
        cin >> k[i];
        if (k[i] > c[i]) {
            cout << -1 << '\n';
            return;
        }
    }

    cout << worstcase() << '\n';
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
}
