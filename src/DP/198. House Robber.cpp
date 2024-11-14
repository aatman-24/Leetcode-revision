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

Question : 198. House Robber
Topic : DP
Problems : https://leetcode.com/problems/house-robber/description/
==============================> Explanation <=============================================


Parent: 4_CN_Maximum sum of non-adjacent elements

It is same problem. Given that, we have to check each possbilities of robbing house with constraint(not to rob two adjancent house).
So at each index, we have two options,
	1) to rob ith house, and jump to (i+2)th house
	2) to not rob ith house and jump to next house.
And we choose the best, decision such that it maximize the cost.

==============================> Approach and Time Complexity <============================

1) DP
Time: O(2^N) => O(N)
Space: O(N)

 */


// TD

class Solution {
public:

	int memo[10001];

	int robHelper(vector<int>&costs, int i) {

		// Base case, In case we reach at last home, then rob that house. Doing that we are maximizing cost, instead of not robbing.
		if (i == costs.size() - 1)
			return costs[i];

		// Base case, Out of bound, mark end of houses. Returning minimum cost because goal is to maximize the cost.
		if (i == costs.size())
			return 0;

		if (memo[i] != -1)
			return memo[i];

		// Two Choice We have, Either rob ith house(where we are at) and jump to i+2 house.
		// Or we can skip the current house and jump to next i+1 house.
		return memo[i] = max(costs[i] + robHelper(costs, i + 2), robHelper(costs, i + 1))
	}

	int rob(vector<int>& nums) {
		memset(memo, -1, sizeof(memo));
		int at = 0;
		return robHelper(nums, at);
	}
};

// BU
class Solution {
public:
	int rob(vector<int>& nums) {
		int N = nums.size();
		vector<int> dp(N + 1, 0);
		dp[N - 1] = nums[N - 1];
		for (int i = N - 2; i >= 0; i--) {
			// Keep track of maxCost
			int maxCost = max(dp[i + 1], dp[i + 2] + nums[i]);
			dp[i] = maxCost;
		}
		return dp[0];
	}
};


// BUS
class Solution {
public:
	int rob(vector<int>& nums) {
		int N = nums.size();
		int prev_1 = dp[N - 1]; // (i+1)th state
		int prev_2 = 0;		// (i+2)th state, assign lower value, we are finding maximum cost

		for (int i = N - 2; i >= 0; i--) {

			// Keep track of maxCost
			int maxCost = 0;

			// Two choice
			if (i + 1 < N) {
				maxCost = max(maxCost, prev_1);
			}
			if (i + 2 < N) {
				maxCost = max(maxCost, prev_2 + nums[i]);
			}

			// Swap the state with curr as prev_1.
			prev_2 = prev_1;
			prev_1 = maxCost;
		}
		return prev_1;
	}
};



// -----------------------------


// BU (0 -> N)
class Solution {
public:
	// Trying to do in reverse from Top-down, 0 -> N
	int rob(vector<int>& nums) {
		int N = nums.size();
		vector<int> dp(N + 1, 0);
		dp[0] = nums[0];
		for (int i = 1; i < N; i++) {

			// Keep track of maxCost
			int maxCost = 0;

			// Two choice
			if (i - 1 >= 0) {
				maxCost = max(maxCost, dp[i - 1]);
			}
			if (i - 2 >= 0) {
				maxCost = max(maxCost, dp[i - 2] + nums[i]);
			}

			dp[i] = maxCost;
		}
		return dp[N - 1];
	}
};