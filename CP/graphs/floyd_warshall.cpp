// Used to find the minimum distance between all pair of nodes.
#include <bits/stdc++.h>
using namespace std;
#define MAX 1000

int graph[MAX][MAX], dist[MAX][MAX];


void floyd_warshall(int n, int m) {
    for(int i = 1; i<= n; i++) {
        for(int j = 1; j<= n; j++) { 
            if(i == j) dist[i][j] = 0;
            else dist[i][j] = INT_MAX;
        }
    }

    while (m--) {
        int a, b;
        int c;
        cin >> a >> b >> c;

        dist[a][b] = min(dist[a][b], c);
        dist[b][a] = min(dist[b][a], c);
    }

    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j<= n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}
