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

Question : 101. Symmetric Tree
Topic : Traversal
Problems : https://leetcode.com/problems/symmetric-tree/description/

==============================> Explanation <=============================================

1) If both left and right side are Symmetric Tree from mainRoot, then we can invert one of the side, then left side of root
and right side of mainRoot should be the same tree(in strcuture and value wise).

2) We can call given Tree Symmetric Tree if,

    Parent -> left -> left = Parent -> right -> right
    Parent -> left -> right = Parent -> right -> left

We use this logic to itarate into the tree and compare the nodes.


        1
       / \
      2   2
     / \ / \
    4  5 5 4

So we check symmetric property at level wise. level = 0 (root) don't need to check.
start from level 1, left.val == right.val...
            level 2, left.left.val == right.right.val
                      left.right.val = right.left.val

            so instead of doing that we can traverse the left->left, right->right || left->right, right->val recurisve manner to chck for all ndoes.


==============================> Approach and Time Complexity <============================

1) Invert Tree
Time: O(N/2)(Invert) + O(N/2) to compare
Space: O(N)(stack memeroy)

2) Traverse Comparsion
Time: O(N/2) (Checking half of the node)
Space: O(N/2)


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

    bool isSame(TreeNode* leftChild, TreeNode* rightChild) {

        if (leftChild == nullptr || rightChild == nullptr)
            return leftChild == rightChild;

        if (leftChild->val != rightChild->val)
            return false;

        return isSame(leftChild->left, rightChild->left) && isSame(leftChild->right, rightChild->right);
    }

    void invertRightSubtree(TreeNode* root) {
        if (root == nullptr)
            return;

        TreeNode* temp = root->left;
        root->left = root->right;
        root->right = temp;

        invertRightSubtree(root->left);
        invertRightSubtree(root->right);
    }



    bool isSymmetric(TreeNode* root) {
        if (root == nullptr)
            return true;
        invertRightSubtree(root->right);
        return isSame(root->left, root->right);
    }
};



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

    bool isSymmetricHelper(TreeNode* left, TreeNode* right) {

        if (left == nullptr || right == nullptr)
            return left == right;

        // both left and right value should be same.
        if (left->val != righ->val)
            return false;


        // checking symmetric we need to compare this.
        // P -> L -> L = P -> R -> R
        // P -> L -> R = P -> R -> L

        return isSymmetricHelper(left->left, right->right) && isSymmetricHelper(left->right, right->left);
    }


    bool isSymmetric(TreeNode* root) {
        if (root == nullptr)
            return true;
        return isSymmetricHelper(root->left, root->right);
    }
};
