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

int a, b;
const double eps = 1e-7;

double v(double x) {
    return (a - 2 * x) * (b - 3 * x)/2.0 * x;
}

void solve() {
    cin >> a >> b;
    double l = 0.0, r = min(a / 2.0, b / 3.0), ans = 0;
    while(abs(r - l) > eps) {
        double m1 = l + (r - l) / 3.0, // (2 * l + r) / 3;
               m2 = r - (r - l) / 3.0; // (2 * r + l) / 3;

        double f1 = v(m1), f2 = v(m2);

        if(f1 >= f2) {
            r = m2;
        } else {
            l = m1;
        }

        if(f1 >= f2) r = m2;
        else l = m1;

        ans = max({ans, f1, f2});
    }
    cout << fixed << setprecision(12);
    cout << l << ' ' << ans << '\n';
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
}
