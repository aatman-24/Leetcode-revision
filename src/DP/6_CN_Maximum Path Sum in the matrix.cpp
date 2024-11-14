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

Question :  6_CN_Maximum Path Sum in the matrix
Topic : DP
Problems : https://www.naukri.com/code360/problems/maximum-path-sum-in-the-matrix_797998
==============================> Explanation <=============================================

Pattern: DP-2D-Grid

Parent problem: 62. Unique Paths

Problem is a slight variation of this pattern. Here we can start from any of (0, j) location and end
at any of (m-1, j) location. (Or Vice Versa)

So we will do exactly that, start at each location of M-1th row and find the maximum cost by ending at 0th row.

Base case, would be when we visit the (0, j) we return that cell as cost.

We can visit three directions given in problem, so check the code!!

Easy & Straighforward.

==============================> Approach and Time Complexity <============================

1) DP
Time: O(2^N) -> O(N^2), Given T = 3(constant)
Space: O(N) (stack space)

 */


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