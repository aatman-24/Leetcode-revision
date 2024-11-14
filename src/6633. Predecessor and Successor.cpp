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

Question : 6633. Predecessor and Successor
Topic : BST
Problems : https://www.geeksforgeeks.org/problems/predecessor-and-successor/1
==============================> Explanation <=============================================


Predecessor: The predecessor of 𝐾 is the largest key in the BST that is smaller than K.
Successor: The SuccessorL of 𝐾 is the smallest key in the BST that is greater than K.

Approaches:

For given BST, I perform the inorder traversal it will give me the sorted array. So for any key, pre(key) is element just less than key and suc(key) is just next element to key.

Brute Force:
- I can perform the inorder traversal, put in one array, locate the key at ith index. return arr[i-1] as predecessor and arr[i+1] as successor.
Time: Traversal(O(N)) + locating key(O(N), O(logN)) => O(N)
Space: O(N)

#2) Second approach is that, inorder(left->root->right) so when we traverse the that time we can find the first node which is greater than (key) for successor
for predecssor keep track of pre until it is same as key or greater than key, that last updated pre is your predecessor..
Time: Traversal(O(N))
Space: O(N) -> O(1) (Morris Traversal)

#3) Best Approach, O(logN)

You already know how to find the pre-suc for BT.
pre => (node->left) then right most node. => moving right most node that time we are getting predessor
suc => (node->right) then left most node => moving left most node that itme we are getting successor

Remember this way.....

Optimization

Inorder Predecessor:
=> key < node->val => we move to leftSubtree... this time we don't update anything.
=> key >= node->val => we move to rightSubtree, but this time that node is latest predecessor. because that, node->val <= key....

Inorder Successor:
=> key > node->val => we move to rightSubtree... this time we don't update anything.
=> key <= node->val => we move to leftSubtree, but this time that node is latest Successor. because that, node->val >= key....

Try to practice via drawing...

==============================> Approach and Time Complexity <============================

1) BST
Time: O(N)
Space: O(H) (stack memory)
 */


// #3: My code
class Solution
{
public:

    Node* findPre(Node* root, int key, Node* pre) {
        if (root == nullptr) {
            return pre;
        }

        // found the node with given key, then search left-subtree right most node. ;
        if (root->key == key) {
            if (root->left == nullptr) return pre;   // left-subtree not found, return pre as its predecessor.
            Node* pre = root->left;
            while (pre->right != nullptr) {
                pre = pre->right;
            }
            return pre;
        }

        return key < (root->key) ? findPre(root->left, key, pre) : findPre(root->right, key, root);
    }


    Node* findSuc(Node* root, int key, Node* succ) {
        if (root == nullptr) {
            return succ;
        }

        if (root->key == key) {
            if (root->right == nullptr) return succ;
            Node* suc = root->right;
            while (suc->left != nullptr) {
                suc = suc->left;
            }
            return suc;
        }

        return key > (root->key) ? findSuc(root->right, key, succ) : findSuc(root->left, key, root) ;
    }



    void findPreSuc(Node* root, Node*& pre, Node*& suc, int key)
    {
        Node* pred = nullptr;
        pre = findPre(root, key, pred);
        Node* succ = nullptr;
        suc = findSuc(root, key, succ);
    }
};



// #3: Optimization
/* Intuition:
    Inorder Predecessor:
    => key < node->val => we move to leftSubtree... this time we don't update anything.
    => key >= node->val => we move to rightSubtree, but this time we considre that node, as latest predecessor. because that, node->val <= key....


Inorder Successor:
    => key > node->val => we move to rightSubtree... this time we don't update anything.
    => key <= node->val => we move to leftSubtree, but this time that node is latest Successor. because that, node->val >= key....

*/
class Solution
{
public:

    Node* findPre(Node* root, int key, Node* pre) {
        if (root == nullptr) {
            return pre;
        }

        // key is same, that time we also move the left... and if not found then we return predecssor found till now. (we can delete this code)
        // if(root->key == key) {
        //     if(root->left == nullptr) return pre;
        //     Node* pre = root->left;
        //     while(pre->right != nullptr) {
        //         pre = pre->right;
        //     }
        //     return pre;
        // }

        // the same logic is here, we just need to do key <= (root-key)
        return key <= (root->key) ? findPre(root->left, key, pre) : findPre(root->right, key, root);
    }


    Node* findSuc(Node* root, int key, Node* succ) {
        if (root == nullptr) {
            return succ;
        }

        // key is same, that time we also move the right... and if not found then we return succ found till now. (we can delete this code)
        // if(root->key == key) {
        //     if(root->right == nullptr) return succ;
        //     Node* suc = root->right;
        //     while(suc->left != nullptr) {
        //         suc = suc->left;
        //     }
        //     return suc;
        // }

        // the same logic is here, we just need to do key <= (root-key)
        return key >= (root->key) ? findSuc(root->right, key, succ) : findSuc(root->left, key, root) ;
    }



    void findPreSuc(Node* root, Node*& pre, Node*& suc, int key)
    {
        Node* pred = nullptr;
        pre = findPre(root, key, pred);
        Node* succ = nullptr;
        suc = findSuc(root, key, succ);
    }
};


// #4: Converted above code in iterative fashion
/* Intuition:

    Inorder Predecessor:
    => key < node->val => we move to leftSubtree... this time we don't update anything.
    => key >= node->val => we move to rightSubtree, but this time we considre that node, as latest predecessor. because that, node->val <= key....


    Inorder Successor:
    => key > node->val => we move to rightSubtree... this time we don't update anything.
    => key <= node->val => we move to leftSubtree, but this time that node is latest Successor. because that, node->val >= key....


*/
class Solution
{
public:

    Node* findPre(Node* root, int key) {
        Node* pre = nullptr;
        while (root != nullptr) {
            if (key <= root->key) {
                root = root->left;
            }
            else {                  // moving right means, node->val < key... so we update the predecessor.
                pre = root;
                root = root->right;
            }
        }
        return pre;

    }


    Node* findSuc(Node* root, int key) {
        Node* succ = nullptr;
        while (root != nullptr) {
            if (key >= root->key) {
                root = root->right;
            }
            else {              // moving left means, node->val > key... so we update the successor.
                succ = root;
                root = root->left;
            }
        }
        return succ;
    }

    void findPreSuc(Node* root, Node*& pre, Node*& suc, int key)
    {
        pre = findPre(root, key);
        suc = findSuc(root, key);
    }
};
