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

Question : 9000. Tree Formation Using InOrder & Preorder
Topic : Traversal
Problems :

==============================> Explanation <=============================================

This is question, in which inorder & preorder || inorder & postorder is given we need to create tree using that.

Idea is that,

Inorder: LEFT -> ROOT -> RIGHT
Preorder: ROOT -> LEFT -> RIGHT

So we start visiting the preorder array(it means every time we get the root node of some of subtree), so using that root node we can divide the inorder array
into two ranges (left, root-1) and (root+1, right). Because left side of that root node is left subtree and right side of it is right subtree based on
inorder rules. And we keep track of that range(start, end) until start > end(nullptr). Check the code!!


Same goes for
Inorder: LEFT -> ROOT -> RIGHT
Postorder: LEFT -> RIGHT -> ROOT

Here, we can get the root node at the end of postorder, so we traverse it from the right->left and use the same concept. One edge case is there,
postorder: left -> right -> root(curr_node)... so obvisouly once we form this child node(root) we will be creating the right node first before left
node because of postorder and right_node even comes first when we visit it postorders array so keep check that in code as well.

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

    // Find the index of "val" in arr between start and end range.
    int findPosition(vector<int> arr, int start, int end, int val) {
        for (int i = start; i <= end; i++) {
            if (arr[i] == val)
                return i;
        }
        return -1;
    }


    // inorder = left -> root -> right
    // preorder = root -> left -> right
    TreeNode* buildTreePreSupport(vector<int> inorder, vector<int> preorder, int start, int end) {

        static int preIndex = 0;

        // base case.
        if (start > end) {
            return nullptr;
        }

        int currValue = preorder[preIndex++];

        TreeNode* node = new TreeNode(currValue);

        if (start == end) return node;

        int indexOfInorder = findPosition(inorder, start, end, currValue);

        // See the range breakdown and which one call first.
        // visting the preorder(root->left->right) (parent left is visited before the execution of current root)
        node->left = buildTreePreSupport(inorder, preorder, start, indexOfInorder - 1);
        node->right = buildTreePreSupport(inorder, preorder, indexOfInorder + 1, end);

        return node;
    }



    TreeNode* buildTreeFromPreOrderAndInOrder(vector<int> inorder, vector<int> preorder) {

        // Total number of nodes in tree.
        int N = 7;

        // First and last position of the element in array.
        int start = 0, end = N - 1;

        return buildTreePreSupport(inorder, preorder, start, end);
    }



    // inorder = left -> right -> root
    // postorder = left -> right -> root
    TreeNode* buildTreePostSupport(vector<int> inorder, vector<int> postorder, int start, int end) {

        static int postIndex = inorder.size() - 1;

        // base case.
        if (start > end) {
            return nullptr;
        }

        int currValue = postorder[postIndex--];

        TreeNode* node = new TreeNode(currValue);

        if (start == end) return node;

        int indexOfInorder = findPosition(inorder, start, end, currValue);

        // See the range breakdown and which one call first. Here we made the call on rigth node first because we are visiting the
        // postorder in which right node got visited before root (left->right->root)
        node->right = buildTreePostSupport(inorder, postorder, indexOfInorder + 1, end);
        node->left = buildTreePostSupport(inorder, postorder, start, indexOfInorder - 1);

        return node;
    }



    TreeNode* buildTreeFromPostOrderAndInOrder(vector<int> inorder, vector<int> postorder) {

        // Total number of nodes in tree.
        int N = inorder.size();

        // First and last position of the element in array.
        int start = 0, end = N - 1;

        return buildTreePostSupport(inorder, postorder, start, end);
    }

};




int main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("inputf.in", "r", stdin);
    freopen("outputf.in", "w", stdout);
#endif


    vector<int> inorder =  {1, 2, 4, 5, 3, 6, 7};
    vector<int> preorder = {4, 2, 1, 5, 6, 3, 7};
    vector<int> postorder = {1, 2, 3, 7, 6, 5, 4};
    Solution* s1 = new Solution();
    TreeNode* root = s1->buildTreeFromPreOrderAndInOrder(inorder, preorder);
    TreeNode* postRoot = s1->buildTreeFromPostOrderAndInOrder(inorder, postorder);
    inorderTraveral(root);
    cout << endl;
    preorderTraveral(root);


    cout << endl;
    inorderTraveral(postRoot);
    cout << endl;
    preorderTraveral(postRoot);


    return 0;
}

