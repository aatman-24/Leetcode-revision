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

Question :10_Count Subsets with Sum K
Topic : DP
Problems : https://www.naukri.com/code360/problems/number-of-subsets_3952532
==============================> Explanation <=============================================

Pattern: SubsetSum
Parent: 7_CN_Subset Sum Equal To K

Instead of checking such subset is possible, here we need to count how many such subset is possible.

Instead of tracking (true/false) we keep track of count.

Other all things remain same, check the code!!

Edge case: target = 0, arr = {0}

	Two ways to reach target, either take it or don't take it.

		base case => return 2


	arr = {0, 0}, T = 0

	arr(1) => take_2nd_zero + don't_take_2nd_zero
		   => arr(0) + arr(0)
		   => 2 + 2
		   => 4

	{0}, {0}, {}, {0, 0}


Two option we have,

	1) Sort in asceding order & check arr[0] = 0 => 2, because if you take it or don't take it will reach target so two ways to reach target.

	2) Sort in desecing order,

		If you do that, you don't need to change algorithm, because all zero will be at last

		so take it or don't to take...also happen on that... which happend with-in algorithm and everything remain same.

		Ex: {1, 0, 0}

		index=2 => take it + not_take it, T=1
		index=1 => take it = not_take it, T =1
		index=0 => take it + not_take it, T =0 (which return 1)

		so all works in place, no code change required!!


Hope you get it, and remember this edge case!!

==============================> Approach and Time Complexity <============================


1) DP
Time: O(2^N) -> O(M*N)
Space: O() => O(N) (stack space)
 */


/* Intuition:

Instead of checking such subset is possible, here we need to count how many such subset is possible.

Instead of tracking (true/false) we keep track of count.

Other all things remain same, check the code!!

Edge case: target = 0, arr = {0}

	Two ways to reach target, either take it or don't take it.

		base case => return 2


	arr = {0, 0}, T = 0

	arr(1) => take_2nd_zero + don't_take_2nd_zero
		   => arr(0) + arr(0)
		   => 2 + 2
		   => 4

	{0}, {0}, {}, {0, 0}


Two option we have,

	1) Sort in asceding order & check arr[0] = 0 => 2, because if you take it or don't take it will reach target so two ways to reach target.

	2) Sort in desecing order,

		If you do that, you don't need to change algorithm, because all zero will be at last

		so take it or don't to take...also happen on that... which happend with-in algorithm and everything remain same.

		Ex: {1, 0, 0}

		index=2 => take it + not_take it, T=1
		index=1 => take it = not_take it, T =1
		index=0 => take it + not_take it, T =0 (which return 1)

		so all works in place, no code change required!!


*/


// Edge Case: Apporach-2.
#include <bits/stdc++.h>
#define mod 1000000007

int t[1001][1001];

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
	else {	// Incase we won't able to take, we move to next element.
		countSubset = subsetSumToKHelper(arr, index - 1, target);
	}

	return t[index][target] = countSubset % mod;
}



int findWays(vector<int>& arr, int k)
{
	memset(t, -1, sizeof(t));

	// Edge Case: Apporach-2.
	sort(arr.begin(), arr.end(), greater<int>());	// Sorting in desceding order:  Edge Case: arr= {1, 1, 0} (You don't need to handle it)

	return subsetSumToKHelper(arr, arr.size() - 1, k);
}




// Edge Case: #2 Approach.
int t[1001][1001];

int subsetSumToKHelper(vector<int> &arr, int index, int target) {

	// Base case, target is zero.
	// Two case:
	// 1) Last element is '0', we return 2. (Take it , or don't take it) doesn't matter.
	// 2) index < 0, out of elements, but reached target so, we return 1.
	if (target == 0 && index <= 0) {
		if (index == 0 && arr[index] == 0)
			return 2;
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
	else {	// Incase we won't able to take, we move to next element.
		countSubset = subsetSumToKHelper(arr, index - 1, target);
	}

	return t[index][target] = countSubset % mod;
}



int findWays(vector<int>& arr, int k)
{
	memset(t, -1, sizeof(t));

	sort(arr.begin(), arr.end());	// Sorting in asceding order:

	return subsetSumToKHelper(arr, arr.size() - 1, k);
}