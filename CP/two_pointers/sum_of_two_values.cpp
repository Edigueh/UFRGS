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

void solve() {
    int n, k;
    cin >> n >> k;
    vector<pii> nums(n);
    for(int i = 0; i < n; i++) {
        cin >> nums[i].first;
        nums[i].second = i +1;
    }

    sort(all(nums));

    int l = 0, r = n - 1;

    while (r > l) {
        if(nums[l].first + nums[r].first == k) {
            cout << nums[l].second << " " << nums[r].second << "\n";
            return;
        }
        if (nums[l].first + nums[r].first > k)
            r--;
        else
            l++;
    }

    cout << "IMPOSSIBLE\n";
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    solve();
}
