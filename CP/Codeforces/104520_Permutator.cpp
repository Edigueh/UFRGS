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

void solve() {
    ll n; cin >> n;
    vector<ll> a(n), b(n);
    
    for (ll &x : a) cin >> x;
    for (ll &x : b) cin >> x;

    vector<ll> coeffs;

    // “Can I rewrite the sum as Σ (something_k) · b[k]?”
    // “What happens if I fix k and count how many times it appears?”
    // weight[k]=(k+1)(n−k)
    // k=0∑n−1​(k+1)(n−k)⋅ak​⋅bk​
    for (ll k = 0; k < n; k++) {
        coeffs.push_back((k + 1) * (n - k) * a[k]);
    }

    // Rearrangement Inequality
    // For two arrays:
    
    // To minimize the sum of products
    // → pair smallest with largest

    // To maximize the sum of products
    // → pair largest with largest
    sort(all(coeffs));            // ascending
    sort(all(b), greater<ll>()); // descending

    ll sum = 0;
    for (ll i = 0; i < n; i++) {
        // Multiply smallests with largests
        // smallest = coeffs[i]
        // largest = b[i]
        sum += coeffs[i] * b[i];
    }

    cout << sum << "\n";
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    solve();
}
