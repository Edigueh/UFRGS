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

void solve() {
    int n, x;
    cin >> n;
    int people = n * 2;
    vector<int> w;
    while (people--) {
        cin >> x;
        w.push_back(x);
    }

    sort(all(w));
    
    int ans = INT_MAX;
    // Try all pairs (i, j) for single kayaks
    for (int i = 0; i < 2*n; i++) {
        for (int j = i+1; j < 2*n; j++) {
            vector<int> rem;
            // Add all except i and j
            for (int k = 0; k < 2*n; k++) {
                if (k != i && k != j) 
                    rem.push_back(w[k]);
            }
            
            int bal = 0;
            for (int k = 0; k < rem.size(); k += 2) {
                bal += rem[k+1] - rem[k];
            }
            
            ans = min(ans, bal);
        }
    }
    cout << ans << "\n";
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    solve();
}
