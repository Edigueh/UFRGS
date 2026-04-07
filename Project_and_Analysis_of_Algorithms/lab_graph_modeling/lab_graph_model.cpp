#include <bits/stdc++.h>
using namespace std;

void adj_list_to_adj_matrix(unordered_map<int, vector<int>> adj, vector<vector<int>> *matrix) {
    for(auto const&[node, neighbours] : adj) {
        for (int neighbour : neighbours) {
            (*matrix)[node][neighbour] = 1;
        }
    }
}

int main(void) {
    unordered_map<int, vector<int>> adj = {
        {0, {1, 2}},
        {1, {0, 2}},
        {2, {0, 1}},
        {3, {}}
    };

    vector<vector<int>> matrix = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };

    adj_list_to_adj_matrix(adj, &matrix);

    for(vector<int> i : matrix){
        for (int j : i) {
            cout << j << " ";
        }
        cout << "\n";
    }
}
