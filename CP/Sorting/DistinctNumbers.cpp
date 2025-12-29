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
    int n, x, c = 0;
    vector<int> v;

    cin >> n;

    while (n--) {
        cin >> x;
        v.push_back(x);
    }

    sort(all(v));

    x = -1;
    for (int i : v) {
        if (i != x) {
            x = i;
            c++;
        }
    }

    cout << c << "\n";
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    solve();
}
