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

Question: 23. Merge k Sorted Lists
Topic : minHeap
Problems : https://leetcode.com/problems/merge-k-sorted-lists/

==============================> Explanation <=============================================

parent: Sort the Two Sorted Array, K sorted Array.


1) Brute-Force: Using Extra Space, First merge all the list. Sort them and
again make new LL based on that. Take O(NlogN) -> N = Total Number of Elements.

2) Use MinHeap + Extra Space:
- Element = <value, nextNode>
- Create a minHeap of K elements. Popped the most promising
node from the heap, if that node node next pointer is not null then push next node into
the heap. Overall N elements is pushed and popped from the heap. But heap can contain maximum
K element at any time. So it will take O(NlogK).
- Here we create new node of popped value so it will take O(N) Extra space.


3) MinHeap + Without Extra Space:
- Element = <value, nextNode>
- Same concept but we don't create the new node rathar orginal node is linked.

4) MinHeap + Comparator:
- Use Comparator so,
Element = <Node>

==============================> Apporach and Time Complexity <=============================================
N = Total Elements.
K = Total Linked List.

1) Brute-Force:
Time: O(NlogN)
Space: O(N)

2) MinHeap + Extra Space
Time: O(NlogK)
Space: O(N)

3) MinHeap + Without Extra Space:
Time: O(NlogK)
Space: O(1)

4) MinHeap + Comparator:
Time: O(NlogK)
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
    ListNode* mergeKLists(vector<ListNode*>& lists) {

        ListNode* head = new ListNode(-1);
        ListNode* temp = head;

        priority_queue<pair<int, ListNode*>, vector<pair<int, ListNode*>>, greater<pair<int, ListNode*>>> pq;
        for (int i = 0; i < lists.size(); i++) {
            if (lists[i] != nullptr) {
                pq.push({lists[i]->val, lists[i]->next});
            }
        }

        while (!pq.empty()) {

            auto [val, nextNode] = pq.top(); pq.pop();

            // Extra Space is used to create new node.
            temp -> next = new ListNode(val);
            temp = temp -> next;

            if (nextNode != nullptr) {
                pq.push({nextNode->val, nextNode->next});
            }
        }
        return head->next;
    }

};


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
    ListNode* mergeKLists(vector<ListNode*>& lists) {

        ListNode* head = new ListNode(-1);
        ListNode* temp = head;

        priority_queue<pair<int, ListNode*>, vector<pair<int, ListNode*>>, greater<pair<int, ListNode*>>> pq;
        for (int i = 0; i < lists.size(); i++) {
            if (lists[i] != nullptr) {
                pq.push({lists[i]->val, lists[i]});
            }
        }

        while (!pq.empty()) {

            auto [val, current] = pq.top(); pq.pop();

            // Relink the node. No extra space.
            temp -> next = current;
            temp = temp -> next;

            if (current -> next != nullptr) {
                pq.push({current -> next ->val, current->next});
            }
        }

        return head->next;
    }
};



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
class compare {
public:
    bool operator() (ListNode* l1, ListNode* l2) {
        return l1->val > l2->val;
    }

};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {

        ListNode* head = new ListNode(-1);
        ListNode* temp = head;

        priority_queue<ListNode*, vector<ListNode*>, compare> pq;

        for (int i = 0; i < lists.size(); i++) {
            if (lists[i] != nullptr) {
                pq.push(lists[i]);
            }
        }

        while (!pq.empty()) {

            auto current = pq.top(); pq.pop();

            // Relink the node. No extra space.
            temp -> next = current;
            temp = temp -> next;

            if (current -> next != nullptr) {
                pq.push(current->next);
            }
        }

        return head->next;
    }
};