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
    int a, b;
    string res;
    cin >> a >> b;

    if (b - a == 1 || b - a == 9) {
        res = "Yes";
    } else {
        res = "No";
    }

    cout << res << endl;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    solve();
}
