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
#define VERBOSE false

map<string, string> gs(map<string, vector<string>> propPrefs, map<string, vector<string>> recPrefs) {
    // Precompute each receivers rank of proposers for comparisons.
    map<string, map<string, int>> recRank;
    for (auto const& [rec, propRank] : recPrefs) {
        for(int i = 0; i < propRank.size(); i++) {
            recRank[rec][propRank[i]] = i;
        }
    }

    // All proposers start free.
    deque<string> freeProps;

    // Store the index where each proposer stop in the last proposal.
    map<string, int> nextProposerIndex;
    for (auto const& [prop, _] : propPrefs) {
        freeProps.push_back(prop);
        nextProposerIndex.insert(mp(prop, 0));
    }

    map<string, string> matches;

    while(!freeProps.empty()) {
        // Remove the first proposer.
        string proposer = freeProps.front(); freeProps.pop_front();

        // If proposer has already proposed to every receiver, skip (no more matches possible).
        if (nextProposerIndex[proposer] >= propPrefs[proposer].size()) {
            if(VERBOSE) cout << proposer << " has already proposed to everyone\n";
            continue;
        }

        // Highest-ranked receiver proposer hasn't proposed to yet.
        string receiver = propPrefs[proposer][nextProposerIndex[proposer]];
        nextProposerIndex[proposer]++;
        if(VERBOSE) cout << proposer << " proposes to " << receiver << "\n";

        // If receiver is free.
        if (matches.find(receiver) == matches.end()) {
            // (proposer, receiver) become engaged.
            matches.insert(make_pair(receiver, proposer));
            if(VERBOSE) { 
                cout << receiver << " is free.\n";
                cout << proposer << " and " << receiver << " become engaged!\n";
            }
        } else {
            string currentReceiverPair = matches[receiver];
            
            // If receiver prefers current pair over new proposer.
            if (recRank[receiver][currentReceiverPair] < recRank[receiver][proposer]) {
                // Proposer remains free; try next receiver later.
                freeProps.push_back(proposer);
                if(VERBOSE) cout << proposer << " remains free.\n";
            } else {
                // Receiver prefers new proposer over current pair.
                matches[receiver] = proposer;

                // The current pair becomes free.
                freeProps.push_back(currentReceiverPair); 

                if(VERBOSE) cout << receiver << " and " << proposer << " engaged. "  << currentReceiverPair << " becomes free.\n";
            }
        }
        // If proposer still hasn't proposed to everyone and is free. It re-enter loop
        // through the deque. Loop continues while there exists a free proposer who
        // hasn't proposed to all receivers.
    }

    return matches;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

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

    map<string, string> ans = gs(propPrefs, recPrefs);

    for (auto const& [key, val] : ans) {
        cout << key << " <-> " << val << "\n";
    }
}
