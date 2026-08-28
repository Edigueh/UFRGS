/*
    N itens from 1..N (i);
    Each item has a weight Wi and a value Vi.
    You have a bag with a specific capacity of weight (W),
    meaning that the sum of the chosen items must be at max W.
    
    What is the biggest possible sum of item values that you can put
    in the bag?
*/

/*
    The idea is to make a table in the following format:
    Columns: 0 to W;
    Rows: 0 to N;
    Each row is indexed with the number of items available.
    Each column is indexed with the capacity of the bag.
    Each w,v pair is aiming at the row below it. 
    E.g W = 15, N = 6:
            0 1 2 3 4 5 6 7  8  9 10 11 12 13 14 15
(w=6,v=5) 0 0 0 0 0 0 0 0 0  0  0  0  0  0  0  0  0
(w=5,v=6) 1 0 0 0 0 0 0 5 5  5  5  5  5  5  5  5  5
(w=6,v=4) 2 0 0 0 0 0 6 6 6  6  6  6 11 11 11 11 11 
(w=6,v=6) 3 0 0 0 0 0 6 6 6  6  6  6 11 11 11 11 11
(w=3,v=5) 4 0 0 0 0 0 6 6 6  6  6  6 12 12 12 12 12 
(w=7,v=2) 5 0 0 0 5 5 6 6 6 11 11 11 12 12 12 17 17
          6 0 0 0 5 5 6 6 6 11 11 11 12 12 12 17 17
*/
#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MAXN = 10;
const int MAXW = 100005;

int weight[MAXN], value[MAXN];
ll dp[MAXN][MAXW];

ll knapsack(int nitems, int capacity) {
    if (nitems == 0 || capacity == 0) return 0;

    if(dp[nitems][capacity] != 0) return dp[nitems][capacity];

    ll not_taken = knapsack(nitems-1, capacity);
    ll taken = 0;

    if(capacity >= weight[nitems] )
        taken = knapsack(nitems-1, capacity - weight[nitems]) + value[nitems];

    dp[nitems][capacity] = max(taken, not_taken);
    
    return dp[nitems][capacity];
}

int main(void) {
    ios::sync_with_stdio();
    cin.tie(NULL);
    cout.tie(NULL);
    int nitems, capacity;
    cin >> nitems >> capacity;

    for (int item = 1; item <= nitems; item++) {
        cin >> weight[item] >> value[item];
    }

    cout << knapsack(nitems, capacity) << "\n";
}