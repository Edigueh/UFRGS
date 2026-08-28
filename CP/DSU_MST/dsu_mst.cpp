#include <bits/stdc++.h>
using namespace std;

// DSU is a Disjoint Set Union (União de Conjuntos Disjuntos).
// É usado para encontrar a que componentes conexos um nodo pertence.
struct DSU {
    int n;
    vector<int> parent, rank;

    DSU(int N) {
        this->n = N;
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

struct Edge {
    int u, v, w;

    Edge(int U = 0, int V = 0, int W = 0) {
        this->u = U;
        this->v = V;
        this->w = W;
    }

    bool operator< (Edge another) const {
        return this->w < another.w;
    }
};

int main (void) {
    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);

    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back(Edge(u, v ,w));
    }

    sort(edges.begin(), edges.end());

    DSU dsu(n);

    vector<Edge> MST;
    for(Edge e : edges) {
        if(dsu.find(e.u) != dsu.find(e.v)) {
            MST.push_back(e);
            dsu.join(e.u, e.v);
        }
    }

    return EXIT_SUCCESS;
}