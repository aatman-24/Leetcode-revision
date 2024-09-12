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

Question : 918. Maximum Sum Circular Subarray
Topic : DP, Kadene
Problems : https://leetcode.com/problems/maximum-sum-circular-subarray/description/

==============================> Explanation <=============================================

Before solving this question you should know kadene's algorithm. 1D-DP Question.

Idea is that,

    - It is straight foward to find the maxSum using kadene's algorithm in 1D array.
    - But given that, need to use circular array... It means we can have the subarray from N-1, 0, 1,... N-2 as well. Which is tricky.

    We can't use that rounding trick to add 0 to N-2 elements at the end of array from starting. If we do that, then all elements are
    positive then we can have subarray sum [0...N-1, 0...N-2]...

So trick is that,

    There is 2 possibilitie either we have answer(subarray) straight forward in array or it is in circular array.

    If it is from (0, N-1): we can use kadene's algorithm for that.

    If it is in round subarray: It means its have prefix-range(some part from starting of array)+ suffix(some part from ending of array) as maxSum subarray.
        For that we can use this logic, if we find range in array which have minimum subarray sum and subtract it from total of subarray then we got the
        maximum subarray sum.  Here is the proof,

If maxSum is from circular subarray:
= max(prefix+suffix)
= max(total sum - subarray),
= total_sum + max(-subarray)
= total_sum - min(subarray)

It means, If maxSum is from circular subarray, we need to find the subarray which have minimum sum value. so we can subtract it from total_sum.
We can use the kadene algorithm, to find the minimum sum of subarray.

Edge case,

If entire array is negative, that case we have maxSum=max(A) and minSum=sum(A).

if, minSum == sum(A), we return our answer maxSum direclty. (not 0).

maxSum = total_sum - min(subarray)
       = total_sum - total_sum
       = 0

so if maxSum is 0, in that case maxSum should be max(A) which we need to keep track of.

==============================> Approach and Time Complexity <============================

N = s.size()

2) kadene
Time: O(N)
Space: O(1)

*/


class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {

        int total = 0; // keep track of total sum.
        int maxCurSum = 0; // keep track of maxSum using kadene algorithm, we cannot forward negative maxCurSum to next element.
        int minCurSum = 0; // keep track of minSum using kadene algorithm, we cannot forward positive minCurSum to next element.

        int maxSum = INT_MIN;
        int minSum = INT_MAX;

        for (int num : nums) {

            total += num;
            maxCurSum += num;
            maxSum = max(maxSum, maxCurSum);
            if (maxCurSum < 0)
                maxCurSum = 0;

            minCurSum += num;
            minSum = min(minSum, minCurSum);
            if (minCurSum > 0)
                minCurSum = 0;
        }

        // If entire array is netative then, minSum and total will be same, in that case one of negative element hold maxValue.
        // Otherwise we return maxSum, found in straight array or circular array which ever is maximum.
        return (total == minSum) ? maxSum : max(maxSum, total - minSum);
    }
};
