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

Question : 113. Path Sum II
Topic : Traversal
Problems : https://leetcode.com/problems/path-sum-ii/description/

==============================> Explanation <=============================================

Parent: 112. Path Sum

It's similar to #112 where we just return true/false if such path found. Here we need to return entire path.

Logic is still the same,

We traverse the tree in preorder manner and keep track of curSum and curPath. If we visit the leaf node and curSum == targetSum, curPath is one of the answer.

***When we traverse back from leaf -> parent, that time we unwind the leaf node from curPath and curSum. So it got deducted and others can path can be build up.

Check the code!!

==============================> Approach and Time Complexity <============================

1)Tree Traversal
Time: O(N)
Space: O(N) (stack memroy, curpath holding)

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
	vector<vector<int>> paths;

	void pathSumSupport(TreeNode* root, vector<int> curPath, int curSum, int targetSum) {

		if (root == nullptr)
			return;

		// Adding the current node into the path.
		curPath.push_back(root->val);

		// Adding into the curSum.
		curSum += root->val;

		if (root->left == nullptr && root->right == nullptr) {
			if (curSum == targetSum) {
				paths.push_back(curPath);
			}
		}

		// visit on left subtree.
		pathSumSupport(root->left, curPath, curSum, targetSum);

		// visit on right subtree.
		pathSumSupport(root->right, curPath, curSum, targetSum);

		// Removing the current node from the path.
		curPath.pop_back();

		// Need to subtract the value from the curSum as well.
		curSum -= root->val;
	}

	vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
		vector<int> curPath;
		pathSumSupport(root, curPath, 0, targetSum);
		return paths;
	}
};