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

Question : 700. Search in a Binary Search Tree
Topic : BST
Problems : https://leetcode.com/problems/search-in-a-binary-search-tree/description/
==============================> Explanation <=============================================

Standard Search in BST.

==============================> Approach and Time Complexity <============================

1) BST
Time: O(logN)
Space: O(logN) (stack memory)
 */


class Solution {
public:
	TreeNode* searchBST(TreeNode* root, int val) {
		if (root == nullptr)
			return nullptr;

		if (root->val == val)
			return root;

		if (root->val < val)
			return searchBST(root->right, val);

		return searchBST(root->left, val);
	}
};