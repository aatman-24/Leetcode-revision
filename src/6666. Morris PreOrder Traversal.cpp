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

Question : 6666. Morris PreOrder Traversal
Topic : BT
Problems : https://www.naukri.com/code360/problems/preorder-traversal_3838888?topList=striver-sde-sheet-problems&utm_source=striver&utm_medium=website&count=25&search=&sort_entity=order&sort_order=ASC&page=1&leftPanelTabValue=PROBLEM

==============================> Explanation <=============================================

Parent Problem: 94 Morris Inorder Traversal.

Inorder => left -> root -> right
preorder=> root -> left -> right

Only change in preorder morris traversal is that, for preorder, we print the value of root node before moving to the
left subtree.

It means, when we make the temporary link, that time we print(root), and once that link is created then we move to left subtree,
which was not case for inorder traversal.

==============================> Approach and Time Complexity <============================


1) Binary Tree
Time: O(N)
Space: O(l)


 */



// Morris Trversal => Inorder
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
            else {     // left node present, that time we first find inorderSuccessor of curr_node and and make temp link.


                // 1) Find rightMost node of left subtree.
                TreeNode* inorderSuccessor = curr->left;
                while (inorderSuccessor->right != nullptr && inorderSuccessor->right != curr) {
                    inorderSuccessor = inorderSuccessor->right;
                }

                // 2) First time, you make temp link. inorderSuccessor-> right = curr.
                if (inorderSuccessor->right == nullptr) {
                    inorderSuccessor->right = curr;
                    curr = curr->left;
                } else {        // 3) second time, when we come to curr node, and perform same stop, inorderSuccessor->right = curr, so we break that link and move to right subtree.

                    inorder_sequence.push_back(curr->val);                  // Change is here for preorder Traversal. When we break the link, left_subtree_already_visited.
                    // left(visited) -> root(visiting) -> right(will visit)
                    curr = curr->right;
                    inorderSuccessor->right = nullptr;

                }


            }

        }

        return inorder_sequence;

    }
};



// morris Traversal => PreOrder
vector<int> getPreOrderTraversal(TreeNode *root) {

    vector<int> preorder_sequence;

    TreeNode* curr = root;

    while (curr != nullptr) {

        if (curr->left == nullptr) {

            preorder_sequence.push_back(root->val);

            curr = curr -> right;

        } else {


            TreeNode* inorderSuccessor = curr->left;

            while (inorderSuccessor->right && inorderSuccessor->right != curr) {
                inorderSuccessor = inorderSuccessor->right;
            }

            if (inorderSuccessor->right == nullptr) {

                inorderSuccessor->right = curr;

                preorder_sequence.push_back(curr->val);     // root(visited)->left(next will visit)->right(will visit)

                curr = curr->left;

            } else {

                inorderSuccessor->right = nullptr;

                curr = curr -> right;
            }


        }

    }

    return preorder_traversal;

}