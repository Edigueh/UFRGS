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
    string inp;
    cin >> inp;

    stack<char> s;
    int ans = 0;
    for (char c : inp) {
        if (c == '.') continue;
        if (c == '<') {
            s.push(c);
        } else if (c == '>' && !s.empty()) {
            ans++;
            s.pop();
        }
    }

    cout << ans << "\n";
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int tc;
    cin >> tc;
    while(tc--) solve();
}
