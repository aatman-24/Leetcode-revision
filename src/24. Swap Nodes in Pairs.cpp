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

Question : 24. Swap Nodes in Pairs
Topic : Two pointer
Problems : https://leetcode.com/problems/swap-nodes-in-pairs/description/

==============================> Explanation <=============================================

1) Iterative: We start to swap pairs from the staring of the list.

Very clear,

We need to swap some pointers. Keep in mind that prev -> (new_pair) -> (next_old_pair).

don't forget to make link bw (prev_new_pair) -> (new_pair).

2) Recursion: We start to swap pairs at the end of the list.

- When we reach at the end then we make our first swap, (1, 2, 3, 4, 5, 6) => (1 2)(unswapped_list)  | (4, 3, 6, 5)(swapped_list)
- Again concept is same, we need to make join with swapped_list by rearranging the pointers.

==============================> Approach and Time Complexity <============================


1) Two pointer
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
public:
    ListNode* swapPairs(ListNode* head) {

        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode* dummyHead = new ListNode(-1);
        dummyHead->next = head;

        // point to first node in pair
        ListNode* first = head;

        // point to previous pair last node after swap.
        ListNode* prev = dummyHead;

        // point to second node in pair
        ListNode* second;

        while (first != nullptr && first->next != nullptr) {

            // get the second node in pair.
            second = first->next;

            // prev -> 1 -> 2 -> 3 => 1->3
            first->next = second->next;

            // prev -> 1 -> 2 -> 3 => 2 -> 1
            second->next = first;

            // prev -> 2
            prev->next = second;

            // moving to next pair
            prev = first;       // prev = 1
            first = first->next; // first = 3


            // at the end, prev -> 2 -> 1 -> 3
        }

        return dummyHead->next;
    }
};


// Recursion


class Solution {
public:
    ListNode* swapPairs(ListNode* head) {

        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode* first = head;
        ListNode* second = head->next;

        first->next = swapPairs(head->next->next); // it will return next swapped pair head. (1, 2) (3, 4) => (1, 2) (4, 3)... return pointer points to 4.
        second->next = first;
        return second;
    }
};