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

Question : 876. Middle of the Linked List
Topic : Fast & Slow Pointer
Problems : https://leetcode.com/problems/middle-of-the-linked-list/description/

==============================> Explanation <=============================================

Approach behind using slow & fast pointer is that,

fast travels distance two times than slow, so when fast reach at the end, slow at middle.

==============================> Approach and Time Complexity <============================


1) Fast & Slow Pointer
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
    ListNode* middleNode(ListNode* head) {

        if (head->next == nullptr)
            return head;

        ListNode* slow = head;
        ListNode* fast = head;

        do {
            slow = slow->next;
            fast = fast->next->next;
        } while (fast != nullptr && fast->next != nullptr);     // fast == nullptr (even length), (fast->next) (odd length)

        return slow;

    }
};