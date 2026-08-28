/*
    Knapsack problem is optmized here to fit better in memory instead of
    N * W;
    We change the columns to be the sum of values we already achieved instead of the backpack capacity.
    For each value I achieved in my bag, what is the least weight I achieved.
    I = INF
            0 1 2 3 4 5 6 7  8  9 10 11 12 13 14 15 16 17 18
(w=6,v=5) 0 0 I I I I I I I  I  I  I  I  I  I  I  I  I  I  I
(w=5,v=6) 1 0 I I I I 6 I I  I  I  I  I  I  I  I  I  I  I  I
(w=6,v=4) 2 0 I I I I 6 5 I  I  I  I 11  I  I  I  I  I  I  I
(w=6,v=6) 3 
(w=3,v=5) 4
(w=7,v=2) 5
          6

Feature, Standard Knapsack (Code 2),Value-based Knapsack (Code 1)
DP State,dp[weight] = max_value,dp[value] = min_weight
Complexity,O(N * W),O(N * Sum of Values)
Best Used When,"Capacity W is small (≤105), but Values are huge.","Values are small (≤105), but Capacity W is huge."
Initialization,0 (base case is zero value),Infinity (base case is infinite weight)
*/

#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 105;
const int MAXSUM = 100000;

int w[MAXN], v[MAXN];
ll dp[MAXN][MAXSUM+5];

ll knapsack_rec(int nitems, int capacity) {
    if (capacity == 0) return 0;
    if (nitems == 0) return (ll) 1e15;
    if(dp[nitems][capacity] != -1) return dp[nitems][capacity];

    ll not_taken = knapsack_rec(nitems -1, capacity);
    ll taken = (ll) 1e15;

    if(capacity >= v[nitems])
        taken = knapsack_rec(nitems -1, capacity - v[nitems]) + w[nitems];
    
    dp[nitems][capacity] = min(taken, not_taken);
    
    return dp[nitems][capacity]; 
}

int main(void) {
    int n, wgt;

    cin >> n >> wgt;

    memset(dp, -1, sizeof(dp));

    for(int i = 1; i <= n; i++)
        cin >> w[i] >> v[i];
    
    for (int sum = MAXSUM; sum >= 0; sum--) {
        if(knapsack_rec(n, sum) <= wgt) {
            cout << sum << "\n";
            break;
        }
    }
}
