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
    string grid[2];
    cin >> grid[0] >> grid[1];

    // visited[r][c] keeps track of the cells we can land on after the forced arrow move.
    vector<vector<bool>> visited(2, vector<bool>(n, false));
    queue<pii> q;

    q.push({0, 0});
    visited[0][0] = true;

    // Up, down, left, right.
    int row_dirs[] = {-1, 1, 0, 0};
    int col_dirs[] = {0, 0, -1, 1};

    while(!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        
        // Reached bottom-right cell.
        if (r == 1 && c == n-1) {
            cout << "YES\n";
            return;
        }

        // Try all 4 possible intentional moves.
        for(int i = 0; i < 4; i++) {
            int new_row = r + row_dirs[i];
            int new_col = c + col_dirs[i];

            // Boundary check.
            if(new_row >= 0 && new_row < 2 && new_col >= 0 && new_col < n) {
                // Apply forced arrow move.
                int forced_row = new_row;
                int forced_col = new_col;

                if(grid[new_row][new_col] == '>') {
                    forced_col++;
                } else if (grid[new_row][new_col] == '<') {
                    forced_col--;
                }

                // Final destination process.
                if(!visited[forced_row][forced_col]) {
                    visited[forced_row][forced_col] = true;
                    q.push({forced_row, forced_col});
                }
            }
        }
    }

    cout << "NO\n";
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int tc;
    cin >> tc;
    while(tc--) solve();
}
