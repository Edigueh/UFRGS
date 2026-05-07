#include <bits/stdc++.h>
using namespace std;
// Determines a max subset of compatible intervals.
deque<pair<int,int>> scheduleByMaxNumberOfEvents(deque<pair<int,int>> intervals) {
    // Sorts the interval list for the 2nd component (end-time).
    sort(intervals.begin(), intervals.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    // List of selected intervals, initialized with the first interval.
    deque<pair<int,int>> selectedIntervals = {intervals.front()};
    intervals.pop_front();

    while (!intervals.empty()) {
        pair<int,int> cur = intervals.front(); intervals.pop_front();

        // If the interval is compatible with the last inserted interval in the selected ones.
        if (cur.first > selectedIntervals.back().second)
            selectedIntervals.push_back(cur);
    }

    return selectedIntervals;
}

void printScheduling(deque<pair<int,int>> interval) {
    cout << "[";
    for(pair<int,int> p : interval) {
        cout << " ";
        cout << p.first << "-" << p.second;
        cout << " ";
    }
    cout << "]" << endl;
}

int main(void) {
    deque<pair<int,int>>  interval1 = {{0,9},{1,2},{3,4},{5,6},{7,8}},
                          interval2 = {{0,5},{6,10},{4,7}},
                          interval3 = {{0,2},{1,4},{1,4},{1,4},{3,6},{5,8},{7,10},{9,12},{9,12},{9,12},{11,14}};

    printScheduling(scheduleByMaxNumberOfEvents(interval1));
    printScheduling(scheduleByMaxNumberOfEvents(interval2));
    printScheduling(scheduleByMaxNumberOfEvents(interval3));
}
