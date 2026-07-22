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

// luck
int cost(int n, int m) {
    if (n == 1 && m == 1) {
        return 0;
    } else if(n == 1) {
        return m - 1;
    } else if(m == 1) {
        return n - 1;
    }

    return cost(n-1, m) + m;
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    if (cost(n, m) == k) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int tc;
    cin >> tc;
    while(tc--) solve();
}
