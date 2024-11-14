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

Question : 213. House Robber II
Topic : DP
Problems : https://leetcode.com/problems/house-robber-ii/description/
==============================> Explanation <=============================================

Parent Problem: 198. House Robber

Given that, we have to check each possbilities of robbing house with constraint(not to rob two adjancent house).
So at each index, we have two options,
	1) to rob ith house, and jump to (i+2)th house
	2) to not rob ith house and jump to next house.
And we choose the best, decision such that it maximize the cost.

With special constraint that, first and last house is connected so we can either rob one of them house if required.

Two subproblem is occured, we perform same algorithm two times...

1) (0 -> N-2) (Last one not included)
2) (1 -> N-1) (First one included)

And take maximum of them.

Reason is that there are total three case for (first and last)

	Not Rob first, Not Rob last
	Not Rob First, Rob last
	Rob First, Not Rob last

Which is covered into two subproblems. 1) Don't Rob last (Rob or not rob first)
                                       2) Don't Rob first (Rob or not rob last)


==============================> Approach and Time Complexity <============================


1) DP
Time: O(2^N) => O(2N)
Space: O(N)

 */


// TD

class Solution {
public:

	int memo[10001];

	int robHelper(vector<int>&costs, int i) {

		// Base case, In case we reach at last house, then loot everything from that house.
		// Doing that we are returning maximum cost.
		if (i == costs.size() - 1)
			return costs[i];

		// Not valid case(out of bound), so we are returning minimum cost because we are finding maximum cost.
		if (i >= costs.size())
			return 0;

		if (memo[i] != -1)
			return memo[i];

		// Two Choice We have, Either loot ith house(where we are at) and jump to i+2 house.
		// Or we can skip the current house and jump to next i+1 house.
		return memo[i] = max(costs[i] + robHelper(costs, i + 2), robHelper(costs, i + 1));
	}

	int rob(vector<int>& nums) {
		// Base case: In case one house, rob that one.
		// This one is required because when we skip the first or last that time we will return {} array if size of nums is 1.
		// So special attention required for this case.
		if (nums.size() == 1)
			return nums[0];

		memset(memo, -1, sizeof(memo));
		int at = 0;
		vector<int> takingFirst(nums.begin(), nums.end() - 1);
		int maxByTakingFirstHouse = robHelper(takingFirst, at);

		memset(memo, -1, sizeof(memo));
		at = 0;
		vector<int> takingLast(nums.begin() + 1, nums.end());
		int maxByTakingLastHouse = robHelper(takingLast, at);

		return max(maxByTakingFirstHouse, maxByTakingLastHouse);
	}
};



// BU - 2 Phase
class Solution {
public:
	int robLinearManner(vector<int>& nums) {
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

	int rob(vector<int>& nums) {

		if (nums.size() == 1)
			return nums[0];

		vector<int> takingFirst(nums.begin(), nums.end() - 1);
		vector<int> takingLast(nums.begin() + 1, nums.end());

		return max(robLinearManner(takingFirst), robLinearManner(takingLast));
	}
};


// BU - 1 Phase
class Solution {
public:
	int rob(vector<int>& nums) {

		int N = nums.size();

		if (nums.size() == 1)
			return nums[0];

		vector<int> dpTakingFirst(N + 1, 0);
		dpTakingFirst[N - 2] = nums[N - 2];	// Not taking Last.

		vector<int> dpTakingLast(N + 1, 0);
		dpTakingLast[N - 1] = nums[N - 1]; // Taking Last.
		int offSet = 1;

		for (int i = N - 3; i >= 0; i--) {

			// Consider Range from (N-2 => 1), We need to add offset for each index.
			dpTakingLast[i + offSet] = max(dpTakingLast[i + 1 + offSet], dpTakingLast[i + 2 + offSet] + nums[i + offSet]);

			// Consider Range from (N-3 => 1)
			dpTakingFirst[i] = max(dpTakingFirst[i + 1], dpTakingFirst[i + 2] + nums[i]);
		}

		return max(dpTakingFirst[0], dpTakingLast[1]);
	}
};

