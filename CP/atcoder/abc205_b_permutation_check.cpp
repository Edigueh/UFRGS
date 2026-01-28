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
    int n, x;
    multiset<int> s;

    cin >> n;

    while (n--) {
        cin >> x;
        s.insert(x);
    }

    for (set<int>::iterator it = s.begin(); next(it) != s.end(); ++it) {
        if ((*next(it) - *it) != 1) {
            cout << "No" << "\n";
            return;
        }
    }

    cout << "Yes" << "\n";
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    solve();
}
