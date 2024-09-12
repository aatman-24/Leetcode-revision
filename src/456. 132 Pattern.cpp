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

Question : 456. 132 Pattern
Topic : Stack, Mono-stack
Problems : https://leetcode.com/problems/132-pattern/description/

==============================> Explanation <=============================================

1) Brute Force: Using three for loops(i, j, k) we need to check manually is there any
triplet which fulfil the given condition. Time: O(N^3), Space: O(1)

2) Mono Incresing stack:
- To get s1 < s3 < s2, for i < j < k
we need to know what is min and max at any ith location from visited elements.
Any time (min, max)(s1, s2)... and current nums[i](s3) is there, min(i) < nums[i](k) < max(j).... we found triplet. But how to achieve that ?

We keep track of (min, max) at every ith location.

i) s1 > nums[i], (found new min)
->  It means s3(new_element) < s1, so we can't use the previous (0, i-1) elements memory for max_element of range. So we need to use
(min, max)(s1, s2) = (nums[i], nums[i])

ii) s2(max) < s3
- we know that from (0, i-1) we have (s1, s2) as (min, max) range. If s3 > s2... means we need to use s3 as our max, not s2.

iii) s1 < s3 && s2(max) > s3 (found our triplet)
- if any time nums[i] is bw s1 and s2... we found our ans.

To keep memeory at each we are using the stack. For condition-2 we need increasing mono stack until we get new min (this is for some portion of array, not for entire arr)

==============================> Approach and Time Complexity <============================

N = s.size()

1) Brute Force
Time: O(N^3)
Space: O(1)

2) Mono incresing stack
Time: O(N)
Space: O(N)


*/




class Solution {
public:

    // s1 < s3 < s2
    bool find132pattern(vector<int>& nums) {

        // Base case.
        if (nums.size() <= 2)
            return false;

        // store the (s1, s2) range for current Ith.
        stack<pair<int, int>> minMaxRange;

        for (int s3 : nums) {

            if (minMaxRange.empty()) {
                minMaxRange.push({s3, s3});
                continue;
            }

            // top of stack is (s1, s2) and s1 > s3. New Global Min Found.
            if (s3 < minMaxRange.top().first) {
                minMaxRange.push({s3, s3});
            } else { // s1 < s3

                // s3 < s2
                if (s3 < minMaxRange.top().second && minMaxRange.top().first < s3) return true;

                // Holding (0, i) min, max range at top of stack.
                // We are using curMinMax.first(s1), and will find out (s2) and place the (s1, s2) as new ranger after adding cur s3.
                // new S2 either can be previous (max of range) or cur s3.
                pair<int, int> curMinMax = minMaxRange.top();

                // Finding operation start: Gaol is to get maximum from previous max(previous_max, cur_s3);

                // until (s2 < s3), we remove those pairs because it can't give that range.
                while (!minMaxRange.empty() && minMaxRange.top().second < s3) {
                    minMaxRange.pop();
                }

                if (!minMaxRange.empty() && minMaxRange.top().second > s3 && minMaxRange.top().first < s3)
                    return true;

                // curTop

                minMaxRange.push({curMinMax.first, s3});
            }

        }

        return false;
    }
};


/*

We are traversing from the end of the array, reason is that It gives gurantee that if curr[i] > st.top(), curr[i] is one of best choice for s2 for range(i, N-1). why ?

arr = {12, 15, 10, 21, 20, 17}

[N-1, N-1] = st: 17
[N-2, N-1] = st: 20
[N-3, N-1] = st: 21

Noticed anything ?
- curr[i] is giving us boundary of maximum when we add it so it can be consider as s2. So if any element added before s2 which is less than curr[i] will be s3. Because,
curr[i](s2) > s3 and j < k.

So using the decreasing stack, we are able to find both s2 and s3 together. What ever is coming out of the stack is s3, because nums[i](s2) is greater than s3. And due to
maintaining the decreasing stack we need to remove it.

And we need to find the s1 which is less than s3.

*/


class Solution {
public:

    // s1 < s3 < s2
    bool find132pattern(vector<int>& nums) {

        int s3 = INT_MIN, N = nums.size();
        stack<int> st;

        for (int i = N - 1; i >= 0; i--) {

            if (st.empty()) {
                st.push(nums[i]);
                continue;
            }

            if (nums[i] < s3)  { return true; }

            else {

                while (!st.empty() && st.top() < nums[i]) {
                    s3 = st.top(); st.pop();        // popped element should be assign to s3, which indicate there is s2 which is greater than s3. (either from stack or current nums[i])
                }

                st.push(nums[i]);
            }
        }

        return false;
    }
};



/*


Why only increasign mono stack don't work when we do iteration from start that time ?

We can't solve using three pointers/sliding window.... It is not talking about continuous(i, j, k)(subsequent 3 elements). It is i < j < k. It can be happend at any point in array.

Give that, order of elements must be 132.

1 -> lowest of all three (i)
3 -> highest of all three (k)
2 -> middle of them (j)

If we use the increasing monotonic stack, it means we are allowing 1 and 3 to be in stack in increasing order. And when we find 2, that time it breaks the order because 1 < 2 > 3.

stack: nums(i) nums(k)          #strictly increasing

add if we found element nums(j)

stack: nums(i) nums(k)      | nums(j)(> nums(k)) that time we found our pattern 132.

Okay this soltuion won't work because

TC: 4 8 3 5

monoStack: 4 8, newEle = 3....

monStack: 3 (need to remove all elemetns)

monoStack: 4 8, newEle = 5....

monStack: 3 5

Here we have triplet (4, 8, 5) but we couldn't find it. Reason is that,
For the next upcoming elements (like here 5) we haven't checked previous mono stack before removing elements.

So we need that state as memory, It is not good idea to store entire stack as memory, we can use the (min, max) of that stack as memory.

*/