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

int divide(int n, int k, int c) {
    //cout << "n: " << n << " k: " << k << " c: " << c << endl;

    if (n<k) {
        //cout << "a\n";
        return -1;
    }

    if (n==k) {
        //cout << "b\n";
        return c;
    }

    int chao = floor((double)n/2);
    //cout << "chao: " << chao << endl;

    int teto = ceil((double)n/2);
    //cout << "teto: " << teto << endl;
    c += 1;
    if(chao == k || teto == k) {
        //cout << "c\n";
        return c;
    }

    if(chao == teto) {
        //cout << "d\n";
        return divide(chao, k, c);
    }

    if(chao % 2 != 0){
        return divide(chao, k, c);
    } else if(teto % 2 != 0) {
        return divide(teto, k, c);
    }
}

void solve() {
    int n, k;
    cin >> n >> k;

    cout << divide(n, k, 0) << endl;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int tc;
    cin >> tc;
    while(tc--) solve();
}
