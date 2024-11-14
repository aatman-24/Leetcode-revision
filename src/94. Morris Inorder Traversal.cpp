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

Question : 94. Morris Inorder Traversal
Topic : BT
Problems : https://leetcode.com/problems/binary-tree-inorder-traversal/description/

==============================> Explanation <=============================================

This algorithm has 2 iteration.

1) Make temp link(predecessor->right = curr_node).
2) Break that temp link, and move to right subtree.

1) Idea is that, for curr node we first find Inorder Predecessor(rightmost node of left subtree) and make temporary link predecessor->right = curr.
2)  And we again come to that node, that time we break the link and move to right subtree of curr node.

Using morris Inorder Traversal is that we don't need space O(N) for recursion traversal or using stack.

It is space optimized solution.

==============================> Approach and Time Complexity <============================

1) Binary Tree
Time: O(N)
Space: O(l)


 */


class Solution {
public:

    // morris inorder Traversal. O(N) - O(1).
    vector<int> inorderTraversal(TreeNode* root) {

        vector<int> inorder_sequence;

        TreeNode* curr = root;

        while (curr != NULL) {

            if (curr->left == nullptr) {
                inorder_sequence.push_back(curr->val);          // left(null) -> root(print this) -> right(jump on right)
                curr = curr -> right;
            }

            // left node present, that time we first find inorderPredessor of curr_node and and make temp link.
            else {

                // 1) Find rightMost node of left subtree.
                TreeNode* inorderPredessor = curr->left;
                while (inorderPredessor->right != nullptr && inorderPredessor->right != curr) {
                    inorderPredessor = inorderPredessor->right;
                }

                // 2) First time, you make temp link. inorderPredessor-> right = curr.
                if (inorderPredessor->right == nullptr) {
                    inorderPredessor->right = curr;
                    curr = curr->left;
                }
                // 3) second time, when we come to curr node, and perform same steps, inorderPredessor->right = curr, so we break that link and move to right subtree.
                else {
                    inorder_sequence.push_back(curr->val);
                    curr = curr->right;
                    inorderPredessor->right = nullptr;

                }
            }

        }
        return inorder_sequence;
    }
};
