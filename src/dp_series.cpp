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

Question : DP SERIES
Problems :
Pattern:

==============================> Explanation <=============================================


==============================> Approach and Time Complexity <============================

1)
Time:
Space:
*/

// PATTERN: FIBONNACI-PATTERN
/*

In this pattern, the outcome of dp[n] is depend on previous state. And processing time of each
node is O(1).

*/


// 509. Fibonacci Number

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



// 70. Climbing Stairs
// BU
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


// TD
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


// TD-Space: We can use two states instead of entire array. (I didn't codede here!!)


// 1_CN_Frog Jump

int memo[100001];

int frogJump(vector<int> &heights, int index) {

    if (index == 1)
        return 0;       // base case, standing at 1st and staring from 1st, no energy required.

    if (memo[index] != -1)
        return memo[index];

    // Why if-else condition instead of equation use direct ?
    // Reason is that, if we do that way... f(index < 1) that time we return INT_MAX... and that is added with some cost
    // which don't fit in INT range... so we never call f(index<1) that's reason we wrote the code this way.


    int minCost = INT_MAX;

    if (index - 1 > 0) {
        minCost = min(minCost, frogJump(heights, index - 1) + abs(heights[index - 1] - heights[index - 2]));
    }

    if (index - 2 > 0) {
        minCost = min(minCost, frogJump(heights, index - 2) + abs(heights[index - 1] - heights[index - 3]));
    }

    return memo[index] = minCost;
}


int frogJump(int n, vector<int> &heights) {

    memset(memo, -1, sizeof(memo));

    return frogJump(heights, n);
}

// BU Approach
int frogJump(int n, vector<int> &heights) {

    vector<int> dp(n + 1, -1);

    // BASE CASE
    dp[1] = 0;

    for (int i = 2; i <= n; i++) {

        dp[i] = INT_MAX;        // MINCOST

        if (i - 1 > 0) {
            dp[i] = min(dp[i], dp[i - 1] + abs(heights[i - 1] - heights[i - 2]));
        }

        if (i - 2 > 0) {
            dp[i] = min(dp[i], dp[i - 2] + abs(heights[i - 1] - heights[i - 3]));
        }

    }

    return dp[n];
}


// BU-SPACE
int frogJump(int n, vector<int> &heights) {

    if (n == 1)
        return 0;

    // Two state to hold the result.
    int prev_1 = 0;             // f(i-1) state
    int prev_2 = INT_MAX;       // f(i-2) state

    for (int i = 2; i <= n; i++) {

        int curr = INT_MAX;     // MINCOST

        if (i - 1 > 0) {
            curr = min(curr, prev_1 + abs(heights[i - 1] - heights[i - 2]));
        }

        if (i - 2 > 0) {
            curr = min(curr, prev_2 + abs(heights[i - 1] - heights[i - 3]));
        }

        // SWAP THE results for next state
        prev_2 = prev_1;
        prev_1 = curr;          // at the end we are storing our result here
    }

    return prev_1;
}


// 2_Frog 1D

int memo[100001];

int frogJump(vector<int> &heights, int index, int k) {          // index=N.

    if (index == 1)
        return 0;       // base case, standing at 1st and reaching to 1st stone, no energy required.

    if (memo[index] != -1)
        return memo[index];

    int minCost = INT_MAX;
    for (int j = 1; j <= k; j++) {
        if ((index - j) > 0) {
            minCost = min(minCost, frogJump(heights, index - j, k) + abs(heights[index - 1] - heights[index - 1 - j]));
        }
    }

    return memo[index] = minCost;

}

// BU
int frogJump(vector<int> &heights, int N, int k) {

    // Base Case
    if (N == 1)
        return 0;

    vector<int> dp(N + 1, -1);

    // base case.
    dp[1] = 0;

    for (int i = 2; i <= N; i++) {
        int minCost = INT_MAX;
        for (int j = 1; j <= k; j++) {      // can jump upto k stone.
            if ((i - j) > 0) {
                minCost = min(minCost, dp[i - j] + abs(heights[i - 1] - heights[i - 1 - j]));
            }
        }
        dp[i] = minCost;
    }

    return dp[N];
}


// BU-Space: We need to know the last K state only. Space:O(K)
// We need to override the kth state every time.. what I mean is that... state=1, k=3 then when we reach at
// state=4..then we store that result at dp[(state-k)=(4-3)=1]..got it ?
int frogJump2(vector<int> &heights, int N, int k) {

    // Base Case
    if (N == 1)
        return 0;

    vector<int> dp(k + 1, -1);

    // offset to adjust dp table index. As we are using the % operator for overriding we need to store result starting from 0th index for easiness.
    // but do this step later.. first write code and then offet the dp table index only.
    // you know why we need to use % K...right.
    int OFFSET = 1;

    // base case.
    dp[1 - OFFSET] = 0;

    for (int i = 2; i <= N; i++) {
        int minCost = INT_MAX;
        for (int j = 1; j <= k; j++) {      // can jump upto k stone.
            if ((i - j) > 0) {
                minCost = min(minCost, dp[(i - j - OFFSET) % k] + abs(heights[i - 1] - heights[i - 1 - j]));
            }
        }
        dp[(i - OFFSET) % k] = minCost;
    }

    return dp[(N - OFFSET) % k];
}


// 4_CN_Maximum sum of non-adjacent elements
int memo[100001];

int helper(vector<int> &nums, int index) {

    if (index == 0)
        return nums[index];

    if (memo[index] != -1)
        return memo[index];

    int maxCost = nums[index];

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
            maxCost = max(maxCost, dp[i - 2] + maxCost);
        }

        // Not taking the current ith num, and choosing the previous number best result.
        if (i - 1 >= 0) {
            maxCost = max(maxCost, dp[i - 1]);
        }

        dp[i] = maxCost;
    }


    return dp[N - 1];
}



// 5_CN_Ninja_Training 2D DP

// TD (0 -> N)

int t[100001][11];

int ninjaTrainingHelper(vector<vector<int>> &points, int day, int task) {

    // base case
    if (day == points.size() - 1)
        return points[day][task];

    if (t[day][task] != -1)
        return t[day][task];

    int maxCost = 0;

    for (int nextTask = 0; nextTask < points[0].size(); i++) {

        if (nextTask != task) {

            maxCost = max(maxCost, points[day][task] + ninjaTraining(points, day + 1, nextTask));

        }
    }

    return t[day][task] = maxCost;
}


int ninjaTraining(int n, vector<vector<int>> &points) {

    int M = points.size(), N = points[0].size();
    memset(t, -1, sizeof(t));

    int maxCost = 0;
    for (int task = 0; task < N; task++) {
        maxCost = max(maxCost, ninjaTrainingHelper(points, 0, task));
    }

    return maxCost;
}




// BU
int ninjaTraining(int n, vector<vector<int>> &points) {

    int M = points.size(), N = points[0].size();

    // dp table.
    vector<vector<int>> dp(M + 1, vector<int>(N + 1, 0));

    // base case.
    for (int t = 0; t < N; t++) {
        dp[M - 1][t] = points[M - 1][t];
    }

    for (int d = M - 2; d >= 0; d--) {
        for (int task = 0; task < N; task++) {
            int maxCost = 0;
            for (int nextTask = 0; nextTask < N; nextTask++) {
                if (task != nextTask) {
                    maxCost = max(maxCost, points[d][task] + dp[d + 1][nextTask]);
                }
            }
            dp[d][task] = maxCost;
        }
    }

    int bestCost = 0;
    for (int i = 0; i < N; i++) {
        bestCost = max(bestCost, dp[0][i]);
    }

    return bestCost;
}


// BUS

int ninjaTraining(int n, vector<vector<int>> &points) {

    int M = points.size(), N = points[0].size();

    // dp row only. (Which hold ith state result)
    vector<int> dp(N + 1, 0);

    // base case.
    for (int t = 0; t < N; t++) {
        dp[t] = points[M - 1][t];
    }

    // Use three variable to compute task.
    for (int d = M - 2; d >= 0; d--) {

        // Storing the current state resutl into new array.
        vector<int> curr_dp(N + 1, 0);

        for (int task = 0; task < N; task++) {

            // same as recursion.
            int maxCost = 0;
            for (int nextTask = 0; nextTask < N; nextTask++) {
                if (task != nextTask) {
                    maxCost = max(maxCost, points[d][task] + dp[nextTask]);
                }
            }
            curr_dp[task] = maxCost;
        }

        // forwarding ith state result to dp array.
        dp = curr_dp;
    }

    // At the dp[0][i] containts the max cost, if we started from that 0th day. So we need to take maximum of that.
    // This also work as base case when N = 1.
    int bestCost = 0;
    for (int i = 0; i < N; i++) {
        bestCost = max(bestCost, dp[i]);
    }

    return bestCost;
}

// 62. Unique Paths
// Top-Down Approach
class Solution {
public:

    int t[101][101];

    int uniquePathsHelper(int m, int n, int i, int j) {

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

//63. Unique Paths II

// Top-Down Approach
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


// 64. Minimum Path Sum


// Top-down approach
class Solution {
public:

    int t[201][201];

    int minPathSumSupport(vector<vector<int>>& grid, int i, int j) {

        if (i == 0 && j == 0)
            return grid[i][j];

        if (i < 0 || j < 0)
            return INT_MAX;

        if (t[i][j] != -1)
            return t[i][j];

        return t[i][j] = grid[i][j] + min(minPathSumSupport(grid, i - 1, j), minPathSumSupport(grid, i, j - 1));
    }


    int minPathSum(vector<vector<int>>& grid) {
        memset(t, -1, sizeof(t));
        return minPathSumSupport(grid, grid.size() - 1, grid[0].size() - 1);
    }
};

// BU

class Solution {
public:

    int minPathSum(vector<vector<int>>& grid) {

        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));

        // base-case
        dp[0][0] = grid[0][0];

        for (int i = 0; i < m; i++) {

            for (int j = 0; j < n; j++) {

                dp[i][j] = grid[i][j];

                if (i - 1 >= 0 && j - 1 >= 0) {
                    dp[i][j] += min(dp[i - 1][j], dp[i][j - 1]);
                }
                else if (j - 1 >= 0) {
                    dp[i][j] += dp[i][j - 1];
                }
                else if (i - 1 >= 0) {
                    dp[i][j] += dp[i - 1][j];
                }
            }
        }

        return dp[m - 1][n - 1];
    }
};


// BUS
class Solution {
public:

    int minPathSum(vector<vector<int>>& grid) {

        int m = grid.size(), n = grid[0].size();

        // base-case
        vector<int> pre(n, 0), cur(n, 0);
        cur[0] = grid[0][0];        // don't need of this line.

        for (int i = 0; i < m; i++) {

            for (int j = 0; j < n; j++) {

                cur[j] = grid[i][j];

                if (i - 1 >= 0 && j - 1 >= 0) {
                    cur[j] += min(pre[j], cur[j - 1]);
                }
                else if (j - 1 >= 0) {
                    cur[j] += cur[j - 1];
                }
                else if (i - 1 >= 0) {
                    cur[j] += pre[j];
                }
            }

            swap(cur, pre);
        }

        // At the end, last result is stored in pre.
        return cur[n - 1];
    }
}

// 120. Triangle
// TD
class Solution {
public:

    int t[201][201];

    int minimumTotalHelper(vector<vector<int>>& triangle, int i, int j) {

        if (i == triangle.size() - 1)
            return triangle[i][j];

        if (t[i][j] != -1)
            return t[i][j];

        return t[i][j] = triangle[i][j] + min(minimumTotalHelper(triangle, i + 1, j),  minimumTotalHelper(triangle, i + 1, j + 1));
    }


    int minimumTotal(vector<vector<int>>& triangle) {

        memset(t, -1, sizeof(t));

        return minimumTotalHelper(triangle, 0, 0);
    }
};

// BU
class Solution {
public:

    int minimumTotal(vector<vector<int>>& triangle) {

        int m = triangle.size(), n = triangle[m - 1].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));

        int k = n - 1;

        for (int i = m - 1; i >= 0; i--) {

            for (int j = k; j >= 0; j--) {

                dp[i][j] = triangle[i][j];

                if (i + 1 < m) {
                    dp[i][j] += min(dp[i + 1][j], dp[i + 1][j + 1]);
                }
            }

            k--; // reduce the length of triangle.
        }

        return dp[0][0];
    }
};

// BUS
class Solution {
public:

    int minimumTotal(vector<vector<int>>& triangle) {

        int m = triangle.size(), n = triangle[m - 1].size();
        vector<int> pre(n, 0), cur(n, 0);

        int k = n - 1;

        for (int i = m - 1; i >= 0; i--) {

            for (int j = k; j >= 0; j--) {

                cur[j] = triangle[i][j];

                if (i + 1 < m) {
                    cur[j] += min(pre[j], pre[j + 1]);      // choose the cost from previous calcualted state (i+1)th
                }
            }

            k--; // reduce the length of triangle.
            swap(pre, cur);
        }

        return pre[0];
    }
};


// 6_CN_Maximum Path Sum in the matrix
// TD
int dy[3] = {0, 1, -1};

int getMaxPathSumHelper(vector<vector<int>> &matrix, int i, int j, vector<vector<int>> &t) {

    if (i == 0) {
        return matrix[i][j];
    }

    if (t[i][j] != INT_MIN)
        return t[i][j];

    int maxi = INT_MIN;

    for (int k = 0; k < 3; k++) {

        int yy = j + dy[k];

        // Out of Boundary.
        if (i < 0 || yy < 0 || yy >= matrix[0].size())
            continue;

        maxi = max(maxi, matrix[i][j] + getMaxPathSumHelper(matrix, i - 1, yy, t));
    }

    return t[i][j] = maxi;
}



int getMaxPathSum(vector<vector<int>> &matrix) {

    // memorization
    int m = matrix.size(), n = matrix[0].size();
    vector<vector<int>> t(m, vector<int>(n, INT_MIN));

    int maxCost = INT_MIN;
    for (int j = 0; j < n; j++) {
        maxCost = max(maxCost, getMaxPathSumHelper(matrix, m - 1, j, t));
    }

    return maxCost;
}


// BU - Converted Above into this one.
int getMaxPathSum(vector<vector<int>> &matrix) {

    // memorization
    int m = matrix.size(), n = matrix[0].size();
    vector<vector<int>> dp(m, vector<int>(n, INT_MIN));

    // base case, for 0th index we are returing (0, j) element as it is.
    for (int j = 0; j < n; j++)
        dp[0][j] = matrix[0][j];

    // directions
    int dy[3] = {0, 1, -1};

    for (int i = 1; i < m; i++) {

        for (int j = 0; j < n; j++) {

            // find the maximum cost from all directions and save at (i, j).

            int maxi = INT_MIN;

            for (int k = 0; k < 3; k++) {

                int yy = j + dy[k];

                // Out of Boundary.
                if (yy < 0 || yy >= matrix[0].size())
                    continue;

                maxi = max(maxi, matrix[i][j] + dp[i - 1][yy]);

            }

            dp[i][j] = maxi;
        }
    }


    // After all steps completed, we can see at last index(target location) which index have maximum cost,
    // will return that.
    int maxCost = INT_MIN;
    for (int j = 0; j < n; j++) {
        maxCost = max(maxCost, dp[m - 1][j]);
    }

    return maxCost;
}

// BUS

int getMaxPathSum(vector<vector<int>> &matrix) {

    // memorization
    int m = matrix.size(), n = matrix[0].size();

    vector<int> pre(n, 0), cur(n, 0);

    // base case, for 0th index we are returing (0, j) element as it is.
    for (int j = 0; j < n; j++)
        pre[j] = matrix[0][j];

    // directions
    int dy[3] = {0, 1, -1};

    for (int i = 1; i < m; i++) {

        for (int j = 0; j < n; j++) {

            // find the maximum cost from all directions and save at (i, j).

            int maxi = INT_MIN;

            for (int k = 0; k < 3; k++) {

                int yy = j + dy[k];

                // Out of Boundary.
                if (yy < 0 || yy >= matrix[0].size())
                    continue;

                maxi = max(maxi, matrix[i][j] + pre[yy]);

            }

            cur[j] = maxi;
        }

        swap(pre, cur);     // at the end, last m-1 row wil be stored in "pre"
    }


    // After all steps completed, we can see at last index(target location) which index have maximum cost,
    // will return that.
    int maxCost = INT_MIN;
    for (int j = 0; j < n; j++) {
        maxCost = max(maxCost, pre[j]);
    }

    return maxCost;
}

// 7_CN_Subset Sum Equal To K

// Top-down
#include <bits/stdc++.h>

int t[1001][1001];

bool subsetSumToKHelper(vector<int> &arr, int index, int target) {

    // Base case
    if (target == 0)
        return true;

    // Incase we are out of element and still target > 0, indicate we failed to find subset.
    if (index < 0)
        return false;

    if (t[index][target] != -1)
        return t[index][target];

    bool foundSubset = false;

    // we take arr[index] into consideration, only when arr[index] <= target.
    // We have two choice either take it or not take it(remember the subset backtracking problem).
    if (target - arr[index] >= 0) {
        foundSubset = subsetSumToKHelper(arr, index - 1, target - arr[index]) || subsetSumToKHelper(arr, index - 1, target);
    }
    else {  // Incase we won't able to take, we move to next element.
        foundSubset = subsetSumToKHelper(arr, index - 1, target);
    }

    return t[index][target] = foundSubset;
}



bool subsetSumToK(int n, int k, vector<int> &arr) {

    memset(t, -1, sizeof(t));

    return subsetSumToKHelper(arr, n - 1, k);
}


// Bottom-Up
bool subsetSumToK(int n, int k, vector<int> &arr) {

    vector<vector<bool>> dp(n + 1, vector<bool>(k + 1, false));

    // base case.
    for (int i = 0; i <= n; i++)
        dp[i][0] = true;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            if (j - arr[i - 1] >= 0) {
                dp[i][j] = dp[i - 1][j - arr[i - 1]] || dp[i - 1][j];
            }
            else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }


    return dp[n][k];
}

// BUS
bool subsetSumToK(int n, int k, vector<int> &arr) {

    vector<int> prev(k + 1, false), cur(k + 1, false);

    // base case, indicate...dp[0][0] = true
    pre[0] = true;

    for (int i = 1; i <= n; i++) {

        // dp[i][0] = true, indicate dp[i][0] = true, as target = 0.
        cur[0] = true;

        for (int j = 1; j <= k; j++) {
            if (j - arr[i - 1] >= 0) {
                cur[j] = prev[j - arr[i - 1]] || prev[j];
            }
            else {
                cur[j] = prev[j];
            }
        }

        swap(cur, prev);        // at the end, result will got stored in prev.
    }


    return prev[k];
}


// 8_CN_Partition Equal Subset Sum
// TD
int t[101][10001];

#include <bits/stdc++.h>

// Return total sum of array.
int getArraySum(vector<int> &arr) {
    int sum = 0;
    for (int num : arr) {
        sum += num;
    }
    return sum;
}

bool findSubsetWithSumEqualK(vector<int> &arr, int index, int target) {

    // Base case
    if (target == 0)
        return true;

    // Edge case, out of range, no more element and target > 0.
    if (index < 0)
        return false;

    if (t[index][target] != -1)
        return t[index][target];

    bool foundSubset = false;
    if (target - arr[index] >= 0) {
        foundSubset = findSubsetWithSumEqualK(arr, index - 1, target - arr[index]) || findSubsetWithSumEqualK(arr, index - 1, target);
    }
    else {
        foundSubset = findSubsetWithSumEqualK(arr, index - 1, target);
    }

    return t[index][target] = foundSubset;
}

bool canPartition(vector<int> &arr, int n) {

    int sum = getArraySum(arr);
    bool isArraySumEven = sum % 2 == 0;
    if (!isArraySumEven)
        return false;
    memset(t, -1, sizeof(t));
    return findSubsetWithSumEqualK(arr, n - 1, sum / 2);
}


// Bottom-Up
bool canPartition(vector<int> &arr, int n) {

    int sum = getArraySum(arr);
    bool isArraySumEven = sum % 2 == 0;
    if (!isArraySumEven)
        return false;

    int target = sum / 2;

    // dp table
    vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));

    // base case
    for (int i = 0; i <= n; i++) {
        dp[i][0] = true;    // dp[i][target] = true, as target = 0.
    }


    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= target; j++) {
            if (j - arr[i - 1] >= 0) {      // following 0th based index in arr.
                dp[i][j] = dp[i - 1][j - arr[i - 1]] || dp[i - 1][j];
            }
            else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    return dp[n][target];
}


// BUS
bool canPartition(vector<int> &arr, int n) {

    int sum = getArraySum(arr);
    bool isArraySumEven = sum % 2 == 0;
    if (!isArraySumEven)
        return false;

    int target = sum / 2;

    // dp table
    vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));
    vector<bool> pre(target + 1, false), cur(target + 1, false);

    // base case
    pre[0] = true;      // indicate.. dp[i][0] = true....

    for (int i = 1; i <= n; i++) {
        cur[0] = true;      // indicate, dp[i][0] = true...
        for (int j = 1; j <= target; j++) {
            if (j - arr[i - 1] >= 0) {      // following 0th based index in arr.
                cur[j] = pre[j - arr[i - 1]] || pre[j];
            }
            else {
                cur[j] = pre[j];
            }
        }
        swap(pre, cur);     // at the end last result will be stored in pre.
    }

    return pre[target];
}


// 9_CN_Array partition with minimum difference*

int getArraySum(vector<int> &arr) {
    int sum = 0;
    for (int num : arr) {
        sum += num;
    }
    return sum;
}


int minSubsetSumDifference(vector<int>& arr, int n) {

    int sum = getArraySum(arr);

    int target = sum / 2;

    vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));

    // base case
    for (int i = 0; i <= n; i++)
        dp[i][0] = true;            // target = 0 =

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= target; j++) {
            if (j - arr[i - 1] >= 0) {
                dp[i][j] = dp[i - 1][j - arr[i - 1]] || dp[i - 1][j];
            }
            else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    // Acutal problem start from here, where we use the last row.
    int min_diff = INT_MAX;
    for (int j = 0; j <= target; j++) {         // s1_sum = 0 => target... because arr[i] also be 0... so start from 0.. s1 can be {0, 0} as well.
        if (dp[n][j] == true) {
            int s1_sum = j;
            int s2_sum = sum - j;
            min_diff = min(min_diff, abs(s1_sum - s2_sum));
        }
    }

    return min_diff;
}


// 10_Count Subsets with Sum K


#include <bits/stdc++.h>
#define mod 1000000007

int t[1001][1001];

int subsetSumToKHelper(vector<int> &arr, int index, int target) {

    // Base case, target is zero, found subset.
    if (target == 0) {
        return 1;
    }

    // Incase we are out of element and still target > 0, indicate we failed to find subset.
    if (index < 0)
        return 0;

    if (t[index][target] != -1)
        return t[index][target];

    long countSubset = 0;

    // we take arr[index] into consideration, only when arr[index] <= target.
    // We have two choice either take it or not take it(remember the subset backtracking problem).
    if (target - arr[index] >= 0) {
        countSubset = (subsetSumToKHelper(arr, index - 1, target - arr[index]) % mod) + (subsetSumToKHelper(arr, index - 1, target) % mod);
    }
    else {  // Incase we won't able to take, we move to next element.
        countSubset = subsetSumToKHelper(arr, index - 1, target);
    }

    return t[index][target] = countSubset % mod;
}





int findWays(vector<int>& arr, int k)
{
    memset(t, -1, sizeof(t));

    sort(arr.begin(), arr.end(), greater<int>());   // Edge Case: arr= {0, 0}

    return subsetSumToKHelper(arr, arr.size() - 1, k);
}

// 11_CN_Partitions With Given Difference

#include <bits/stdc++.h>
#define mod 1000000007

int t[1001][1001];

int getArraySum(vector<int> &arr) {
    int sum = 0;
    for (int num : arr) {
        sum += num;
    }
    return sum;
}


int subsetSumToKHelper(vector<int> &arr, int index, int target) {

    // Base case, target is zero, found subset.
    if (target == 0) {
        return 1;
    }

    // Incase we are out of element and still target > 0, indicate we failed to find subset.
    if (index < 0)
        return 0;

    if (t[index][target] != -1)
        return t[index][target];

    long countSubset = 0;

    // we take arr[index] into consideration, only when arr[index] <= target.
    // We have two choice either take it or not take it(remember the subset backtracking problem).
    if (target - arr[index] >= 0) {
        countSubset = (subsetSumToKHelper(arr, index - 1, target - arr[index]) % mod) + (subsetSumToKHelper(arr, index - 1, target) % mod);
    }
    else {  // Incase we won't able to take, we move to next element.
        countSubset = subsetSumToKHelper(arr, index - 1, target);
    }

    return t[index][target] = countSubset % mod;
}


int countPartitions(int n, int d, vector<int> &arr) {

    int sum = getArraySum(arr);

    int target = (d + sum) >> 1;

    if ((d + sum) % 2 == 1) return 0;       // check descirption... (d+sum) odd we can't divide into two subsets.

    memset(t, -1, sizeof(t));

    sort(arr.begin(), arr.end(), greater<int>());   // Edge Case: arr= {0, 0}

    return subsetSumToKHelper(arr, arr.size() - 1, target);
}

// Pattern: 0-1 Knapsack Pattern


// 12_CN_0_1_Knapsack_Standard

// Top-Down Apporach.
// For easiness, we are treating i=0 as out of bound. So managed index of weight and values
// that way by subtracting -1 whenever we select any item.

#include <bits/stdc++.h>

int t[101][1001];

int knapsackSupport(int i, vector<int> wt, vector<int> values, int W) {

    // Base case
    // Out of bound, For easiness we are treating index from (1, N).
    // Finding maximum value, so returned smallest positive value.
    if (i == 0) {
        return 0;
    }

    // Base case: No weight we can add any more, so we are returning value = 0.
    if (W == 0) {
        return 0;
    }

    if (t[i][W] != -1)
        return t[i][W];

    // If we are able to take ith item
    // We have two choice to try, take it or don't take it.
    int maxValue = 0;
    if (W - wt[i - 1] >= 0) {
        maxValue = max(knapsackSupport(i - 1, wt, values, W - wt[i - 1]) + values[i - 1], knapsackSupport(i - 1, wt, values, W));
    }

    // If we can't take ith item due to Weight constraint, we don't take it.
    else {
        maxValue = knapsackSupport(i - 1, wt, values, W);
    }

    return t[i][W] = maxValue;
}


int knapsack(vector<int> wt, vector<int> values, int n, int maxWeight) {

    // fill the memo table with -1.
    memset(t, -1, sizeof(t));

    return knapsackSupport(wt.size(), wt, values, maxWeight);
}


// Bottom-Up Approach
int knapsack(vector<int> wt, vector<int> values, int n, int W) {

    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    // Base case (Covered, dp table is initialize with 0 value)
    // dp[0][j] = 0.
    // dp[i][0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= W; j++) {
            int maxValue = 0;
            if (j - wt[i - 1] >= 0) {
                maxValue = max(dp[i - 1][j - wt[i - 1]] + values[i - 1], dp[i - 1][j]);
            }
            else {
                maxValue = dp[i - 1][j];
            }
            dp[i][j] = maxValue;
        }
    }

    return dp[n][W];
}


// Bottom-Up Approach With Space Optimization
int knapsack(vector<int> wt, vector<int> values, int n, int W) {

    vector<int> prev(W + 1, 0), cur(W + 1, 0);
    // Base case (Covered, dp table is initialize with 0 value)
    // cur[0][j] = 0.

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= W; j++) {
            int maxValue = 0;
            if (j - wt[i - 1] >= 0) {
                maxValue = max(prev[j - wt[i - 1]] + values[i - 1], prev[j]);
            }
            else {
                maxValue = prev[j];
            }
            cur[j] = maxValue;
        }
        swap(cur, prev);
    }

    return prev[W];
}

// 13_CN_Minimum Elements

// Top-Down Approach

// 1 <= N <= 15
// 1 <= T <= 10000
#include <bits/stdc++.h>
int t[16][10001];
int MAX = 1e9;

int minimumElementsHelper(int i, vector<int> &nums, int T) {

    // Edge case, last element left and still T > 0.
    if (i == 0) {
        if (T % nums[0] == 0)
            return T / nums[0];
        return MAX;
    }

    if (t[i][T] != -1) return t[i][T];

    // Keep track of minimum elements.
    int minimumElements = INT_MAX;

    // Take it or don't take it.
    if (T - nums[i] >= 0) {
        minimumElements = min(1 + minimumElementsHelper(i, nums, T - nums[i]), minimumElementsHelper(i - 1, nums, T));
    }
    else {
        minimumElements = minimumElementsHelper(i - 1, nums, T);
    }

    return t[i][T] = minimumElements;
}

int minimumElements(vector<int> &num, int T) {

    memset(t, -1, sizeof(t));

    sort(num.begin(), num.end());

    int minimumElements =  minimumElementsHelper(num.size() - 1, num, T);

    return min_elements < MAX ? min_elements : -1;
}


// Bottom-Up Approach

#include <bits/stdc++.h>
int MAX = 1e9;

int minimumElements(vector<int> &nums, int target) {

    // Total elements
    int N = nums.size();

    vector<vector<int>> dp(N, vector<int>(target + 1, 0));

    // BASE CASE: Last element left && T > 0.
    for (int j = 0; j <= target; j++) {
        if (j % nums[0] == 0) {
            dp[0][j] = j % nums[0];
        }
        else {
            dp[0][j] = MAX;
        }
    }

    for (int i = 1; i < N; i++) {
        for (int j = 0; j <= target; j++) {
            int minimumElements = MAX;
            if (j - nums[i] >= 0) {         // TAKE IT OR DON'T TAKE IT
                minimumElements = min(1 + dp[i][j - nums[i]], dp[i - 1][j]);
            }
            else {
                minimumElements = dp[i - 1][j];
            }
            dp[i][j] = minimumElements;
        }
    }

    int ans = dp[N - 1][target];
    if (ans >= MAX)
        return -1;
    return ans;
}


// 494. Target Sum

class Solution {

    int OFFSET = 2e4;

public:

    int t[21][100000];

    int findTargetSumWaysSupport(int index, int target, vector<int>& nums) {

        // out of bound, index range (1, N)
        if (index == 0) {
            return target == 0;
        }

        if (t[index][target + OFFSET] != -1)
            return t[index][target + OFFSET];

        return t[index][target + OFFSET] = findTargetSumWaysSupport(index - 1, target - nums[index - 1], nums) + findTargetSumWaysSupport(index - 1, target + nums[index - 1], nums);
    }


    int findTargetSumWays(vector<int>& nums, int target) {

        memset(t, -1, sizeof(t));

        return findTargetSumWaysSupport(nums.size(), target, nums);
    }
};


// 518. Coin Change II
// Top-down Approach
class Solution {
public:

    int t[500][5001];

    int changeSupport(int index, vector<int> &coins, int T) {

        // If you reach T = 0, it means there is one way to select amount = 0 (by selecting nothing)
        if (T == 0)
            return 1;

        // Out of bound.
        if (index <= 0)
            return 0;

        if (t[index][T] != -1) return t[index][T];

        int count = 0;

        if (T - coins[index - 1] >= 0) {
            count = changeSupport(index, coins, T - coins[index - 1]) + changeSupport(index - 1, coins, T);
        }
        else {
            count = changeSupport(index - 1, coins, T);
        }

        return t[index][T] = count;
    }


    int change(int amount, vector<int>& coins) {

        memset(t, -1, sizeof(t));

        return changeSupport(coins.size(), coins, amount);
    }
};


// Bottom-Up Approach
class Solution {
public:

    int change(int amount, vector<int>& coins) {

        int n = coins.size();

        vector<vector<int>> dp(n + 1, vector<int> (amount + 1, 0));

        // 1) base case
        for (int i = 1; i <= n; i++) {
            dp[i][0] = 1;           // T == 0, index <= 0 so we started with i = 1, instead of 0.
        }

        // 2) base case: index <= 0 => index = 0...
        // we covered this case during initialization, making entire dp table fill up with zero.

        for (int i = 1; i <= n; i++) {
            for (int T = 1; T <= amount; T++) {
                if (T - coins[i - 1] >= 0) {
                    dp[i][T] = dp[i][T - coins[i - 1]] +  dp[i - 1][T];
                }
                else {
                    dp[i][T] = dp[i - 1][T];
                }
            }
        }

        return dp[n][amount];
    }
};


// Bottom-up Space optimization
class Solution {
public:

    int change(int amount, vector<int>& coins) {

        int n = coins.size();

        vector<vector<int>> dp(n + 1, vector<int> (amount + 1, 0));

        // dp table converted into single array. Currently, prev => 0th row... cur is pointing to (prev+1) row.
        vector<int> prev(amount + 1, 0), cur(amount + 1, 0);

        // 1) base case
        prev[0] = 1;            //  dp[i][0] = 1 => dp[0][0] = 1 because prev currently pointing to 0th row only.

        // 2) base case: index <= 0 => index = 0...
        // we covered this case during initialization. prev = {1, 0, 0, 0...}

        for (int i = 1; i <= n; i++) {
            cur[0] = 1; // base case: dp[i][0] = 1 => cur[0] = 1.
            for (int T = 1; T <= amount; T++) {
                if (T - coins[i - 1] >= 0) {
                    cur[T] = cur[T - coins[i - 1]] +  prev[T];
                }
                else {
                    cur[T] = prev[T];
                }
            }
            swap(prev, cur);
        }

        return prev[amount];
    }
};

// 14_GFG_Rod Cutting
// Top-Down Approach
class Solution {
public:

    int t[1001][1001];

    int MAX = 1e6;

    int cutRodHelper(int index, int price[], int T) {

        // No Rod left, maximum value possible is 0.
        if (T == 0)
            return 0;

        // Out of Bound, index <= 0, it menas we have some T > 0 and doesn't have anything to pick up,
        // and we maximize the value so returned smallest value.
        if (index <= 0)
            return -MAX;

        if (t[index][T] != -1) return t[index][T];

        int maxValue = 0;

        // index=weight, so we check weather we can take (index) length rod or not. (same as pick up item based on weight)
        if (T - index >= 0) {
            maxValue = max(cutRodHelper(index, price, T - index) + price[index - 1], cutRodHelper(index - 1, price, T));
        }
        else {
            maxValue = cutRodHelper(index - 1, price, T);
        }

        return t[index][T] = maxValue;
    }


    int cutRod(int price[], int n) {

        memset(t, -1, sizeof(t));

        return cutRodHelper(n, price, n);
    }
};

// Bottom-up Approach
class Solution {
public:

    int MAX = 1e6;

    int cutRod(int price[], int n) {

        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        // base case - 1
        // already covered (T = 0)

        // base case - 2
        for (int j = 0; j <= n; j++)
            dp[0][j] = -MAX;

        for (int i = 1; i <= n; i++) {
            for (int T = 1; T <= n; T++) {
                if (T - i >= 0) {
                    dp[i][T] = max(dp[i][T - i] + price[i - 1], dp[i - 1][T]);
                }
                else {
                    dp[i][T] = dp[i - 1][T];
                }
            }
        }

        return dp[n][n];
    }
};


// Space Optimization
class Solution {
public:

    int MAX = 1e6;

    int cutRod(int price[], int n) {

        // prev, curr
        vector<int> prev(n + 1, -MAX), cur(n + 1, 0);


        // prev points to index = 0, right now.

        for (int i = 1; i <= n; i++) {
            cur[0] = 0;  // base case   T == 0
            for (int T = 1; T <= n; T++) {
                if (T - i >= 0) {
                    cur[T] = max(cur[T - i] + price[i - 1], prev[T]);
                }
                else {
                    cur[T] = prev[T];
                }
            }
            swap(prev, cur);
        }

        return prev[n];
    }
};



// 1143. Longest Common Subsequence

// Recursion
class Solution {
public:

    int longestCommonSubsequenceHelper(int i, int j, string s1, string s2) {

        // If one the string is empty, we don't get common subsequence so return it 0.
        if (i == 0 || j == 0)
            return 0;

        if (s1[i - 1] == s2[j - 1]) {
            return 1 + longestCommonSubsequenceHelper(i - 1, j - 1, s1, s2);
        }
        else {
            return max(longestCommonSubsequenceHelper(i - 1, j, s1, s2), longestCommonSubsequenceHelper(i, j - 1, s1, s2));
        }
    }


    int longestCommonSubsequence(string s1, string s2) {
        return longestCommonSubsequenceHelper(s1.size(), s2.size(), s1, s2);
    }
};

// Top-Down

class Solution {
public:

    int t[1001][1001];

    int longestCommonSubsequenceHelper(int i, int j, string s1, string s2) {

        // If one the string is empty, we don't get common subsequence so return it 0.
        if (i == 0 || j == 0)
            return 0;

        if (t[i][j] != -1)
            return t[i][j];

        int longest = 0;

        if (s1[i - 1] == s2[j - 1]) {
            longest = 1 + longestCommonSubsequenceHelper(i - 1, j - 1, s1, s2);
        }
        else {
            longest = max(longestCommonSubsequenceHelper(i - 1, j, s1, s2), longestCommonSubsequenceHelper(i, j - 1, s1, s2));
        }

        return t[i][j] = longest;
    }


    int longestCommonSubsequence(string s1, string s2) {
        memset(t, -1, sizeof(t));
        return longestCommonSubsequenceHelper(s1.size(), s2.size(), s1, s2);
    }
};


// Bottom-up

class Solution {
public:
    int longestCommonSubsequence(string s1, string s2) {
        int m = s1.size(), n = s2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        // base case, (i == 0, j == 0) covered during initialization dp[i][0] = 0, dp[0][j] = 0.
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                }
                else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[m][n];
    }
};


// Space Optimization
class Solution {
public:
    int longestCommonSubsequence(string s1, string s2) {
        int m = s1.size(), n = s2.size();
        vector<int> pre(n + 1, 0), cur(n + 1, 0);
        // base case, (i == 0, j == 0) pre = {0, 0, 0....} and curr = {0, 0, 0..} which covered. .
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    cur[j] = 1 + pre[j - 1];
                }
                else {
                    cur[j] = max(pre[j], cur[j - 1]);
                }
            }
            swap(pre, cur);
        }
        return pre[n];
    }
};


// 1143. Longest Common Subsequence(print LCS)


class Solution {

public:

    string printLCS(int i, int j, vector<vector<int>> dp, string s, string t) {

        // first create, longest_common_subseq length temp string.
        string str = "";
        int len = dp[i][j];
        for (int i = 1; i <= len; i++) {
            str += "$";
        }
        int index = len - 1;

        // Perform backtracking..
        while (i > 0 && j > 0) {

            if (s[i - 1] == t[j - 1]) { // both character match, add it in LCS
                str[index] = s[i - 1];
                index--;
                i--;
                j--;
            }
            else if (dp[i - 1][j] > dp[i][j - 1]) { // Otherwise pick up the maximum(where we came from)
                i--;
            }
            else {
                j--;
            }
        }

        return str;
    }

    string all_longest_common_subsequences(string s, string t) {
        int m = s1.size(), n = t.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s[i - 1] == t[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                }
                else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        int longestSubLen = dp[m][n];

        return printLCS(i, j, dp, s, t);
    }
};

// 21_GFG_Longest Common Substring
// Top-down Approach
class Solution {
public:

    int t[1001][1001];

    // keep track of longest common substring.
    int longestCommSubstr = 0;

    int longestCommonSubstrHelper(int i, int j, string s1, string s2) {

        if (i == 0 || j == 0)
            return 0;

        if (t[i][j] != -1)
            return t[i][j];

        int countOfLen = 0;

        if (s1[i - 1] == s2[j - 1]) {
            countOfLen = 1 + longestCommonSubstrHelper(i - 1, j - 1, s1, s2);   // Here only, we get the maxLen due to consecutive match.
            if (longestCommSubstr < countOfLen) {
                longestCommSubstr = countOfLen;
            }
        } else {                                        // mismatch break the lcs... so we return 0.
            longestCommonSubstrHelper(i - 1, j, s1, s2);
            longestCommonSubstrHelper(i, j - 1, s1, s2);
            countOfLen = 0;
        }

        return t[i][j] = countOfLen;
    }

    int longestCommonSubstr(string s1, string s2) {

        memset(t, -1, sizeof(t));

        longestCommonSubstrHelper(s1.size(), s2.size(), s1, s2);

        return longestCommSubstr;
    }
};



// Bottom-up Approach
class Solution {
public:

    int longestCommonSubstr(string s1, string s2) {

        int m = s1.size(), n = s2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        int maxCommonSubstr = 0;

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                    maxCommonSubstr = max(maxCommonSubstr, dp[i][j]);
                }
            }
        }

        return maxCommonSubstr;
    }
};


// 516. Longest Palindromic Subsequence
class Solution {
public:


    int longestCommonSubseq(string s1, string s2) {

        int m = s1.size(), n = s2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        // base case
        // dp[i][0] = 0, dp[0][j] = 0 (already covered).

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                }
                else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        return dp[m][n];
    }



    int longestPalindromeSubseq(string s) {

        // Base case, len(s) <= 1 for such string, longest palindrome of string is itself.
        if (s.size() <= 1)
            return s.size();

        string s2 = s;
        reverse(s2.begin(), s2.end());

        return longestCommonSubseq(s, s2);
    }
};


// 583. Delete Operation for Two Strings


class Solution {
public:


    int longestCommonSubseq(string s1, string s2) {

        int m = s1.size(), n = s2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        // base case
        // dp[i][0] = 0, dp[0][j] = 0 (already covered).

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                }
                else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        return dp[m][n];
    }


    int minDistance(string word1, string word2) {


        int longestCommonSubseqLen = longestCommonSubseq(word1, word2);

        return word1.size() - longestCommonSubseqLen + word2.size() - longestCommonSubseqLen;
    }
};


// 1312. Minimum Insertion Steps to Make a String Palindrome*

class Solution {
public:

    int longestCommSubseq(string s1, string s2) {

        int m = s1.size(), n = s2.size();

        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                }
                else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[m][n];
    }




    int minInsertions(string s) {

        // Convert S1 => S2, Cost = (len(S1) - len(LCS)) + (len(S2) - len(LCS)) (But Here, s2 == rev(s1), both are same)
        // Convert S1 => S2, Cost = (len(S1) - len(LCS))
        // How to get LCS of S1 = LPS(S1) = LCS(S1, reverse(S1))
        string s2 = s;
        reverse(s2.begin(), s2.end());
        int lcsLen = longestCommSubseq(s, s2);
        return s.size() - lcsLen;
    }
};



// 115. Distinct Subsequences (LCS+Knapsack)

// Top-down
class Solution {
public:

    int memo[1001][1001];

    int numDistinctHelper(int i, int j, string s, string t) {

        // End of target String.
        if (j == 0)
            return 1;

        // Don't able to match string "s" entirely with target string "t"
        if (i == 0)
            return 0;

        cout << i << " " << j << endl;

        if (memo[i][j] != -1) {
            return memo[i][j];
        }

        int count = 0;
        if (s[i - 1] == t[j - 1]) {
            // two choice, match and don't match
            count = numDistinctHelper(i - 1, j - 1, s, t) + numDistinctHelper(i - 1, j, s, t);
        }
        else {
            count = numDistinctHelper(i - 1, j, s, t);
        }


        return memo[i][j] = count ;
    }


    int numDistinct(string s, string t) {

        memset(memo, -1, sizeof(memo));

        return numDistinctHelper(s.size(), t.size(), s, t);
    }
};



// Bottom-up
class Solution {
public:

    int numDistinct(string s, string t) {

        int m = s.size(), n = t.size();
        vector<vector<unsigned int>> dp(m + 1, vector<unsigned int>(n + 1, 0));

        // base case
        for (int i = 0; i <= m; i++)
            dp[i][0] = 1;

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s[i - 1] == t[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j]; // (match + don't match)
                }
                else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }

        return dp[m][n];
    }
};


// 1092. Shortest Common Supersequence
class Solution {
public:
    string shortestCommonSupersequence(string s1, string s2) {


        // 1. Find LCS

        int m = s1.size(), n = s2.size();

        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                }
                else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        // print length of shortestCommonSupersequence => s1.size() + s2.size() - dp[m][n];


        // 2. Construct the shortestCommonSupersequence.

        string scs = "";

        int i = m, j = n;

        while (i > 0 && j > 0) {

            // match, add character in our answer one time (that's how we elimiate duplicate)
            if (s1[i - 1] == s2[j - 1]) {
                scs += s1[i - 1];
                i--; j--;
            }
            else if (dp[i - 1][j] > dp[i][j - 1]) {     // moving (i, j) => (i-1, j)...add s1[i] in scs.
                scs += s1[i - 1];
                i--;        // jump to (i-1, j)
            }
            else {                                      // moving (i, j) => (i, j-1)...add s1[j] in scs.
                scs += s2[j - 1];
                j--;
            }
        }

        // Add remaining characters
        while (i > 0) {
            scs += s1[i - 1];
            i--;        // jump to (i-1, j)
        }

        while (j > 0) {
            scs += s2[j - 1];
            j--;
        }


        // reverse scs....
        reverse(scs.begin(), scs.end());

        return scs;
    }
};


// 72. Edit Distance
// Top-down Approach
class Solution {
public:

    int t[501][501];

    int minDistanceHelper(int i, int j, string s1, string s2) {
        if (i == 0) return j;
        if (j == 0) return i;
        if (t[i][j] != -1) return t[i][j];
        int minCost = INT_MAX;
        if (s1[i - 1] == s2[j - 1]) {                                       // match, no cost
            minCost = minDistanceHelper(i - 1, j - 1, s1, s2);
        }
        else {
            int insertCost = 1 + minDistanceHelper(i, j - 1, s1, s2);       // sometime given insert, update and delete cost.
            int updateCost = 1 + minDistanceHelper(i - 1, j - 1, s1, s2);
            int deleteCost = 1 + minDistanceHelper(i - 1, j, s1, s2);
            minCost = min(insertCost, min(updateCost, deleteCost));
        }
        return t[i][j] = minCost;
    }


    int minDistance(string word1, string word2) {
        memset(t, -1, sizeof(t));
        return minDistanceHelper(word1.size(), word2.size(), word1, word2);
    }
};


// Bottom-Approach
class Solution {
public:

    int minDistance(string s1, string s2) {

        int m = s1.size(), n = s2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        // base case
        for (int j = 0; j <= n; j++) {
            dp[0][j] = j;
        }

        for (int i = 0; i <= m; i++) {
            dp[i][0] = i;
        }

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else {
                    // sometime each operation have diff cost...so change according to it.
                    int insertCost = 1 + dp[i][j - 1];
                    int updateCost = 1 + dp[i - 1][j - 1];
                    int deleteCost = 1 + dp[i - 1][j];
                    dp[i][j] = min(insertCost, min(updateCost, deleteCost));
                }
            }
        }

        return dp[m][n];
    }
};



// 44. Wildcard Matching*
// Top-down Approach
class Solution {
public:

    int memo[2001][2001];

    bool allStars(string pattern, int j) {
        for (int k = 0; k < j; k++) {
            if (pattern[k] != '*')
                return false;
        }
        return true;
    }

    bool isMatchSupport(int i, int j, string s, string p) {

        // both string "s" and pattern "p" is empty.
        if (i <= 0 && j <= 0)
            return true;

        // s = "", and pattern = "***"
        if (i <= 0 && j > 0) {
            return allStars(p, j);
        }

        // pattern = "", and s = "abc"
        if (j <= 0 && i > 0)
            return false;


        if (memo[i][j] != -1)
            return memo[i][j];

        bool matched = false;

        // First check wildcards
        if (p[j - 1] == '?' || s[i - 1] == p[j - 1]) {
            matched = isMatchSupport(i - 1, j - 1, s, p);
        }
        else if (p[j - 1] == '*') {
            matched = isMatchSupport(i, j - 1, s, p) || isMatchSupport(i - 1, j, s, p); // (i, j-1)(* matched with empty string) || (i-1, j) (* matched with one character and still present)
        }
        else if (s[i - 1] != p[j - 1]) {
            matched = false;
        }
        return memo[i][j] = matched;
    }


    bool isMatch(string s, string p) {

        memset(memo, -1, sizeof(memo));

        return isMatchSupport(s.size(), p.size(), s, p);
    }
};


// Bottom-up Approach

class Solution {
public:

    bool allStars(string pattern, int j) {
        for (int k = 0; k < j; k++) {
            if (pattern[k] != '*')
                return false;
        }
        return true;
    }

    bool isMatch(string s, string p) {

        int m = s.size(), n = p.size();
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));

        // 1. Base condition
        dp[0][0] = true;

        // 2. Base condition, Indicate... str = "", len(p) > 1... then all characters in p should be *...
        for (int j = 1; j <= n; j++) {
            dp[0][j] = allStars(p, j);
        }
        // 3. Base condition
        for (int i = 1; i <= m; i++)
            dp[i][0] = false;

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                bool matched = false;
                if (p[j - 1] == '?' || s[i - 1] == p[j - 1]) {
                    matched = dp[i - 1][j - 1];
                }
                else if (p[j - 1] == '*') {
                    matched = dp[i][j - 1] || dp[i - 1][j];
                }
                else if (s[i - 1] != p[j - 1]) {
                    matched = false;
                }
                dp[i][j] = matched;
            }
        }
        return dp[m][n];
    }
};



// Bottom-up Approach - Space Optimization

class Solution {
public:

    bool allStars(string pattern, int j) {
        for (int k = 0; k < j; k++) {
            if (pattern[k] != '*')
                return false;
        }
        return true;
    }

    bool isMatch(string s, string p) {

        int m = s.size(), n = p.size();
        vector<bool> prev(n + 1, false), cur(n + 1, false);

        // 1. Base condition
        prev[0] = true;            // dp[0][0] = true;

        // 2. Base condition
        for (int j = 1; j <= n; j++) {
            prev[j] = allStars(p, j);   //  dp[0][j] = allStars(p, j);
        }

        // // 3. Base condition
        // for(int i = 1; i <= m; i++)
        //     dp[i][0] = false;

        for (int i = 1; i <= m; i++) {
            cur[0] = false;         // Base condition-3
            for (int j = 1; j <= n; j++) {
                bool matched = false;
                if (p[j - 1] == '?' || s[i - 1] == p[j - 1]) {
                    matched = prev[j - 1];
                }
                else if (p[j - 1] == '*') {
                    matched = cur[j - 1] || prev[j];
                }
                else if (s[i - 1] != p[j - 1]) {
                    matched = false;
                }
                cur[j] = matched;
            }
            swap(prev, cur);
        }
        return prev[n];
    }
};

// 121. Best Time to Buy and Sell Stock
// Top-down Approach
class Solution {
public:

    // Keep track of maximum Profit.
    int maximumProfit = 0;

    int getMinBuyingPriceForDay(int day, vector<int> &prices) {

        // Base case: At 0th day... we can't sell anything so maximumProfit = 0.
        if (day == 0)
            return prices[0];

        int minBuying = getMinBuyingPriceForDay(day - 1, prices);
        if (prices[day] - minBuying > maximumProfit) {
            maximumProfit = prices[day] - minBuying;
        }

        // return minimum buying price for next day (day+1)
        return min(prices[day], minBuying);
    }

    int maxProfit(vector<int>& prices) {
        getMinBuyingPriceForDay(prices.size() - 1, prices);
        return maximumProfit;
    }
};

// Bottom-up
class Solution {
public:

    int maxProfit(vector<int>& prices) {

        // Keep track of maximum Profit.
        int maximumProfit = 0;

        int m = prices.size();

        // Base case
        int minBuying = prices[0];

        for (int day = 1; day < m; day++) {

            if (prices[day] - minBuying > maximumProfit) {
                maximumProfit = prices[day] - minBuying;
            }

            minBuying = min(prices[day], minBuying);
        }

        return maximumProfit;
    }
};





// 122. Best Time to Buy and Sell Stock II
// Top-down Approach
class Solution {
public:

    int t[100000][2];

    int maxProfitSupport(int day, int buyToAllow, vector<int>& prices) {

        // base condition
        if (day == prices.size())
            return 0;

        if (t[day][buyToAllow] != -1)
            return t[day][buyToAllow];

        int profit = 0;
        if (buyToAllow) {
            profit = max(-prices[day] + maxProfitSupport(day + 1, 0, prices),
                         0 + maxProfitSupport(day + 1, 1, prices ));
        }
        else {
            profit = max(prices[day] + maxProfitSupport(day + 1, 1, prices),
                         0 + maxProfitSupport(day + 1, 0, prices ));
        }

        return t[day][buyToAllow] = profit;
    }

    int maxProfit(vector<int>& prices) {

        memset(t, -1, sizeof(t));

        return maxProfitSupport(0, 1, prices);
    }
};

// Bottom-up Approach
class Solution {
public:

    int maxProfit(vector<int>& prices) {

        int m = prices.size();
        vector<vector<int>> dp(m + 1, vector<int>(2, 0));

        // base condition
        dp[m][0] = 0;
        dp[m][1] = 0;

        for (int day = m - 1; day >= 0; day--) {
            dp[day][1] = max(-prices[day] + dp[day + 1][0], 0 + dp[day + 1][1]);
            dp[day][0] = max(prices[day] + dp[day + 1][1], 0 + dp[day + 1][0]);
        }

        return dp[0][1];    // Starting at first day, buyToAllow=true... so we consider that only as our answer.
    }
};


// 123. Best Time to Buy and Sell Stock III


// Top-down Appraoch
class Solution {
public:


    int t[100001][2][2];

    int maxProfitSupport(int day, int buyToAllowed, int curTran, vector<int>& prices) {

        // Base case
        if (day == prices.size() || curTran >= 2)
            return 0;

        if (t[day][buyToAllowed][curTran] != -1)
            return t[day][buyToAllowed][curTran];

        int profit;
        if (buyToAllowed) {
            profit = max(-prices[day] + maxProfitSupport(day + 1, !buyToAllowed, curTran, prices), 0 + maxProfitSupport(day + 1, buyToAllowed, curTran, prices));
        }
        else {
            profit = max(prices[day] + maxProfitSupport(day + 1, !buyToAllowed, curTran + 1, prices), 0 + maxProfitSupport(day + 1, buyToAllowed, curTran, prices));
        }


        return t[day][buyToAllowed][curTran] = profit;
    }


    int maxProfit(vector<int>& prices) {
        memset(t, -1, sizeof(t));
        int curTran = 0;
        int buyToAllowed = 1;
        return maxProfitSupport(0, buyToAllowed, curTran, prices);
    }
};


// Bottom-Up Appraoch
class Solution {
public:

    int maxProfit(vector<int>& prices) {

        int m = prices.size();

        vector<vector<vector<int>>> dp(m + 1, vector<vector<int>>(2, vector<int>(3, 0)));

        // Base case (All covered during initialization)
        // dp[m][j][k] = 0;
        // dp[m][j][k] = 0;

        // dp[i][j][2] = 0;
        // dp[j][j][2] = 0;


        for (int day = m - 1; day >= 0; day--) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    int profit = 0;
                    if (j == 1) {
                        profit = max(-prices[day] + dp[day + 1][!j][k], dp[day + 1][j][k]);
                    }
                    else {
                        profit = max(prices[day] + dp[day + 1][!j][k + 1], dp[day + 1][j][k]);
                    }
                    dp[day][j][k] = profit;
                }
            }
        }

        return dp[0][1][0]; // get idea from top-down, where we start at day=0, buyToAllowed=1, curTran = 0
    }
};


// 188. Best Time to Buy and Sell Stock IV

class Solution {
public:

    int t[100001][2][100];

    int maxProfitSupport(int day, int buyToAllowed, int curTran, vector<int>& prices, int maxTran) {

        // Base case (change here)
        if (day == prices.size() || curTran >= maxTran)
            return 0;

        if (t[day][buyToAllowed][curTran] != -1)
            return t[day][buyToAllowed][curTran];

        int profit;
        if (buyToAllowed) {
            profit = max(-prices[day] + maxProfitSupport(day + 1, !buyToAllowed, curTran, prices, maxTran), 0 + maxProfitSupport(day + 1, buyToAllowed, curTran, prices, maxTran));
        }
        else {
            profit = max(prices[day] + maxProfitSupport(day + 1, !buyToAllowed, curTran + 1, prices, maxTran), 0 + maxProfitSupport(day + 1, buyToAllowed, curTran, prices, maxTran));
        }


        return t[day][buyToAllowed][curTran] = profit;
    }


    int maxProfit(int k, vector<int>& prices) {
        memset(t, -1, sizeof(t));
        int curTran = 0;
        int buyToAllowed = 1;
        return maxProfitSupport(0, buyToAllowed, curTran, prices, k);
    }
};


// 309. Best Time to Buy and Sell Stock with Cooldown
// Top-down approach

class Solution {
public:

    int t[5001][2];

    int maxProfitHelper(int day, int allowedToBuy, vector<int>& prices) {

        // base condition change... day > prices.size() as well so need to think about that as well.
        if (day >= prices.size())
            return 0;

        if (t[day][allowedToBuy] != -1)
            return t[day][allowedToBuy];

        int profit = 0;

        if (allowedToBuy) {
            profit = max(-prices[day] + maxProfitHelper(day + 1, !allowedToBuy, prices), 0 + maxProfitHelper(day + 1, allowedToBuy, prices));
        }
        else {
            // once we sell, we can't buy at day+1... due to cooldown period, so we can buy on (day+2) directly.
            profit = max(prices[day] + maxProfitHelper(day + 2, !allowedToBuy, prices), 0 + maxProfitHelper(day + 1, allowedToBuy, prices));
        }

        return t[day][allowedToBuy] = profit;
    }


    int maxProfit(vector<int>& prices) {

        memset(t, -1, sizeof(t));

        return maxProfitHelper(0, 1, prices);
    }
};

// Bottom-up Approach (Just converted top-down in bottom-up)


class Solution {
public:

    int maxProfit(vector<int>& prices) {

        int m = prices.size();

        // dp table.
        vector<vector<int>> dp(m + 2, vector<int>(2, 0));   // day=(m-1) => dp[day+2] => dp[m-1+2] => dp[m+1] considering that we have added one more row in dp table.

        // base condition.. (Already convered during initialization)
        // dp[m][j] = 0;
        // dp[m+1][j] = 0;

        for (int day = m - 1; day >= 0; day--) {
            dp[day][1] = max(-prices[day] + dp[day + 1][0], 0 + dp[day + 1][1]);
            dp[day][0] = max(prices[day] + dp[day + 2][1], 0 + dp[day + 1][0]);
        }

        return dp[0][1];
    }
};






class Solution {
public:

    int maxProfit(int k, vector<int>& prices) {

        int m = prices.size();
        int maxTran = k;

        // (change here, increase the limit)
        vector<vector<vector<int>>> dp(m + 1, vector<vector<int>>(2, vector<int>(maxTran + 1, 0)));

        // Base case (All covered during initialization)
        // dp[m][j][k] = 0;
        // dp[m][j][k] = 0;

        // dp[i][j][maxTran] = 0;
        // dp[j][j][maxTran] = 0;

        for (int day = m - 1; day >= 0; day--) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < maxTran; k++) {
                    int profit = 0;
                    if (j == 1) {
                        profit = max(-prices[day] + dp[day + 1][!j][k], dp[day + 1][j][k]);
                    }
                    else {
                        profit = max(prices[day] + dp[day + 1][!j][k + 1], dp[day + 1][j][k]);
                    }
                    dp[day][j][k] = profit;
                }
            }
        }

        return dp[0][1][0]; // get idea from top-down, where we start at day=0, buyToAllowed=1, curTran = 0
    }
};


// 714. Best Time to Buy and Sell Stock with Transaction Fee
// Top-down Approach
class Solution {
public:

    int t[50001][2];

    int maxProfitSupport(int day, int allowedToBuy, vector<int> &prices, int fee) {

        if (day == prices.size())
            return 0;

        if (t[day][allowedToBuy] != -1) {
            return t[day][allowedToBuy];
        }

        int profit = 0;
        if (allowedToBuy) {
            profit = max(-prices[day] + maxProfitSupport(day + 1, !allowedToBuy, prices, fee), 0 + maxProfitSupport(day + 1, allowedToBuy, prices, fee));
        }
        else {
            // fee applied during selling of stocks (we can put during buying as well... )
            profit = max(prices[day] - fee + maxProfitSupport(day + 1, !allowedToBuy, prices, fee), 0 + maxProfitSupport(day + 1, allowedToBuy, prices, fee));
        }

        return t[day][allowedToBuy] = profit;
    }



    int maxProfit(vector<int>& prices, int fee) {
        memset(t, -1, sizeof(t));
        return maxProfitSupport(0, 1, prices, fee);
    }
};


// Bottom-up Apporach
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {

        int m = prices.size();

        // dp table
        vector<vector<int>> dp(m + 1, vector<int> (2, 0));

        // base case (added during dp table initialization)
        // dp[0][j] = 0;

        for (int day = m - 1; day >= 0; day--) {
            dp[day][1] = max(-prices[day] + dp[day + 1][0], 0 + dp[day + 1][1]);
            dp[day][0] = max(prices[day] - fee + dp[day + 1][1], 0 + dp[day + 1][0]);
        }

        return dp[0][1];
    }
};


// Pattern=LIS

// 300. Longest Increasing Subsequence
// Recursive solution
class Solution {
public:

    int LIS(int i, int prev_index, vector<int> &nums) {

        if (i >= nums.size())
            return 0;

        int lengthOfLIS;

        // you can take nums[i] in LIS, so you have two choice to take it or don't take it.
        if (prev_index == -1 || nums[prev_index] < nums[i]) {

            // // take it
            // 1 + LIS(i+1, i, nums);

            // // don't take it
            // LIS(i+1, prev_index, nums);

            lengthOfLIS = max(1 + LIS(i + 1, i, nums), LIS(i + 1, prev_index, nums));
        }
        else {
            lengthOfLIS = LIS(i + 1, prev_index, nums);
        }

        return lengthOfLIS;
    }


    int lengthOfLIS(vector<int>& nums) {

        return LIS(0, -1, nums);
    }
};


// Top-down
// 1 <= nums.length <= 2500
class Solution {
public:

    int t[2502][2502];

    int OFFSET = 1;

    int LIS(int i, int prev_index, vector<int> &nums) {

        if (i >= nums.size())
            return 0;

        if (t[i][prev_index + OFFSET] != -1)
            return t[i][prev_index + OFFSET];

        int lengthOfLIS;

        // you can take nums[i] in LIS, so you have two choice to take it or don't take it.
        if (prev_index == -1 || nums[prev_index] < nums[i]) {

            // // take it
            // 1 + LIS(i+1, i, nums);

            // // don't take it
            // LIS(i+1, prev_index, nums);

            lengthOfLIS = max(1 + LIS(i + 1, i, nums), LIS(i + 1, prev_index, nums));
        }
        else {
            lengthOfLIS = LIS(i + 1, prev_index, nums);
        }

        return t[i][prev_index + OFFSET] = lengthOfLIS;
    }


    int lengthOfLIS(vector<int>& nums) {
        memset(t, -1, sizeof(t));
        return LIS(0, -1, nums);
    }
};


// Bottom-up
// 1 <= nums.length <= 2500
class Solution {
public:

    int OFFSET = 1;

    int lengthOfLIS(vector<int>& nums) {
        int m = nums.size();
        vector<vector<int>> dp(m + 1, vector<int>(m + 1, 0));

        // base case (covered during initialization)
        // dp[m][j] = 0;

        for (int i = m - 1; i >= 0; i--) {

            for (int prev_index = i - 1; prev_index >= -1; prev_index--) {

                int lengthOfLIS;

                // you can take nums[i] in LIS, so you have two choice to take it or don't take it.
                if (prev_index == -1 || nums[prev_index] < nums[i]) {

                    // // take it
                    // 1 + LIS(i+1, i, nums);

                    // // don't take it
                    // LIS(i+1, prev_index, nums);

                    lengthOfLIS = max(1 + dp[i + 1][i + OFFSET], dp[i + 1][prev_index + OFFSET]);
                }
                else {
                    lengthOfLIS = dp[i + 1][prev_index + OFFSET];
                }

                dp[i][prev_index + OFFSET] = lengthOfLIS;

            }
        }

        return dp[0][-1 + OFFSET];
    }
};

// Bottom-up Space Optimization
class Solution {
public:

    int OFFSET = 1;

    int lengthOfLIS(vector<int>& nums) {
        int m = nums.size();

        vector<int> prev(m + 1, 0), cur(m + 1, 0);
        // base case dp[m][j] = 0, covered.

        for (int i = m - 1; i >= 0; i--) {

            for (int prev_index = i - 1; prev_index >= -1; prev_index--) {

                int lengthOfLIS;

                // you can take nums[i] in LIS, so you have two choice to take it or don't take it.
                if (prev_index == -1 || nums[prev_index] < nums[i]) {

                    // // take it
                    // 1 + LIS(i+1, i, nums);

                    // // don't take it
                    // LIS(i+1, prev_index, nums);

                    lengthOfLIS = max(1 + prev[i + OFFSET], prev[prev_index + OFFSET]);
                }
                else {
                    lengthOfLIS = prev[prev_index + OFFSET];
                }

                cur[prev_index + OFFSET] = lengthOfLIS;
            }

            swap(prev, cur);
        }

        return prev[-1 + OFFSET];
    }
};


// Bottom-up Withou Using DP
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int m = nums.size();
        vector<int> lis(m, 1);
        int maxLis = 1; // keep track of maxLis Length
        for (int i = 1; i < m; i++) {
            for (int j = i - 1; j >= 0; j--) {
                if (nums[j] < nums[i] && (1 + lis[j]) > lis[i]) {
                    lis[i] = 1 + lis[j];
                }
            }
            maxLis = max(maxLis, lis[i]);   // update after computing lis[i], we are considering ith element as end of lis so taking its length.
        }
        return maxLis;
    }
};

// Bottom-up Without Using DP (Printing LIS)
class Solution {
public:
    vector<int> longestIncreasingSubsequence(int m, vector<int>& nums) {
        vector<int> lis(m, 1), prev(m, 0);
        int maxLis = 1; // keep track of maxLis Length
        for (int i = 0; i < m; i++) {
            prev[i] = i;    // setting prev element as itself.
            for (int j = 0; j < i; j++) {       // for lexo order we need to check from (0 , j) else (j --> i) is also fine.
                if (nums[j] < nums[i] && (1 + lis[j]) > lis[i]) {
                    lis[i] = 1 + lis[j];
                    prev[i] = j;        // indicate... ith element previous element is at jth index.
                }
            }
            maxLis = max(maxLis, lis[i]);   // update after computing lis[i], we are considering ith element as end of lis so taking its length.
        }

        // find the index, which have maxLis so we can start from that.
        int index = 0;
        while (lis[index] != maxLis) {
            index++;
        }

        vector<int> lisOrder;

        // Until we don't reach to last element keep doing that..
        while (prev[index] != index) {
            lisOrder.push_back(nums[index]);
            index = prev[index];
        }

        // Add last prev[index] == index... element (because that is last number which is also part of LIS)
        lisOrder.push_back(nums[index]);

        reverse(lisOrder.begin(), lisOrder.end());

        return lisOrder;
    }
};

// LIS using the Binary Search, O(NlogN)
class Solution {


    // Return index of element which is equal to "target" or just greater than "target".
    int lower_bound(vector<int>& arr, int num) {

        int low = 0, high = arr.size() - 1;

        while (low <= high) {

            int mid = (low + high) >> 1;

            if (arr[mid] == num) {
                return mid;
            } else if (num < arr[mid]) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        return low;
    }

public:
    int lengthOfLIS(vector<int>& nums) {

        int m = nums.size();

        // Keep track of increasing order.
        vector<int> incOrder;

        incOrder.push_back(nums[0]); // base case, add first element... as we know atleast LIS=1 is possible with any single number

        for (int i = 1; i < m; i++) {

            // if nums[i] <= last_element of incOrder.. it means it can swap one of greater number than it.
            if (nums[i] <= incOrder.back()) {
                int replaceAt = lower_bound(incOrder, nums[i]);
                incOrder[replaceAt] = nums[i];
            } else {        // nums[i] > last_elememt.... then nums[i] extend the lis by ending at nums[i]
                incOrder.push_back(nums[i]);
            }
        }
        return incOrder.size(); // size of incOrder will be length of LIS. Note: lncOrder is not LIS order it is just increasing order.
    }
};


// 1_GFG_LIS_Print Longest Increasing Subsequence

// Bottom-up Without Using DP
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int m = nums.size();
        vector<int> lis(m, 1);
        int maxLis = 1; // keep track of maxLis Length
        for (int i = 1; i < m; i++) {
            for (int j = i - 1; j >= 0; j--) {
                if (nums[j] < nums[i] && (1 + lis[j]) > lis[i]) {
                    lis[i] = 1 + lis[j];
                }
            }
            maxLis = max(maxLis, lis[i]);   // update after computing lis[i], we are considering ith element as end of lis so taking its length.
        }
        return maxLis;
    }
};

// Bottom-up Without Using DP (Printing LIS)
class Solution {
public:
    vector<int> longestIncreasingSubsequence(int m, vector<int>& nums) {
        vector<int> lis(m, 1), prev(m, 0);
        int maxLis = 1; // keep track of maxLis Length
        for (int i = 0; i < m; i++) {
            prev[i] = i;    // setting prev element as itself.
            for (int j = 0; j < i; j++) {       // for lexo order we need to check from (0 , j) else (j --> i) is also fine.
                if (nums[j] < nums[i] && (1 + lis[j]) > lis[i]) {
                    lis[i] = 1 + lis[j];
                    prev[i] = j;        // indicate... ith element previous element is at jth index.
                }
            }
            maxLis = max(maxLis, lis[i]);   // update after computing lis[i], we are considering ith element as end of lis so taking its length.
        }

        // find the index, which have maxLis so we can start from that.
        int index = 0;
        while (lis[index] != maxLis) {
            index++;
        }

        vector<int> lisOrder;

        // Until we don't reach to last element keep doing that..
        while (prev[index] != index) {
            lisOrder.push_back(nums[index]);
            index = prev[index];
        }

        // Add last prev[index] == index... element (because that is last number which is also part of LIS)
        lisOrder.push_back(nums[index]);

        reverse(lisOrder.begin(), lisOrder.end());

        return lisOrder;
    }
};

// 368. Largest Divisible Subset

/* Intuition:

Given that, largest divisible subset which is simliar to LIS.

Because, LIS = nums[j] < nums[i] and follow transitive property. Here,

         LDS = nums[i] % nums[j] == 0 && follow transitive property.

Both we need largest subsets. Directly using the Bottom-up approach(quite easy).


*/

class Solution {
public:

    vector<int> largestDivisibleSubset(vector<int>& nums) {

        int N = nums.size();

        // DP Table
        // Each element divisible by itself, make 1 length subset
        // previous of each element can be -1.
        vector<int> dp(N, 1), pre(N, -1);

        // Sort array, so we can form the transitive relation n1 < n2 < n3
        // n3 % n2 == 0 && n2 % n1 == 0 => n3 % n1 == 0.
        sort(nums.begin(), nums.end());

        // Atleast each element is divisible by itself
        int maxSubsetLIS = 1;

        for (int i = 1; i < N; i++) {

            // keep track of previous element for forming the path.
            int prev = -1;

            for (int j = i - 1; j >= 0; j--) {
                if (nums[i] % nums[j] == 0 && (dp[i] < dp[j] + 1)) {
                    dp[i] = 1 + dp[j];
                    prev = j;
                }
            }

            // keep track of maximum LIS (which we will use to get first element)
            maxSubsetLIS = max(maxSubsetLIS, dp[i]);

            pre[i] = prev;
        }

        // Find the subset using DFS Traversal in reverse manner
        vector<int> largestSubset;
        int index = 0;
        for (int i = 0; i < N; i++) {
            if (dp[i] == maxSubsetLIS) {
                index = i;
                break;
            }
        }

        while (index != -1) {
            largestSubset.push_back(nums[index]);
            index = pre[index];
        }

        // (doesn't require)
        reverse(largestSubset.begin(), largestSubset.end());

        return largestSubset;
    }
};


// 1048. Longest String Chain
// Direct Applying LIS Time: (N^2*L)
/* Intution:
    Bottom-up is quite easy, applied directly that one. Just check the isPredecessor() logic.
    Apart from that it is same as LIS. We have sorted the given words in terms of length, because
    we want predecessor(less length) words are visited first.
    Time: O(N^2) * O(16)(for comparsion of two string)
*/
class Solution {
public:

    static bool compartor(string a, string b) {
        return a.size() < b.size():
        }

        // Check if string "b" can be predecssor of string "a".
        // Logic is that: If both string length is differ by 1...
        // Will compare each character one by one, allow one mismatch, if second mismatch encounter return false.
        bool isPredecessor(string a, string b) {

        // check size first, must be differ by "1".
        if (a.size() - b.size() != 1) return false;

        // check relative position.
        int i = 0, j = 0;

        bool allowoneMismatch = true;

        while (i < a.size()) {

            if (a[i] == b[j]) {
                i++; j++;
            }
            else if (allowoneMismatch) {
                i++;
                allowoneMismatch = false;
            }
            else {
                return false;
            }
        }

        return true;
    }

    int longestStrChain(vector<string>& words) {

        int N = words.size();

        vector<int> lis(N, 1);

        sort(words.begin(), words.end(), compartor);

        int maxChain = 1;

        for (int i = 1; i < N; i++) {

            for (int j = i - 1; j >= 0; j--) {

                if (isPredecessor(words[i], words[j]) && (1 + lis[j] > lis[i])) {
                    lis[i] = 1 + lis[j];
                }

                maxChain = max(maxChain, lis[i]);
            }
        }

        return maxChain;
    }
};


// Applying LIS in different way, so we can reduce that mathching alogrithm.
/* Intution:
   Idea is that, (L-1) length words will be visited first, compare to L length words.
   So when we visit the L length words, we can make it (L-1) by drooping one of its characer,
   and then we can find in alreday visited (L-1) words, to find it predecessory, If we get it
   then we extend that chain by updating LIS_map.
*/
class Solution {
public:

    static bool compartor(string a, string b) {
        return a.size() < b.size();
    }

    int longestStrChain(vector<string>& words) {

        int N = words.size();

        unordered_map<string, int> dp;

        sort(words.begin(), words.end(), compartor);

        int maxChain = 1;

        for (string w : words) {

            // Each word can create atleast 1 size of chain. (base case)
            dp[w] = 1;

            for (int i = 0; i < w.length(); i++) {

                // break the word, by removing "ith" character, so we can check in map
                // if such predecessor is already visited or not, if yes, then we can extend it more.
                string pre = w.substr(0, i) + w.substr(i + 1);

                // found predecessor, extend it.
                if (dp.count(pre)) {
                    dp[w] = max(dp[w], dp[pre] + 1);
                }

            }

            maxChain = max(maxChain, dp[w]);
        }

        return maxChain;
    }
};

// 673. Number of Longest Increasing Subsequence

/* Intution:

This is LIS Pattern that we know, but in this question ask is, return number of LIS.

So we just not need to track maxLIS but its count as well.

Simple idea is that,

    1 3 5 4 7
    LIS ending at 3 => 1 3
    LIS ending at 5 => 1 3 5
    LIS ending at 4 => 1 3 4
    LIS ending at 7 => 1 3 5 7 | 1 3 4 7

    If we notice, LIS ending at 7.... is considering all the LIS of length 3.

    LIS => 3 + 1 => 4
    LIS_Count => 1 + 1 => 2

    So there is slight change standard LIS,

        The way we are calculating LIS will remain same, only change is there...

        1 + lis[j] == lis[i] => indicate that... lis[i] is already updated with this length,
        but there are subsequence which are ending at jth also can have same length lis[i].

        So we need to consider its count.

        For example:

            LIS ending at 7 = 1 3 4 7

            But it can also extend the "LIS ending at 5 => 1 3 5"

            So we only update the count of maxLIS.

    So it is obvious that, we need 2D array dp[N][2]... to keep track of LIS and LISCount.


    // Got bigger length LIS
    dp[i][0] = 1 + dp[j][0]
    dp[i][1] = dp[j][1] (can extend all subseq which are ending at dp[j])

    // Got same length LIS
    dp[i][1] += dp[j][1] (only update count)

*/
class Solution {
public:

    int findNumberOfLIS(vector<int>& nums) {

        int N = nums.size();

        // dp table store, dp[0][0] => maxLIS, dp[0][1] => maxLISCount
        // First Index[0], it store the length of longest LIS
        // Second Index[1], it store the number of longest LIS
        vector<vector<int>> dp(N, vector<int>(2, 1));

        int maxLIS = 1;

        for (int i = 1; i < N; i++) {

            for (int j = i - 1; j >= 0; j--) {

                if (nums[j] < nums[i] && (1 + dp[j][0] >= dp[i][0])) {

                    // Found Bigger LIS
                    if (1 + dp[j][0] > dp[i][0]) {
                        dp[i][0] = 1 + dp[j][0];    // Update LIS Length
                        dp[i][1] = dp[j][1];        // Same number of LIS, ended at jth index we can extend it
                    }

                    // Got other LIS whose length is also same as lis[i]
                    // So we can increase the count of LIS, which are ending at jth index
                    // and can be extended of same length.
                    else {
                        dp[i][1] += dp[j][1];
                    }
                }
            }

            maxLIS = max(maxLIS, dp[i][0]);
        }

        // Count all LIS which have largest LIS
        int count = 0;
        for (int i = 0; i < N; i++) {
            // Consider all chain, which have maxLIS.
            if (dp[i][0] == maxLIS) {
                count += dp[i][1];
            }
        }
        return count;
    }
};

// 2_GFG_Longest_Bitonic_subsequence


/* Intution:

    We need subseq which is increasing and decreasing from center point. And center point can be any of nums[i].

    For increasing subsequence we can use LIS Algorithm.

    For decreasing subsequence as well, we can use LIS(LDS) algorithm, but twist is that. We have to find LDS from behind.

    Because,

    First_part_increassing + nums[i] + Second_Part_Decreasing

    LIS: 1 3 5 7
    LDS: 7 2 1

    Also given that, both part should be present to consider it as Bitonic. So we don't consider nums[i] length
    when we compute nums[i]...that's why I initialized with "0"... and Later during computation we will add that.

    Check the code!!

*/


class Solution {
public:
    int LongestBitonicSequence(int N, vector<int> &nums) {

        // Initialize with "0", not considering length of number itself.
        vector<int> lis(N, 0), lds(N, 0);

        // Find LIS
        for (int i = 1; i < N; i++) {
            for (int j = i - 1; j >= 0; j--) {
                if ((nums[j] < nums[i]) && (1 + lis[j] > lis[i])) {
                    lis[i] = 1 + lis[j];
                }
            }
        }

        // Find LDS
        for (int i = N - 2; i >= 0; i--) {
            for (int j = i + 1; j < N; j++) {
                if ((nums[j] < nums[i]) && (1 + lds[j] > lds[i])) {
                    lds[i] = 1 + lds[j];
                }
            }
        }

        // get MaxBitonicSub Length
        int maxBitonicSub = 0;
        for (int i = 0; i < N; i++) {
            if (lis[i] > 0 && lds[i] > 0) {
                maxBitonicSub = max(maxBitonicSub, lis[i] + lds[i] + 1);    // +1 (nums[i], should be present atleast one time)
            }
        }

        return maxBitonicSub;
    }
};




// DP Series: MCM PATTERN

// 1_dp_gfg_Matrix Chain Multiplication

// Top-down
int t[101][101];

int mcm(int arr[], int i, int j) {

    // base condition
    if (i == j || i > j)
        return 0;

    if (t[i][j] != -1)
        return t[i][j];

    int minCost = INT_MAX;
    // M1 = (i-1, i), M2 = (k, j)
    for (int k = i; k <= j - 1; k++) {
        int cost = mcm(arr, i, k) + mcm(arr, k + 1, j) + arr[i - 1] * arr[k] * arr[j];
        minCost = min(minCost, cost);
    }

    return t[i][j] = minCost;
}


int matrixMultiplication(int N, int arr[]) {
    memset(t, -1, sizeof(t));
    return mcm(arr, 1, N - 1);
}


// Bottom-up

int matrixMultiplication(int N, int arr[]) {

    vector<vector<int>> dp(N + 1, vector<int>(N + 1, 0));

    // base condition
    // dp[0][0] = dp[1][1] = dp[2][2] = 0; (covered during initalization)


    // Started with i = N-1, because if you see top-down approach.... it will
    // first solve (4, 5) and then (0, 4) because (0,4) needs (4, 5) as intermidatory result.
    for (int i = N - 1; i >= 0; i--) {
        for (int j = i + 1; j < N; j++) {   // j = i+1, because i < j
            int minCost = INT_MAX;
            for (int k = i; k <= j - 1; k++) {
                int cost = dp[i][k] + dp[k + 1][j] + arr[i - 1] * arr[k] * arr[j];
                minCost = min(minCost, cost);
            }
            dp[i][j] = minCost;
        }
    }

    return dp[1][N - 1];
}


// 1547. Minimum Cost to Cut a Stick

// Top-down Approach (With Boundary Addition)
class Solution {
public:

    int t[103][103];

    int minCost(vector<int> &cuts, int i, int j) {

        if (i > j) return 0;

        if (t[i][j] != -1)
            return t[i][j];

        int minimumCost = INT_MAX;
        for (int k = i + 1; k < j; k++) {
            int cost = minCost(cuts, i, k) + minCost(cuts, k, j) + abs(cuts[i] - cuts[j]);
            minimumCost = min(minimumCost, cost);
        }

        // (i, j) is irrelveant... keeping as "0" only, otherwise above cost calculation given out of range for int.
        return t[i][j] = minimumCost == INT_MAX ? 0 : minimumCost;
    }


    int minCost(int n, vector<int>& cuts) {
        memset(t, -1, sizeof(t));
        cuts.push_back(0);
        cuts.push_back(n);
        sort(cuts.begin(), cuts.end());
        return minCost(cuts, 0, cuts.size() - 1);
    }
};



// Bottom-up with boundary Addition
class Solution {
public:
    int minCost(int n, vector<int>& cuts) {

        // Adding,(0, N) to form the boundary.
        cuts.push_back(0);
        cuts.push_back(n);

        sort(cuts.begin(), cuts.end());

        int m = cuts.size();

        vector<vector<int>> dp(m, vector<int>(m, 0));

        for (int i = m - 1; i >= 0; i--) {
            for (int j = i + 1; j < m; j++) {
                int minimumCost = INT_MAX;
                for (int k = i + 1; k < j; k++) {
                    int cost = dp[i][k] + dp[k][j] + abs(cuts[i] - cuts[j]);
                    minimumCost = min(cost, minimumCost);
                }
                // don't confuse with this... I'm keeping dp[i][j] as "0" only, not assiging INT_MAX because (i, j) is irrevalnt
                // (i, j) subproblem can't be solution of any other range...
                // and during cost calcualtion given out of range for int.
                dp[i][j] = minimumCost == INT_MAX ? 0 : minimumCost;
            }
        }

        return dp[0][m - 1];
    }
};


int maxCoins(vector<int>& nums, int i, int j) {

    if (i > j) return 0;

    if (t[i][j] != -1)
        return t[i][j];

    int maxCost = 0;

    for (int k = i; k <= j; k++) {

        // direct cost
        int cost = nums[k];

        // range: (i, k-1), k, (k+1, j)

        // kth is last ballon we are bursting in range(i, j), indicate we have already bursted (i, k-1) & (k+1, j) ballons.
        // so adjancent element of kth element is (i-1) and (j+1) which are still left to burst. That's why we are taking those to calculate direct cost.
        if (i - 1 >= 0)
            cost *= nums[i - 1];

        if (j + 1 < nums.size())
            cost *= nums[j + 1];

        cost += maxCoins(nums, i, k - 1) + maxCoins(nums, k + 1, j);

        maxCost = max(maxCost, cost);
    }
    return t[i][j] = maxCost;
}


// 312. Burst Balloons


// Recursive (boundary approach #1, use apporach #2)
class Solution {
public:

    int maxCoins(vector<int>& nums, int i, int j) {

        if (i > j) return 0;

        int maxCost = 0;

        for (int k = i; k <= j; k++) {

            // direct cost
            int cost = nums[k];

            // range: (i, k-1), k, (k+1, j)

            // kth is last ballon we are bursting in range(i, j), indicate we have already bursted (i, k-1) & (k+1, j) ballons.
            // so adjancent element of kth element is (i-1) and (j+1) which are still left to burst. That's why we are taking those to calculate direct cost.
            if (i - 1 >= 0)
                cost *= nums[i - 1];

            if (j + 1 < nums.size())
                cost *= nums[j + 1];

            cost += maxCoins(nums, i, k - 1) + maxCoins(nums, k + 1, j);

            maxCost = max(maxCost, cost);
        }
        return maxCost;
    }

    int maxCoins(vector<int>& nums) {

        // using boundary nums {1, nums, 1}... to avoid handling edge case.
        // Because when we burst 0th & last ballon we need to handle that case...better to use boundary array.
        vector<int> numsWithBoundary = {1};
        for (int num : nums) {
            numsWithBoundary.push_back(num);
        }
        numsWithBoundary.push_back(1);

        int m = numsWithBoundary.size();

        return maxCoins(numsWithBoundary, 1, m - 2);
    }
};




// Top-down (Boundary Apporach-2)
class Solution {
public:

    int t[302][302];

    int maxCoins(vector<int>& nums, int i, int j) {

        if (i > j) return 0;

        if (t[i][j] != -1)
            return t[i][j];

        int maxCost = 0;

        for (int k = i + 1; k < j; k++) {       // (i, j) is exclusive boundary...

            // direct cost
            int cost = nums[k];

            // range: (i, k), k, (k, j)         // (i, k) & (k, j) is exclusive boundary..they are not added in that range...

            // kth is last ballon we are bursting in range(i, j), indicate we have already bursted [i+1 k-1] & [k+1, j-1] ballons.
            // so adjancent element of kth element are ith and jth, which are still left to burst. That's why we are taking those to calculate direct cost.
            if (i >= 0)
                cost *= nums[i];

            if (j < nums.size())
                cost *= nums[j];

            cost += maxCoins(nums, i, k) + maxCoins(nums, k, j);

            maxCost = max(maxCost, cost);
        }
        return t[i][j] = maxCost;
    }

    int maxCoins(vector<int>& nums) {

        memset(t, -1, sizeof(t));

        // using boundary nums {1, nums, 1}... to avoid handling edge case.
        // Because when we burst 0th & last ballon we need to handle that case...better to use boundary array.
        vector<int> numsWithBoundary = {1};
        for (int num : nums) {
            numsWithBoundary.push_back(num);
        }
        numsWithBoundary.push_back(1);

        int m = numsWithBoundary.size();

        return maxCoins(numsWithBoundary, 0, m - 1); // (i, j) is exclusive boundary
    }
};

// Bottom-up approach (Boundary Apporach-2)
class Solution {
public:

    int maxCoins(vector<int>& nums) {

        vector<int> numsWithBoundary = {1};
        for (int num : nums) {
            numsWithBoundary.push_back(num);
        }
        numsWithBoundary.push_back(1);

        int m = numsWithBoundary.size();

        // dp table
        vector<vector<int>> dp(m + 1, vector<int>(m + 1, 0));

        for (int i = m - 1; i >= 0; i--) {              // (i, j) is exclusive boundary... (k will be choose between them)...dp[i][j] = dp[i][k] + dp[k][j] + direct_cost
            for (int j = i + 1; j <= m - 1; j++) {
                int maxCost = 0;
                for (int k = i + 1; k < j; k++) {
                    int cost = numsWithBoundary[k];
                    if (i >= 0)
                        cost *= numsWithBoundary[i];
                    if (j < m)
                        cost *= numsWithBoundary[j];
                    cost += dp[i][k] + dp[k][j];
                    maxCost = max(maxCost, cost);
                }
                dp[i][j] = maxCost;
            }
        }

        return dp[0][m - 1];
    }
};



// Bottom-up (MCM Pattern Template)
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        //including the nums[-1] and nums[n]
        int n = nums.size() + 2;
        vector<vector<int>> dp(n, vector<int>(n));
        vector<int> new_nums(n, 1);
        int i = 1;
        for (auto num : nums) {
            new_nums[i++] = num;
        }
        for (int len = 2; len <= n; len++) {                // start with small range length of 2...
            //iterate from interval length from 2 to n
            for (int i = 0; i <= n - len; i++) {            // (i, i+len-1) (exclusive boundary)
                int j = i + len - 1;
                //select between left and right boundary (i, j)
                for (int k = i + 1; k < j; k++) {               // (i, j) work as boundary of range... exclusive
                    dp[i][j] = max(dp[i][j], dp[i][k] + dp[k][j] + new_nums[i] * new_nums[k] * new_nums[j]);
                }
            }
        }
        return dp[0][n - 1];
    }
};



// 132. Palindrome Partitioning II

// Specific solution - 1

class Solution {
public:
    /* Intuition:

        For s[i...j] substr....if s[i] == s[j] && s[i+1...j-1] inside string is also palindrome,

        minimum cutting is from (0, j) => minCut[i-1] + 1

        Cuts are => {0, i-1}, {i, j]}

        Again, when we have longer substr of k length(0, k) that time we will use this computed result from (0, j) to get minCuts.

        See how subproblems order got resolved...

            (4, 4) => (3, 4) => (2, 4) => (1, 4)

            (5, 5) => (4, 5)(here we check (3, 4) is palindrome or not) => (3, 5) => (2, 5) => (1, 5)
    */
    int minCut(string s) {

        int N = s.size();

        if (N <= 1)
            return 0;

        // Taking every s[i...j] as not palindrome.
        vector<vector<int>> isPalindrome(N, vector<int>(N, 0));

        // minCuts require for s[0...j], will be stored dp[j+1].
        vector<int> dp(N + 1, 0);

        // Worst case, ith length string require (i-1) cuts, with single digit as pal
        for (int i = 0; i <= N; i++)
            dp[i] = i - 1;

        for (int j = 1; j < N; j++) {
            for (int i = j; i >= 0; i--) {

                // characters are matchings..
                // 1) (i, i) || (i-1, j) with s[i-1] == s[j]
                // 2) s[i] == s[j] && s[i+1...j-1] is pal
                if ((s[i] == s[j]) && ((j - i < 2) || isPalindrome[i + 1][j - 1])) {
                    isPalindrome[i][j] = 1;
                    dp[j + 1] = min(dp[j + 1], 1 + dp[i]);
                }
            }
        }

        return dp[N];
    }
};


// Specific solution - 2: Manancher-like solutiion


class Solution {
public:

    /* Intuition:

        With this solution, we are not checking every (i, j) as palindrome, but we try to increase the length
        of palindrome from the center as much as we can.

        Similar to #1 Specific solution.

        But in this, we consider (ith) character as center of palindrome and increase the length.

        we check, (i-1, i, i+1), (i-2, i-1, i, i+1, i+2)... this way

        And again for this substr [(i-2, i-1, i, i+1, i+2)], we need intermidate result of [(i-1, i, i+1)].

        As we are using centric apporach, we need to check for both even and odd length substr at mid.

        Apart from that, Recurrent Relation remain same but twisted with new indexes,

            Recurrent Relation:

                minCut[j] = min(minCut[j], 1 + minCut[i]]

    */
    int minCut(string s) {

        int N = s.size();

        if (N <= 1)
            return 0;

        // minCuts require from (0, j) will be stored dp[j+1] location...
        vector<int> dp(N + 1, 0);

        // Worst case, ith length string require (i-1) cuts
        for (int i = 0; i <= N; i++)
            dp[i] = i - 1;


        for (int i = 1; i < N; i++) {

            // Odd length center
            for (int j = 0; (i - j) >= 0 && (i + j) < N && s[i - j] == s[i + j]; j++) {
                dp[i + j + 1] = min(dp[i + j + 1], 1 + dp[i - j]);
            }

            // Even length center.. [a,b,b,a]... we are checking form 2nd "b"... for i = 2..first comparision will be (0, 3)
            for (int j = 0; (i - j - 1) >= 0 && (i + j) < N && s[i - j - 1] == s[i + j]; j++) {
                dp[i + j + 1] = min(dp[i + j + 1], 1 + dp[i - j - 1]);
            }
        }

        return dp[N];
    }
};


// MCM_5_Boolean Evaluation

/* Intution

    It is very obvious that, we have to divide string into two parts, and find how many ways
    left and right expression can return true and do aggregation. We can divide string at each
    operator.

    If operator is reside at kth location => count(i, k-1) + count(k+1, j)

    count(i, j) return total count of ways expression can resolved to true.

    What if experssion return false ? => We ignore that...right ? NOOOOO

    See,

    OR
    T T => T
    T F => T (see this one)
    F T => T (see this one)
    F F => F

    One of experssion is returning false, still the overall experssion can be resolved to true.

    Same goes for AND & XOR. So we have to consider that as well......

    So basically, third dimension comes into picture, let's call it "isTrue"..

    count(i, j, isTrue=1) => return total number of ways experssion can be resolved to True
    count(i, j, isTrue=0) => return total number of ways experssion can be resolved to False

    So now we know how to resolve experssion as true/false, and how to count all the ways.

    Let's see Base case,

    i > j => return 0. (out of bound)
    i == j, isTrue = 1, => return (int) exp[i] == 'T'; (if last charater is = T and isTrue = 1, then only we return 1, else 0)
    i == j, isTrue = 0, => return (int) exp[j] == 'F'; (same as above, but vice versa).
*/
int getNumberOfWaysBasedOnOperator(char oper, int lt, int rt, int lf, int rf, int resolvedAsTrue) {

    /* OR
        T T => T
        T F => T
        F T => T
        F F => F
    */
    if (oper == '|') {
        if (resolvedAsTrue)
            return lt * rt + lt * rf + lf * rt;
        else
            return lf * rf;
    }


    /* AND
        T T => T
        T F => F
        F T => F
        F F => F
    */
    if (oper == '&') {
        if (resolvedAsTrue)
            return lt * rt;
        else
            return lt * rf + lf * rt + lf * rf;
    }

    /* XOR
        T T => F
        T F => T
        F T => T
        F F => F
    */

    if (oper == '^') {
        if (resolvedAsTrue)
            return lt * rf + lf * rt;
        else
            return lt * rt + lf * rf;
    }

}

int evaluateExp(string &exp, int i, int j, int isTrue) {

    // base case

    // out of bound
    if (i > j) return 0;

    if (i == j) {
        if (isTrue) return exp[i] == 'T';
        else return exp[i] == 'F';
    }

    int count = 0;

    // with increment of 2, k now only point to operator in experssion.
    // jth point to last oprand, so we stop k at last operator.
    for (int k = i + 1; k < j; k += 2) {

        int leftExpTrue = evaluateExp(exp, i, k - 1, 1);
        int rightExpTrue = evaluateExp(exp, k + 1, j, 1);
        int leftExpFalse = evaluateExp(exp, i, k - 1, 0);
        int rightExpFalse = evaluateExp(exp, k + 1, j, 0);

        count += getNumberOfWaysBasedOnOperator(exp[k], leftExpTrue, rightExpTrue, leftExpFalse, rightExpFalse, isTrue);
    }

    return count;
}

int evaluateExp(string &exp) {

    // Given isTrue = 1, because we want to resolve all exp as True.
    return evaluateExp(exp, 0, exp.size() - 1, 1);

}


// 1043. Partition Array for Maximum Sum
// #1: Brute-Force(Recursive)
/* Intuition
=> Given that choose k elements, I can choose (0, k) elements from "start" index, and remaining elements I can do same thing recursively.
Recurrent Relation:
    cut = start => cut <= start + k && cut < end
        solve(start, cut) + solve(cut+1, end)
    Base case: Whenever we have subarray whose length is < K...that time we can get the cost by choosing maximum of that range and replace with all other elements.
    => maxii * (len_of_array)
Time => O(N*K)(For each subarray division) * O(K)(To get maximum of k size subarray).
*/
class Solution {
public:

    int maxElement(vector<int> &arr, int start, int end) {
        int maxiii = 0;
        for (int i = start; i <= end; i++) {
            maxiii = max(maxiii, arr[i]);
        }
        return maxiii;
    }

    int maxSumAfterPartitioning(vector<int>& arr, int start, int end, int k) {

        // // base case: Out of bound.
        if (start > end) return 0;

        if ((abs(end - start) < k)) {
            int maxi = maxElement(arr, start, end);
            return maxi * (end - start + 1);
        }

        int maxCost = 0;

        for (int cut = start; cut < min(start + k, end); cut++) {

            maxCost = max(maxCost, maxSumAfterPartitioning(arr, start, cut, k) + maxSumAfterPartitioning(arr, cut + 1, end, k));
        }

        return maxCost;
    }

    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        return maxSumAfterPartitioning(arr, 0, arr.size() - 1, k);
    }
};


// Memo-Optimization
/* Intuition
=> Instead of choosing maximum element separately, we are doing in-place during for loop. A little change in recurrent relation as well.
Check the code!!
Recurrent Relation:
    cut = start => cut <= start + k && cut < end
        directCost = max(start...cut) * (cut+1)(times)  (because here we are considering cut=start, k = 0... that's why added +1 offset)
        directCost + solve(cut+1, end)
Time => O(N*K)
*/
class Solution {
public:

    int t[501][501];

    int maxSumAfterPartitioning(vector<int>& arr, int i, int j, int k) {

        // // base case: Out of bound.
        if (i > j) return 0;

        if (t[i][j] != -1)
            return t[i][j];

        int maxCost = 0;
        int maxii = 0;
        for (int cut = 0; cut < k && i + cut <= j; cut++) {
            maxii = max(maxii, arr[i + cut]);
            int directCost = maxii * (cut + 1);
            maxCost = max(maxCost, directCost + maxSumAfterPartitioning(arr, i + cut + 1, j, k));
        }

        return t[i][j] = maxCost;
    }

    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        memset(t, -1, sizeof(t));
        return maxSumAfterPartitioning(arr, 0, arr.size() - 1, k);
    }
};

// 2D-1D DP
// Memo-Optimization
/* Intuition
=> Now If I observe the solution well, I can see the jth index is not contributing into the equation... because we don't have left_subproblem,
only right_subproblem is present...so j = N - 1 for each of right subproblem.
We can reduce the 2D DP => 1D DP... by replacing j = N - 1.
*/
class Solution {
public:

    int t[501][501];

    int maxSumAfterPartitioning(vector<int>& arr, int i, int k) {

        // // base case: Out of bound.
        if (i > arr.size() - 1) return 0;

        if (t[i] != -1)
            return t[i];

        int maxCost = 0;
        int maxii = 0;
        for (int cut = 0; cut < k && i + cut <= arr.size() - 1; cut++) {
            maxii = max(maxii, arr[i + cut]);
            int directCost = maxii * (cut + 1);
            maxCost = max(maxCost, directCost + maxSumAfterPartitioning(arr, i + cut + 1, k));
        }

        return t[i] = maxCost;
    }

    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        memset(t, -1, sizeof(t));
        return maxSumAfterPartitioning(arr, 0, k);
    }
};



// Bottom-up: Converted Top-down into bottom-up.
class Solution {
public:

    int maxSumAfterPartitioning(vector<int>& arr, int k) {

        int N = arr.size();

        vector<vector<int>> dp(N + 1, 0);

        // base case
        // (i > j) return 0. make sure in for loop that won't happen.

        for (int i = N - 1; i >= 0; i--) {
            int maxCost = 0;
            int maxii = 0;
            for (int cut = 0; cut < k && i + cut < N; cut++) {      // at which index I can make cut... (here cut = cutIndex)
                maxii = max(maxii, arr[i + cut]);
                int directCost = maxii * (cut + 1);                 // cut+1, because I'm starting from cut = 0... i + cut = ith element.. indicate 1 element
                maxCost = max(maxCost, directCost + dp[i + cut + 1]);
            }

            dp[i] = maxCost;
        }

        return dp[0];
    }
};



// Reverse Bottom-Up.
class Solution {
public:

    int maxSumAfterPartitioning(vector<int>& arr, int start, int k) {

        // Out of Index
        if (start < 0)
            return 0;

        int maxCost = 0;
        int maxii = 0;

        for (int cut = 1; cut <= k && start - cut >= 0; cut++) {    // Here cut means (0, K)

            maxii = max(maxii, arr[start - cut]);

            int directCost = maxii * cut;

            maxCost = max(maxCost, directCost + maxSumAfterPartitioning(arr, start - cut, k));
        }

        return maxCost;
    }

    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        return maxSumAfterPartitioning(arr, arr.size(), k);
    }
};









int main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("inputf.in", "r", stdin);
    freopen("outputf.in", "w", stdout);
#endif

    cout << fib(6) << endl;

    return 0;
}

