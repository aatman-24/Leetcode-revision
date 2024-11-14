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

Question : 64. Minimum Path Sum
Topic : DP
Problems : https://leetcode.com/problems/minimum-path-sum/description/
==============================> Explanation <=============================================

Pattern: DP-2D-Grid

Parent Problem: 62. Unique Paths

To reach (0, 0) -> (M, N)(or vice versa) there are multiple ways, but we need to select path which
return the minimum path sum.

It is very clear that, we need to try all possible ways and choose the minimum one. We apply backtesting with memroizatino.

Recurrent Relation:

	solve(i, j) = grid[i][j](cost) + min(solve(i-1, j) + solve(i, j-1))

Then we converted this into Bottom-Up with space optimization.

Check the code!!
==============================> Approach and Time Complexity <============================

1) DP
Time: O(2^(M+N)) -> O(M*N)
Space: O(M*N) => O(M)

Depth => (M+N)
Breadth => 2 (either go up or left)

 */


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
