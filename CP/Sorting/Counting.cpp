#include <bits/stdc++.h>
using namespace std;

// Works only for non-negative integers.
void countingSort(vector<int>& v) {
    int n = v.size();
    vector<int> bk(*max_element(v.begin(), v.end()) + 1, 0);

    for (int i : v) {
        bk[i]++;
    }

    int j = 0;
    for (int i = 0; i < bk.size(); i++) {
        while(bk[i]--) {
            v[j] = i;
            j++;
        }
    }
}

void printVector(vector<int>& v) {
    for (auto i : v)
        cout << i << " ";
    cout << "\n";
}

int main(void) {
    vector<int> v = {1, 3, 6, 9, 9, 3, 5, 9};

    cout << "Before sort: ";
    printVector(v);

    countingSort(v);

    cout << "After sort: ";
    printVector(v);
    
    cout << "\n";
}
