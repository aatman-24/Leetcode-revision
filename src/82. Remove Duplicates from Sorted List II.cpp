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

Question : 82. Remove Duplicates from Sorted List II
Topic : Two pointer, STack
Problems : https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/description/

==============================> Explanation <=============================================

Parent: 83. Remove Duplicates from Sorted List

#1) In #83, We have used curr & runner pointers, where current pointer points to first occurance of val, whenever we see runner points to other new_val, we make the join between them and
current pointer points to that new value and again we look for unique element.

But here, the problem is that, we can't even add the current pointer if (curr->val == runner->val) both are same. So it is clear that we need to keep track of last
unique element got added into the list.

How we can know current have more than one elements in list ?

1) Use the map: We can use extra space, to know which element got duplicated so we can't add those. Here val = [-200, 200]. So it can be achieved in O(1).

2) Use counter(Which I did):
curr -> points to new element with count = 1,
runner => curr->next

now if (curr->val == runner->val) count++, count = 2 (curr got duplicated so we won't add curr)
so we skip all elements until we see (curr->val != runner->val)... found new element so we can keep track of it by pointing current to that element, with freq=1.

Check the code!! you get it.


#Edge cases:
1 - 2 -> 3 -> 3 -> 3 -> 4, at the end if count>1, we need to add that last visited element into the list.
1 - 2 - 2 - 2, we need to mark the end of the list by setting lastUniq->next = nullptr.






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

        // base condition
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode* dummyHead = new ListNode(INT_MIN);
        dummyHead->next = head;

        // Keep track of lastUniqueEle.
        ListNode* lastUniqueEle = dummyHead;
        ListNode* current = head;
        ListNode* runner = current->next;

        // Keep track of current node frquency.
        int currCount = 1;

        while (runner != nullptr) {

            // Current and runner are same, increase the frequency.
            if (current->val == runner->val) {
                runner = runner->next;
                currCount++;
            }

            // If not same,
            else {

                // how many times current got repeated, until we found new element at runner.
                // If it less than times, curr is unique add into our answer list.
                if (currCount < 2) {

                    // Add current into the list.
                    lastUniqueEle->next = current;
                    lastUniqueEle = current;
                }

                // make current as our new found element and runner pointing next to it. Reset currCount as 1.
                current = runner;
                runner = runner->next;
                currCount = 1;
            }
        }

        // At the end, if currCount is 1 then we need to add that node, For ex: 1 -> 2 -> 3 -> 3 -> 4(Need to add this last node. )
        if (currCount == 1) {
            lastUniqueEle->next = current;
        }

        // Otherwise mark the end of list. 1 -> 2 -> 3 -> 3 -> 3 (Then we need to set 2 -> next = nullptr)
        else {
            // set the last node next as null, to make a end of list.
            lastUniqueEle->next = nullptr;
        }

        return dummyHead->next;
    }
};


// Recursive

public class Solution {
    public ListNode deleteDuplicates(ListNode head) {

        if (head == null || head.next == null) return head;

        if (head.val != head.next.val) {
            head.next = deleteDuplicates(head.next);
            return head;                                    // no duplicate, so we return current element by joining with remaining list answer
        }
        else {
            while (head.next != null && head.val == head.next.val)
                head = head.next;

            return deleteDuplicates(head.next);         // got duplicated elements, so whatever return by remaining list we return that.
        }

    }
}