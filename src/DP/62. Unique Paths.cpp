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

Question : 62. Unique Paths
Topic : DP
Problems : https://leetcode.com/problems/unique-paths/description/

==============================> Explanation <=============================================

Pattern: DP-2D-Grid

Find out all possible way to reach (0, 0) => (M-1, N-1)(Or vice versa).

Recurrence Relation=> solve(i, j) => solve(i-1, j) + solve(i, j-1). (count all ways)

==============================> Approach and Time Complexity <============================

1) DP
Time: O(2^(M+N)) -> O(M*N)
Space: O(M*N) => O(M+N)

Depth => 2N
Breadth => 2

 */


// Top-Down Approach

/* Intuition:

Find out all possible way to reach (0, 0) => (M-1, N-1)(Or vice versa).

Recurrence Relation=> solve(i, j) => solve(i-1, j) + solve(i, j-1). (count all ways)

*/

class Solution {
public:

    int t[101][101];

    int uniquePathsHelper(int m, int n, int i, int j) {

        // Reached target
        if (i == 0 && j == 0)
            return 1;

        // OUT OF BOUND, NOT VALID MOVE
        if (i < 0 || j < 0)
            return 0;

        if (t[i][j] != -1)
            return t[i][j];

        return t[i][j] = uniquePathsHelper(m, n, i - 1, j) + uniquePathsHelper(m, n, i, j - 1);
    }


    int uniquePaths(int m, int n) {

        memset(t, -1, sizeof(t));

        return uniquePathsHelper(m, n, m - 1, n - 1);
    }
};


// Bottom-Up Apporach
class Solution {
public:
    int uniquePaths(int m, int n) {

        // dp-table
        int dp[101][101];
        memset(dp, 0, sizeof(dp));

        // base case
        dp[0][0] = 1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i - 1 >= 0) {
                    dp[i][j] += dp[i - 1][j];
                }
                if (j - 1 >= 0) {
                    dp[i][j] += dp[i][j - 1];
                }
            }
        }

        return dp[m - 1][n - 1];
    }
};

// Bottom-Up Space Optimization
// From BU, you can see when we calculate the dp[i][x]...that time we are using the
// result from previous state dp[i-1][x].. so we can optimize that.
// Same thing won't possible for dp[j].. Remember you can reduce the space by 1 degree only.
// If it is O(N^2) you can make to O(N) only.

// NOTE: To avoid too many if-else condition, use the last soulution of this file.
class Solution {
public:
    int uniquePaths(int m, int n) {

        // dp-table
        vector<int> dp(n, 0);

        // base case
        dp[0] = 1;

        for (int i = 0; i < m; i++) {

            vector<int> pre = dp;

            for (int j = 0; j < n; j++) {

                // ignore this, it is base case.
                if (i == 0 && j == 0)
                    continue;

                // reset d[i][j] = 0
                dp[j] = 0;

                if (i - 1 >= 0) {
                    dp[j] += pre[j]; // dp[i-1][j] => pre[j] (previous
                    // dp_row)
                }

                if (j - 1 >= 0) {
                    dp[j] += dp[j - 1]; // dp[i][j-1] => dp[j-1] (current_dp_row)
                }
            }
        }

        return dp[n - 1];
    }
};



// clear-code
class Solution {
public:
    int uniquePaths(int m, int n) {

        // all the dp[i][0] and dp[0][j] has one way to reach to the (0,0) either in single
        // column or row so directly use that. and start from row=1 and col=1.
        vector<vector<int>> dp(m, vector<int>(n, 1));
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1];
    }
};


// BUS
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<int> pre(n, 1), cur(n, 1);
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                cur[j] = pre[j] + cur[j - 1];
            }
            swap(pre, cur);
        }
        return pre[n - 1];
    }
};