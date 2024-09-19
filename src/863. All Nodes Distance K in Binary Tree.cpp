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

Question : 863. All Nodes Distance K in Binary Tree
Topic : Traversal
Problems : https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/description/

==============================> Explanation <=============================================

Getting all the nodes at K distance from given node in subtree is easy(check getNodesInSubtreeAtK()). But main diffculty is that, how you
get the nodes from adjancent nodes, because you can't traverse back to the parent.

Due to that reason, we have to use the stack memory and return value.

Idea is that,

    A
  /  \
 B   C

B is target node, I can find all the nodes in B subtree whose distance is at K. But we need to figure out, how to find the node from A subtree.
It is possible,
When we hit the target B, we return 0, (else -1)

    dist = 0 = B()
    So now A know that, target node is at (0 + 1) distance from him.
    First I check (dist(0) + 1) == K, if yes then A is also at kth distance, then no nodes apart from A can be at kth distance.
    If no, then I need to find all the nodes from C's subtree whose distance is = k - dist - 2. Here, dist = 0, (Why 2 ? B->A, A->C)
    Same way, A might have parent as well, for example Z,
    again we need to check for Z => (dist(1)[B->A] + 1[A->Z]) == K, if yes then no need to make other calls,
    If no, then I need to find all the ndoes from Z's right subtree whose distance is = K - dist - 2. Here dist = 1 (Why 2 ? A->Z, Z->right_subtree_node)

    So we do this recursively, until we don't find the parent node whose distance is at K from target.


    Our target node found on left subtree, then we are checking parent->right_node

    Same if we get the target node on right subtree, we need to check on parent->left_node.


Check the code!!





==============================> Approach and Time Complexity <============================

1) Level Order Traversal
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
class Solution {
public:

    vector<int> distAtKNodes;

    // will print out all the nodes in root's subtree whose distance is k from given root.
    void getNodesInSubtreeAtK(TreeNode* root, int k) {
        if (root == nullptr || k < 0)
            return;
        if (k == 0) {
            distAtKNodes.push_back(root->val);
        }
        getNodesInSubtreeAtK(root->left, k - 1);
        getNodesInSubtreeAtK(root->right, k - 1);
    }


    int distanceKSupport(TreeNode* root, TreeNode* target, int k) {

        if (root == nullptr)
            return -1;

        // found target.
        if (root == target) {
            // check all nodes of root's subtree whose are at k distance.
            getNodesInSubtreeAtK(root, k);
            return 0;
        }

        int leftDist = distanceKSupport(root->left, target, k);
        // leftDist != -1, it means we found the target node in subtree of root.
        // leftDist indicate the distance from root -> target, without connecting to root in path. So to add root we need to do leftDist + 1.
        if (leftDist != -1) {
            if (leftDist + 1 == k) {    // WE ADD +1 TO CHECK IF ROOT IS At k distance.
                distAtKNodes.push_back(root->val);  // Yes, add it in answer.
            }
            else {
                getNodesInSubtreeAtK(root->right, k - leftDist - 2);    // NO, then check on root-> right.
            }
            return leftDist + 1;        // return leftDist+1, +1 for indicate distance of adding root in path.
        }

        // same as above, but for right node.
        int rightDist = distanceKSupport(root->right, target, k);
        if (rightDist != -1) {
            if (rightDist + 1 == k) {
                distAtKNodes.push_back(root->val);
            }
            else {
                getNodesInSubtreeAtK(root->left, k - rightDist - 2);
            }
            return rightDist + 1;
        }

        return -1;
    }


    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        distanceKSupport(root, target, k);
        return distAtKNodes;
    }
};