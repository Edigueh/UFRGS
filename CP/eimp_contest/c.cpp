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

int rook(int r1, int c1, int r2, int c2) {
    if(r1 == r2 && c1 == c2) {
        return 0;
    }

    if(r1 == r2 || c1 == c2) {
        return 1;
    }

    return 2;
}

int bishop(int r1, int c1, int r2, int c2) {
    if (r1 == r2 && c1 == c2) {
        return 0;
    }

    char src_color, dst_color;

    bool row_parity = r1 % 2 == 0;
    bool col_parity = c1 % 2 == 0;

    if(row_parity == col_parity) {
        src_color = 'w';
    } else {
        src_color = 'b';
    }

    row_parity = r2 % 2 == 0;
    col_parity = c2 % 2 == 0;

    if(row_parity == col_parity) {
        dst_color = 'w';
    } else {
        dst_color = 'b';
    }

    if (src_color != dst_color) {
        return 0;
    }

    // Same diagonal.
    int row_diff = abs(r1 - r2);
    int col_diff = abs(c1 - c2);
    if (row_diff == col_diff) {
        return 1;
    }

    return 2;
}

int king(int r1, int c1, int r2, int c2) {
    if(r1 == r2 && c1 == c2) {
        return 0;
    }

    // King takes the maximum of two distances, because it can alway go diag and eat up both, so its limited by the largest distance.
    return max(abs(r1 - r2), abs(c1 - c2));
}

void solve() {
    int r1, c1, r2, c2;
    cin >> r1 >> c1 >> r2 >> c2;

    cout << rook(r1, c1, r2, c2) << " " << bishop(r1, c1, r2, c2) << " " << king(r1, c1, r2, c2) << endl;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
}
