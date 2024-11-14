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

Question : 98. Validate Binary Search Tree
Topic : BST
Problems : https://leetcode.com/problems/validate-binary-search-tree/description/
==============================> Explanation <=============================================

1) APPROACH: TOP-DOWN APPROACH.
- In this approach, we maintain one range(min, max) and check each node's value is within that range.
And when we visit left node => (min, parent->val)
And when we visit right node => (parent->val, max)

2) APPROACH: BOTTOM-UP APPROACH
- This is simliar to above one but here we first visit the leaf node and then create the range from there.
Here instead of using min and max value, I'm using those node itself(we can use values as well).
Idea is that,
	when we visit the parent,
		(left_subtree_max) < parent->val < (right_subtree_min)

	And we update the min and max,

			min = min(left_subtree_min, parent->val)
			max = max(right_subtree_max, parent->val)

Check the code... in this we have to handle mulitple conditions, so use it above one.

3) APPROACH: Iterative pre-order traversal
We use the in-order traversal... left->root->right.... we perform that and check left->val < root->val.... we don't need to check for right because we
are visiting tree in specific manner if that failed that means it is not the BST.
Check the code.....


==============================> Approach and Time Complexity <============================

1) BST
Time: O(N)
Space: O(H) (stack memory)
 */



// Top-down Approach
/* Intuition:
 we keep track of boundary (low, high), and we start traversal from root node and
 check node is within that range.
 For left_subtree_boundary will be (left, root->val)
 For right_subtree_boundary will be (root->val, high).
*/
class Solution {
public:

	bool support(TreeNode* root, long low, long high) {
		if (root == nullptr) return true;
		if (root->val <= low || root->val >= high) return false;
		return support(root->left, low, root->val) && support(root->right, root->val, high);

	}

	bool isValidBST(TreeNode* root) {
		long low = LONG_MIN;
		long high = LONG_MAX;
		return support(root, low, high);
	}
};


// 2) Bottom up approach (Tracking (low, high) as boundary)
/* Intuition:
We keep track of boundary (low, high), and we start from leaf node.
So for any node, we need to check three condition.
	1) left subtree is valid BST
	2) right subtree is valid BSt
	3) left_subtree_max < node-val && node->val < right_subtree_min
	And need to return rigth (low, high) range, which can be used to check for parent node.
	 For low = min(root->val, left_subtree_min)
	 For high = max(root->val, right_subtree_max).
*/
class Solution {
public:

	bool support(TreeNode* root, long &low, long &high) {

		// Base case:
		// For node==null, we return true.
		// We are setting up low=MAX && high=MIN, so for parent node bst condition become valid.
		// Try with pen and paper for one node you will get idea.
		if (root == nullptr) {
			low = LONG_MAX;
			high = LONG_MIN;
			return true;
		}

		long lh_low, lh_high;
		bool isLeftValid = support(root->left, lh_low, lh_high);
		if (!isLeftValid)
			return false;

		long rh_low, rh_high;
		bool isRightValid = support(root->right, rh_low, rh_high);
		if (!isRightValid)
			return false;

		// Left subtree is BST + Right subtree is BST
		// left_subtree_max_node < curNode && curNode < right_subtree_min_node
		if (root->val > lh_high && root->val < rh_low) {

			// need to return, lowest value of subtree with considering the current node.
			// which form the boudary for parent node.
			low = min((long)root->val, lh_low);

			// need to return, highest value of subtree with considering the current node.
			// which form the boudary for parent node.
			high = max((long)root->val, rh_high);

			return true;
		}

		return false;
	}

	bool isValidBST(TreeNode* root) {
		long low, high;
		return support(root, low, high);
	}
};


// 2) Bottom up approach (Tracking Node* as boundary)
/* Intuition:
	Simliar to above one, but sometime given attribute doesn't have high and low values. For example: BST with Custom Class. (Guessing, not sure)
	That time we need to keep track of entire node.
*/
class Solution {
public:

	bool support(TreeNode* root, TreeNode* &low, TreeNode* &high) {

		if (root == nullptr) {
			low = nullptr;
			high = nullptr;
			return true;
		}

		if (!root->left && !root->right) {
			low = root;
			high = root;
			return true;
		}


		TreeNode* low_left_subtree = nullptr;
		TreeNode*  high_left_subtree = nullptr;
		bool isLeftValid = support(root->left, low_left_subtree, high_left_subtree);
		if (!isLeftValid)
			return false;

		TreeNode* low_right_subtree = nullptr;
		TreeNode*  high_right_subtree = nullptr;
		bool isRightValid = support(root->right, low_right_subtree, high_right_subtree);
		if (!isRightValid)
			return false;

		// both child available.
		if (high_left_subtree && low_right_subtree) {
			if (high_left_subtree->val < root->val && root->val < low_right_subtree->val) {
				low = low_left_subtree;
				high = high_right_subtree;
				return true;
			}
			return false;
		}

		// left child available only
		if (low_right_subtree) {
			if (root->val < low_right_subtree->val) {
				low = root;
				high = high_right_subtree;
				return true;
			}
		}

		// right child available only
		if (high_left_subtree) {
			if (high_left_subtree->val < root->val) {
				high = root;
				low = low_left_subtree;
				return true;
			}
		}

		return false;
	}

	bool isValidBST(TreeNode* root) {
		TreeNode* low;
		TreeNode* high;
		return support(root, low, high);
	}
};


// 3) Iterative Approach
/* Intuition:
	We perform inorder traversal, and keep track of two values (pre) and (cur).
	For each pairs pre < cur, if that is not the case we return false.
*/
class Solution {
public:
	bool isValidBST(TreeNode* root) {
		if (root == nullptr)
			return true;
		stack<TreeNode*> st;
		TreeNode* pre = nullptr;		// we store the previous pointer
		while (root != nullptr || !st.empty()) {
			while (root != nullptr) {
				st.push(root);
				root = root->left;
			}
			root = st.top(); st.pop();
			if (pre != nullptr && pre->val >= root->val) return false;	// and validate for all the nodes when coming out of the stack.

			// update the poitners.
			pre = root;
			root = root->right;
		}
		return true;
	}
};



// This is code for inorder traversal using the stack.
class Solution {
public:
	bool inorderTraversal(TreeNode* root) {
		if (root == nullptr)
			return true;
		stack<TreeNode*> st;
		while (root != nullptr || !st.empty()) {
			while (root != nullptr) {
				st.push(root);
				root = root->left;		// left
			}
			root = st.top(); st.pop();
			cout << root->val << ' ';	// root(print value here)
			root = root->right;			// right
		}
		return true;
	}
};




