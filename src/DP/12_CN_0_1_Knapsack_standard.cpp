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

Question : 12_CN_0_1_Knapsack_Standard
Topic : DP
Problems : https://www.naukri.com/code360/problems/0-1-knapsack_920542
==============================> Explanation <=============================================

Pattern: 0-1 Knapsack

What is this pattern 0-1 Knapsack pattern ?
=> In this you have given some choices to select such that max/min value is possible through any combination.
But constraint is that, each item can be selected only once and either fully or not at all. And selecting
any item cost you some amount, so your task is to find combination to get the max/min value, by staying within that cost limit.


Problem:
Given that, items with, weight[] and values[], need to select item(weight[]) such that we don't go above W and return maxValue possible.

It is very clear, we have to try all possible combination with constraint we don't go over maxWeight, which can be done
through backtracking(take it or don't take it) and we apply memorization on it.

Recurrent Relation:

	solve(i) => max(solve(i+1, value+val[i], wt+wt[i]), solve(i+1, value, wt))

Explanation: We are adding the current ith item or don't.


Top-Down Approach: For easiness, we are treating i=0 as out of bound. So managed index of weight and values
that way by subtracting -1 whenever we select any item.



==============================> Approach and Time Complexity <============================


1) DP
Time: O(2^N) -> O(M*N)
Space: O() => O(N) (stack space)
 */



// Top-Down Apporach.
// For easiness, we are treating i=0 as out of bound.
// So managed index that way for weight[] and values[] (with -1 offset)

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