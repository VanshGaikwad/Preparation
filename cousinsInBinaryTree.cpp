#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/*
===========================================================
              COUSINS IN BINARY TREE
===========================================================

QUESTION:

Given the root of a binary tree and two different values
x and y, return true if x and y are cousins.

Two nodes are cousins if:

1. They are at the SAME DEPTH.
2. They have DIFFERENT PARENTS.

Example:

        1
       / \
      2   3
     /     \
    4       5

x = 4, y = 5

Output:
true

Because:
4 and 5 are at the same level.
Parent of 4 = 2
Parent of 5 = 3
Parents are different.


===========================================================
                       INTUITION
===========================================================

Use BFS because BFS processes the tree level by level.

For every level:

1. Find x and y.
2. Store their parents.
3. If both are found at the same level:
       parentX != parentY → true
       parentX == parentY → false
4. If only one is found at this level:
       They are at different depths → false.

===========================================================
                    INPUT FORMAT
===========================================================

T = number of test cases

For each test case:

n
n values of the tree in level-order
x y

Use -1 for NULL nodes.

Example:

1
5
1 2 3 4 5
4 5

Expected:
true

===========================================================
*/

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) {
        val = x;
        left = nullptr;
        right = nullptr;
    }
};


// Build binary tree from level-order input
TreeNode* buildTree(vector<int>& values) {

    if (values.empty() || values[0] == -1)
        return nullptr;

    TreeNode* root = new TreeNode(values[0]);

    queue<TreeNode*> q;
    q.push(root);

    int i = 1;

    while (!q.empty() && i < values.size()) {

        TreeNode* node = q.front();
        q.pop();

        // Left child
        if (i < values.size() && values[i] != -1) {
            node->left = new TreeNode(values[i]);
            q.push(node->left);
        }
        i++;

        // Right child
        if (i < values.size() && values[i] != -1) {
            node->right = new TreeNode(values[i]);
            q.push(node->right);
        }
        i++;
    }

    return root;
}


bool isCousins(TreeNode* root, int x, int y) {
    if(root == nullptr) return false;

    queue<pair<TreeNode*,TreeNode*>> q;
    q.push({root,nullptr});

    while(!q.empty()){

        int size = q.size();

        TreeNode* parentX = nullptr;
        TreeNode* parentY = nullptr;

        while(size--){
            auto [node , parent] = q.front();
            q.pop();

            if(node -> val == x ){
                parentX = parent;
            }
            if(node -> val == y){
                parentY = parent;
            }

            if(node -> left) {
                q.push({node -> left,node});

            }
            if(node -> right){
                q.push({node -> right, node});
            }
        }
        if(parentX && parentY){
            return parentX != parentY;
        }
        if(parentX || parentY) {return false;}

    }
    return false;
    

};


int main() {

    int T;
    cin >> T;

    while (T--) {

        int n;
        cin >> n;

        vector<int> values(n);

        for (int i = 0; i < n; i++) {
            cin >> values[i];
        }

        int x, y;
        cin >> x >> y;

        TreeNode* root = buildTree(values);

        cout << (isCousins(root, x, y) ? "true" : "false") << endl;
    }

    return 0;
}