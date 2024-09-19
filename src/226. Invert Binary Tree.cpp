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

Question : 226. Invert Binary Tree
Topic : Tree
Problems : https://leetcode.com/problems/invert-binary-tree/description/

==============================> Explanation <=============================================

Idea is that, for each node swap left and right childs to make it invert.

==============================> Approach and Time Complexity <============================

1) PreOrder Traversal
Time: O(N)
Space: O(N) (stack space)

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
    TreeNode* invertTree(TreeNode* root) {

        // root is null or it is leaf node return it.
        if (root == nullptr || (!root->left && !root->right))
            return root;

        // swap left and right child links to make inversion
        TreeNode* temp = root->left;
        root->left = root->right;
        root->right = temp;

        // do the same for the child nodes as well.
        root->left = invertTree(root->left);
        root->right = invertTree(root->right);

        // return root
        return root;
    }
};
