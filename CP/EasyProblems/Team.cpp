#include <bits/stdc++.h>
using namespace std; // Includes std:: before every call like vector, cin, cout...

#define ll long long
#define ar array

// Input
// The first input line contains a single integer n (1 ≤ n ≤ 1000) — the number of problems in the contest. 
// Then n lines contain three integers each, each integer is either 0 or 1. 
// If the first number in the line equals 1, then Petya is sure about the problem's solution, otherwise he isn't sure. 
// The second number shows Vasya's view on the solution, the third number shows Tonya's view. The numbers on the lines are separated by spaces.

// Output
// Print a single integer — the number of problems the friends will implement on the contest.

// Examples
// Input:
// 3
// 1 1 0
// 1 1 1
// 1 0 0
// Output:
// 2

// Input:
// 2
// 1 0 0
// 0 1 1
// Output:
// 1

// Write your solution here.
void solve() {
    int n, pr = 0;
    cin >> n;

    while(n--) {
        int p, v, t;
        cin >> p >> v >> t;

        if (p + v + t >= 2) {
            pr++;
        }
    }

    cout << pr << "\n";
}

int main() {
    ios::sync_with_stdio(0); // Turns inputs/outputs of streams off.
    cin.tie(0); // Unties cin from cout, cin will no longer force cout to flush its buffer before every input operation.
    
    solve();
}
