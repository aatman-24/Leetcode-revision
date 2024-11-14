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

Question : 5551 Floor And Ceil in BST
Topic : BST
Problems : https://www.naukri.com/code360/problems/floor-from-bst_920457
==============================> Explanation <=============================================

Already solved this problem.

Floor() => inorder predecessor
Ceil() => inorder successor

==============================> Approach and Time Complexity <============================


1) Binary Tree
Time: O(N)
Space: O(H)


 */

/* Intuition:

    Floor() => Inorder Predecessor

    Moving to left subtree, we don't update predecessor, but when we
    move to right subtree we consider root as choice of predecessor, among
    visited nodes.

*/
int floorInBST(TreeNode<int> * root, int X)     // floor(x): either x or just smaller than x
{
    TreeNode<int>* inPred = nullptr;
    while (root != nullptr) {
        if (X < root->val) {            // when we move from root->left_child, we don't update the inorderPredecessor
            root = root->left;
        }
        else {
            inPred = root;              // moving from root -> right_child, we update the inPred.. becasue root->val < root->right->val.
            root = root->right;
        }
    }
    return inPred->val;
}


/* Intuition:

    Ceil() => Inorder Successor

    Moving to right subtree, we don't update Successor, but when we
    move to left subtree we consider root as choice of Successor, among
    visited nodes.

*/
int findCeil(BinaryTreeNode<int> *root, int x) {    // ceil(x): either x or just greater than x
    BinaryTreeNode<int>* inorderSucc = nullptr;
    while (root != nullptr) {
        if (root->data == x)
            return root->data;
        if (x > root->data) {                       // moving from root->right, we don't update
            root = root->right;
        }
        else {
            inorderSucc = root;                     // moving from root->left_child we udpate, becasue root->val > root->left->val.
            root = root->left;
        }
    }
    return inorderSucc->data;
}