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

void solve(int n) {
    deque<int> dq;
    for(int i = 1; i <= n; i++) dq.push_back(i);

    vector<int> discarded;
    while(dq.size() >= 2) {
        discarded.push_back(dq.front()); dq.pop_front();
        int c = dq.front(); dq.pop_front();
        dq.push_back(c);
    }

    cout << "Discarded cards: ";
    for(auto it = discarded.begin(); it != discarded.end(); ++it) {
        if (next(it) == discarded.end()) {
            cout << *it << "\n";
            break;
        }
        cout << *it << ", ";
    }

    cout << "Remaining card: " << dq.front() << "\n";
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    while(n != 0){
        solve(n);
        cin >> n;
    }
}
