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
    int n;
    cin >> n;

    float min = MAXFLOAT, p, res;
    int g;
    while (n--) {
        cin >> p >> g;
        res = (p * 1000) / g;
        if (res < min) min = res;
    }

    cout << fixed << setprecision(2) << min << "\n";
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
}
