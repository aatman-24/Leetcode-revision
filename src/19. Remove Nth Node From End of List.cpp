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

Question : 19. Remove Nth Node From End of List
Topic : Two pointer
Problems : https://leetcode.com/problems/remove-nth-node-from-end-of-list/description/

==============================> Explanation <=============================================

Idea behind this apporach is that,

1) Two pass:
- First pass calculate total number of nodes.
- Remove the nth node from end === #Remove node after, K(total-N)th node from start
For ex: 1 -> 2 -> 3 -> 4, Remove N = 2 (second last node) => K = 4 - 2 => Remove node after 2nd node from start.
Handle the case: When you need to delete the first node of list, add dummyHead for handling the case efficently.


2) One pass:

- Idea behind this approach is that,

    If we maintain two pointer such that, distance between them is K. Then when a fast(forward) pointer reach to at the end of list, slow(backward) pointer
    reach to node which we want to delete.

    We have to maintain pointer such that, slow->next = (deleteNode)...

    To handle the edge case when we need to delete the first node of list, we add dummyHead to handle the case efficiently.


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
class Solution {

    int ListNode* length(ListNode* head) {
        int count = 0;
        while (head != nullptr) {
            head = head->next;
            count++;
        }
    }


public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {

        int total = length(head);
        if (total == n) {
            if (total == 1)
                return null;
            return head->next;
        }

        int removeAfter = total - n;
        ListNode* runner = head;


        while (removeAfter > 1) {
            runner = runner->next;
            removeAfter--;
        }

        // skip the runner->next node.
        runner->next = runner->next->next;

        return head;
    }
};



// Optimization code
class Solution {

    int length(ListNode* head) {
        int count = 0;
        while (head != nullptr) {
            head = head->next;
            count++;
        }
        return count;
    }


public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {

        // Add dummyHead node.
        ListNode* dummyHead = new ListNode(-1);
        dummyHead->next = head;

        // total number of nodes.
        int N = length(dummyHead);

        int removeAfter = N - n;

        ListNode* runner = dummyHead;

        while (removeAfter > 1) {       // removeAfter == 1, then next node after runner we want to delete.
            runner = runner->next;
            removeAfter--;
        }

        runner->next = runner->next->next;

        return dummyHead->next;
    }
};


// One pass
class Solution {

public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {

        // Add dummyHead node.
        ListNode* dummyHead = new ListNode(-1);
        dummyHead->next = head;

        ListNode* runner = dummyHead;

        // we forward the runner N steps ahead.
        while (n > 0) {
            runner = runner->next;
            n--;
        }

        // start slow pointer again from start, until we reach the at the end of list.
        ListNode* slow = dummyHead;
        while (runner->next != NULL) {
            runner = runner->next;
            slow = slow->next;
        }

        // slow->next points to node which we want to delete.
        slow->next = slow->next->next;

        return dummyHead->next;
    }
};