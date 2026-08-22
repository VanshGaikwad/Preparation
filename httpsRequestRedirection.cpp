#include <iostream>
#include<climits>
#include<cstdlib>
#include<vector>
using namespace std;

/*
============================================================
QUESTION: HTTP Request Redirection
============================================================

There are n servers on an infinite 2D plane.

locations[i] = [x, y] represents the coordinates of server i.

The request starts at locations[0], and locations[0] is visited.

Each value in redirectRecords represents a redirect direction:

Direction 1:
    (a,b) -> (a+Z, b+Z)

Direction 2:
    (a,b) -> (a+Z, b-Z)

Direction 3:
    (a,b) -> (a-Z, b+Z)

Direction 4:
    (a,b) -> (a-Z, b-Z)

Z is any positive integer.

For every redirect:
- Find the nearest UNVISITED server in that direction.
- If multiple servers are possible, choose the nearest one.
- If no valid server exists, skip the redirect.
- Whenever we move to a server, mark it visited.

Return the final server's coordinates.

============================================================
INPUT FORMAT
============================================================

First line:
T

For each test case:

n

Then n lines:
x y

Then:
m

Then m integers:
redirectRecords

============================================================
OUTPUT
============================================================

For each test case print:

x y

============================================================
EXAMPLE INPUT

2

4
3 4
1 2
7 8
5 6
2
1 4

3
0 0
1 1
2 2
2
1 1

============================================================
EXPECTED OUTPUT

1 2
2 2

============================================================
*/

class Solution {
public:

    vector<int> findFinalServer(
        vector<vector<int>>& locations,
        vector<int>& redirectRecords
    ) {

        // WRITE YOUR SOLUTION HERE
        int curr = 0;
        int n = locations.size();
        vector<bool>  visited(n,false);
        visited[0] = true;

        for(int dir : redirectRecords){

            int cx = locations[curr][0];
            int cy = locations[curr][1];

            int best =  -1;
            int minDis = INT_MAX;

            for(int i=0; i<n; i++){
                if(visited[i]){
                    continue;
                }
                int x = locations[i][0];
                int y = locations[i][1];

                bool valid = false;
                if(dir == 1 && x > cx && y > cy && x - cx == y - cy){
                    valid = true;
                }
                if(dir == 2 && x > cx &&  y < cy && x - cx == cy - y){
                    valid = true;
                }
                if(dir == 3 && x < cx && y > cy && cx - x == y - cy ){
                    valid = true;
                }
                if(dir == 4 && x < cx && y < cy && cx - x == cy - y){
                    valid = true;
                }

                if(valid){
                    int distance = abs(x - cx);
                    if(distance < minDis){
                        minDis = distance;
                        best = i;
                    }
                }
            }
            if(best != -1){
                curr = best ;
                visited[curr] = true;
            }

        }

        return locations[curr];
    }
};


int main() {

    int T;
    cin >> T;

    while (T--) {

        // Number of servers
        int n;
        cin >> n;

        // locations
        vector<vector<int>> locations(n, vector<int>(2));

        for (int i = 0; i < n; i++) {
            cin >> locations[i][0] >> locations[i][1];
        }

        // Number of redirects
        int m;
        cin >> m;

        // redirect records
        vector<int> redirectRecords(m);

        for (int i = 0; i < m; i++) {
            cin >> redirectRecords[i];
        }

        // Solve
        Solution sol;

        vector<int> ans =
            sol.findFinalServer(locations, redirectRecords);

        // Output
        cout << ans[0] << " " << ans[1] << "\n";
    }

    return 0;
}