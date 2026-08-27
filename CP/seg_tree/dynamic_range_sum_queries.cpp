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
#define MAXN 2000010

ll  seg[4*MAXN];
ll  vet[MAXN];

ll build(int node, int l, int r) {
    if (l == r) return seg[node] = vet[l];
    int mid = (l + r) / 2;
    seg[node] = build(2*node, l, mid) + build(2*node+1, mid+1, r);
    return seg[node];
}

ll update(int node, int l, int r, int k, int u) {
if(l == r) return seg[node] = u;
    int mid = (l + r) / 2;
    if (k <= mid) {
        seg[node] = seg[2*node+1] + update(2*node, l, mid, k, u);
    } else if (k > mid) {
        seg[node] = seg[2*node] + update(2*node + 1, mid+1, r, k, u);
    }

    return seg[node];
}

ll sum(int node, int l, int r, int l0, int r0) {
    if (l >= l0 && r <= r0)
        return seg[node];
    else if(l > r0 || r < l0)
        return 0;
    int mid = (l + r) / 2;
    return sum(2*node, l, mid, l0, r0) + sum(2*node+1, mid+1, r, l0, r0);
}

void solve() {
    ll n, q;
    cin >> n >> q;

    for(int i = 1; i <= n; i++) cin >> vet[i];
    build(1, 1, n);

    while(q--) {
        int op;
        cin >> op;

        switch(op) {
            case 1:
                ll k, u;
                cin >> k >> u;
                update(1, 1, n, k, u);
                break;
            case 2:
                ll l0, r0;
                cin >> l0 >> r0;
                cout << sum(1, 1, n, l0, r0) << "\n";
                break;
        }
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
}
