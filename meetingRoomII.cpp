#include <iostream>
#include<vector>
#include<queue>
#include <algorithm>
using namespace std;

/*
===========================================================
                    MEETING ROOMS II
===========================================================

Given an array of meeting time intervals where
intervals[i] = [start_i, end_i], return the minimum number
of conference rooms required.

Example 1:

Input:
[[0,30],[5,10],[15,20]]

Output:
2

Explanation:
Since the meetings [0,30] and [5,10] overlap, we need
two conference rooms.

Example 2:

Input:
[[7,10],[2,4]]

Output:
1


CONSTRAINTS:

1 <= intervals.length <= 10^4
0 <= start_i < end_i <= 10^6


===========================================================
                       INTUITION
===========================================================

We need to find the maximum number of meetings happening
at the same time.

1. Sort meetings by their START TIME.

2. We need to know which currently running meeting
   finishes FIRST.

3. Use a MIN HEAP to store END TIMES.

4. For every meeting:

       current_start >= earliest_end

   means a room has become free, so REUSE that room.

   Otherwise, we need a NEW ROOM.

5. The size of the heap represents the number of
   currently occupied rooms.

===========================================================
*/

int minMeetingRooms(vector<vector<int>>& intervals) {

    // YOUR CODE HERE
    sort(intervals.begin(), intervals.end(), [](auto &a, auto&b){
        return a[0] < b[0];
    });

    priority_queue<int, vector<int>, greater<int>> pq;
    pq.push(intervals[0][1]);

    for(int i=1; i<intervals.size(); i++){
        if(intervals[i][0] >= pq.top()){
            pq.pop();
        }
        pq.push(intervals[i][1]);

    }
    return pq.size();

}


int main() {

    // Number of test cases
    int T;
    cin >> T;

    while (T--) {

        int n;
        cin >> n;

        vector<vector<int>> intervals(n, vector<int>(2));

        for (int i = 0; i < n; i++) {
            cin >> intervals[i][0] >> intervals[i][1];
        }

        cout << minMeetingRooms(intervals) << endl;
    }

    return 0;
}