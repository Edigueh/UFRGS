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

void allocate_to_group(int employee, vector<int>& relations, vector<int>& groups) {
    int gp = 0;
    bool allocated = false;
    vector<int> direct_managers
}

void solve() {
    int n;
    cin >> n;

    // idx = employee
    // content = manager
    vector<int> relations(n+1);
    
    // idx = employee
    // content = group assigned
    vector<int> groups(n+1);
    for(int employee = 1; employee <= n; employee++) {
        int manager;
        cin >> manager;

        //printf("%d is the direct manager of %d\n", manager, employee);
        relations[employee] = manager;
        groups[employee] = -1;
    }

    for (int employee = 1; employee <= groups.size(); employee++) {
        if(employee == 1) {
            groups[employee] = 0;
            continue;
        }
        allocate_to_group(employee, relations, groups);
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
}
