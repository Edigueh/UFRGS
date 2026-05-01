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

vector<int> slicing(vector<int>& arr, int X, int Y) {
    auto start = arr.begin() + X;
    auto end = arr.begin() + Y + 1;

    vector<int> result(Y - X + 1);

    copy(start, end, result.begin());

    return result;
}

void solve() {
    int n, q, x;
    cin >> n >> q;
    
    vector<int> v;
    for (int i = 0; i < n; i++) {
        cin >> x;
        v.push_back(x);
    }

    int l, r, k;
    while(q--) {
        cin >> l >> r >> k;
        l--;r--;k--;
        vector<int> range = slicing(v, l, r);
        sort(all(range));
        cout << range[k] << "\n";
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
}
