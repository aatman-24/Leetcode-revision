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

Question : 230. Kth Smallest Element in a BST
Topic : BST
Problems : https://leetcode.com/problems/kth-smallest-element-in-a-bst/description/

==============================> Explanation <=============================================

Getting kth smallest, we know that BST inorder give you the right order and you need to pick up the kth element.

We use the stack apporach to print the inorder and stop once we visited kth element.

Getting kth largest, again we print the BST inorder but in reverse order (right, left, root) so that greater element come first and then smaller elements.

Check the code!!

For Brute Force:
-> we can say that, traverse the tree, in inorder manner and put in one array and then pick up the kth element.

==============================> Approach and Time Complexity <============================

1) Binary Search Tree
Time: O(K)
Space: O(N)

 */


/* Intuition:
Idea is that, we need to return kth element during the inorder traversal.
    We can use the Iterative approach of Inorder Trversal of BST, and keep
    track of visited element.

kthSmallest => left -> root -> right
kthLargest => right -> root -> left

*/
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        stack<TreeNode*> st;
        while (root != nullptr || !st.empty()) {
            while (root != nullptr) {
                st.push(root);
                root = root->left;                  // inorder(left)
            }
            root = st.top(); st.pop();


            k--;
            if (k == 0) {           // print root (inorder[root])
                return root->val;
            }

            root = root->right;     // inorder(right)
        }
        return -1;
    }
};


class Solution
{
public:
    int kthLargest(Node *root, int K)
    {
        stack<Node*> st;
        while (root != nullptr || !st.empty()) {
            while (root != nullptr) {
                st.push(root);
                root = root->right;             // inorder(right)
            }
            root = st.top(); st.pop();          // print root (inorder[root])
            K--;
            if (K == 0)
                return root->data;
            root = root->left;                  // inorder(left)
        }
        return -1;
    }
};