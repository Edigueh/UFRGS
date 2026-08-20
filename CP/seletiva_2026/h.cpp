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
   
   unordered_map<int, int> arrows;
   int total = 0;
   
   for (int i = 0; i < n; i++) {
        int h;
        cin >> h;
        // If there are no more arrows at that height (which has a baloon).
        if(arrows[h] == 0) {
            // Shoot a new arrow at current height.
            total++;
            // Add arrow to the height below current.
            arrows[h-1]++;
        } else {
            // Remove arrow from current height.
            arrows[h]--;
            // Add arrow to the height below current.
            arrows[h-1]++;   
        }
   }

   cout << total << endl;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
}
