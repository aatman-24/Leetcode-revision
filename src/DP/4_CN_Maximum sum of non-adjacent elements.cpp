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

Question : 4_CN_Maximum sum of non-adjacent elements
Topic : DP
Problems : https://www.naukri.com/code360/problems/maximum-sum-of-non-adjacent-elements_843261?source=youtube&campaign=striver_dp_videos&leftPanelTabValue=PROBLEM
==============================> Explanation <=============================================

First step is to identify the given problem is DP or not.
Clue: Given that, all possible subsequence with some constraint(no two adjacent element together) you need to pick one which
      give you maximum sum. For that we need to explore all possible subsequence and choose maximum one.

What choice diagram looks like ?

F(i) => Return the maximum sum possible with given constraint from [arr[i] -> arr[N]).
For that we have two choice,
    Pick up current element, or not to pick up current elemment
        pick up:
            cost = arr[i] + F(i+2)[Which give best result from [arr[i+2] => N]]
        not pick up:
            cost = F(i+1)[Which give best result from [arr[i+1] => N]]

So we got our recurrence relation which looks like this,

    F(i) = max(arr[i] + F(i+2), F(i+1))

    And each F(i) have atleast arr[i] as maxCost in case, (i+2) and (i+1) is not valid.

    Check the code!!

We can more optimize with space from O(N) => O(1) using two state.

==============================> Approach and Time Complexity <============================

1) DP
Time: O(2^N) => O(N)
Space: O(N)

 */


// TD (From 0 -> N)
/* Intuition:

What choice diagram looks like ?

F(i) => Return the maximum sum possible with given constraint in question from [arr[i] -> arr[N]).
For that we have two choice,
    Pick up current element, or not to pick up current elemment
        If we pick up ith element, then we can't pick up next element, can pick up (i+2)th element:
            cost = arr[i] + F(i+2)[Which give best result from [arr[i+2] => N]]
        not pick up:
            cost = F(i+1)[Which give best result from [arr[i+1] => N]]

So we got our recurrence relation which looks like this,

    F(i) = max(arr[i] + F(i+2), F(i+1))

    And each F(i) have atleast arr[i] as maxCost in case, (i+2) and (i+1) is not valid.
*/


int memo[100001];

int helper(vector<int> &nums, int index) {

    // Base case: Only one element left, you have to take it.
    if (index == nums.size() - 1)
        return nums[index];

    if (memo[index] != -1)
        return memo[index];

    // Assigned direct cost, because for array [1, 2] when we take 0th element, we can't jump to index=2...
    // So to consider the cost of 0th index, we pre-assign the cost.
    int maxCost = nums[index];

    // Take current "index", then jump to "index+2"
    if ((index + 2) < nums.size()) {
        maxCost = max(maxCost, helper(nums, index + 2) + nums[index]);
    }

    // Not to take current "index", then we can take cost from "index+1".
    if ((index + 1) < nums.size()) {
        maxCost = max(maxCost, helper(nums, index + 1));
    }

    return memo[index] = maxCost;
}


int maximumNonAdjacentSum(vector<int> &nums) {
    memset(memo, -1, sizeof(memo));
    return helper(nums, 0);
}


// BU
int maximumNonAdjacentSum(vector<int> &nums) {

    int N = nums.size();

    // base case
    if (N == 1)
        return nums[0];

    vector<int> dp(N, -1);
    dp[N - 1] = nums[N - 1]; // base case

    for (int i = N - 1; i >= 0; i--) {

        // Atleast ith number have cost nums[i]. (bare minimum)
        int maxCost = nums[i];

        // Taking current "ith" num.
        if (i + 2 < N) {
            maxCost = max(maxCost, dp[i + 2] + nums[i]);
        }

        // Not taking the current "ith" num, and choosing the previous number best result.
        if (i + 1 < N) {
            maxCost = max(maxCost, dp[i + 1]);
        }

        dp[i] = maxCost;
    }

    // At the end, final result stored in dp[0].
    return dp[0];
}






// TD TD (From N -> 0)

int memo[100001];

int helper(vector<int> &nums, int index) {

    // base case
    if (index == 0)
        return nums[index];

    if (memo[index] != -1)
        return memo[index];

    int maxCost = nums[index];

    // Taking "index" element, then jump to (index-2)th element.
    if ((index - 2) >= 0) {
        maxCost = max(maxCost, helper(nums, index - 2) + nums[index]);
    }
    if ((index - 1) >= 0) {
        maxCost = max(maxCost, helper(nums, index - 1));
    }

    return memo[index] = maxCost;
}


int maximumNonAdjacentSum(vector<int> &nums) {
    memset(memo, -1, sizeof(memo));
    return helper(nums, nums.size() - 1);
}


// BU
int maximumNonAdjacentSum(vector<int> &nums) {
    int N = nums.size();

    // base case
    if (N == 1)
        return nums[0];

    vector<int> dp(N + 1, -1);
    dp[0] = nums[0]; // base case

    for (int i = 1; i < N; i++) {

        // atleast ith number have cost nums[i]. (bare minimum)
        int maxCost = nums[i];

        // Taking current ith num.
        if (i - 2 >= 0) {
            maxCost = max(maxCost, dp[i - 2] + nums[i]);
        }

        // Not taking the current ith num, and choosing the previous number best result.
        if (i - 1 >= 0) {
            maxCost = max(maxCost, dp[i - 1]);
        }

        dp[i] = maxCost;
    }

    return dp[N - 1];
}
