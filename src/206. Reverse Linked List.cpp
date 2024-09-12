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

Question : 206. Reverse Linked List
Topic : Stack, Two pointers
Problems : https://leetcode.com/problems/reverse-linked-list/description/

==============================> Explanation <=============================================

1) Stack: Add all elements into stack, again pop it and make a list out of it.

2) Iterative: Using three pointers we can reverse entire list.

    [prev, curr, next]

    next = curr -> next (save the next node pointer)
    curr -> next = prev (make node points to prev node)
    prev = curr (forward the prev pointer for next node)
    curr = next  (forward the curr pointer)

    When reach curr == nullptr, that time prev hold the newhead so return that.

3) Recursion:
    - We are using reference pointer to save the newHead when we reach at the end of list.
    - Apart from that, helper() return the last node of reversed list... so we keep adding the curr node at the end of list.
        By prev = helper(), prev->next = curr and return curr because it is the last node of that reversed list.

==============================> Approach and Time Complexity <============================

1) Stack, Recursion
Time: O(N).
Space: O(N)

2) Iterative
Time: O(N)
Space: O(1)

*/

// Stack Approach.
class Solution {
public:
    ListNode* reverseList(ListNode* head) {

        if (head == nullptr || head->next == nullptr) {
            return head;
        }


        stack<ListNode*> st;

        // push all elements into the stack.
        ListNode* runner = head;
        while (runner != nullptr) {
            st.push(runner);
            runner = runner->next;
        }

        ListNode* dummy = new ListNode(-1);
        runner = dummy;
        while (!st.empty()) {           // pop all element from stack and create a new list.
            runner -> next = st.top(); st.pop();
            runner = runner->next;
            if (st.empty())             // last element should point to the null, make sure that.
                runner->next = nullptr;
        }

        return dummy->next;
    }
};


// Iterative Approach
class Solution {
public:
    ListNode* reverseList(ListNode* head) {

        // base case
        if (head == nullptr ) {
            return head;
        }

        // holding three pointers. [prev, curr, next]
        ListNode* curr = head;
        ListNode* prev = nullptr;
        ListNode* next = nullptr;

        // making adjustment
        while (curr != nullptr) {
            next = curr -> next;
            curr -> next = prev;
            prev = curr;
            curr = next;
        }

        // at the end prev hold newHead.
        return prev;
    }
};



// Recursive Apporach.
class Solution {
public:

    ListNode* reverseListHelper(ListNode* curr, ListNode* &newHead) {

        // Single node, return it
        if (curr->next == nullptr) {
            newHead = curr;         // setting the last node as new Head.
            return curr;
        }

        // prev, In the reversed list returning the last node. Fo ex: 1->2->3....    1   (2<-3), here 2 is prev.
        ListNode* prev = reverseListHelper(curr->next, newHead);

        prev->next = curr;  // making connection between 2 -> 1. #(1 <- 2 <- 3)
        curr->next = nullptr; // clearing the next poninter of curr. It is necessary otherwise last node 1 again point to itself.

        // returning the curr, by adding it as last node of reverse List.
        return curr;
    }



    ListNode* reverseList(ListNode* head) {

        // Base case
        if (head == nullptr || head->next == nullptr ) {
            return head;
        }

        ListNode* newHead = nullptr;        // we are passing the newHead reference, so when we reach at the end of list, we just save last node as newHead.
        ListNode* lastNodeOfReverseList = reverseListHelper(head, newHead);

        // Returing new Head.
        return newHead;
    }
};