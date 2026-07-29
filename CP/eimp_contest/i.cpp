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

int cost(int rs, int cs, int rt, int ct) {
    return (rs-rt)*(rs-rt) + (cs-ct)*(cs-ct);
}

void solve() {
    int n, r1, c1, r2, c2;
    cin >> n >> r1 >> c1 >> r2 >> c2;
    r1--; c1--; r2--; c2--;

    // Properly initialize grid to avoid out-of-bounds memory errors
    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    // Up, down, left, right.
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    // visited[r][c] keeps track of the cells we can land.
    vector<vector<bool>> visited1(n, vector<bool>(n, false));
    vector<pii> comp1; //stores all coords in the start component
    queue<pii> q;
    q.push({r1, c1});
    visited1[r1][c1] = true;
    comp1.pb({r1,c1});
    while(!q.empty()) {
        auto [r, c] = q.front(); q.pop();

        // Try all 4 possible intentional moves.
        for(int i = 0; i < 4; i++) {
            int new_row = r + dr[i];
            int new_col = c + dc[i];

            // Boundary check.
            if(new_row >= 0 && new_row < n && new_col >= 0 && new_col < n) {
                // Final destination process.
                if(grid[new_row][new_col] == '0' && !visited1[new_row][new_col]) {
                    visited1[new_row][new_col] = true;
                    q.push({new_row, new_col});
                    comp1.pb({new_row,new_col});
                }
            }
        }
    }

    if (visited1[r2][c2]) {
        cout << 0 << endl;
        return;
    }

    // Find all land cells reachable from dest
    vector<vector<bool>> visited2(n, vector<bool>(n, false));
    vector<pii> comp2; // store all coords in dest component.
    q.push({r2, c2});
    visited2[r2][c2] = true;
    comp2.pb({r2, c2});
    while(!q.empty()) {
        auto [r, c] = q.front(); q.pop();

        for(int i = 0; i < 4; i++) {
            int new_row = r + dr[i];
            int new_col = c + dc[i];

            if(new_row >= 0 && new_row < n && new_col >= 0 && new_col < n) {
                if(grid[new_row][new_col] == '0' && !visited2[new_row][new_col]) {
                    visited2[new_row][new_col] = true;
                    q.push({new_row, new_col});
                    comp2.pb({new_row,new_col});
                }
            }
        }
    }

    int min_cost = INT_MAX;
    for(auto p1 : comp1) {
        for (auto p2: comp2) {
            min_cost = min(min_cost, cost(p1.F, p1.S, p2.F, p2.S));
        }
    }

    cout << min_cost << endl;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
}
