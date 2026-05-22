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

void fillPanel(stack<char>& s) {
    s.push('F');
    s.push('A');
    s.push('C');
    s.push('E');
}

bool wins(stack<char> s, queue<char> q) {
    while(!q.empty()) {
        if (q.front() == s.top()){
            q.pop();
            s.pop();
        } else return false;
    }

    return true;
}

void removeFromPanel(stack<char>& s) {
    for(int i = 0; i < 4; i++) {
        s.pop();
    }
}

void loadIntoPanel(stack<char>& s, queue<char>& q) {
    while(!q.empty()) {
        s.push(q.front());
        q.pop();
    }
}

void solve() {
    int n, ans = 0;
    cin >> n;
    
    stack<char> s;
    queue<char> q;
    char c;
    fillPanel(s);
    while(n--) {
        for(int i = 0; i < 4; i++) {
            cin >> c;
            q.push(c);
        }

        if(wins(s, q)) {
            removeFromPanel(s);
            while(!q.empty()) q.pop();
            ans++;
        } else
            loadIntoPanel(s, q);

        if(s.empty()) fillPanel(s);
    }

    cout << ans << "\n";
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
}
