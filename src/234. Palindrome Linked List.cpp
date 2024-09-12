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

Question : 234. Palindrome Linked List
Topic : Stack, Two pointer
Problems : https://leetcode.com/problems/palindrome-linked-list/description/

==============================> Explanation <=============================================

Idea behind this apporach is that,

If we want to test the palindrome LL, then we need compare the elements (mid-k) and (mid+k). K=1,2....

But we can't traverse reverse in single LL.

1) We save it somewhere, like I did using stack, why stack ? Because it gives LIFO property which can be used for comparsion as well.

2) We make the half of the list reverse and then compare it.


==============================> Approach and Time Complexity <============================


1) Fast & Slow Pointer
Time: O(N)
Space: O(1)

*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:

    int lengthOfList(ListNode* head) {
        int count = 0;
        while (head != nullptr) {
            head = head->next;
            count++;
        }
        return count;
    }

    bool isPalindrome(ListNode* head) {

        if (head->next == nullptr)
            return true;

        // Calculate total number of nodes.
        int N = lengthOfList(head);
        int mid = (N + 1) / 2;

        // Which hold the nodes from first half.
        stack<ListNode*> st;

        ListNode* runner = head;

        // Push node until N/2.
        while (mid > 0) {
            st.push(runner);
            runner = runner->next;
            mid--;
        }

        // Odd length, remove the middle element. 1 3 1, we need to remove 3 before comparsion.
        if (N % 2 == 1)
            st.pop();

        // Comparsion. First half in stack(so we have reverse order), Second half on LL.
        while (runner != nullptr) {
            if (st.top()->val != runner->val) {
                return false;
            }

            st.pop();
            runner = runner->next;
        }

        return true;
    }
};



// 2nd: Reverse first half of list, the compare
class Solution {
public:

    int lengthOfList(ListNode* head) {
        int count = 0;
        while (head != nullptr) {
            head = head->next;
            count++;
        }
        return count;
    }

    // make the list reverse upto given "upto" node.
    ListNode* reverseFirstHalfOfList(ListNode* head, int upto) {

        ListNode* curr = head;
        ListNode* prev = nullptr;
        ListNode* next = nullptr;

        while (upto > 0) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
            upto--;
        }

        return prev;        // hold the newHead
    }

    bool isPalindrome(ListNode* head) {

        if (head->next == nullptr)
            return true;

        // Calculate total number of nodes.
        int N = lengthOfList(head);
        int mid = N / 2;

        ListNode* runner = head;

        // Push node until N/2.
        while (mid > 0) {
            runner = runner->next;
            mid--;
        }

        // Odd length, skip the middle element. 1 3 1, we need to skip 3 before comparsion.
        if (N % 2 == 1)
            runner = runner->next;

        ListNode* newHead = reverseFirstHalfOfList(head, N / 2);

        // Comparsion.
        while (runner != nullptr) {
            if (newHead->val != runner->val) {
                return false;
            }

            newHead = newHead->next;
            runner = runner->next;
        }

        return true;
    }
};