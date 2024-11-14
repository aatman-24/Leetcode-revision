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

Question : 11_CN_Partitions With Given Difference
Topic : DP
Problems : https://www.naukri.com/code360/problems/partitions-with-given-difference_3751628
==============================> Explanation <=============================================

Pattern: SubsetSum
Parent: 10_Count Subsets with Sum K

Similar to count subset with target.... We need to count how many ways we can find such s1 & s2 pair, whose diff s1-s2 = d.

Given that, diff between two subset is D, and total of it is sum(arr).

S1 + S2 = T
S1 - S2 = D... Given that S1 > S2... S1 and S2 indicate respective set sum.

S1 = (T + D) / 2

Again we converted above problem in single variable... with target = s1...

#Edge case: If (T+D) is odd number, we can't divide arr then two subsets we will return 0.

Else, We apply 10_Count Subsets with Sum K...

==============================> Approach and Time Complexity <============================


1) DP
Time: O(2^N) -> O(M*N)
Space: O() => O(N) (stack space)
 */


/* Intuition:

	Similar to count subset with target.... We need to count how many ways we can find such s1 & s2 pair, whose diff s1-s2 = d.

	Given that, diff between two subset is D, and total of it is sum(arr).

	S1 + S2 = T
	S1 - S2 = D... Given that S1 > S2... S1 and S2 indicate respective set sum.

	S1 = (T + D) / 2

	Again we converted above problem in single variable... with target = s1...

	#Edge case: If (T+D) is odd number, we can't divide arr then two subsets we will return 0.

	Else, We apply 10_Count Subsets with Sum K...

*/


#include <bits/stdc++.h>
#define mod 1000000007

int t[1001][1001];

int getArraySum(vector<int> &arr) {
	int sum = 0;
	for (int num : arr) {
		sum += num;
	}
	return sum;
}


int subsetSumToKHelper(vector<int> &arr, int index, int target) {

	// Base case, target is zero, found subset.
	if (target == 0) {
		return 1;
	}

	// Incase we are out of element and still target > 0, indicate we failed to find subset.
	if (index < 0)
		return 0;

	if (t[index][target] != -1)
		return t[index][target];

	long countSubset = 0;

	// we take arr[index] into consideration, only when arr[index] <= target.
	// We have two choice either take it or not take it(remember the subset backtracking problem).
	if (target - arr[index] >= 0) {
		countSubset = (subsetSumToKHelper(arr, index - 1, target - arr[index]) % mod) + (subsetSumToKHelper(arr, index - 1, target) % mod);
	}
	else {  // Incase we won't able to take, we move to next element.
		countSubset = subsetSumToKHelper(arr, index - 1, target);
	}

	return t[index][target] = countSubset % mod;
}


int countPartitions(int n, int d, vector<int> &arr) {

	int sum = getArraySum(arr);

	int target = (d + sum) >> 1;

	if ((d + sum) % 2 == 1) return 0;		// check descirption... (d+sum) odd we can't divide into two subsets.

	memset(t, -1, sizeof(t));

	sort(arr.begin(), arr.end(), greater<int>());   // Edge Case: arr= {0, 0}

	return subsetSumToKHelper(arr, arr.size() - 1, target);
}


