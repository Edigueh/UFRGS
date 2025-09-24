#include <bits/stdc++.h>
using namespace std; // Includes std:: before every call like vector, cin, cout...

#define ll long long
#define ar array

// Write your solution here.
void solve() {
    string word;
    cin >> word;

    int len = word.length();

    if (len > 10) {
        cout << word.front() << len - 2 << word.back() << endl;
    } else {
        cout << word << endl;
    }
}

int main() {
    ios::sync_with_stdio(0); // Turns inputs/outputs of streams off.
    cin.tie(0); // Unties cin from cout, cin will no longer force cout to flush its buffer before every input operation.
    
    int tc;
    cin >> tc; // Stores the number of test cases.
    while(tc--) solve(); // Runs solve for t times.
}
