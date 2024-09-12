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

Question : 61. Rotate List
Topic : Two pointer
Problems : https://leetcode.com/problems/rotate-list/description/

==============================> Explanation <=============================================

#1) Idea is that, if we rotate key k times or n*k times result will be the same. And instead of acutally rotating the list, we can break the list and
make arrangement such way that it looks like rotation.

So if we need to rotate k times in circular way, it means last k node is coming in front of list. So we can break the list into two parts.

1) N-K elements starting from the begin
2) last K elements (Which will be the new head)

And join them by 2) -> 1)

Check the code!!


#2) Same thing we can do this way as well.

1) make the list in circular. last -> first again.
2) again start from first, break at (N-k) elements, and declare the next element newHead.

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

    int lengthOfList(ListNode* head) {
        int count = 0;
        while (head != nullptr) {
            head = head->next;
            count++;
        }
        return count;
    }


    ListNode* rotateRight(ListNode* head, int k) {

        // base case
        // 1. Empty list => no affect of rotating it.
        // 2. One element in list => no affect of rotating it.
        // 3. No rotation k = 0 => nothing to do return og list.
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        int N = lengthOfList(head);

        // perform mod because if N = 4. Then we rotate list 3 times or 7 times, result will be the same.
        k = k % N;

        // edge case(I would say base case)
        if (k == 0) {
            return head;
        }

        // keep track of runner. Want to move runner "upto" times forward.
        ListNode* runner = head;

        // move runner "upto" next node.
        int upto = N - k;

        while (upto > 1) {
            runner = runner->next;
            upto--;
        }

        // runner->next is the new Head of the list.
        ListNode* newHead = runner->next;

        // cut this first half of list from second half. And join first half at the end of second half.
        runner->next = nullptr;

        // we need last node so we can make that join.
        runner = newHead;
        while (runner->next != nullptr) {
            runner = runner->next;
        }

        // join both the list.
        runner->next = head;

        return newHead;
    }
};



// #2
class Solution {
public:

    ListNode* rotateRight(ListNode* head, int k) {

        // base case
        // 1. Empty list => no affect of rotating it.
        // 2. One element in list => no affect of rotating it.
        // 3. No rotation k = 0 => nothing to do return og list.
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        // keep track of runner. Want to move runner "upto" times forward.
        ListNode* runner = head;

        int N = 0;
        while (runner->next != nullptr) {
            runner = runner->next;
            N++;
        }
        runner->next = head; N++; // last node was not counted previously. Make it Circular LinkedList.

        // perform mod because if N = 4. Then we rotate list 3 times or 7 times, result will be the same.
        k = k % N;

        // edge case(I would say base case)
        if (k == 0) {
            runner->next = nullptr; // unset the last node again.
            return head;
        }

        // move runner upto jth times forward break the list.
        int j = N - k;

        // again runner points to head;
        runner = head;

        while (j > 1) {
            runner = runner->next;
            j--;
        }

        // runner->next is the new Head of the list.
        ListNode* newHead = runner->next;

        // cut this first half of list from second half. And join first half at the end of second half.
        runner->next = nullptr;

        return newHead;
    }
};