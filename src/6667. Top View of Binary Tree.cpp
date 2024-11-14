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

Question : 6667. Top View of Binary Tree
Topic : BT
Problems : https://www.geeksforgeeks.org/problems/top-view-of-binary-tree/1

==============================> Explanation <=============================================

Question is print top view.

Idea is directly comes to my mind,

    root node is at center, dist = 0
    left subtree is on left side so all nodes distance from the root node < 0
    right subtree is on right side of root, so all nodes distance from the root node > 0
    So what I mean is + and - indicate the position of node, whether it is on left and right side and the value indicate how far it is from root node.

And when we print the top view, we need this attribute only. If you view the tree from top.

            1
          /   \
         2     3
        / \   / \
       4  5  6   7


You see this view, 4(-2), 2(-1), 1(0), 3(1), 7(2).... this is (dist) from the root node.

So we use that approach, if we are seeing the distnace first time then it must be seen first when we see tree from top view.

        root->left distance = parent_dist - 1
        root->right distance = parent_dist + 1

We keep track of dist and one map. At the end we get all the nodes from [less_distance -> highest_distance] order which is possible with map iteration.


#Wrong-Approach:
I thought I can do this by using simple traversal technique, but it won't work. Because If the tree is heavily left/right subtree, then its subtree nodes visited first rathar than adjacent node,
which is wrong, we need to visit nodes in level wise. Because top node whose level is minimum can hide the nodes whose level is more than it. But it cannot be true in reverse.

In simple...This is edge case,

            1
           / \
          2   6
         / \ / \
            3
           / \
             4
            / \
               5

You see if we use wrong approach then, all subnodes of 2 is visited first so it consider as top view, while actual top view consider "6" nodes not "5".


#Right-Approach:
That's why we shifted to level order traversal instead of in-pre-post.

==============================> Approach and Time Complexity <============================


1) Binary Tree
Time: O(N)
Space: O(l)


 */



// Wrong Approach.
class Solution
{

    void topViewHelper(Node* root, int dist, map<int, int> &mp) {

        if (root == nullptr) return;

        if (mp.count(dist) == 0) {
            mp[dist] = root->data;
        }

        topViewHelper(root->left, dist - 1, mp);
        topViewHelper(root->right, dist + 1, mp);
    }


public:
    //Function to return a list of nodes visible from the top view
    //from left to right in Binary Tree.
    vector<int> topView(Node *root)
    {

        map<int, int> mp;
        int dist = 0;
        topViewHelper(root, dist, mp);

        vector<int> top_view_sequence;

        for (auto it : mp) {
            top_view_sequence.push_back(it.second);
        }

        return top_view_sequence;
    }

};



/* Intuition:

    Idea is that, We need to see the Tree From Top View, and whatever node we are able to see, we consider it as top_view.

    So we know, root = 0 (center) then left_subtree_node = rootPoisition - 1, right_subtree_node = rootPosition + 1.

    So we use one map, to keep track of, node from center point(root location).

    Core logic is that, when we add any node with new distnace it will be consider as top_view, if we get another node with same
    distnace we don't consider it, because that node will be hidden when we see from top.

    We use the Level Order Traversal.

*/
class Solution
{

public:
    //Function to return a list of nodes visible from the top view
    //from left to right in Binary Tree.
    vector<int> topView(Node *root)
    {

        map<int, int> mp;
        int dist = 0;

        // level order Traversal.
        queue<pair<Node*, int>> q.size();

        // add root node;
        q.push({root, 0});

        while (!q.empty()) {

            int size = 0;

            for (int i = 0; i < size; i++) {

                auto it = q.front(); q.pop();
                Node* curr = it.first;
                int dist = it.second;

                // first time node visited at "dist" then it is part of top-view.
                if (mp.count(dist) == 0) {
                    mp[dist] = curr->data;
                }

                if (curr->left) {
                    q.push({curr->left, dist - 1});     // maintain dist from root.
                }

                if (curr->right) {
                    q.push({curr->right, dist + 1});     // maintain dist from root.
                }

            }
        }

        vector<int> top_view_sequence;

        for (auto it : mp) {
            top_view_sequence.push_back(it.second);
        }

        return top_view_sequence;
    }

};



