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
    int n, m;
    cin >> n >> m;

    bool swap = false;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i % 2 == 0) {
                cout << "#";
            } else {
                if(!swap) {
                    if(j + 1 == m) {
                        cout << "#";
                        swap = !swap;
                    } else {
                        cout << ".";
                    }
                } else {
                    if(j == 0) {
                        cout << "#";
                    } else {
                        cout << ".";
                        if(j+1 == m) swap = !swap;
                    }
                }
            }
        }
        cout << endl;
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    solve();
}
