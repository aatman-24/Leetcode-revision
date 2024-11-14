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

Question : 143. Reorder List
Topic : Two pointer, STack
Problems : https://leetcode.com/problems/reorder-list/description/

==============================> Explanation <=============================================

Pattern: 234. Palindrome Linked List

#1) Idea is that, We can't use any pointers or something to remeber the node. So it is not about managing the pointers direclty, first
we need nodes in some pattern so we can do that. We need memory in reverse order!!
- First thing came in my mind was stack.
- So if we break the list in two parts, and second parts goes into the stack, then we can make that arrangement, L1 -> LN -> L2 -> LN-1......

#2) Instead of using stack, we can make the second list reverse and then use those pointers.... Same thigns... but space: O(1)...

==============================> Approach and Time Complexity <============================

1) Stack
Time: O(N)
Space: O(N)

2) Reverse List
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

    void reorderList(ListNode* head) {

        if (head == nullptr || head->next == nullptr) {
            return;
        }

        int N = lengthOfList(head);
        int mid = (N + 1) / 2;

        // Traverse until the mid node.
        ListNode* runner = head;
        int count = 1;
        while (count < mid) {
            runner = runner->next;
            count++;
        }

        // Got the head of second list.
        ListNode* nextNode = runner->next;
        runner->next = nullptr;     // End the first half.


        // Put the rest of nodes into stack.  (Here you can even reverse the second half of list)
        stack<ListNode*> st;
        runner = nextNode;
        while (runner != nullptr) {
            st.push(runner);
            runner = runner->next;
        }

        // make an arrangement, list1->next = st.top()->next = list1->next->next.
        runner = head;
        while (!st.empty()) {
            nextNode = runner->next;
            ListNode* topOfStack = st.top(); st.pop();
            topOfStack->next = nextNode;
            runner->next = topOfStack;
            runner = nextNode;
        }

    }
};




// #2: Java Solution... Just for idea.... Easy!!
public void reorderList(ListNode head) {
    if (head == null) {
        return;
    }

    // Find the middle node
    ListNode slow = head, fast = head.next;
    while (fast != null && fast.next != null) {
        slow = slow.next;
        fast = fast.next.next;
    }

    // Reverse the second half
    ListNode head2 = reverse(slow.next);
    slow.next = null;

    // Link the two halves together
    while (head != null && head2 != null) {
        ListNode tmp1 = head.next;
        ListNode tmp2 = head2.next;
        head2.next = head.next;
        head.next = head2;
        head = tmp1;
        head2 = tmp2;
    }
}

private ListNode reverse(ListNode n) {
    ListNode prev = null;
    ListNode cur = n;
    while (cur != null) {
        ListNode tmp = cur.next;
        cur.next = prev;
        prev = cur;
        cur = tmp;
    }
    return prev;
}