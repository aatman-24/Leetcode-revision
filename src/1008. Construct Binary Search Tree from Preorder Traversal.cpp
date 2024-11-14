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

Question : 1008. Construct Binary Search Tree from Preorder Traversal
Topic : BST
Problems : https://leetcode.com/problems/construct-binary-search-tree-from-preorder-traversal/description/
==============================> Explanation <=============================================


#1: O(NlogN) solution using splitIndex.
PreOrder = root->left->right
So we maintain the (left, right) subarray in which left is root of that range because preorder traversal,
and we find the splitIndex such that arr[left] < arr[splitIndex], (next greater element than arr[left](root))
And we divide that range,
	 root->left = (left+1, splitIndex-1) (left_subtree)
	 root->right =(splitIndex, right) (right_subtree)
Each time we have to find splitIndex, which take O(N) time and considering height of tree there will be O(logN) calls.
Total time is = O(NlogN).

#2: O(N) stack solution

Idea is that, we iterave the given preorder(root->left->right) array and consider each node as root node. If we are getting the (5 -> 3 -> 1) then we add it
in root->left->left manner until some order change happen(preorder[i](node which are visiting) > last_added_node) during iteration. So when we see node is coming have higher value then
added node then we need to unwind(for that reason we will use the stack) until we get the node whose value is > preorder[i] and we add preorder[i] as right node...



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

	Idea is that, PreOrder Traversal: (root, left, right)

	So for range (left, right) => arr[left] become the root of subtree.

	And to find left_subtree and right_subtree, we have to find splitIndex.

	For that, we know root->val < root->right.... so find first greater element than curr "root",

	so from (splitIndex, right) form the right_subtree, and
			(left+1, splitIndex) form the left_subtree.

*/
class Solution {
public:

	int findNextGreaterElementIndex(vector<int> &arr, int val, int l, int h) {
		for (int i = l; i <= h; i++) {
			if (arr[i] > val) {
				return i;
			}
		}
		return h + 1;		// incase not found return h+1 as answer.
	}


	TreeNode* support(vector<int>& preorder, int low, int high) {

		if (low > high)
			return nullptr;

		TreeNode* node = new TreeNode(preorder[low]);	// current low is root.
		if (low == high) {
			return node;
		}

		// splitIndex points to next greater element.
		int splitIndex = findNextGreaterElementIndex(preorder, preorder[low], low + 1, high);
		node->left = support(preorder, low + 1, splitIndex - 1);		// (low+1, splitIndex-1) < (low)(node) <(splitIndex, high)
		node->right = support(preorder, splitIndex, high);
		return node;
	}


	TreeNode* bstFromPreorder(vector<int>& preorder) {

		int low = 0, high = preorder.size() - 1;

		return support(preorder, low, high);
	}

};

// #2 Iterative approach

/* Intuition:

	Idea is that, We have given preorder traveral of BST(root->left->right).

	We already knew inorder traversal and preorder trversal of BST using stack. So we just try to do that in reverse manner(from array => BST).

	Here is how,

		We maintain one stack, in which we push left subtree nodes which are added as part of left subtree.

		For ex: preorder: 5 3 1 => st: [1, 3, 5]

	We start from 0th index and consider it as root node, and add into the stack.

	After start iteration from the index=1,

		If curr->val < st.top()->val,

			We add curr node as left child of st.top() node.

		Else,

			We popped out all elements which are less than "curNode",

			And we add curNode as, right child of last minimal node than "curNode".

			Ex: 5 2 1 => st: [1, 2, 5]

			currNode: 3

				1 popped out: [2, 5]
				2 popped out: [5]

				Add 3, as right child of "2".
*/
class Solution {
public:

	TreeNode* bstFromPreorder(vector<int>& preorder) {

		if (preorder.size() == 0)
			return nullptr;

		stack<TreeNode*> st;
		TreeNode* root = new TreeNode(preorder[0]);		// first node will be the root node.
		st.push(root);									// add root into the st.
		for (int i = 1; i < preorder.size(); i++) {
			TreeNode* node = new TreeNode(preorder[i]);	// create new node
			if (preorder[i] < st.top()->val) {			// find its position, if it is in leftsubtree, make left node of st.top().
				st.top()->left = node;
			}
			// remove all the node whose value is less than current node,
			// and add current node as right child of last minimum node than current node.
			else {

				TreeNode* parent = st.top();
				while (!st.empty() && preorder[i] > st.top()->val) {
					parent = st.top(); st.pop();
				}
				parent->right = node;					// make link
			}
			st.push(node);			// add current node.
		}

		return root;

	}


};