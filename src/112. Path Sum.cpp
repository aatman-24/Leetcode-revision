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

Question : 112. Path Sum
Topic : prefix-sum
Problems : https://leetcode.com/problems/path-sum/description/

==============================> Explanation <=============================================

During traversal of tree, I am computing prefix sum dynamically, and at the leaf node I check path has sum == targetSum or not.


==============================> Approach and Time Complexity <============================

1) Tree Traversal + prefix sum
Time: O(N)
Space: O(N)

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

	bool hasPathSumSupport(TreeNode* root, int curSum, int targetSum) {

		// Given that, last node must be leaf node to construct path. Only root node cannot build path.
		if (root == nullptr)
			return false;

		// We are checking of current node is leaf node, and curSum+root->val == targetSum.
		if (root -> left == nullptr && root->right == nullptr) {
			return curSum + root->val == targetSum;
		}

		// curNode is not leaf node, we check on left and right subtree.
		return hasPathSumSupport(root->left, curSum + root->val, targetSum) || hasPathSumSupport(root->right, curSum + root->val, targetSum);
	}


	bool hasPathSum(TreeNode* root, int targetSum) {

		return hasPathSumSupport(root, 0, targetSum);
	}
};