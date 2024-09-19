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

Question : 199. Binary Tree Right Side View
Topic : Traversal
Problems : https://leetcode.com/problems/binary-tree-right-side-view/description/

==============================> Explanation <=============================================

1) Perform the Level Order Traversal and pickup the rightMost node in each level.
2) Perform modified preorder traversal but from right->left. (root -> right -> left).

Both take same time and space.

==============================> Approach and Time Complexity <============================

1) Level Order Traversal
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
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {

        if (root == nullptr)
            return {};

        // store the right view.
        vector<int> rightView;

        // for level order traversal.
        queue<TreeNode*> q;

        // add the root node init
        q.push(root);

        while (!q.empty()) {

            int size = q.size();

            for (int i = 0; i < size; i++) {

                TreeNode* node = q.front();
                q.pop();

                // performing in left->right. so right node will be at the end of the level.
                // In case we do right -> left, then right node will be found at 0th index in level.
                if (node->left)
                    q.push(node->left);

                if (node->right)
                    q.push(node->right);

                // If it is last node in current level we add this node as right view.
                if (i == size - 1) {
                    rightView.push_back(node->val);
                }
            }
        }

        return rightView;
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
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
public:
    void preOrder(TreeNode* root, vector<int>& treeLevels, int level) {

        if (root == nullptr)
            return;

        // if we are visiting this level first then that's right most node in that level.
        if (treeLevels[level] == INT_MIN) {
            treeLevels[level] = root->val;
        }

        // modified pre-order traversal to visit right node first.
        preOrder(root->right, treeLevels, level + 1);
        preOrder(root->left, treeLevels, level + 1);
    }

    vector<int> rightSideView(TreeNode* root) {

        if (root == nullptr)
            return {};

        // In question given that, maximum node can be 100. So max 100 level possible if it is right tree.
        vector<int> treeLevels(100, INT_MIN);
        int level = 0;
        preOrder(root, treeLevels, level);

        // Getting all the nodes which form the right view.
        vector<int> rightView;
        int i = 0;
        while (i < 100 && treeLevels[i] != INT_MIN) {
            rightView.push_back(treeLevels[i++]);
        }
        return rightView;
    }
};



// Simliar to above one. But we don't need that treeLevels array because we are storing right_view dynamically.
class Solution {
public:
    void preOrder(TreeNode* root, vector<int>& rightView, int level) {

        if (root == nullptr)
            return;

        // This is logic: We are visiting the rightMost node first.
        // rightView.size() indicate how many levels are visited < level (It means current root is rightMost node of new Level) so we add it.
        if (rightView.size() < level) {
            rightView.push_back(root->val);
        }

        preOrder(root->right, rightView, level + 1);
        preOrder(root->left, rightView, level + 1);
    }

    vector<int> rightSideView(TreeNode* root) {

        if (root == nullptr)
            return {};

        vector<int> rightView;
        int level = 1;
        preOrder(root, rightView, level);

        return rightView;
    }
};