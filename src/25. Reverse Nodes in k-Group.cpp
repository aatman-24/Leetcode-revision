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
================================================================================
                                Problem Description
================================================================================

Problem: 25. Reverse Nodes in k-Group
Topic: Linked List
Link: https://leetcode.com/problems/reverse-nodes-in-k-group/description/

================================================================================
                                Problem Summary
================================================================================

You are given the head of a linked list and an integer k.

Reverse the nodes of the list k at a time, and return the modified list.
Nodes that are left at the end with fewer than k elements should remain in their original order.

You may not alter the values in the list's nodes, only nodes themselves may be changed.

================================================================================
                                Intuition & Explanation
================================================================================

We traverse the linked list in chunks of size k. If we find k nodes available, we reverse that segment.
Otherwise, we leave the remaining nodes as they are.

To make pointer manipulation easier and handle edge cases cleanly (like reversing the head segment), we use a dummy node.

For every k-sized segment:
- We record the start (`klast`) and try to move forward `k` steps to validate whether there are at least `k` nodes.
- If not enough nodes, we break.
- If we have enough nodes, we reverse those k nodes using a helper function.
- Then we connect the previous reversed segment to the newly reversed one.

This process repeats until we reach the end of the list.

================================================================================
                          Approach & Time/Space Complexity
================================================================================

Approach: Iterative with pointer manipulation and helper reverse function
Time Complexity: O(N), where N is the total number of nodes
Space Complexity: O(1), as we do in-place reversal without extra data structures
*/


// Recursive
class Solution {
public:
    int length(ListNode* head) {
        int cnt = 0;
        while (head != NULL) {
            head = head -> next;
            cnt++;
        }
        return cnt;
    }


    ListNode* reverseK(ListNode* head, int k, int n) {

        ListNode* prevptr = NULL;
        ListNode* currptr = head;
        ListNode* nextptr;

        // edge case
        if (n < k) return currptr;

        int cnt = 0;
        while (currptr != NULL && cnt < k) {
            nextptr = currptr -> next;
            currptr -> next = prevptr;
            prevptr = currptr;
            currptr = nextptr;
            n--;
            cnt++;
        }

        if (nextptr != NULL) {
            head -> next = reverseK(currptr, k, n);
        }

        return prevptr;
    }

    // Recursive O(N) - O(1)
    ListNode* reverseKGroup(ListNode* head, int k) {
        return reverseK(head, k, length(head));
    }
};


// Iterative

class Solution {
public:

    // Main function to reverse nodes in k group
    ListNode* reverseKGroup(ListNode* head, int k) {

        ListNode* dummy = new ListNode(0);
        dummy->next = head;

        ListNode* runner = head;
        ListNode* prev = dummy;

        while (runner != nullptr) {

            ListNode* kLast = runner;
            int num = k;

            // Move runner k steps forward
            while (num > 0 && runner != nullptr) {
                runner = runner->next;
                num--;
            }

            // If remaining nodes are less than k
            if (num != 0) {
                prev->next = kLast;
                break;
            }

            // Reverse k nodes starting from kLast
            ListNode* kStart = reverse(kLast, k);

            // Connect previous group with current reversed group
            prev->next = kStart;

            // Move prev pointer to the end of current reversed group
            prev = kLast;
        }

        return dummy->next;
    }

private:
    // Reverse k nodes and return new head
    ListNode* reverse(ListNode* head, int k) {
        ListNode* prev = nullptr;
        while (head != nullptr && k > 0) {
            ListNode* next = head->next;
            head->next = prev;
            prev = head;
            head = next;
            k--;
        }
        return prev;
    }
};


