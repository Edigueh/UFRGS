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

void dfs(vector<vector<int>> &tree, int emp, int sup, vector<int> &subordinates) {
    for(int sub : tree[emp]) {
        dfs(tree, sub, emp, subordinates);
        subordinates[emp] += (subordinates[sub]+1);
    }
}

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> tree(n+1);

    vector<int> subordinates(n+1);
    int dir_man;
    for(int emp = 2; emp <= n; emp++) {
        cin >> dir_man;
        tree[dir_man].push_back(emp);
    }

    dfs(tree, 1, 1, subordinates);

    for(int i = 1 ; i <= n; i++) cout << subordinates[i] << ' ';
    cout << endl;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
}
