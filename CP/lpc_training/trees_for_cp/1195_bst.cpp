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

typedef struct Tree {
    int val;
    struct Tree *l, *r;
} Tree;

Tree* insertBst(Tree *r, int node) {
    if (r == NULL) {    
        r = (Tree*)malloc(sizeof(Tree));
        r->val = node;
        r->l = NULL;
        r->r = NULL;
    } else {
        if (node < r->val) {
            r->l = insertBst(r->l, node);
        } else {
            r->r = insertBst(r->r, node);
        }
    }

    return r;
}

void prefix(Tree *r, bool &first) {
    if (r != NULL) {
        if (!first) cout << " ";
        cout << r->val;
        first = false;
        prefix(r->l, first);
        prefix(r->r, first);
    }
}

void infix(Tree *r, bool &first) {
    if (r != NULL) {
        infix(r->l, first);
        if (!first) cout << " ";
        cout << r->val;
        first = false;
        infix(r->r, first);
    }
}

void sufix(Tree *r, bool &first) {
    if (r != NULL) {
        sufix(r->l, first);
        sufix(r->r, first);
        if (!first) cout << " ";
        cout << r->val;
        first = false;
    }
}

void solve(int tc) {
    int n, v;
    cin >> n;
    Tree *bst = NULL;
    while(n--) {
        cin >> v;
        bst = insertBst(bst, v);
    }

    cout << "Case " << tc << ":\n";
    bool first;
    cout << "Pre.: "; first = true; prefix(bst, first); cout << "\n";
    cout << "In..: "; first = true; infix(bst, first); cout << "\n";
    cout << "Post: "; first = true; sufix(bst, first); cout << "\n";
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int tc;
    cin >> tc;
    for(int i = 1; i <= tc; i++) {
        solve(i);
        cout << "\n";
    }
    return 0;
}
