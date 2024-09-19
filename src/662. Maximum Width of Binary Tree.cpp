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

Question : 662. Maximum Width of Binary Tree
Topic : Level Order Traversal
Problems : https://leetcode.com/problems/maximum-width-of-binary-tree/description/

==============================> Explanation <=============================================

Intuition is that,

Getting maximum width in each level, means we have to perform the level order traversal.

We can get both extreme and see how many nodes are in between them. But the actual hurdle start when we need to count NULL between them as well.

which is not possible with standard level order traversal.

This can be solved using one trick.

We know that in binary tree, root(pos), left_child(2*pos), right_child(2*pos+1). (if we start pos = 0)
We know that in binary tree, root(pos), left_child(2*pos+1), right_child(2*pos+2). (if we start pos = 1)

So we use the same concept here, we push the (static) position of node, so we can count diff between it without adding the null nodes.

But there is one problem,

Given that, tree can have 3000 nodes, and if we calculate position = 2 * pos, .... it can go upto 2^3000 (which we can't store it in long long) in case of strict left tree.

To handle this situation,

we can subtract the above level, left extreme so that it won't generate big number in case of left or right tree. And we care about position within level, not positino among levels
because we are calculating the diff between left extreme and right extreme within level.

Check the code!!


==============================> Approach and Time Complexity <============================

1) Level Order Traversal
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
	int widthOfBinaryTree(TreeNode* root) {

		if (root == nullptr)
			return 0; // no-node, 0 width.

		queue<pair<TreeNode*, long long>> q;
		q.push({root, 0});

		// maximum width
		long long maxWidth = 1;

		while (!q.empty()) {

			int size = q.size();

			long long startOfLevel = q.front().second;
			long long endOfLevel = q.back().second;

			for (int i = 0; i < size; i++) {

				TreeNode* node = q.front().first;
				long long parentPos = q.front().second;
				q.pop();

				// main logic is here: For level L, we need to subtract above level left extreme position(2^(L-1))
				// It means that for child node, we calcualte the index position by subtracting current level left extreme(startOfLevel).
				long long idxPos = parentPos - startOfLevel;

				if (node->left) {
					q.push({node->left, 2 * idxPos});
				}

				if (node->right) {
					q.push({node->right, 2 * idxPos + 1});
				}

			}

			maxWidth = max(maxWidth, (endOfLevel - startOfLevel + 1));
		}

		return maxWidth;
	}
};