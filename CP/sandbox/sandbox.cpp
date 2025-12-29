#include <bits/stdc++.h>
using namespace std;

int main(void) {
    set<int> v = {1, 3, 5, 0, -1};

    auto it = min_element(v.begin(), v.end());

    cout << *it << "\n";
}
