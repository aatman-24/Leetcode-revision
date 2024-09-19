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

Question : 105. Construct Binary Tree from Preorder and Inorder Traversal
Topic : Tree Traversal
Problems : https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/description/

==============================> Explanation <=============================================

This is already solved.

preorder & inorder => Tree Formation
postorder & inorder => Tree Formation

check #9000. Tree Formation Using InOrder & Preorder

==============================> Approach and Time Complexity <============================

1) Tree Traversal
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
	int search(vector<int>& inorder, int val) {
		for (int i = 0; i < inorder.size(); i++) {
			if (inorder[i] == val)
				return i;
		}
		return -1;
	}

	TreeNode* buildTreeSupport(vector<int>& preorder, vector<int>& inorder,
	                           int begin, int end, int& preorderRunner) {
		// boundary, violate return nullptr.
		if (begin > end)
			return nullptr;

		// create node, root pickup from preorder(root->left->right)
		TreeNode* node = new TreeNode(preorder[preorderRunner++]);
		if (begin == end)     // leaf node
			return node;

		// create left and right node recursively.
		int indexInInorder = search(inorder, node->val);
		node->left = buildTreeSupport(preorder, inorder, begin,
		                              indexInInorder - 1, preorderRunner);
		node->right = buildTreeSupport(preorder, inorder, indexInInorder + 1,
		                               end, preorderRunner);

		return node;
	}

	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {

		// setup boundary for [begin, end] for root node.
		int begin = 0;
		int end = preorder.size() - 1;
		int preorderRunner = 0;

		return buildTreeSupport(preorder, inorder, begin, end, preorderRunner);
	}
};
