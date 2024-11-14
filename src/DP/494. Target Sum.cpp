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

Question : 494. Target Sum
Topic : DP
Problems : https://leetcode.com/problems/target-sum/description/
==============================> Explanation <=============================================

Pattern: Subset Sum Pattern

Don't solve this problem, by assigning + and - two choice to each element
and then apply recursion with memorization.

It will work that way... Check the code... But,


This is same problem: Count S1 - S2 = D. Because when we assing sign to element that time, we are dividing them in two subset.

+ sign => S1
- sign => S2


So solve this problem using that. The same solution ##11_CN_Partitions With Given Difference


==============================> Approach and Time Complexity <============================


1) DP
Time: O(2^N) -> O(M*N)
Space: O() => O(N) (stack space)
 */


// Top-Down Approach (Don't use this solution)
class Solution {

	int OFFSET = 2e4;

public:

	int t[21][100000];

	int findTargetSumWaysSupport(int index, int target, vector<int>& nums) {

		// out of bound, index range (1, N)
		if (index == 0) {
			return target == 0;
		}

		if (t[index][target + OFFSET] != -1)
			return t[index][target + OFFSET];

		return t[index][target + OFFSET] = findTargetSumWaysSupport(index - 1, target - nums[index - 1], nums) + findTargetSumWaysSupport(index - 1, target + nums[index - 1], nums);
	}


	int findTargetSumWays(vector<int>& nums, int target) {

		memset(t, -1, sizeof(t));

		return findTargetSumWaysSupport(nums.size(), target, nums);
	}
};





