#include <bits/stdc++.h>
using namespace std;

// DSU is a Disjoint Set Union (União de Conjuntos Disjuntos).
// É usado para encontrar a que componentes conexos um nodo pertence.
struct DSU {
    int n;
    vector<int> parent, rank;

    DSU(int N) {
        n = N;
        parent.resize(N);
        
        // Fills the parent vector with 0 incremented 1 by 1.
        iota(parent.begin(), parent.end(), 0);
        rank.resize(N);
    }

    int find(int tgt) {
        if(parent[tgt] == tgt)
            return tgt;
        return parent[tgt] = find(parent[tgt]);
    }

    void join(int c1, int c2) {
        c1 = find(c1);
        c2 = find(c2);

        if (c1 == c2)
            return;
        
        if(rank[c1] > rank[c2])
            swap(c1, c2);
        
        parent[c1] = c2;
        rank[c2] += (rank[c1] == rank[c2]);
    }
};

int main (void) {
    return EXIT_SUCCESS;
}