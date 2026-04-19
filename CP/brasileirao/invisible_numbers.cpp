#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long
#define ar array
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define F first
#define S second
#define all(x) x.begin(), x.end()
#define loop(it, start, end) for(int it = start; it < end; it++)

ull memoSum[25][2][2], memoCount[25][2][2];
const ull MOD = 1e9 + 7ULL;

// Returns the sum of digits and quantity of numbers.
pair<ull, ull> fastSolve(int idx, bool isLess, bool isStarted, const vector<int>& limit) {
    if (idx == limit.size()) return {0, isStarted ? 1 : 0};
    if (memoSum[idx][isLess][isStarted] != -1)
        return {memoSum[idx][isLess][isStarted], memoCount[idx][isLess][isStarted]};

    ull totalSum = 0ULL, totalCount = 0ULL;
    int upper = isLess ? 9 : limit[idx];

    if (!isStarted) {
        auto res = fastSolve(idx + 1, true, false, limit);
        totalSum = (totalSum + res.first) % MOD;
        totalCount = (totalCount + res.second) % MOD;
    }

    for(int d = 1; d <= upper; d++) {
        auto res = fastSolve(idx + 1, isLess || d < upper, true, limit);
        ull contrib = (d * res.second) % MOD;
        totalSum = (totalSum + res.first + contrib) % MOD;
        totalCount = (totalCount + res.second) % MOD;
    }

    memoSum[idx][isLess][isStarted] = totalSum;
    memoCount[idx][isLess][isStarted] = totalCount;

    return {totalSum, totalCount};
}

void solve() {
    ull n;
    cin >> n;

    vector<int> digits;
    while(n > 0) {
        digits.push_back((n - 1) % 9 + 1);
        n = (n - 1) / 9;
    }

    reverse(all(digits));
    memset(memoSum, -1, sizeof(memoSum));
    memset(memoCount, -1, sizeof(memoCount));

    cout << fastSolve(0, false, false, digits).first << "\n";
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
}
