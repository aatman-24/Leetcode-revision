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

Question : 3344. Children Sum in a Binary Tree
Topic : BT
Problems : https://www.geeksforgeeks.org/problems/children-sum-parent/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=hildren-sum-parent
==============================> Explanation <=============================================

Idea is that,

We go bottom-up approach.

We start to check from the leaf node -> root node. Each time we reach any node its value should be = left_subtree_sum + right_subtree_sum.

If condition doesn't match we return false. If met, we just return that node_value(= left_subtree_sum + right_subtree_sum).

Check the code, and you will get idea.



==============================> Approach and Time Complexity <============================


1) Post-Order Traversal
Time: O(N)
Space: O(N) (in worst case, based on tree structure).


 */




/* Intuition:

    Idea is that,

    We start to check from the leaf node -> root node. Each time we reach any node its value should be = left_subtree_sum + right_subtree_sum.

    If condition doesn't match we return false. If met, we just return that node_value(= left_subtree_sum + right_subtree_sum).


*/

class Solution {
public:
    bool helper(Node *root, int &curSum)
    {
        // base case: set curSum as 0, return true.
        if (root == nullptr) {
            curSum = 0;
            return true;
        }

        // base case: When node is leaf node, return it's value and return true.
        if (!root->left && !root->right) {
            curSum = root->data;
            return true;
        }

        // Otherwise we get the sum from it's left-subtree and right-subtree, in case any of that subtree node won't able to meet condition that time
        // we return false.
        int leftSum, rightSum;
        bool leftValid = helper(root->left, leftSum);
        if (!leftValid) return false;

        bool rightValid = helper(root->right, rightSum);
        if (!rightValid) return false;

        // set the curSum as root->data(or leftSum+rightSum)
        curSum = root->data;

        // match sum, return true else false.
        return (leftSum + rightSum == root->data) ? true : false;
    }

    int isSumProperty(Node *root) {
        int curSum = 0;
        return helper(root, curSum);
    }


};