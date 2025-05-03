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

Question : 23. Merge k Sorted Lists
Topic : Priority Queue
Problems : https://leetcode.com/problems/merge-k-sorted-lists/description/?envType=problem-list-v2&envId=heap-priority-queue

==============================> Explanation <=============================================

Idea is that,

We can add the first element of each list into PQ...so it can give which element goes first into sorted list....
and also we keep track of head of list...so we can add next element from that list into PQ.

==============================> Approach and Time Complexity <============================

1) Priority Queue
Time: O(N)
Space: O(N)

*/


class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {

        priority_queue<pair<int, ListNode*>, vector<pair<int, ListNode*>>, greater<pair<int, ListNode*>>> pq;

        // Iterate over all the lists, and add the first element of that list.
        for (ListNode* head : lists) {
            if (head != nullptr) {
                pq.push({head->val, head});
            }
        }

        // sorted list head
        ListNode* dummy = new ListNode(INT_MIN);
        ListNode* runner = dummy;

        while (!pq.empty()) {

            ListNode* node = pq.top().second; pq.pop();

            // add the node into sorted list...
            runner->next = node;
            runner = runner->next;

            ListNode* nextNode = node->next;
            if (nextNode) {
                pq.push({nextNode->val, nextNode});
            }
        }

        return dummy->next;
    }
};