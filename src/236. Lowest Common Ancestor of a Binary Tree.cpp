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

Question : 236. Lowest Common Ancestor of a Binary Tree
Topic : Traversal
Problems : https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/description/

==============================> Explanation <=============================================

Lowest Common Ancestor => It is lowest ancestor(parent) of any two node.

    1
   / \
  2   3

1 is anecstor of 2 and 3.

    1
   /
  2

1 is ancestor of 1 and 2.

Given that p and q, we have to find the LCA of that nodes.

Two case possibles:

If both node p and q, are part of one subtree, then one of the node itself is ancestor. (#case-2 in picture)
If both node p and q, are part of diff subtree, then we have to find that common node.

Idea is that, to find LCA in generic way,

For each node,
- we check either it is one of the node or not, if yes then we check on its subtress and other node also found in any subtree, then that node itself is LCA. (#case-2)
- if not, then we check its both subtree hold one-one node, if yes then it become LCA.  (Check the code!!)


#2

But here, It is given that p and q are both part of given tree, so it is obvious that there is LCA.

So we can optimize a little bit here,

if we get root == p, root == q, we can return that node itself without checking its subtree. If root is LCA(case-1), then any other nodes above
root can't become LCA. so we don't need to check in subtree of root to find other nodes, because it will be there.

==============================> Approach and Time Complexity <============================

1) Traversal
Time: O(N)
Space: O(N)

 */



/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */


// Generic solution, Given that p&q "can be" or "can not be" part of given tree. That time we need to check all nodes to find p and q both..
class Solution {
public:

    // It is null, first time count == 2, then that node become lca, after we dont' change it.
    TreeNode* lca = nullptr;

    bool lcaSupport(TreeNode* root, TreeNode* p, TreeNode* q) {

        if (root == nullptr)
            return false;

        // keep track of both nodes encounter. If count == 2, it means p and q both got visited.
        int count = 0;

        // for case-1, root is one of the nodes.
        if (root == p || root == q)
            count++;

        // We still exploring its left and right subtree. To find both nodes.
        bool first = lcaSupport(root->left, p, q);
        if (first) {
            count++;
        }

        bool second = lcaSupport(root->right, p, q);
        if (second) {
            count++;
        }

        // Here we found both nodes, lca node is still null, it means current node is root.
        if (count == 2 && !lca) {
            lca = root;
        }

        // root and subtree holds the one of the node or not, will determine by the count.
        return count > 0;
    }



    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        lcaSupport(root, p, q);
        return lca;
    }
};




/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr || root == p || root == q)
            return root;

        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);

        if (left && right)
            return root;

        return left != nullptr ? left : right;
    }
};