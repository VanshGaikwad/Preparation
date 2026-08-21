#include <iostream>
#include<vector>
#include<queue>
using namespace std;

/*
===========================================================
          COUSINS IN BINARY TREE II - 2641
===========================================================

QUESTION:

Given the root of a binary tree, replace the value of each
node in the tree with the sum of the values of all its
cousins.

Two nodes are cousins if they have the same depth but
different parents.

If a node has no cousins, replace its value with 0.


Example:

            1
          /   \
         2     3
        / \   / \
       4   5 6   7

For node 4:
Cousins = 6 and 7
New value = 6 + 7 = 13

For node 6:
Cousins = 4 and 5
New value = 4 + 5 = 9


===========================================================
                       INTUITION
===========================================================

We use BFS level by level.

For every current level:

1. Find the TOTAL SUM of all children of the current
   level's nodes.

2. For each current node, calculate its SIBLING SUM:

       left child + right child

3. A child's cousins are:

       TOTAL SUM
            -
       SIBLING SUM

   So:

       child->val = total - siblingSum

4. Push the children into the queue for the next level.

Important:

The current nodes are pushed back into the queue after
calculating the total, so that we can process the SAME
current level again and calculate sibling sums.

Flow:

       Current Level
            ↓
       Calculate total
            ↓
       Process same level again
            ↓
       Calculate sibling sum
            ↓
       child value = total - sibling sum
            ↓
       Push children
            ↓
       Next level


Example:

        1
       / \
      2   3
     / \ / \
    4  5 6  7

At level [2,3]:

Total of children:

    4 + 5 + 6 + 7 = 22

For node 2:

    siblingSum = 4 + 5 = 9

    4's new value = 22 - 9 = 13
    5's new value = 22 - 9 = 13

For node 3:

    siblingSum = 6 + 7 = 13

    6's new value = 22 - 13 = 9
    7's new value = 22 - 13 = 9


===========================================================
                       COMPLEXITY
===========================================================

Time:  O(n)

Space: O(n)


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


// Build tree from level-order input.
// Use -1 for NULL.
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

        if (i < values.size() && values[i] != -1) {
            node->left = new TreeNode(values[i]);
            q.push(node->left);
        }

        i++;

        if (i < values.size() && values[i] != -1) {
            node->right = new TreeNode(values[i]);
            q.push(node->right);
        }

        i++;
    }

    return root;
}


// Print tree in level order
void printTree(TreeNode* root) {

    if (root == nullptr) {
        cout << "[]\n";
        return;
    }

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {

        TreeNode* node = q.front();
        q.pop();

        cout << node->val << " ";

        if (node->left)
            q.push(node->left);

        if (node->right)
            q.push(node->right);
    }

    cout << endl;
}


TreeNode* replaceValueInTree(TreeNode* root) {

    // YOUR CODE HERE
    if(root == nullptr) return nullptr;

        queue<TreeNode*> q;

        q.push(root);
        root -> val = 0;

        while(!q.empty()){
            int size = q.size();
            int total = 0;
            
            for(int i =0; i<size ; i++){
                TreeNode* node = q.front();
                q.pop();
                
                if(node -> left){
                   
                    total += node -> left -> val;
                }
                if(node -> right){
                   
                    total += node -> right -> val;
                }
                q.push(node);
            }
            for(int i=0; i<size; i++){
                TreeNode* node = q.front();
                q.pop();
                int sibSum = 0;

               
                if(node -> left){
                    sibSum  += node -> left -> val;
                }
                if(node -> right ){
                    sibSum += node -> right -> val;
                }
                if(node -> left ){
                    node -> left -> val = total - sibSum;
                    q.push(node -> left);
                }
                if(node -> right){
                    node -> right -> val = total - sibSum;
                    q.push(node -> right);
                }
                

            }
        }
        return root;


}


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

        TreeNode* root = buildTree(values);

        root = replaceValueInTree(root);

        printTree(root);
    }

    return 0;
}