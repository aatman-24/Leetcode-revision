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

Question : 518. Coin Change II
Topic : DP
Problems : https://leetcode.com/problems/coin-change-ii/description/
==============================> Explanation <=============================================

Pattern: 0-1 Unbounded Knapsack

There is infinite supply of the source it means you can select any coins unlimited times.

Recurrence Relation:

	solve(i, T) => solve(i, T-coins[i]) + solve(i-1, T), solve(i-1, T)

==============================> Approach and Time Complexity <============================

1) DP
Time: O(2^N) -> O(N*T)
Space: O(N*T) => O(T) (stack space)
 */

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
			dp[i][0] = 1; 			// T == 0, index <= 0 so we started with i = 1, instead of 0.
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
		prev[0] = 1; 			//  dp[i][0] = 1 => dp[0][0] = 1 because prev currently pointing to 0th row only.

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