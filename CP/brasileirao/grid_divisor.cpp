#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ul unsigned long
#define ar array
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define F first
#define S second
#define all(x) x.begin(), x.end()
#define loop(it, start, end) for(int it = start; it < end; it++)

int hexToDec(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return 0;
}

void solve() {
    int n = 2, m = 4;
    //cin >> n >> m;

    int r = m % 4;
    string ignored = "";


    if (r != 0) {
        for (int i = 0; i < r; i++) ignored.append("0");
    }

    queue<string> q;
    q.push("0"); q.push("1");
    vector<vector<int>> grid = {{}};
    for (int row = 0; row < n; row++) {
        string hexStr = q.front(); q.pop();
        //cin >> hexStr;
        // hexStr.append(ignored);
        for (char c : hexStr) {
            int val = hexToDec(c);
            for (int i = 3; i >= 0; i--) {
                grid[row].push_back((val >> i) & 1);
            }
        }
    }

    for (vector<int> row : grid) {
        for (int i : row) {
            cout << i << " ";
        }
        cout << endl;
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
}
