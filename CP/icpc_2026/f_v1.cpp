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
/*
    f(x) > x
    x > y => f(x) > f(y)
    f(f(x)) = 3x

    f(1)  = 2
    f(2)  = 3
    f(3)  = 6
    f(4)  = 7
    f(5)  = 8
    f(6)  = 9
    f(7)  = 12
    f(8)  = 15
    f(9)  = 18
    f(10) = 19
    f(11) = 20
    f(12) = 21
    f(13) = 22
    Se há um y tal que f(y) = x, f(x) = 3 * y.
    Senão => f(x) = f(x-1) + 1
*/

/*
    Regras:

    1. f(x) > x
    2. x > y => f(x) > f(y)
    3. f(f(x)) = 3x

    Se há um y tal que f(y) = x, f(x) = 3 * y.
    Senão => f(x) = f(x-1) + 1
*/
#define MAXN 10000010

int n;
int f[MAXN], inv[MAXN];

void solve() {
    cin >> n;

    f[1] = 2;
    inv[2] = 1;
    for (int i = 2; i <= n; i++) {
        if (inv[i])
            f[i] = 3*inv[i];
        else
            f[i] = f[i-1] + 1;
        if(f[i] <= n)
            inv[f[i]] = i;
    }

    cout << f[n] << '\n';
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
}
