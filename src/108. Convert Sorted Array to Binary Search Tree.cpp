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

Question : 108. Convert Sorted Array to Binary Search Tree
Topic : BST
Problems : https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/description/

==============================> Explanation <=============================================

Straighfoward right....

find mid,
node=new Node(mid);
node->left = (left, mid-1)
node->right = (mid+1, right);


==============================> Approach and Time Complexity <============================

1) BST
Time: O(N)
Space: O(H) (stack memory)
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
/* Intuition:

Sorted array of length of N, from (0, N-1)
mid => (l + h) >> 1, become center node of BST.

Repeat same thing for,
	left_subtree => (0, mid-1)
	right_subtree=> (mid+1, 0)

*/
class Solution {
public:

	TreeNode* helper(vector<int> &nums, int low, int high) {
		if (low > high)
			return nullptr;
		int mid = (low + high) >> 1;
		TreeNode* node = new TreeNode(nums[mid]);
		node->left = helper(nums, low, mid - 1);
		node->right = helper(nums, mid + 1, high);
		return node;
	}

	TreeNode* sortedArrayToBST(vector<int>& nums) {
		int low = 0, high = nums.size() - 1;
		return helper(nums, low, high);
	}
};