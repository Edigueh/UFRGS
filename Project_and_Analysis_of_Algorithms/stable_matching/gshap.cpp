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

set<pair<string, string>> gs(map<string, vector<string>> propPrefs, map<string, vector<string>> recPrefs) {
    // Precompute each receivers rank of proposers for comparisons.
    map<string, map<string, int>> recRank; // <------- When the code reaches this line it crashes.
    // for (auto const& [rec, propRank] : recPrefs) {
    //     for(int i = 0; i < propRank.size(); i++) {
    //         recRank[rec][propRank[i]] = i;
    //     }
    // }

    // deque<string> freeProps;
    // for(auto const& [key, val] : propPrefs) freeProps.push_back(key);

    // cout << "DEBUG END\n";

    set<pair<string, string>> ans;
    return ans;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    if (__cplusplus == 202302L) std::cout << "C++23\n";
   else if (__cplusplus == 202002L) std::cout << "C++20\n";
   else if (__cplusplus == 201703L) std::cout << "C++17\n";
   else if (__cplusplus == 201402L) std::cout << "C++14\n";
   else if (__cplusplus == 201103L) std::cout << "C++11\n";
   else if (__cplusplus == 199711L) std::cout << "C++98\n";
   else std::cout << "pre-standard C++\n";

    map<string, vector<string>> propPrefs = {
        {"Atlanta", {"Wayne", "Val", "Yolanda", "Zeus", "Xavier"}},
        {"Boston", {"Yolanda", "Wayne", "Val", "Xavier", "Zeus"}},
        {"Chicago", {"Wayne", "Zeus", "Xavier", "Yolanda", "Val"}},
        {"Detroit", {"Val", "Yolanda", "Xavier", "Wayne", "Zeus"}},
        {"El Paso", {"Wayne", "Yolanda", "Val", "Zeus", "Xavier"}}
    };

    map<string, vector<string>> recPrefs = {
        {"Val", {"El Paso", "Atlanta", "Boston", "Detroit", "Chicago"}},
        {"Wayne", {"Chicago", "Boston", "Detroit", "Atlanta", "El Paso"}},
        {"Xavier", {"Boston", "Chicago", "Detroit", "El Paso", "Atlanta"}},
        {"Yolanda", {"Atlanta", "El Paso", "Detroit", "Chicago", "Boston"}},
        {"Zeus", {"Detroit", "Boston", "El Paso", "Chicago", "Atlanta"}}
    };

    cout << "hi\n";
    set<pair<string, string>> ans = gs(propPrefs, recPrefs);

    // for(auto it = ans.begin(); it != ans.end(); ++it)
    //     cout << it->first << " : " << it->second << "\n";
}
