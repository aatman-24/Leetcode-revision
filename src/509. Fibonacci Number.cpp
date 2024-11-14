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

Question : 509. Fibonacci Number
Topic : DP
Problems : https://leetcode.com/problems/fibonacci-number/
==============================> Explanation <=============================================

Pattern=Fib

Standard DP Question.

FIB = 1, 1, 2, 3, 5, 8....

Recurrence Relation: fib(n) = fib(n-1) + fib(n-2).

Base case,
    n = 0 => 0 (Out of bound)
    n = 1 => 1
    n = 2 => 1

NOTE: I haven't handled the base case N = 0... Please do it if you are doing this question.

==============================> Approach and Time Complexity <============================

1) DP
Time: O(2^N)(Recursion) => O(N)(DP)
Space: O(N) => O(1)

For Recursion,
Formula => processing_time_for_each_node * (breadth^depth) => O(1) * O(2^N)
Space => (maximum_depth)(stack space)

 */


// FIB = 1, 1, 2, 3, 5, 8....
// Recursion
int fib(int n) {
    if (n <= 2) {
        return 1;
    }
    return fib(n - 1) + fib(n - 2);
}
// time: 2^N, space: N


// Top-Down
int fib(int n, int memo[]) {

    if (n <= 2) {
        memo[n] = 1;
        return 1;
    }

    if (memo[n] != -1)
        return memo[n];

    return memo[n] = fib(n - 1) + fib(n - 2);
}

int fib(n) {
    int memo[n + 1] = { -1};
    return fib(n, memo);
}

// Bottom-Up
int fib(int n) {

    // declare dp table.
    int dp[n + 1] = {0};

    // base case
    dp[1] = dp[2] = 1;


    for (int i = 3; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    // return dp[n] which hold the result for fib(n).
    return dp[n];
}

// BUS
// As we can see, dp[i] only need two previous state. We can use two variable instead of having entire array.
int fib(int n) {

    // To handle the base case.
    if (n <= 2)
        return true;

    int prev_1 = 1;     // dp[i-1]
    int prev_2 = 1;     // dp[i-2]

    for (int i = 3; i <= n; i++) {
        int curr = prev_1 + prev_2;
        prev_2 = prev_1;
        prev_1 = curr;      // At the end we store result prev_1.
    }

    return prev_1;
}
