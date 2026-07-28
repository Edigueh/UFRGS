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

bool is_possible(int n, int m) {
    if(n == m)
        return true;

    if (n < m || n % 3 != 0)
        return false;

    if(is_possible((n/3) * 2, m) || is_possible(n/3, m))
        return true;

    return false;
}

void solve() {
    int n, m;
    cin >> n >> m;

    if(is_possible(n, m))
        cout << "YES";
    else
        cout << "NO";

    cout << endl;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int tc;
    cin >> tc;
    while(tc--) solve();
}
