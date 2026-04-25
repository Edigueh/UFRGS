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

vector<string> split(const string& s, char delim) {
    vector<string> res;
    stringstream ss(s);
    string item;

    while(getline(ss, item, delim)){
        res.push_back(item);
    }

    return res;
}

void solve() {
    int m, n;
    cin >> m >> n;
    map<string, string> dict;
    while(m--) {
        string key, val;
        cin >> key; cin.ignore();
        getline(cin, val);

        dict[key] = val;
    }

    string line;
    while(n--) {
        getline(cin, line);
        vector<string> words = split(line, ' ');
        for(auto it = words.begin(); it != words.end(); it++) {
            if(dict.find(*it) == dict.end())
                cout << *it;
            else
                cout << dict[*it];
            if(next(it) == words.end())
                cout << "\n";
            else
                cout << " ";
        }
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int tc;
    cin >> tc;
    while(tc--){
        solve();
        cout << "\n";
    }
}
