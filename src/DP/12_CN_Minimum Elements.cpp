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

Question : 13_CN_Minimum Elements*
Topic : DP
Problems : https://www.naukri.com/code360/problems/minimum-elements_3843091
==============================> Explanation <=============================================

Pattern: 0-1 Knapsack
Subpattern: #4 UnLimited Supply, Finding minimum elements

Infinite Source means, you can take same element unlimited time.
For ex: Target = 6, nums = {1, 2, 3} => One of combiniation is = {3, 3}.

Recurrent Relation:

	solve(index, target) = min(

		solve(index, target-nums[index]) + 1, 	// take the current nums[index], count + 1

		solve(index-1, target) )				// Don't take the current element. Move to next element

Base condition:

	// Last element left, T >= 0
	if(index == 0)
		return T/nums[0], if T % nums[0] == 0.. (using x times nums[0], can make to target ? )

	In short, if last element is left then we need to take that again and again to make T = zero(T % nums[i]), if not possible then we
	return sum large value(MAX).






==============================> Approach and Time Complexity <============================


1) DP
Time: O(2^N) -> O(M*N)
Space: O() => O(N) (stack space)
 */



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
			dp[0][j] = j / nums[0];
		}
		else {
			dp[0][j] = MAX;
		}
	}

	for (int i = 1; i < N; i++) {
		for (int j = 0; j <= target; j++) {
			int minimumElements = MAX;
			if (j - nums[i] >= 0) {			// TAKE IT OR DON'T TAKE IT
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