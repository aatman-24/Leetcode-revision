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

Question : 92. Reverse Linked List II
Topic : Two pointer, STack
Problems : https://leetcode.com/problems/reverse-linked-list-ii/description/

==============================> Explanation <=============================================

Idea is that,

For given list => 1 -> 2 - |3 -> 4 -> 5 | 6 -> 7

We break the list (0, left-1) (left, right) (right+1, end)

Reverse the (left, right) => (right, left)

And agian make the join (0, left-1) -> (right, left) -> (right+1, end)

Check the code!!

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

    // Reverse the give list.
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* runner = head;
        ListNode* nextNode;

        while (runner != nullptr) {
            nextNode = runner->next;
            runner->next = prev;
            prev = runner;
            runner = nextNode;
        }

        // return the head of reversed list.
        return prev;
    }

    ListNode* reverseBetween(ListNode* head, int left, int right) {

        // Add dummnyNode, for easiness in case of left = 1.
        ListNode* dummyNode = new ListNode(-1);
        dummyNode->next = head;

        // points to left-1.
        ListNode* leftBoundary = nullptr;

        // points to right+1.
        ListNode* rightBoundaryHead;
        ListNode* runner = dummyNode;

        int index = 0;
        while (runner != nullptr) {

            if (index == left - 1) {
                leftBoundary = runner;
            }

            if (index == right) {
                rightBoundaryHead = runner->next;   // store the remaining list head
                runner->next = nullptr;             // end the list here. so we have list (left, right)
                break;
            }

            runner = runner->next;
            index++;
        }

        // Reverse the list (left, right)... and join it with left-1 => {reversed_list}
        leftBoundary->next = reverseList(leftBoundary->next);
        runner = leftBoundary->next;

        // In case right is end of the list, then runner is nullptr.
        if (runner == nullptr) {
            return dummyNode->next;
        }

        // find the tail of the reversed list.
        while (runner->next != nullptr) {
            runner = runner->next;
        }

        // join the tail->next = remaining list head
        runner->next = rightBoundaryHead;

        // return the head.
        return dummyNode->next;
    }
};