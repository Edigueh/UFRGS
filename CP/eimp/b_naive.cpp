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

bool has_superior(int employee, vector<int> relations, vector<int> gp) {
    int cur = relations[employee];
    while(cur != -1) {
        // se direto n está no grupo
        if(find(all(gp), cur) == gp.end()) {
            // olha os antecessores
            //printf("manager of %d is %d\n", cur, relations[cur]);
            cur = relations[cur];
        } else return true;
    }

    return false;
}

void solve() {
    int n;
    cin >> n;

    // idx = group_id
    // content = group members
    vector<vector<int>> groups;
    // idx = employee
    // content = manager
    vector<int> relations(n+1);
    for(int employee = 1; employee <= n; employee++) {
        int manager;
        cin >> manager;

        //printf("%d is the manager of %d\n", manager, employee);
        relations[employee] = manager;
        
        bool added_to_group = false;
        for(int i = 0; i < groups.size(); i++) {
            vector<int> gp = groups[i];
            //printf("Trying to allocate employee %d to a group\n", employee);
            if (!has_superior(employee, relations, gp)) {
                //printf("Managers %d or %d not in group %d, adding employee %d to group %d\n", manager, relations[manager], i, employee, i);
                groups[i].push_back(employee);
                added_to_group = true;
                break;
            } /*else {
                printf("A higher manager %d is in group %d\n", manager, i);
            }*/
        }

        if (!added_to_group) {
            //printf("Creating group %d to allocate employee %d\n", (int)groups.size(),employee);
            groups.push_back({employee});
        }
    }

    // int i = 0;
    // for(vector<int> gp : groups) {
    //     printf("Group %d: ", i);
    //     for(int p : gp) {
    //         cout << p << " ";
    //     }
    //     i++;
    //     cout << endl;
    // }

    cout << groups.size() << endl;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
}
