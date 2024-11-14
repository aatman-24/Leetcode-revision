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

Question : 116. Populating Next Right Pointers in Each Node
Topic : BST
Problems : https://leetcode.com/problems/populating-next-right-pointers-in-each-node/description/

==============================> Explanation <=============================================

Idea is that,

For any node(consider it as parent node),

	Left node:
		parent->left->next = parent->right

	Right node:
		parent->right->next = parent->next->left(if null then use parent->next->right). (parent->next) must be available.

Idea is that, before connecting the child nodes next pointer, parent node next pointer must be linked.

==============================> Approach and Time Complexity <============================

1) BST
Time: O(N)
Space: O(H) (stack memory)
 */


/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
public:

	Node* getLeftMostNode(Node* currNextNode) {

		if (currNextNode == nullptr)		// currNextNode node is null then return null.
			return nullptr;

		if (currNextNode->left)			// return left node if available.
			return currNextNode->left;

		if (currNextNode->right)			// return right node if that available.
			return currNextNode->right;

		return nullptr;			// no children, return null.
	}



	Node* connect(Node* curr) {

		if (curr == nullptr)
			return curr;

		if (curr->left) {
			curr->left->next = curr->right;
		}

		if (curr->right) {
			curr->right->next = getLeftMostNode(curr->next);
		}

		// before moving to children, parent node next link must be available.
		connect(curr->left);
		connect(curr->right);

		return curr;
	}
};