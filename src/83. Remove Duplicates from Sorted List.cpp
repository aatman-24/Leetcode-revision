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

Question : 83. Remove Duplicates from Sorted List
Topic : Two pointer
Problems : https://leetcode.com/problems/remove-duplicates-from-sorted-list/description/

==============================> Explanation <=============================================

#1) Idea is that, our current pointer points to first occurance of new_val, whenever we see runner points to other val, we make the join between them and
start tracking that other val ocurrance by moving current pointers there.

Edge case: At the end, 1 -> 2 -> 3 -> 3 -> 3...... in such list if need to mark cur->next = nullptr to mark end of the list.

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
    ListNode* deleteDuplicates(ListNode* head) {

        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode* dummyHead = new ListNode(INT_MIN);
        dummyHead->next = head;

        ListNode* current = dummyHead;
        ListNode* runner = current->next;

        while (runner != nullptr) {

            if (current->val == runner->val) {
                runner = runner->next;
            } else {
                current->next = runner;
                current = runner;
                runner = runner->next;
            }
        }

        // set the last node next as null, to make a end of list.
        current->next = nullptr;

        return dummyHead->next;
    }
};



// optimization of code in if-else condition.
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
    ListNode* deleteDuplicates(ListNode* head) {

        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode* dummyHead = new ListNode(INT_MIN);
        dummyHead->next = head;

        ListNode* current = dummyHead;
        ListNode* runner = current->next;

        while (runner != nullptr) {

            if (current->val != runner->val) {
                current->next = runner;
                current = runner;
            }

            runner = runner->next;
        }

        // set the last node next as null, to make a end of list.
        current->next = nullptr;

        return dummyHead->next;
    }
};