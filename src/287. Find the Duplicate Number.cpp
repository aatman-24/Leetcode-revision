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

Question : 287. Find the Duplicate Number
Topic : Floyd's Tortoise and Hare algorithm
Problems : https://leetcode.com/problems/find-the-duplicate-number/description/

==============================> Explanation <=============================================


1) Brute Force:
- Use two for loops to find duplicate.

2) Hashing
- Use map to keep track of count.

3) Marking visited value within the array
- We can create memory by doing this: we can mark the value with its negative, so we can have abs(num) as original value and negative mark signal
elements are got visited two times. Check the code!!

3) Fast & Slow Pointer (Loop Detection):
The problem might initially seem challenging to solve using this method. However, the key insight is that the elements in the array are in the range [1, N], and the array contains N+1 elements, indicating the presence of a duplicate.

Starting from index 0, we can conceptualize the array as a linked list where each element points to the next index given by its value. If there's a duplicate, a cycle will form in this linked list. The starting point of this cycle is the element visited twice.

The intuition behind this approach is that each element points to a single source, but a duplicate will have multiple sources pointing to it. For example:

1 3 4 2 2

0 -> 1 -> 3 -> 2 -> 4 -> 2 (loop)



==============================> Approach and Time Complexity <============================

N = nums.size()

1) Brute Force:
Time: O(N^2)
Space: O(1)

2) Sorting:
Time: O(NlogN)
Space: O(1)

3) Hashing
Time: O(N)
Space: O(N)

4) Marking visited value within the array (array got modified)
Time: O(N)
Space: O(1)

5) Fast & Slow Pointer (Loop Detection):
Time: O(N)
Space: O(1)


*/


// Approach-4
class Solution {
public:
    int findDuplicate(vector<int>& nums) {

        for (int num : nums) {

            int idx = abs(num);

            // If idx(num) is telling that, nums[idx] already visited, it means that idx is value which is duplicate in array that's why
            // It pointing us to mark negative number second time.
            if (nums[idx] < 0) {
                return idx;
            }

            nums[idx] = -nums[idx];

        }

        return -1;
    }
};


// Approach-5
class Solution {
public:
    int findDuplicate(vector<int>& nums) {

        int slow = nums[0];
        int fast = nums[0];

        // detect loop.
        do {
            slow = nums[slow];
            fast = nums[nums[fast]];
        } while (slow != fast);

        slow = nums[0];
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }

        return slow;
    }
};