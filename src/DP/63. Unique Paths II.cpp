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

Question : 63. Unique Paths II
Topic : DP
Problems : https://leetcode.com/problems/unique-paths/description/

==============================> Explanation <=============================================

Pattern: DP-Grid

Parent: 62. Unique Paths I

Additionaly give that, we can't pass through obstacle.. so whichever path going through it will be block.

so we consider dp[i][j] = 0 for such blocker, becasue we can't reach (i, j) => (0, 0) due to it.

Other path which is passing through it also will be affected, which is correct.

Recurrence Relation=> solve(i, j) => solve(i-1, j) + solve(i, j-1).

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

Additionaly give that, we can't pass through obstacle.. so whichever path going through it will be block.

so we consider dp[i][j] = 0 for such blocker, becasue we can't reach (m-1, n-1) => (0, 0) due to such blocker.

Other path which is passing through it also will be affected, which is correct.


*/

class Solution {
public:

    int t[101][101];

    int uniquePathsWithObstaclesCount(vector<vector<int>>& obstacleGrid, int i, int j) {

        // reach the destination.
        if (i == 0 && j == 0)
            return 1;

        // OUT OF BOUND, NOT VALID MOVE
        if (i < 0 || j < 0)
            return 0;

        // We can't go through obstacle or from it, so total number of ways to reach destination is 0.
        if (obstacleGrid[i][j] == 1)
            return 0;

        if (t[i][j] != -1)
            return t[i][j];

        return t[i][j] = uniquePathsWithObstaclesCount(obstacleGrid, i - 1, j) + uniquePathsWithObstaclesCount(obstacleGrid, i, j - 1);
    }


    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        memset(t, -1, sizeof(t));
        // Edge Case: If destination is itself obstacle, then there is no way we reach there.
        if (obstacleGrid[0][0] == 1)
            return 0;
        return uniquePathsWithObstaclesCount(obstacleGrid, obstacleGrid.size() - 1, obstacleGrid[0].size() - 1);
    }
};


// Bottom-Up Apporach
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {

        // Edge case
        if (obstacleGrid[0][0] == 1)
            return 0;

        // dp-table
        int dp[101][101];
        memset(dp, 0, sizeof(dp));

        // base case
        dp[0][0] = 1;

        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (obstacleGrid[i][j] == 1) {
                    dp[i][j] = 0;
                    continue;
                }
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
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {

        // Edge case
        if (obstacleGrid[0][0] == 1)
            return 0;

        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();

        // dp-table with base case.
        vector<int> cur(n, 0);

        for (int i = 0; i < m; i++) {

            // store previous state.
            vector<int> pre = cur;

            for (int j = 0; j < n; j++) {

                // base case; for this we don't want to set cur[j] = 0, because dp[0][0] = 1 => cur[0] = 1.
                if (i == 0 && j == 0)  {
                    cur[j] = 1;
                    continue;
                }

                // edge case
                if (obstacleGrid[i][j] == 1) {
                    cur[j] = 0;
                    continue;
                }

                // reset it
                cur[j] = 0;

                if (i - 1 >= 0) {
                    cur[j] += pre[j];
                }
                if (j - 1 >= 0) {
                    cur[j] += cur[j - 1];
                }
            }
        }

        return cur[n - 1];
    }
};