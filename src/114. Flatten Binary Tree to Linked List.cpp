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

Question : 114. Flatten Binary Tree to Linked List
Topic : BT
Problems : https://leetcode.com/problems/flatten-binary-tree-to-linked-list/description/
==============================> Explanation <=============================================

Check all the apporach behind.

Every apporach one this common,

how you make link between.... right_most_node of left subtree to right_subtreee first node.

1) My approach, flatten left and then right.
2) Simple postorder traversal, by keep track of last added node.
3) use of stack, to simulate above solution, idea is similar
4) same as above, using morris traversal (don't need to extra space) (one of the best())

==============================> Approach and Time Complexity <============================


1) Binary Tree
Time: O(N)
Space: O(N) -> O(1)


 */





// Approach, idea is that, support(root) flatten the subtree and return the last_added_node in chain so that it can be use by parent node.
// first we flatten left_subtree.... which return last_added_node as lastLinkedNode
// we make connection lastLinkedNode->right = root->right.
class Solution {
public:

    bool isLeaf(TreeNode* root) {
        return !root->left && !root->right;
    }

    TreeNode* support(TreeNode* &root) {
        if (root == nullptr || isLeaf(root)) return root;
        TreeNode* lastLinkedNode = support(root->left);         // last_added_node in left_subtree
        TreeNode* rightSubTree = root->right;                   // hold the curr->right pointer.
        if (lastLinkedNode) {                                   // not, null
            root->right = root->left;                           // swap left and right
            root->left = nullptr;
            lastLinkedNode->right = rightSubTree;               // make link, last_added_node->right = curr->right
        }
        return rightSubTree ? support(rightSubTree) : lastLinkedNode;       // rightSubTree is not null, then we get the last_added_node from that, otherwise curr lastLinkedNode will return.
    }

    void flatten(TreeNode* root) {
        support(root);
    }
};

// Algo: We keep track of last added node in chain as previous, We perform bottom-up approach. So we use the postorder_traversal(right, left, root) to create entire chain.
// First, we flatten right subtree(from bottom-up) so root->right is prev node, when we visit the left_subtree.
// Second, we flatten left subtree(from bottom-up) so last added node in chain -> right = previous
class Solution {
public:
    TreeNode* previous = nullptr;
    void flatten(TreeNode* root) {
        if (root == nullptr)
            return;
        flatten(root->right);
        flatten(root->left);

        // These three lines define the logic.
        root->right = previous;     // Visit the root node that time make link with last added node.
        root->left = nullptr;
        previous = root;            // keep track of last visited node.
    }
};


// Stack Approach: This approach is similar to above one, instead of recursion we are using stack here.
// Idea is that, we first add right and then left node in stack, so when we pop that time left node comes first so we make link node->right=st.top().
// Doing that... we make sure that, left_subtree last node->right = st.top()(right_subtree_first_node) because until we explored all the nodes in left_subtree
// then and after we traverse the right_subtree node.
class Solution {
public:
    void flatten(TreeNode* root) {
        if (root == nullptr)
            return;
        stack<TreeNode*> st;
        st.push(root);
        while (!st.empty()) {
            TreeNode* curr = st.top(); st.pop();
            if (curr->right)                // add right node first
                st.push(curr->right);
            if (curr->left)
                st.push(curr->left);        // add left node after right
            if (!st.empty())
                curr->right = st.top();     // so st.top() return left node.... root->right = left_node, and jump to left node for traversal in next iteration
            curr->left = nullptr;
        }
    }
};

// 4) Same as above one, but using morris traversal to perform that. Idea is same, before starting traversal on right side of subtree.... there should be connection
// left subtree last node -> right = right_sub_tree first node. which we try to get using morris traversal.
// For each node, we find the inorder predecessor of that node(left_most_node) -> right = curr->right.
// Check the code....
class Solution {
public:
    TreeNode* previous = nullptr;
    void flatten(TreeNode* root) {
        if (root == nullptr)
            return;
        while (root != nullptr) {
            if (root->left != nullptr) {            // if there is left_subtree, then and only, otherwise we directly jump to right node.

                // find inorder predecessor
                TreeNode* inPred = root->left;
                while (inPred->right)
                    inPred = inPred->right;

                // make link, leftMostNode->right = root->right
                inPred->right = root->right;

                // swap right, left link.
                root->right = root->left;

                root->left = nullptr;
            }
            root = root->right;
        }
    }
};