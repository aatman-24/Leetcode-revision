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

Question : 328. Odd Even Linked List
Topic : Two pointer
Problems : https://leetcode.com/problems/odd-even-linked-list/description/

==============================> Explanation <=============================================

Very clear,

We need to maintain two list, odd and even. And join odd->even with oddLastNode->next = even->head.

Check the code!!

==============================> Approach and Time Complexity <============================


1) Two pointer
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
    ListNode* oddEvenList(ListNode* head) {

        // Create new two lists with dummy nodes.
        ListNode* oddHead = new ListNode(-1);
        ListNode* evenHead = new ListNode(-1);
        int index = 1;

        // Keep track of their runner.
        ListNode* oddRunner = oddHead;
        ListNode* evenRunner = evenHead;

        while (head != nullptr) {

            if (index % 2) {
                oddRunner->next = head;
                oddRunner = oddRunner->next;
            }
            else {
                evenRunner->next = head;
                evenRunner = evenRunner->next;
            }

            head = head->next;
            index++;
        }

        // make the end of list
        evenRunner->next = nullptr;

        // Join the list. (odd -> even)
        oddRunner->next = evenHead->next;

        // return the head oddList head.
        return oddHead->next;

    }
};