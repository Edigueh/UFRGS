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

int card_val(int card) {
    return card > 10 ? 10 : card;
}

void solve() {
    int n;
    cin >> n;

    int j1, j2;
    cin >> j1 >> j2;

    int m1, m2;
    cin >> m1 >> m2;

    int cards = 0, c;
    
    // cartas em jogo - quantidade
    vector<int> deck(14, 0);
    deck[m1]++;
    deck[m2]++;
    deck[j1]++;
    deck[j2]++;
    for (int i = 1; i <= n; i++) {
       cin >> c;
       deck[c]++;
       cards += card_val(c);
    }

    int tot_m = card_val(m1) + card_val(m2) + cards;
    int tot_j = card_val(j1) + card_val(j2) + cards;

    for (int i = 1; i <= 13; i++) {
        if(deck[i] < 4) {
            if ((tot_j+card_val(i) > 23 && tot_m + card_val(i) <= 23) || tot_m + card_val(i) == 23) {
                cout << i << endl;
                return;
            }
        }
    }

    cout << -1 << endl;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
}
