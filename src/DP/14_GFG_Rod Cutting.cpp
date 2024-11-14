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

Question : 14_GFG_Rod Cutting
Topic : DP
Problems : https://www.geeksforgeeks.org/problems/rod-cutting0840/1
==============================> Explanation <=============================================

Pattern: 0-1 Unbounded Knapsack
Sub-Pattern: Pattern-2: Unlimited Supply, Maximum Value

It is exact problem of 0-1 Unbounded Knapsack.

How to identify ?

Given that values[i] and Length of Rod, we have to select diff length of Rod such that we can maximize the value. We can
pick up same length rod multiple times as well.

Only things which is not given is wt[], which we can create by our own with given length.

wt[i] => ith length rod value.

Recurrence Relation:

	solve(i, T) => max(solve(i, T-i) + values[i], solve(i, T))

Base case:

	T == 0, NO ROD => value = 0
	i < 0, (out of bound) No element => value = 0 | -MAX

==============================> Approach and Time Complexity <============================


1) DP
Time: O(2^N) -> O(N^2)
Space: O(N^2) => O(N) (stack space)
 */

// 1 ≤ N ≤ 1000 => Length of Rod
// 1 ≤ Ai ≤ 105	=> price[i]


// Top-Down Approach
// considering 1th based index, for price[]. index=0 => out of bound.
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
		// considering 1th based index, for price[]. index=0 => out of bound.
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
			cur[0] = 0;  // base case	T == 0
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