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

Question : 21. Merge Two Sorted Lists
Topic : LinkedList, Two Pointer
Problems : https://leetcode.com/problems/merge-two-sorted-lists/description/

==============================> Explanation <=============================================

Idea is that,

We can create a new LinkedList by inserting those nodes from given lists.

Managing the head of new LL is diffcult(in terms of writting code, need to add few if-else conditions), instead of that we can create a new dummyHead,
and add those nodes after it, and at the end we can return dummy->next, where actual list start.

Optimization: When we traverse one of the list entirely, second list may have few nodes left, so instead of traversing and adding those in new LL, we can just
make a join of it (Bcz it is LL).

==============================> Approach and Time Complexity <============================

1) Two Pointer
Time: O(N+M).
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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {

        // dummyHead for merging two list.
        ListNode* dummy = new ListNode(-1);

        // runner node to extend the list.
        ListNode* runner = dummy;

        while (list1 != nullptr && list2 != nullptr) {

            // one of the list node join the runner based on value.
            if (list1->val < list2->val) {
                runner->next = list1;       // join the runner
                runner = runner->next;      // move to that node
                list1 = list1->next;        // move to next node in list1
            }
            else {
                runner->next = list2;
                runner = runner->next;
                list2 = list2->next;
            }
        }

        // If one of the list, still got some nodes, we can add at the end of runner.
        while (list1 != nullptr) {
            runner->next = list1;
            list1 = list1->next;
            runner = runner->next;
        }

        while (list2 != nullptr) {
            runner->next = list2;
            list2 = list2->next;
            runner = runner->next;
        }

        // return the first node, which is next of our dummy head.
        return dummy->next;

    }
};



class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* dummy = new ListNode(-1);
        ListNode* runner = dummy;

        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val < list2->val) {
                runner->next = list1;
                runner = runner->next;
                list1 = list1->next;
            }
            else {
                runner->next = list2;
                runner = runner->next;
                list2 = list2->next;
            }
        }

        // OPTIMIZATION: We don't need to go through each node to add it in runner, It is LinkedList we can just make join of that list to runner.
        if (list1 != nullptr) {
            runner->next = list1;
        }

        if (list2 != nullptr) {
            runner->next = list2;
        }

        // return the first node, which is next of our dummy head.
        return dummy->next;

    }
};