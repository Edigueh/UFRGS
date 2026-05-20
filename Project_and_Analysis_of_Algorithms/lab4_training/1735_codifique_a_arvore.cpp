// Brief: beecrowd 1735 - Codifique a Arvore.
//        Reads a labeled tree in `(N S)` notation and prints the Prufer code.
//
// Algorithm: recursive parser for the grammar T ::= "(" N S ")", adjacency
// list, then Prufer encode (remove the lowest-labeled leaf, record its
// neighbor). n <= 50, so O(n^2) is sufficient.

#include <bits/stdc++.h>
using namespace std;

static vector<string> tokens;
static size_t pos;
static map<int, vector<int>> adj;

int parse_node() {
    pos++; // '('
    int label = stoi(tokens[pos]);
    pos++;
    if (!adj.count(label)) adj[label] = {};
    while (pos < tokens.size() && tokens[pos] == "(") {
        int child = parse_node();
        adj[label].push_back(child);
        adj[child].push_back(label);
    }
    pos++; // ')'
    return label;
}

vector<int> prufer_encode() {
    int n = (int)adj.size();
    if (n <= 1) return {};
    map<int, int> deg;
    for (auto it = adj.begin(); it != adj.end(); ++it) {
        deg[it->first] = (int)it->second.size();
    }
    vector<int> code;
    for (int i = 0; i < n - 1; i++) {
        int leaf = INT_MAX;
        for (auto it = deg.begin(); it != deg.end(); ++it) {
            if (it->second == 1 && it->first < leaf) leaf = it->first;
        }
        int neighbor = -1;
        for (int u : adj[leaf]) {
            if (deg[u] > 0) { neighbor = u; break; }
        }
        code.push_back(neighbor);
        deg[neighbor]--;
        deg[leaf] = 0;
    }
    return code;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    string raw((istreambuf_iterator<char>(cin)), istreambuf_iterator<char>());
    string spaced;
    spaced.reserve(raw.size() * 3);
    for (char c : raw) {
        if (c == '(' || c == ')') {
            spaced.push_back(' ');
            spaced.push_back(c);
            spaced.push_back(' ');
        } else {
            spaced.push_back(c);
        }
    }
    {
        stringstream ss(spaced);
        string t;
        while (ss >> t) tokens.push_back(t);
    }
    pos = 0;
    while (pos < tokens.size()) {
        if (tokens[pos] != "(") { pos++; continue; }
        adj.clear();
        parse_node();
        vector<int> code = prufer_encode();
        for (size_t i = 0; i < code.size(); i++) {
            if (i) cout << ' ';
            cout << code[i];
        }
        cout << '\n';
    }
    return 0;
}
