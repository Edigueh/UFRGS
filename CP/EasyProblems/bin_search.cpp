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

#define P_MAX 1000000000000000000LL

ll n_athletes, pizzas_to_deliver;

ll athletes[200000];

// Returns the amount of pizas the team can carry on a given time.
bool try_deliver_pizzas_in_time(ll tgt_time) {
    ll tot_delivered_pizzas = 0;

    for(int i = 0; i < n_athletes; i++) {
        tot_delivered_pizzas += tgt_time/athletes[i] ;
        if (tot_delivered_pizzas >= pizzas_to_deliver) return true;
    }

    return tot_delivered_pizzas >= pizzas_to_deliver;
}

ll bs(ll lower_bound_time = 1, ll upper_bound_time = P_MAX) {
    ll minimum_time_to_deliver = -1, time_to_deliver;

    while(lower_bound_time <= upper_bound_time) {
        time_to_deliver = (lower_bound_time + upper_bound_time) / 2;
        if(try_deliver_pizzas_in_time(time_to_deliver)){
            upper_bound_time = time_to_deliver -1;
            minimum_time_to_deliver = time_to_deliver;
        } else {
            lower_bound_time = time_to_deliver + 1;
        }
    }

    return minimum_time_to_deliver;
}

void solve() {
    cin >> n_athletes >> pizzas_to_deliver;
    for (int i = 0; i < n_athletes; i++) cin >> athletes[i];

    cout << bs() << endl;
}
    

int main(void) {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    solve();
}
