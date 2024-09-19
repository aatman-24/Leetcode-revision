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

Question : 543. Diameter of Binary Tree
Topic : Traversal
Problems : https://leetcode.com/problems/diameter-of-binary-tree/description/

==============================> Explanation <=============================================

Idea is that, Maximum Diameter of binary tree must pass through atleast one root node for any subtree/tree.
So we get left_height and right_height of each of node, get max diameter by = left_height + right_height.
So we keep track of max diameter.


==============================> Approach and Time Complexity <============================

1) Tree Traversal
Time: O(N)
Space: O(N) (stack memory)

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

    int getHeight(TreeNode* root, int &maxDiameter) {

        // base condition.
        if (root == nullptr)
            return -1;

        int leftHeight = getHeight(root->left, maxDiameter) + 1;
        int rightHeight = getHeight(root->right, maxDiameter) + 1;

        maxDiameter = max(maxDiameter, leftHeight + rightHeight);
        return max(leftHeight, rightHeight);
    }



    int diameterOfBinaryTree(TreeNode* root) {
        int maxDiameter = INT_MIN;
        getHeight(root, maxDiameter);
        return maxDiameter;
    }
};