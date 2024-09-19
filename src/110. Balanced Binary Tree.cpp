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

Question : 110. Balanced Binary Tree
Topic : Tree-Traversal
Problems : https://leetcode.com/problems/balanced-binary-tree/description/

==============================> Explanation <=============================================

for balanced binary tree,

    to check current root is balance or not we need to check,

            abs(depth(root->left)-depth(root->right)) <= 1

So basically, so we need to find depth of the each of node,

            depth(curr) = max(depth(root->left), depth(root->right)) + 1

if anytime any of subtree is not balanced it means, entire tree is not balanced.

==============================> Approach and Time Complexity <============================

1) Traversal
Time: O(N)
Space: O(1)

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

    bool isBalancedSupport(TreeNode* root, int &depth) {

        // leaf node, depth is 0.
        if (root == nullptr) {
            depth = 0;
            return true;
        }

        // get left depth
        int leftDepth = 0;
        bool isLeftBalanced = isBalancedSupport(root->left, leftDepth);

        // get right depth
        int rightDepth = 0;
        bool isRightBalanced = isBalancedSupport(root->right, rightDepth);

        // get max depth from child, add current node depth to that, so we can return it.
        depth = max(leftDepth, rightDepth) + 1;

        // both are balanced, add diff bw the depth is less than 1, it is balanced.
        if (isLeftBalanced && isRightBalanced) {
            return abs(leftDepth - rightDepth) <= 1;
        }

        // else return false.
        return false;
    }

    bool isBalanced(TreeNode* root) {
        int depth = 0;
        return isBalancedSupport(root, depth);
    }
};

// optimization via pre-checks.
class Solution {
public:

    bool isBalancedSupport(TreeNode* root, int &depth) {

        // leaf node, depth is 0.
        if (root == nullptr) {
            depth = 0;
            return true;
        }

        // get left depth
        int leftDepth = 0;
        bool isLeftBalanced = isBalancedSupport(root->left, leftDepth);

        // pre-checks
        if (!isLeftBalanced)
            return false;

        // get right depth
        int rightDepth = 0;
        bool isRightBalanced = isBalancedSupport(root->right, rightDepth);

        // pre-checks
        if (!isRightBalanced)
            return false;

        // get max depth from child, add current node depth to that, so we can return it.
        depth = max(leftDepth, rightDepth) + 1;

        // both are balanced, add diff bw the depth is less than 1, it is balanced.
        if (isLeftBalanced && isRightBalanced) {
            return abs(leftDepth - rightDepth) <= 1;
        }

        // else return false.
        return false;
    }

    bool isBalanced(TreeNode* root) {
        int depth = 0;
        return isBalancedSupport(root, depth);
    }
};