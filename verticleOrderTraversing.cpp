/*
===========================================================
QUESTION:
===========================================================

Given the root of a binary tree, return the vertical order
traversal of its nodes.

Rules:
1. Assign every node a vertical column:
      root       -> column 0
      left       -> column -1
      right      -> column +1

2. Assign every node a level:
      root       -> level 0
      child      -> level +1

3. Nodes should be returned:
      - From leftmost column to rightmost column
      - Within the same column, from top to bottom
      - If multiple nodes have the same column and level,
        sort them by their value.

Example:

            3
           / \
          9   20
             /  \
            15   7

Answer:

[
    [9],
    [3,15],
    [20],
    [7]
]


===========================================================
APPROACH:
===========================================================

1. Use BFS to traverse the tree.

2. For every node, store:
      node
      vertical/column
      level

   Queue stores:
      {node, vertical, level}

3. Use:

      map<int, map<int, multiset<int>>> mp;

   Structure:

      vertical
          ↓
        level
          ↓
       values

   Example:

      mp[0][2] = {15, 20}

   means:
      vertical = 0
      level = 2
      nodes = 15, 20

4. For every node:

      left  -> vertical - 1
      right -> vertical + 1
      child -> level + 1

5. If multiple nodes have the same vertical and level,
   insert their values into a multiset.

   multiset keeps them sorted automatically.

6. Finally, traverse the map:

      outer map   -> vertical order
      inner map   -> level order
      multiset    -> sorted values

7. Store every vertical column in the answer.


===========================================================
TIME COMPLEXITY:
===========================================================

BFS traversal:
    O(N)

Insertion into multiset:
    O(log N)

Overall:
    O(N log N)

Space:
    O(N)


===========================================================
CODE:
===========================================================
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

class Solution {
public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {

        // Queue stores:
        // node, vertical/column, level
        queue<tuple<TreeNode*, int,int>>q;
        q.push({root , 0 ,0});

        // vertical -> level -> sorted node values
        // verticle, lev, value
        map<int,map<int,multiset<int>>> mp;

        
        while(!q.empty()){
           
            vector<int> curr ;
           
            // Get current node and its position
            auto [node,verticle, level] = q.front();
            q.pop();

            // Store node according to:
            // vertical -> level -> value
            mp[verticle][level].insert(node->val);

            // Left child goes one column left
            // and one level down
            if(node -> left ){
                q.push({node->left,verticle -1, level +1});
            }

            // Right child goes one column right
            // and one level down
            if(node -> right ){
                q.push({node -> right, verticle + 1, level +1});
            }
        }

        vector<vector<int>> ans;

        // Traverse vertical columns
        // map automatically gives vertical order
        for(auto p : mp){

            vector<int> col;

            // Traverse levels from top to bottom
            // map automatically gives level order
            for(auto  q : p.second){

                // Add all values of this level
                // multiset keeps them sorted
                col.insert(col.end(),q.second.begin(),q.second.end());

            }

            // Add complete vertical column to answer
            ans.push_back(col);
        }

        return ans;
    }
};