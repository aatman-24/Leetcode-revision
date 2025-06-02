#include <bits/stdc++.h>
#define ll long long
#define REP(i,n) for(int i = 0; i < n; i++)
#define REP1(i,n) for(int i = 1; i <= n; i++)
#define debug cout << "Ok" << endl;
#define mod 1000000007
#define eps 1e-6

using namespace std;

typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef map<char, int> mci;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vi> vvi;
typedef map<int, int> mii;


/*
================================================================================
                                Problem Note
================================================================================

Problem: NC_47_Count Good Nodes in Binary Tree
Topic: BFS / DFS
Link: https://neetcode.io/problems/count-good-nodes-in-binary-tree?list=blind75

--------------------------------------------------------------------------------
Problem Summary:
--------------------------------------------------------------------------------
Given a binary tree, a node X in the tree is considered *good* if on the path
from the root to X there are no nodes with a value greater than X.

Return the number of good nodes in the binary tree.

--------------------------------------------------------------------------------
Intuition & Explanation:
--------------------------------------------------------------------------------
- We traverse the tree using either DFS or BFS.
- While traversing from root to leaf, we keep track of the maximum value seen so far (`currMax`).
- A node is considered "good" if its value is greater than or equal to `currMax`.
- Since the tree has no cycles, each path behaves like a unique linked list.

--------------------------------------------------------------------------------
Approach & Complexity:
--------------------------------------------------------------------------------
Approach: DFS or BFS
Time Complexity: O(N), where N is the number of nodes in the tree
Space Complexity: O(N), due to recursion stack or queue in DFS/BFS

*/


// DFS
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:

    int count = 0;

    void dfs(TreeNode* root, int curMax) {

        if (root == nullptr) return;

        if (root->val >= curMax) count++;

        dfs(root->left, max(curMax, root->val));
        dfs(root->right, max(curMax, root->val));
    }


    int goodNodes(TreeNode* root) {
        dfs(root, root->val);
        return count;
    }
};


// BFS
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int goodNodes(TreeNode* root) {

        queue<pair<TreeNode*, int>> q;          // {node, maxSoFar}
        q.push({root, INT_MIN});

        int count = 0;

        while (!q.empty()) {

            int size = q.size();

            for (int j = 0; j < size; j++) {

                auto [node, maximumSoFar] = q.front(); q.pop();

                if (node -> val >= maximumSoFar)
                    count++;

                if (node -> left)
                    q.push({node->left, max(node->val, maximumSoFar)});

                if (node -> right)
                    q.push({node->right, max(node->val, maximumSoFar)});
            }
        }

        return count;
    }
};