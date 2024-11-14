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

Question :  120. Triangle
Topic : DP
Problems : https://leetcode.com/problems/triangle/description/
==============================> Explanation <=============================================

Pattern: DP-2D-Grid

Parent problem: 62. Unique Paths

There are many ways to reach (0, 0) to last row of triangle, Need to explore and choose the one which provide minimum cost.
Backtracking with memorization.

Recurrent Relation:

	solve(i, j) = cost[i, j] + min(solve(i+1, j), solve(i+1, j+1))

Check the code!!

==============================> Approach and Time Complexity <============================

1) DP
Time: O(2^(M+N)) -> O(M*N)
Space: O(M*N) => O(N) (stack space)

 */





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