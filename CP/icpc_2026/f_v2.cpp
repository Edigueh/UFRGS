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

int n;

void solve() {
    cin >> n;
    int pot = 1;
    for (pot = 1; pot*3 <= n; pot *= 3);

    int ans = (
        (n <= 2 * pot) ?
        (2 * pot + (n - pot)) :
        (pot * 3 + 3 * (n - 2 * pot))
    );

    cout << ans << '\n';
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
}
