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

Question : 70. Climbing Stairs
Topic : DP
Problems :https://leetcode.com/problems/climbing-stairs/description/
==============================> Explanation <=============================================

Pattern=Fib

This time, we go from 0th_stair => Nth_stair. We are doing the reverse, then what is asked in question but both are same. (Previously We went from Nth=>0th)

1) Recurrence Relation (Nth_stair => 0th_stair)
F(N) => F(N-1) + F(N-2) (To reach, 0th step from Nth step, we can take N-1 step or N-2 step downside)
Base case, N < 0 => 0, N = 0 => 1

2) Recurrence Relation (0th_stair => Nth_stair)
F(N) => F(N+1) + F(N+2) (To reach, Nth step from 0th step, we can take N+1 step or N+2 step upward)
Base case, M > N  => 0, M = N => 1

"+" => asked, number of ways.

==============================> Approach and Time Complexity <============================

1) DP
Time: O(2^N)(Recursion) => O(N)
Space: O(N) => O(1)

For Recursion,
Formula => processing_time_for_each_node * (breadth^depth) => O(1) * O(2^N)
Space => (maximum_depth)(stack space)

*/


// TD [0th step => Nth step]
/* Intution:
    Recurrence Relation (0th_stair => Nth_stair)
    F(N) => F(N+1) + F(N+2) (To reach, Nth step from 0th step, we can take N+1 step or N+2 step upward)
    Base case, M > N  => 0, M = N => 1
*/
class Solution {

public:

    int memo[100];

    int helper(int at, int N) {

        // Went above Nth stair, not acceptable we return 0. (How many way to reach at Nth step, when you are N+1 step ? => 0)
        if (at > N)
            return 0;

        // How many way to reach at Nth step, when you are Nth step ? => 1.
        if (at == N)
            return 1;

        if (memo[at] != -1)
            return memo[at];

        // climbStairs(n) = climbStairs(n+1) + climbStairs(n+2)
        // To reach Nth step we can either jump from (n-1)th step To Nth step or from (n-2)th step to N. (Yeah It looks counter intutitive in descriptive manner).
        return memo[at] = helper(at + 1, N) + helper(at + 2, N);
    }

    int climbStairs(int n) {
        memset(memo, -1, 100);
        return helper(0, n);
    }
};


// BU [0th step => Nth step]
class Solution {

public:

    int climbStairs(int n) {

        // Create dp table.
        int dp[100] = {0};

        // Base condition
        dp[N] = 1;

        for (int j = N - 1; j >= 0; j--)
            dp[j] = dp[j + 1] + dp[j + 2];

        return dp[0];
    }
};


// TD-Space: We can use two states instead of entire array. (I didn't coded here!!)