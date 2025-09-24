#include <bits/stdc++.h>
using namespace std; // Includes std:: before every call like vector, cin, cout...

#define ll long long
#define ar array

// Input
// The first (and the only) input line contains integer number w (1 ≤ w ≤ 100) — the weight of the watermelon bought by the boys.

// Output
// Print YES, if the boys can divide the watermelon into two parts, each of them weighing even number of kilos; and NO in the opposite case.

// Examples
// Input:
// 8
// Output:
// YES

// Write your solution here.
void solve() {

}

int main() {
    ios::sync_with_stdio(0); // Turns inputs/outputs of streams off.
    cin.tie(0); // Unties cin from cout, cin will no longer force cout to flush its buffer before every input operation.
    
    int w;
    cin >> w; // Stores the number of test cases.

    if (w % 2 == 0 && w != 2) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}
