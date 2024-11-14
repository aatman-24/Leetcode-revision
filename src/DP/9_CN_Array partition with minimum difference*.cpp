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

Question :  9_CN_Array partition with minimum difference*
Topic : DP
Problems : https://www.naukri.com/code360/problems/partition-a-set-into-two-subsets-such-that-the-difference-of-subset-sums-is-minimum_842494
==============================> Explanation <=============================================

Pattern: SubsetSum
Parent: 7_CN_Subset Sum Equal To K

We have to find two subsets such that, min|sum(s1) - sum(s2)| absolute difference as small as possible.

Remember we already solved such problem, 8_CN_Partition Equal Subset Sum => Where => sum(s1) - sum(s2) == 0,

You need to remember this problem.

This is also can be solved, same way we are solving other subset sum equal to K pattern...

First of all, let's make one thing clear,

	arr = {1, 3, 4, 7}

	dp[3][5] = true, what it means ?

	From first three element(1, 3, 4) we can find subset(1, 4) whose sum is equal to target = 5.

Now lets jump to question again,

	Need to find two subset => S1 & S2

	Whose sum diff should be as minimum as possible.

	Instead of finding both subset we can focus on finding one subset such that whose sum is in range
	of [0, sum(arr)/2]... Doing that we will automatically find other subset s2 from [sum(arr)/2... sum(arr)].. right ?

	But how we can find all subset sum whose range is from [0, sum(arr)/2] ?

	Remember, during Bottom-up approach, last row of dp table,

		dp[n-1][target] what it indicate,

			dp[n-1][5] => Indicate we can find subset whose target=5, from given array.
			dp[n-1][12] => Indicate we can find subset whose target=12, from given array.


		So, we use that last row to find our both subset diff....

			Total = 30, target=12(s1 sum), then s2_sum = 30-12 = 18, min{s1-s2} = 6....

		So we iterate over the last row and see if dp[n-1][j] == true, it means target=j possible with
		one subset...so we calculate second subset and find min diff from that.


Hope you get it.

1) Top-down approach: In this case, all code will be the same, we use the memo table to perform the last step.
So instead of doing that I will directly jump to bottom-up approach.

2) Bottom-up: Added

3) BUS: No need for that, it will be same, doing everything on pre.

==============================> Approach and Time Complexity <============================


1) DP
Time: O(2^N) -> O(M*N)
Space: O() => O(N) (stack space)
 */



int getArraySum(vector<int> &arr) {
	int sum = 0;
	for (int num : arr) {
		sum += num;
	}
	return sum;
}


int minSubsetSumDifference(vector<int>& arr, int n) {

	int sum = getArraySum(arr);

	int target = sum / 2;

	vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));

	// base case
	for (int i = 0; i <= n; i++)
		dp[i][0] = true; 			// target = 0

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= target; j++) {		// j = sum
			if (j - arr[i - 1] >= 0) {
				dp[i][j] = dp[i - 1][j - arr[i - 1]] || dp[i - 1][j];
			}
			else {
				dp[i][j] = dp[i - 1][j];
			}
		}
	}

	// Acutal problem start from here, where we use the last row.
	int min_diff = INT_MAX;
	for (int j = 0; j <= target; j++) {			// s1_sum = 0 => target... because arr[i] also be 0... so start from 0.. s1 can be {0, 0} as well.
		if (dp[n][j] == true) {
			int s1_sum = j;
			int s2_sum = sum - j;
			min_diff = min(min_diff, abs(s1_sum - s2_sum));
		}
	}

	return min_diff;
}


