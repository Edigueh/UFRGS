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
    int n, q;
    string s;
    cin >> n >> q >> s;

    int rot_offset = 0;
    while(q--) {
        int op;
        cin >> op;
        ll x;
        cin >> x;
        switch (op){
            case 1:
                rot_offset = (rot_offset - (x % n) + n) % n;
            break;
            case 2:
                cout << s[(rot_offset + (x - 1)) % n] << "\n";
            break;
            default: break;
        }
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    solve();
}
