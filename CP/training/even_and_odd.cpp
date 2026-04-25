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
    int n, i;
    cin >> n;

    multiset<int> even;
    multiset<int, greater<int>> odd;
    while(n--) {
        cin >> i;

        if(i % 2 == 0) even.insert(i);
        else odd.insert(i);
    }

    for(int num : even) cout << num << "\n";
    for(int num : odd) cout << num << "\n";
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
}
