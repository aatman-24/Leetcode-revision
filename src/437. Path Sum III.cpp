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

Question : 437. Path Sum III
Topic : Traversal
Problems : https://leetcode.com/problems/path-sum-iii/description/

==============================> Explanation <=============================================

Parent: 113. Path Sum II

It's variation of #113 in which we consider path from root -> leaf node only, but here intermidate node is also construct path with any node from parent -> leaf.

Logic is still remain almost same in terms of traversal,

But we need to figure out way for intermidate paths.

Each tree from root -> leaf node is linkedlist(array). So we can use the concept of prefix_sum. We can calcualte the prefix sum on fly.

Using the map we can find out if there is sum = (curSum - targetSum) is already in map. If yes then we encounter path whose sum = targetSum.

We have to think about unwinding the position as well ?

Because in tree, each node can setup two diff LinkedList with left and right subtree. So when we visited left subtree and now we will visit right subtree
that time we don't want any compuation  of left-subtree into the right-subtree so we need to unwind such computation(check the code!!)

Given that,

node.val => [10^9], total nodes can be = 1000.

so we have to use long long for holding the curSum.. curSum can go upto 10^9 * 10^3 = 10^12....

==============================> Approach and Time Complexity <============================

1)Tree Traversal
Time: O(N)
Space: O(N) (stack memroy, map holding)

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

	// hashing for prefix-sum. Similar to Two-sum Apporach.
	unordered_map<long long, int> mp;

	// keep track of total paths.
	int totalPaths = 0;

	void pathSumSupport(TreeNode* root, long long curSum, int targetSum) {

		if (root == nullptr)
			return;

		// Adding into the curSum.
		curSum += root->val;

		// calculation of total paths. Simliar logic to TwoSum.
		if (mp.count(curSum - targetSum) && mp[curSum - targetSum] > 0) {
			totalPaths += mp[curSum - targetSum];
		}

		// We store curSum in our map. So in the future we can check (curSum - Target) is present into the map.
		mp[curSum] += 1;

		// visit on left subtree.
		pathSumSupport(root->left, curSum, targetSum);

		// visit on right subtree.
		pathSumSupport(root->right, curSum, targetSum);

		// UNWIND: We remove the curSum from the map because we are traversing back from node(leaf) -> parent. So node can't be in path of its adjancent ndoes.
		mp[curSum] -= 1;

		// UNWIND: Need to subtract the value from the curSum as well.
		curSum -= root->val;
	}

	int pathSum(TreeNode* root, int targetSum) {

		long long curSum = 0;
		mp[curSum] = 1;	// There is one path whose sum is 0 as initial position.

		pathSumSupport(root, curSum, targetSum);
		return totalPaths;
	}
};