#include <bits/stdc++.h>
using namespace std; // Includes std:: before every call like vector, cin, cout...

#define ll long long
#define ar array

// Input
// The first line of the input contains two integers n and k (1 ≤ k ≤ n ≤ 50) separated by a single space.

// The second line contains n space-separated integers a1, a2, ..., an (0 ≤ ai ≤ 100), where ai is the score earned by the participant who got the i-th place. The given sequence is non-increasing (that is, for all i from 1 to n - 1 the following condition is fulfilled: ai ≥ ai + 1).

// Output
// Output the number of participants who advance to the next round.

// Examples
// InputCopy
// 8 5
// 10 9 8 7 7 7 5 5
// OutputCopy
// 6
// InputCopy
// 4 2
// 0 0 0 0
// OutputCopy
// 0

// Write your solution here.
void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> scores(n);
    for (int i = 0; i < n; i++) {
        cin >> scores[i];
    }

    int cut = scores[k-1];
    int pass = 0;

    for (int i = 0; i < n; i++) {
        if (scores[i] >= cut && scores[i] > 0) {
            pass++;
        } else {
            break;
        }
    }

    cout << pass << "\n";
}

int main() {
    ios::sync_with_stdio(false); // Turns inputs/outputs of streams off.
    cin.tie(NULL); // Unties cin from cout, cin will no longer force cout to flush its buffer before every input operation.
    
    solve(); // Runs solve for t times.
}
