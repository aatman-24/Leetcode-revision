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
                                Problem Description
================================================================================

Problem: 94. Binary Tree Inorder Traversal (Iterative)
Topic: Binary Tree
Link: https://leetcode.com/problems/binary-tree-inorder-traversal/description/

================================================================================
                                Problem Summary
================================================================================

Given the root of a binary tree, return the inorder traversal of its nodes' values.

Inorder traversal follows the order:
    Left Subtree → Root → Right Subtree

The goal is to implement this traversal **iteratively** (not recursively), using a stack.

================================================================================
                                Intuition & Explanation
================================================================================

To perform an inorder traversal iteratively, we simulate the recursion using a stack.

### Traversal Order:
    Left → Root → Right

### Idea:
- Use a stack to store the path while moving to the leftmost node.
- For each node:
  1. Push all its left children onto the stack.
  2. When the leftmost is reached (`curr == nullptr`), pop from the stack.
  3. Process the node (i.e., store its value).
  4. Move to the right child of that node and repeat.

### Example Case:
- If the leftmost node is a **leaf**, after processing it, the right child is `null`, so we backtrack by popping the next node from the stack (the parent).
- If the node has a **right subtree**, we repeat the same left-subtree traversal on the right child.

================================================================================
                          Approach & Time/Space Complexity
================================================================================

Approach: Stack-based iterative traversal

Time Complexity: O(N)
- Every node is visited exactly once.

Space Complexity: O(N)
- In the worst case (completely unbalanced tree), the stack could hold up to N nodes.

*/



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

    vector<int> inorderTraversal(TreeNode* root) {

        vector<int> inorderSeq;

        // for keep track of current node.
        stack<TreeNode*> st;

        while (root != nullptr || !st.empty()) {

            // Inorder: left => root => right
            while (root != NULL) {
                st.push(root);
                root = root->left;
            }

            // popped the leftMost node
            root = st.top(); st.pop();

            // put the current node into seq
            inorderSeq.push_back(root->val);

            // visit the rightMost node, if any
            root = root -> right;
        }

        return inorderSeq;

    }
};