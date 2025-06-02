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

Question : NC_14_Jump Game
Topic : Greedy, DP
Problems : https://neetcode.io/problems/jump-game

==============================> Explanation <=============================================

Can be solved using the DP with O(N) space and time, But we can also apply the greedy because
we are making the link to reach end goal, and each time if we use the maxValue then it is also fine.

But I would suggest to go with DP only... don't need to rememeber the greedy sollution


==============================> Approach and Time Complexity <============================

1) Greedy
Time: O(N)
Space: O(1)

*/

// top down approach
class Solution {
public:

	int t[1001];

	bool canJumpSupport(vector<int> &nums, int i) {
		if (i >= nums.size() - 1) return true;
		if (t[i] != -1)
			return t[i];
		int maxJump = nums[i];
		for (int jump = 1; jump <= maxJump; jump++) {
			if (canJumpSupport(nums, i + jump))
				return t[i] = true;
		}
		return t[i] = false;
	}

	bool canJump(vector<int>& nums) {
		memset(t, -1, sizeof(t));
		return canJumpSupport(nums, 0);
	}
};


// bottom up approach (just converted from above)

class Solution {
public:

	bool canJump(vector<int>& nums) {

		int N = nums.size();

		// initialization, with dp[i] = false
		vector<int> dp(N + 1, 0);

		// base condition
		dp[N - 1] = dp[N] = 1;

		for (int i = N - 2; i >= 0; i--) {

			int maxJump = nums[i];

			for (int jump = 1; jump <= maxJump; jump++) {

				if (dp[i + jump]) {
					dp[i] = true;
				}
			}
		}

		return dp[0];
	}
};


// greedy approach

class Solution {
public:

	bool canJump(vector<int>& nums)	 {

		int N = nums.size();

		// main target is to reach the end of the array.
		int goal = N - 1;

		for (int i = N - 2; i >= 0; i--) {

			// we are checking with maximum effort, nums[i] if we reach
			// the goal from current position "i"... then next goal is to reach
			// current position
			if (i + nums[i] >= goal) {
				goal = i;
			}
		}

		// it means, from the index 0 we have achieved our main goal.
		return goal == 0;
	}
};
