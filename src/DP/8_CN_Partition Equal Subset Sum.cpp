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

Question : 8_CN_Partition Equal Subset Sum
Topic : DP
Problems : https://www.naukri.com/code360/problems/partition-equal-subset-sum_892980
==============================> Explanation <=============================================

Pattern: SubsetSum

Parent: 7_CN_Subset Sum Equal To K

We need to find whether we can divide the given array into two subset such that both subset hold equal sum.
Indirectly indicate that, can we find the subset whose sum is arr(sum)/2. That case only possible to divide
given array into two equal subset whose sum is equal.

First we check, sum(arr) is even or odd, in case it odd we can't divide.

If it is even, then we need to find SubsetSum(target = sum(arr)/2)(#7_CN_Subset Sum Equal To K)

check the code!!

==============================> Approach and Time Complexity <============================

1) DP
Time: O(2^N) -> O(N*K)
Space: O(N*K) => O(K)
 */


// TD
/* Intuition:

	We need to find whether we can divide the given array into two subset such that both subset hold equal sum.
	Indirectly indicate that, can we find the subset whose sum is arr(sum)/2. That case only possible to divide
	given array into two equal subset whose sum is equal.

	First we check, sum(arr) is even or odd, in case it odd we can't divide.

	If it is even, then we need to find SubsetSum(target = sum(arr)/2)(#7_CN_Subset Sum Equal To K)

*/

int t[101][10001];

#include <bits/stdc++.h>

// Return total sum of array.
int getArraySum(vector<int> &arr) {
	int sum = 0;
	for (int num : arr) {
		sum += num;
	}
	return sum;
}

bool findSubsetWithSumEqualK(vector<int> &arr, int index, int target) {

	// Base case
	if (target == 0)
		return true;

	// Edge case, out of range, no more element and target > 0.
	if (index < 0)
		return false;

	if (t[index][target] != -1)
		return t[index][target];

	bool foundSubset = false;
	if (target - arr[index] >= 0) {
		foundSubset = findSubsetWithSumEqualK(arr, index - 1, target - arr[index]) || findSubsetWithSumEqualK(arr, index - 1, target);
	}
	else {
		foundSubset = findSubsetWithSumEqualK(arr, index - 1, target);
	}

	return t[index][target] = foundSubset;
}

bool canPartition(vector<int> &arr, int n) {

	int sum = getArraySum(arr);
	bool isArraySumEven = sum % 2 == 0;
	if (!isArraySumEven)
		return false;
	memset(t, -1, sizeof(t));
	return findSubsetWithSumEqualK(arr, n - 1, sum / 2);
}


// Bottom-Up
bool canPartition(vector<int> &arr, int n) {

	int sum = getArraySum(arr);
	bool isArraySumEven = sum % 2 == 0;
	if (!isArraySumEven)
		return false;

	int target = sum / 2;

	// dp table
	vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));

	// base case
	for (int i = 0; i <= n; i++) {
		dp[i][0] = true;	// dp[i][target] = true, as target = 0.
	}


	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= target; j++) {
			if (j - arr[i - 1] >= 0) {		// following 0th based index in arr.
				dp[i][j] = dp[i - 1][j - arr[i - 1]] || dp[i - 1][j];
			}
			else {
				dp[i][j] = dp[i - 1][j];
			}
		}
	}

	return dp[n][target];
}


// BUS
bool canPartition(vector<int> &arr, int n) {

	int sum = getArraySum(arr);
	bool isArraySumEven = sum % 2 == 0;
	if (!isArraySumEven)
		return false;

	int target = sum / 2;

	// dp table
	vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));
	vector<bool> pre(target + 1, false), cur(target + 1, false);

	// base case
	pre[0] = true; 		// indicate.. dp[i][0] = true....

	for (int i = 1; i <= n; i++) {
		cur[0] = true;		// indicate, dp[i][0] = true...
		for (int j = 1; j <= target; j++) {
			if (j - arr[i - 1] >= 0) {		// following 0th based index in arr.
				cur[j] = pre[j - arr[i - 1]] || pre[j];
			}
			else {
				cur[j] = pre[j];
			}
		}
		swap(pre, cur);		// at the end last result will be stored in pre.
	}

	return pre[target];
}