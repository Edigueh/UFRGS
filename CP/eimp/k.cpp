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

// Árvores de segmentos.
// Prefix sum.
/*
    [1, 2, 6, 1, 1, 7, 1]
     0  1  2  3  4  5  6

    soma acumulada = [1, 3, 9, 10, 11, 18, 19]
*/
/*
    Árvore de segmentos:
    - É uma arvore binária que contem associados a um nodo o valor da soma de um respectivo intervalo (inicio e fim).
    - Geralmente se representa em um vetor, alocando 4x o tamanho do vetor oficial em um vetor.
*/
void solve() {
    int n, k;
    cin >> n >> k;

    int acc = 0, h;
    vector<int> sums(n+1, 0);
    for(int i = 1; i <= n; i++) {
        cin >> h;
        acc += h;
        sums[i] = acc;
    }

    for (int i : sums) {
        cout << i << " ";
    } cout << endl;

    int ans;
    int sum = INT_MAX, x;

    if (n == k) {
        cout << 1 << endl;
        return;
    }

    for(int r = k; r <= n; r++) {
        x = sums[r] - sums[r-k];
        printf("r: %d\nr-k: %d\nsums[r]: %d\nsums[r-k]; %d\nx: %d\n",r,r-k, sums[r],sums[r-k],x);
        if (x < sum) {
            printf("minimum sum is %d, ans idx: %d\n", x,r-k+1);
            sum = x;
            ans = r-k+1;
        }
    }

    cout << ans << endl;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
}
