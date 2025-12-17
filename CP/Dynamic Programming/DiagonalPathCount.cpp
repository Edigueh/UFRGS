#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ar array

map<pair<int, int>, int> memo;

int countDiagonalPaths(int rows, int columns) {
    pair<int, int> p = make_pair(rows, columns);

    if (memo.count(p)) {
        return memo[p];
    }

    if (rows == 1 || columns == 1) {
        return 1;
    }

    int res = countDiagonalPaths(rows - 1, columns) + countDiagonalPaths(rows, columns - 1);
    memo[p] = res;
    return res;
}

int main() {
    int rows, columns;
    cin >> rows >> columns;

    cout << countDiagonalPaths(rows, columns) << endl;
}
