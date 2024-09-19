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

Question : 572. Subtree of Another Tree
Topic : Traversal
Problems : https://leetcode.com/problems/subtree-of-another-tree/description/

==============================> Explanation <=============================================

We have to check given subRoot is one of root in main tree(root). It means that we have to traverse
each of the node, and check whether currNode is subRoot or not.

To check that, we need to check subtree from that node => currNode and given subRoot is same tree.

We are not checking T1 contains T2, we are checking one of subtree node is T2. So if found out T1 contains T2, and
some additions node in T1 are there, we need to return false.

==============================> Approach and Time Complexity <============================

1) Tree Traversal
Time: O(N)
Space: O(N)


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


    // Check both tree are same in structure wise and also value needs to be same.
    bool isSame(TreeNode* root1, TreeNode* root2) {

        if (root1 == nullptr || root2 == nullptr)
            return root1 == root2;

        if (root1->val != root2->val)
            return false;

        return isSame(root1->left, root2->left) && isSame(root1->right, root2->right);
    }

    bool isSubtree(TreeNode* root, TreeNode* subRoot) {

        // main tree is null, we return false(Given that subRoot contains atleast one node)
        if (root == nullptr) {
            return false;
        }

        // If current node is starting points then and only check.
        if (root->val == subRoot->val && isSame(root, subRoot))
            return true;

        // We check on both side of tree to find subRoot.
        return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
    }
};