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
    vector<int> v;
    int x, n = 0;
    cin >> n;
    int c = n;

    while (n--) {
        cin >> x;
        v.push_back(x);
    }

    int best = 0, sum = 0;
    for (int i = 0; i < c; i++) {
        sum = max(v[i], sum + v[i]);
        best = max(sum, best);
    }

    cout << best << endl;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    solve();
}
