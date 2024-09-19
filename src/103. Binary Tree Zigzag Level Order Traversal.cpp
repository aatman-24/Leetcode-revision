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

Question : 103. Binary Tree Zigzag Level Order Traversal
Topic : Traversal
Problems : https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/description/

==============================> Explanation <=============================================

Level Order Traversal.

One time we need to add element from left -> right, next time we need to add from right -> left. So we manage one flag which decide
how we add element into level(array).

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
	vector<vector<int>> zigzagLevelOrder(TreeNode* root) {

		vector<vector<int>> zigzag;

		if (root == nullptr) {
			return zigzag;
		}

		queue<TreeNode*> q;
		q.push(root);

		// flag determine, how to add traverse level from left -> right or right -> left.
		bool leftRight = true;

		while (!q.empty()) {

			int size = q.size();
			vector<int> level;

			for (int i = 0; i < size; i++) {

				TreeNode* node = q.front(); q.pop();

				if (node->left)
					q.push(node->left);

				if (node->right)
					q.push(node->right);

				level.push_back(node->val);
			}

			// right->left, reverse the array and then add.
			if (!leftRight)
				reverse(level.begin(), level.end());

			zigzag.push_back(level);

			// toggle flag.
			leftRight = !leftRight;
		}

		return zigzag;

	}
};



// optimize, without reversing the array.
class Solution {
public:
	vector<vector<int>> zigzagLevelOrder(TreeNode* root) {

		vector<vector<int>> zigzag;

		if (root == nullptr) {
			return zigzag;
		}

		queue<TreeNode*> q;
		q.push(root);

		// flag determine, how to add traverse level from left -> right or right -> left.
		bool leftRight = true;

		while (!q.empty()) {

			int size = q.size();
			vector<int> level(size);

			for (int i = 0; i < size; i++) {

				TreeNode* node = q.front(); q.pop();

				if (node->left)
					q.push(node->left);

				if (node->right)
					q.push(node->right);

				// determine at which index we need to put based on leftRight flag.
				// either we fill up the value from the start or from the end.
				int index = (leftRight) ? i : (size - i - 1);
				level[index] = node->val;
			}

			zigzag.push_back(level);

			// toggle flag.
			leftRight = !leftRight;
		}

		return zigzag;

	}
};