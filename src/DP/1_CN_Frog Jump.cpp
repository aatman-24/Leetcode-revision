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

Question : 1_CN_Frog Jump
Topic : 1D-DP
Problems : https://www.naukri.com/code360/problems/frog-jump_3621012?source=youtube&campaign=striver_dp_videos&utm_source=youtube&utm_medium=affiliate&utm_campaign=striver_dp_videos&leftPanelTabValue=PROBLEM
==============================> Explanation <=============================================

Identify the problem as DP first.

- Given that find the minimum of cost required among all possible ways, indicate we need to explore all possible ways and choose the minimum.

NOTE: I can go from 1st step => Nth step. But keeping the BU-Space Approach in mind I did in reverse manner by going from Nth to 1st step. Because In this way
we can mark the base case as starting of index(which looks good!) (We can do from 1st->Nth step as well by traversing the array in reverse...).

Recurrence Relation:
	F(i) = min(F(i-1) + abs(h[i]-h[i-1]), F(i-2) + abs(h[i]-h[i-2]))

Explanation: If we are going from Nth => 1th Stair, Then we can move to (i-1)th stair or (i-2)th stair from ith stair + energy lost due to that jump.

Energy Lost = difference between stair's height.

In the code, height[i] indicate the (i+1)th step height... so based on that we need to offset it.

Check the code!!

==============================> Approach and Time Complexity <============================

1) DP
Time: O(2^N) => O(N)
Space: O(N) => O(1)

 */


// TD Approach

/* Intuition:

Recurrence Relation:
	F(i) = min(F(i-1) + abs(h[i]-h[i-1]), F(i-2) + abs(h[i]-h[i-2]))

Explanation: If we are going from Nth => to 1st Stair, Then we can move to (i-1)th stair or (i-2)th stair from ith stair + (direct cost) energy lost due to that jump.

Energy Lost = difference between stair's height.

*/

int memo[100001];

int frogJump(vector<int> &heights, int index) {

	if (index == 1)
		return 0;		// base case, standing at 1st and staring from 1st, no energy required.

	if (memo[index] != -1)
		return memo[index];

	// Why if-else condition instead of equation use direct ?
	// Reason is that, if we do that way... f(index < 1) that time we return INT_MAX... and that is added with some cost
	// which don't fit in INT range... so we never call f(index<1) that's reason we wrote the code this way.


	int minCost = INT_MAX;

	if (index - 1 > 0) {
		minCost = min(minCost, frogJump(heights, index - 1) + abs(heights[index - 1] - heights[index - 2]));	// offset heights index by -1.
	}

	if (index - 2 > 0) {
		minCost = min(minCost, frogJump(heights, index - 2) + abs(heights[index - 1] - heights[index - 3]));
	}

	return memo[index] = minCost;
}


int frogJump(int n, vector<int> &heights) {

	memset(memo, -1, sizeof(memo));

	return frogJump(heights, n);
}

// BU Approach
int frogJump(int n, vector<int> &heights) {

	vector<int> dp(n + 1, -1);

	// BASE CASE
	dp[1] = 0;

	for (int i = 2; i <= n; i++) {

		dp[i] = INT_MAX;		// MINCOST

		if (i - 1 > 0) {
			dp[i] = min(dp[i], dp[i - 1] + abs(heights[i - 1] - heights[i - 2]));
		}

		if (i - 2 > 0) {
			dp[i] = min(dp[i], dp[i - 2] + abs(heights[i - 1] - heights[i - 3]));
		}

	}

	return dp[n];
}


// BU-SPACE
int frogJump(int n, vector<int> &heights) {

	if (n == 1)
		return 0;

	// Two state to hold the result.
	int prev_1 = 0; 			// f(i-1) state
	int prev_2 = INT_MAX;		// f(i-2) state

	for (int i = 2; i <= n; i++) {

		int curr = INT_MAX;		// MINCOST

		if (i - 1 > 0) {
			curr = min(curr, prev_1 + abs(heights[i - 1] - heights[i - 2]));
		}

		if (i - 2 > 0) {
			curr = min(curr, prev_2 + abs(heights[i - 1] - heights[i - 3]));
		}

		// SWAP THE results for next state
		prev_2 = prev_1;
		prev_1 = curr;			// at the end we are storing our result here
	}

	return prev_1;
}