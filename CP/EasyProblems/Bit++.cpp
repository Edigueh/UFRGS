#include <bits/stdc++.h>
using namespace std; // Includes std:: before every call like vector, cin, cout...

#define ll long long
#define ar array

// Input
// The first line contains a single integer n (1 ≤ n ≤ 150) — the number of statements in the programme.

// Next n lines contain a statement each. Each statement contains exactly one operation (++ or --) and exactly one variable x (denoted as letter «X»).
// Thus, there are no empty statements. The operation and the variable can be written in any order.

// Output
// Print a single integer — the final value of x.

// Examples
// InputCopy
// 1
// ++X
// OutputCopy
// 1

// InputCopy
// 2
// X++
// --X
// OutputCopy
// 0

// Write your solution here.
void solve() {
    int n, x = 0;
    cin >> n;

    while(n--) {
        string op;
        cin >> op;

        if(op[1] == '+') x++;
        else if(op[1] == '-') x--;
    }

    cout << x << "\n";
}

int main() {
    ios::sync_with_stdio(false); // Turns inputs/outputs of streams off.
    cin.tie(NULL); // Unties cin from cout, cin will no longer force cout to flush its buffer before every input operation.
    
    solve();
}
