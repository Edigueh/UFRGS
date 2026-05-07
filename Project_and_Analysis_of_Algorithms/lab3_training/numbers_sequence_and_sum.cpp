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
    int f, s;
    cin >> f >> s;
    while(f > 0 && s > 0) {
        int start, end;
        
        if (f >= s) {
            end = f;
            start = s;
        } else {
            end = s;
            start = f;
        }

        int sum = 0;
        for (int i = start; i <= end; i++) {
            cout << i << " ";
            sum += i;
        }
        cout << "Sum=" << sum << "\n";
        cin >> f >> s;
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
}
