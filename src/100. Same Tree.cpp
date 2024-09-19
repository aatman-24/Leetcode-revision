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

Question : 100. Same Tree
Topic : Traversal
Problems : https://leetcode.com/problems/same-tree/description/

==============================> Explanation <=============================================

- I'm just checking the everything is same, strcuture and value and all that.

==============================> Approach and Time Complexity <============================

1) Queue
Time: O(N)
Space: O(N)

*/

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
    bool isSameTree(TreeNode* p, TreeNode* q) {

        if (p == nullptr || q == nullptr) {
            return p == q;
        }

        if (p->val != q->val)
            return false;

        if (!isSameTree(p->left, q->left))
            return false;


        return isSameTree(p->right, q->right);

    }
};