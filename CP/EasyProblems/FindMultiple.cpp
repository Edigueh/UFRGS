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
    int a, b, c;
    cin >> a >> b >> c;

    int res = -1;

    for (int i = a; i <= b; i++) {
        if (i % c == 0) {
            res = i;
            break;
        }
    }

    cout << res << endl;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    solve();
}
