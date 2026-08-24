#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;

int tin[maxn], tout[maxn];
int timer;
vector<int> graph[maxn];
vector<int> vec;
void dfs(int v, int p) {
    tin[v] = ++timer;

    for(auto a : graph[v]) {
        if(a == p) continue;
        dfs(a, v);
    }

    tout[v] = ++timer;
    vec.push_back(v);
}