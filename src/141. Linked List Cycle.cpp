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

Question : 141. Linked List Cycle
Topic : Hashing, Fast&Slow Pointer
Problems : https://leetcode.com/problems/linked-list-cycle/description/

==============================> Explanation <=============================================

Approach to solve this problem is use the fast & slow pointer,

If there is cycle, then fast pointer meet the slow pointer again.

If there is no cycle, in that case list have last element pointing to NULL.

we are double jumping for the fast pointer so we need to consider fast->next != NULL for jumping two times.

Edge case:

Even Length: fast == null
Odd Length: fast->next == null

Base case:

- empty list
- list with single node.

2) Hashing
- We hash the entire node, if we get second time it means there is cycle.


==============================> Approach and Time Complexity <============================

1) Hashing
Time: O(N).
Space: O(N)

2) Slow & Fast Pointer
Time: O(N)
Space: O(1)

*/


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {

        // Base case
        if (head == nullptr || head->next == nullptr)
            return false;

        ListNode* fast = head;
        ListNode* slow = head;

        do {
            slow = slow->next;
            fast = fast->next->next;
        } while (fast != nullptr && fast -> next != nullptr && slow != fast);   // odd length list, fast->next == NULL, even length = fast == nullptr



        return  slow == fast;
    }
};



class Solution {
public:
    bool hasCycle(ListNode *head) {

        unordered_map<ListNode*, int> mp;

        while (head != nullptr) {

            if (mp.count(head)) {
                return true;
            }

            mp[head] = 1;

            head = head->next;

        }

        return head != nullptr;

    }
};