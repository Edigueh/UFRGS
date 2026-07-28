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

int steps(int n, int m) {
    // Revert the problem and goes backwards.
    int c = 0;
    while(m > n) {
        if(m % 2 == 0) {
            m /= 2;
        } else {
            m++;
        }
        c++;
    }

    return c + (n - m);
}

void solve() {
    int n, m;
    cin >> n >> m;

    cout << steps(n, m) << endl;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
}
