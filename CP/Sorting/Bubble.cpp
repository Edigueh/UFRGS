#include <bits/stdc++.h>
using namespace std;

void bubble(vector<int>& v) {
    int n = v.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (v[j] > v[j + 1]) {
                swap(v[j], v[j + 1]);
            }
        }
    }
}

int main(void) {
    vector<int> v = {5, 1, 4, 2, 8};

    bubble(v);
    for (auto i : v)
        cout << i << " ";
    cout << "\n";

    return 0;
}
