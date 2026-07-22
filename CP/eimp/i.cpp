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

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a, b;
    while(n--) {
        int x;
        cin >> x;
        a.push_back(x);
    }

    sort(all(a));

    while(m--) {
        int bj;
        cin >> bj;

        cout << upper_bound(a.begin(), a.end(), bj) - a.begin();
        if (m > 0) {
            cout << " ";
        }
    }
    cout << endl;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
}
