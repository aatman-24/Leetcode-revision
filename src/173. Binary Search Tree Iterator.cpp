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
==============================> Description <=============================================

Question : 173. Binary Search Tree Iterator
Topic : BST
Problems : https://leetcode.com/problems/binary-search-tree-iterator/description/

==============================> Explanation <=============================================

This can be solved using inorder traversal using the stack.

        while(curr != nullptr || !st.empty()) {         // this condition tell us, whether there is next node or not.
            while(curr != nullptr) {                // look for the next node.
                st.push(curr);
                curr = curr -> left;
            }
            TreeNode* nextNode = st.top(); st.pop();        // got next node, return it...
            curr = nextNode->right;     // jump to the right subtree of node.   // before returning the nextNode... update the curr pointer
            return nextNode->val;
        }

Time: next().... worst case: O(N), avg case: O(logN)(perfect binary tree)

==============================> Approach and Time Complexity <============================


1) Binary Tree
Time: O(N)
Space: O(N)


 */

/* Intuition:

    One thing we know for sure that we need to use inorder traversal.

    We have recursion approach and iterative approach.

    In recursion approach, doing the backtracking with multiple fucntion involved is not easy.

    And Iterative approach using stack is perfect choice, because we use stack for backtracking

    We have just breakdown OG, algorithm in layer.

*/
class BSTIterator {
public:

    TreeNode* curr;
    stack<TreeNode*> st;

    BSTIterator(TreeNode* root) {
        curr = root;
    }

    int next() {                            // O(logN)
        while (hasNext()) {
            while (curr != nullptr) {
                st.push(curr);
                curr = curr -> left;
            }
            TreeNode* nextNode = st.top(); st.pop();
            curr = nextNode->right;     // jump to the right subtree of node.
            return nextNode->val;
        }
        return -1;          // given that, next() alwasy call valid way.. if there is node...
    }

    bool hasNext() {                    // O(1)
        // checking is there any node left or we reach at the end of tree during traversal.
        return (curr != nullptr || !st.empty());
    }
};


// This is code for inorder traversal using the stack.
class Solution {
public:
    bool inorderTraversal(TreeNode* root) {
        if (root == nullptr)
            return true;
        stack<TreeNode*> st;
        while (root != nullptr || !st.empty()) {    // check next node available or not
            while (root != nullptr) {
                st.push(root);
                root = root->left;      // left
            }
            root = st.top(); st.pop();
            cout << root->val << ' ';   // root(print value here)
            root = root->right;         // right
        }
        return true;
    }
};