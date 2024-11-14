## Dynamic programming, Pattern = 2D DP Grind

---



#### [5_CN_Ninja_Training 2D DP](https://www.naukri.com/code360/problems/ninja-s-training_3621003)



```c
// TD (0 -> N)
/* Intuition:
    Basically I need to try all possible ways using backtesting and choose the best among them, what I mean is that
    I can select any task at day=0 and then day=1, I make sure I won't select the same task, moving forward day=2.. I make sure I won't select the previous day selected task.
    So there are many combination possible, which is backtesting and will apply DP to use as memory.
    
    Recurrence Relation,
        f(day, task) => 
            nextTask: 1 => N,        // nextTask which I will take
                if(task != nextTask):
                    max(points[day][task] + f(day+1, nextTask)) // return maximum of this

*/

int t[100001][11];

int ninjaTrainingHelper(vector<vector<int>> &points, int day, int task) {

    // base case (reached at last day)
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

        // At day=0, I can pick one of task which give maximum cost. 
        maxCost = max(maxCost, ninjaTrainingHelper(points, 0, task));   
    }

    return maxCost;
}

// BU(IMP)
int ninjaTraining(int n, vector<vector<int>> &points) {

    int M = points.size(), N = points[0].size();

    // dp table. [day][task]
    vector<vector<int>> dp(M + 1, vector<int>(N + 1, 0));

    // base case. (for day = M - 1)
    for (int t = 0; t < N; t++) {
        dp[M - 1][t] = points[M - 1][t];
    }

    for (int d = M - 2; d >= 0; d--) {
        for (int task = 0; task < N; task++) {
            int maxCost = 0;
            // Why this loop ? (Please understand)
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

```



[62. Unique Paths](https://leetcode.com/problems/unique-paths/)



```c
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
```



[63. Unique Paths II](https://leetcode.com/problems/unique-paths-ii/)



```c
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
```

[64. Minimum Path Sum](https://leetcode.com/problems/minimum-path-sum/)



```c
// Top-down approach
/* Intuition:
	To reach (0, 0) -> (M, N)(or vice versa) there are multiple ways, but we need to select path which
	return the minimum path sum.

	It is very clear that, we need to try all possible ways and choose the minimum one. We apply backtesting with memroizatino.

	Recurrent Relation:

		solve(i, j) = grid[i][j](cost) + min(solve(i-1, j) + solve(i, j-1))

*/

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
		cur[0] = grid[0][0];		// don't need of this line.

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
		return pre[n - 1];
	}
};

```



[120. Triangle](https://leetcode.com/problems/triangle/)

```c
// TD
/* Intuition:

There are many ways to reach from (0, 0) to last row of triangle, Need to explore and choose the one which provide minimum cost.
Backtracking with memorization.

Recurrent Relation:

	solve(i, j) = cost[i, j] + min(solve(i+1, j), solve(i+1, j+1))


*/
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

		// Keep track of elements in current row. Each time it's reducing by 1. 
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
					cur[j] += min(pre[j], pre[j + 1]);		// choose the cost from previous calcualted state (i+1)th
				}
			}

			k--; // reduce the length of triangle.
			swap(pre, cur);
		}

		return pre[0];
	}
};
```



#### [6_CN_Maximum Path Sum in the matrix](https://www.naukri.com/code360/problems/maximum-path-sum-in-the-matrix_797998)

```c
// TD (Going from (M-1, N-1) => To (0, 0))
/* Intuition:

Parent problem: 62. Unique Paths

	Problem is a slight variation of this pattern. Here we can start from any of (0, j) location and end
	at any of (m-1, j) location. (Or Vice Versa)

	So we will do exactly that, start at each location of M-1th row and find the maximum cost by ending at 0th row.

	Base case, would be when we visit the (0, j) we return that cell as cost.

	We can visit three directions

*/


int dy[3] = {0, 1, -1};

int getMaxPathSumHelper(vector<vector<int>> &matrix, int i, int j, vector<vector<int>> &t) {

	// Reached, at 0th row (final row)
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

		swap(pre, cur);		// at the end, last m-1 row wil be stored in "pre"
	}


	// After all steps completed, we can see at last index(target location) which index have maximum cost,
	// will return that.
	int maxCost = INT_MIN;
	for (int j = 0; j < n; j++) {
		maxCost = max(maxCost, pre[j]);
	}

	return maxCost;
}
```
