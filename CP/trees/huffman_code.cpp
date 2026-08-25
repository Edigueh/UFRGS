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

// The huffman code generates a prefix free encoding language.
// The strategy is to take the two letters that appear the less and put them as leafs.
// Then go summing up until the root (the most common symbol).
ll huffman_cost(vector<int> num_aparicoes) {
    multiset<int> S;
    for(int num : num_aparicoes) {
        S.insert(num);
    }

    ll cost = 0;
    while(S.size() > 1) {
        int leaf1 = *S.begin();
        S.erase(S.find(leaf1));
        int leaf2 = *S.begin();
        S.erase(S.find(leaf2));
        cost += leaf1 + leaf2;
        S.insert(leaf1 + leaf2);
    }

    return cost;
}

void solve() {

}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
}