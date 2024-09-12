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

Question : 2. Add Two Numbers
Topic : Two pointer
Problems : https://leetcode.com/problems/add-two-numbers/description/

==============================> Explanation <=============================================

Straight foward, think about how we can perform the carry-over.

Edge case: (99 + 99 = 100). When both nubmer got visited, and still some carry left we need to add that as node.

==============================> Approach and Time Complexity <============================


1) Two Pointer
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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {

        ListNode* dummyHead = new ListNode(-1);
        ListNode* runner = dummyHead;

        // keep track of carry foward.
        int carry = 0;

        // This should continue to process until both nubmer is visited entirely(1 + 3231), if both visited entirely then there shouldn't be any carry > 0(99+99=100).
        // If yes then we have to add carry node at the end.
        while (l1 != nullptr || l2 != nullptr || carry > 0) {

            int curSum = carry;

            if (l1 != nullptr) {
                curSum += l1->val;
                l1 = l1->next;
            }

            if (l2 != nullptr) {
                curSum += l2->val;
                l2 = l2->next;
            }

            carry = curSum / 10;            // return the carray

            runner->next = new ListNode(curSum % 10);       // return the digit

            runner = runner->next;
        }

        return dummyHead->next;
    }
};