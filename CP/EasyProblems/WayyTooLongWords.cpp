#include <bits/stdc++.h>
using namespace std; // Includes std:: before every call like vector, cin, cout...

#define ll long long
#define ar array

// Input
// The first line contains an integer n (1 ≤ n ≤ 100). Each of the following n lines contains one word.
// All the words consist of lowercase Latin letters and possess the lengths of from 1 to 100 characters.

// Output
// Print n lines. The i-th line should contain the result of replacing of the i-th word from the input data.

// Examples
// Input
// 4
// word
// localization
// internationalization
// pneumonoultramicroscopicsilicovolcanoconiosis

// Output
// word
// l10n
// i18n
// p43s

// Write your solution here.
void solve() {
    string word;
    cin >> word;

    int len = word.length();

    if (len > 10) {
        cout << word.front() << len - 2 << word.back() << "\n";
    } else {
        cout << word << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0); // Turns inputs/outputs of streams off.
    cin.tie(0); // Unties cin from cout, cin will no longer force cout to flush its buffer before every input operation.
    
    int tc;
    cin >> tc; // Stores the number of test cases.
    while(tc--) solve(); // Runs solve for t times.
}
