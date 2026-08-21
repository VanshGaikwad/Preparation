
#include <iostream>
#include <vector>
using namespace std;

/*
===========================================================
          COUNT THE NUMBER OF COMPLETE COMPONENTS
===========================================================

PROBLEM:

You are given an undirected graph with n vertices numbered
from 0 to n - 1.

You are also given an array edges where:

    edges[i] = [u, v]

represents an undirected edge between vertices u and v.

A connected component is called COMPLETE if every pair of
vertices in that component has an edge between them.

Return the number of complete connected components.

-----------------------------------------------------------

EXAMPLE:

Input:

n = 6

edges = [
    [0,1],
    [0,2],
    [1,2],
    [3,4]
]

Graph:

    0
   / \
  1---2

  3---4

  5

Components:

    {0,1,2} → 3 nodes, 3 edges → COMPLETE

    {3,4}   → 2 nodes, 1 edge  → COMPLETE

    {5}     → 1 node, 0 edges → COMPLETE

Answer = 3


===========================================================
                    KEY OBSERVATION
===========================================================

Suppose a component has:

    k = number of nodes

For the component to be COMPLETE, every pair of nodes must
have an edge.

Maximum possible number of edges:

                k * (k - 1)
                -----------
                     2

So:

    edges == k * (k - 1) / 2

means the component is COMPLETE.


===========================================================
                      APPROACH
===========================================================

1. Build an adjacency list.

2. Use DFS to find every connected component.

3. During DFS, maintain:

       node = number of nodes in the component
       edge = number of edges encountered

4. Because the graph is UNDIRECTED, every edge is counted
   twice in the adjacency list.

   Example:

       0 ---- 1

   Adjacency:

       0 -> 1
       1 -> 0

   So after DFS:

       edge /= 2


5. Check:

       edge == node * (node - 1) / 2

   If true, this component is complete.

6. Increment answer.


===========================================================
                     COMPLEXITY
===========================================================

Building adjacency list:

    O(E)

DFS:

    O(V + E)

Overall:

    Time  = O(V + E)
    Space = O(V + E)


===========================================================
                     TEST CASES
===========================================================

TEST CASE 1:

Input:

6 4
0 1
0 2
1 2
3 4

Expected Output:

3


-----------------------------------------------------------

TEST CASE 2:

Input:

6 5
0 1
0 2
1 2
3 4
3 5

Expected Output:

1


-----------------------------------------------------------

TEST CASE 3:

Input:

4 0

Expected Output:

4

Explanation:

There are 4 isolated vertices.

Each single vertex is considered a complete component.


-----------------------------------------------------------

TEST CASE 4:

Input:

5 4
0 1
1 2
2 3
3 4

Expected Output:

0


-----------------------------------------------------------

TEST CASE 5:

Input:

5 10
0 1
0 2
0 3
0 4
1 2
1 3
1 4
2 3
2 4
3 4

Expected Output:

1


===========================================================
                     SAMPLE INPUT
===========================================================

5

6 4
0 1
0 2
1 2
3 4

6 5
0 1
0 2
1 2
3 4
3 5

4 0

5 4
0 1
1 2
2 3
3 4

5 10
0 1
0 2
0 3
0 4
1 2
1 3
1 4
2 3
2 4
3 4


===========================================================
                    EXPECTED OUTPUT
===========================================================

3
1
4
0
1

===========================================================
*/


class Solution {
public:

    void dfs(int u,
             vector<int>& vis,
             int& node,
             int& edge,
             vector<vector<int>>& adj) {

        // Mark current node as visited
        vis[u] = 1;

        // Count this node
        node++;

        // Visit all neighbours
        for (int v : adj[u]) {

            // Count this edge
            edge++;

            // If neighbour is not visited
            if (vis[v] == -1) {
                dfs(v, vis, node, edge, adj);
            }
        }
    }


    int countCompleteComponents(int n, vector<vector<int>>& edges) {

        // -------------------------------------------------
        // Step 1: Build adjacency list
        // -------------------------------------------------

        vector<vector<int>> adj(n);

        for (auto x : edges) {

            // Undirected graph
            adj[x[0]].push_back(x[1]);
            adj[x[1]].push_back(x[0]);
        }


        // -------------------------------------------------
        // Step 2: Visited array
        // -------------------------------------------------

        vector<int> vis(n, -1);

        int ans = 0;


        // -------------------------------------------------
        // Step 3: Find every connected component
        // -------------------------------------------------

        for (int i = 0; i < n; i++) {

            if (vis[i] == -1) {

                int nodes = 0;
                int edge = 0;

                // DFS for this component
                dfs(i, vis, nodes, edge, adj);


                // -------------------------------------------------
                // Because graph is undirected, every edge was
                // counted twice.
                // -------------------------------------------------

                edge /= 2;


                // -------------------------------------------------
                // Step 4: Check whether component is complete
                // -------------------------------------------------

                if (edge == nodes * (nodes - 1) / 2) {
                    ans++;
                }
            }
        }


        return ans;
    }
};


int main() {

    int T;
    cin >> T;

    while (T--) {

        int n, m;

        cin >> n >> m;

        vector<vector<int>> edges(m, vector<int>(2));

        for (int i = 0; i < m; i++) {

            cin >> edges[i][0] >> edges[i][1];
        }

        Solution sol;

        cout << sol.countCompleteComponents(n, edges) << endl;
    }

    return 0;
}
