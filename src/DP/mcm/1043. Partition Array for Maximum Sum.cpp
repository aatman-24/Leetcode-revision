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

Question : 1043. Partition Array for Maximum Sum
Topic : DP-MCM
Problems : https://leetcode.com/problems/partition-array-for-maximum-sum/description/
==============================> Explanation <=============================================

Pattern: MCM

Given that, you can break the array into maximum "k" length subarray, and replace those subarray with maximum of that range. Doing that give maximum sum we can get for array.

1) Brute-Force(Recursion):
=> Given that choose k elements, I can choose (0, k) elements from "start" index, and remaining elements I can do same thing recursively.
Recurrent Relation:
	cut = start => cut <= start + k && cut < end
		solve(start, cut) + solve(cut+1, end)
	Base case: Whenever we have subarray whose length is < K...that time we can get the cost by choosing maximum of that range and replace with all other elements.
	=> maxii * (len_of_array)
Time => O(N*K)(For each subarray division) * O(K)(To get maximum of k size subarray).


2) Optimiation in terms of choosing max element
=> Instead of choosing maximum element separately, we are doing in-place during for loop. A little change in recurrent relation as well.
Check the code!!
Recurrent Relation:
	cut = start => cut <= start + k && cut < end
		directCost = max(start...cut) * (cut+1)(times)	(because here we are considering cut=start, k = 0... that's why added +1 offset)
		directCost + solve(cut+1, end)
Time => O(N*K)


3) Optimization by correcting mistake from 2D DP -> 1D DP
=> Now If I observe the solution well, I can see the jth index is not contributing into the equation... because we don't have left_subproblem,
only right_subproblem is present...so j = N - 1 for each of right subproblem.
We can reduce the 2D DP => 1D DP... by replacing j = N - 1.


4) Bottom-up
=> Converted Top-down into bottom-up.

5) Reverse Bottom-up (If I started top down from the end of array)

==============================> Approach and Time Complexity <============================



1) DP
Time: O(N*K)
Space: O(N^2) => O(K)

 */


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
		directCost = max(start...cut) * (cut+1)(times)	(because here we are considering cut=start, k = 0... that's why added +1 offset)
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
			for (int cut = 0; cut < k && i + cut < N; cut++) {		// at which index I can make cut... (here cut = cutIndex)
				maxii = max(maxii, arr[i + cut]);
				int directCost = maxii * (cut + 1);					// cut+1, because I'm starting from cut = 0... i + cut = ith element.. indicate 1 element
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

		for (int cut = 1; cut <= k && start - cut >= 0; cut++) {	// Here cut means (0, K)

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
