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

Question : 312. Burst Balloons
Topic : DP-MCM
Problems : https://leetcode.com/problems/burst-balloons/description/
==============================> Explanation <=============================================

Pattern: MCM Pattern

1) Brute Force: So we know that, when we burst ballon that ballon got eliminated... and later we can choose any of remaining ballon to burst...
In short... whatever is optimium solution...those ballon got bursted in some orders..right... so what if we try all orders(permutation) and
see which one give maximum cost. (permuation...checking O(N))

2) DP:

This question is crazy!!.... Remember the trick of this question....

Basically...we are following the MCM pattern....but there is one problem....

Question is that, for given ballons[].... we have to burst all ballons such that cost will be maximum.

if we burst kth ballon =>

	direct cost = ballons[k-1] * ballons[k] * ballons[k+1] (incase out of bound, use the 1 as cost)

so what I thought is that....

	I can burst any of the ballons from given range (i, j) and then calculate cost for (i, k-1) and (i, k+1)... make sense(following MCM pattern....)

	But problem is that....

		we burst kth ballon... new array will look like....

			before: [i, i+1...k-1, k, k+1,....j]

			after:  [i, i+1...k-1, k+1...j]		(see k ballon got bursted)

		And next time when we burst k-1 ballon that time... A[k+1] is considered in direct costing... which is different than MCM pattern.

		In MCM, what we are doing is that when we make cut(choose) kth element... (i, k-1) and (k+1, j) is independent recursion subproblem. So we will resolve that
		and choose optimum costing from both range...

		But here...That's not the case... if we burst kth ballon.... formed this subproblems (i, k-1) and (k+1, j).. and these are dependent on each other... during calculation of costing..
		So those independent calculation won't work here(wait before coming to final verdict!!!)

		Ex: arr[] = {1, 3, 4, 2}... k=3 bursting... arr[] = {1, 4, 2}...1 & 4 become neighbors of each other..so we again choose 4 for bursting... costing of "1"(left element)
		will be added.

		Ex2: arr[] = {1, 2, 3, 4, 5}....

			burst: 3...cost = 2 * 3 * 4, arr[] = {1, 2, 4, 5}
			burst: 4...cost = 2 * 4 * 5, arr[] = {1, 2, 5}
			burst: 5....cost = 2 * 5 * 1, arr[] = {1, 2}

			See.... 2 is repeating many times...which was not case in MCM...... (Hope you understand)

			Not, Go through this: https://leetcode.com/problems/burst-balloons/solutions/892552/for-those-who-are-not-able-to-understand-any-solution-with-diagram


How to solve then ? If we can't we apply the MCM pattern then how to solve this ?

Issue is that, if we burst kth ballon A[k-1] * A[k] * A[k+1] is direct cost... and both side subproblems cannot be resovled independently...right...

We will apply MCM... but instead of bursting kth ballon first in (i, j) range we will burst at last... because if we do that way....

	(i, k-1) k (k+1, j)

	then (i, k-1) && (k+1, j) is not dependent on each other.. because when we burst kth ballon.... already (i, k-1) && (k+1, j) all ballons are bursted...

	Then...question is how we will compute direct cost ?

	Easy: If I'm saying that... (i, k-1) && (k+1, j) already bursted....it means

		cost = A[i-1] * A[k] * A[j+1]

		because (i-1) and (j+1) is next neighbors of k.....

	Hope you get it!!

At high level if you think...from (0, m-1) range we will select kth element which will be burst at last...then in subproblems (i, k-1) & (k+1, j)... we again pick up kth element
to burst at last.... this chaining will continue until there is one ballon left(base case)... which will be added as direct cost(because after that subproblems become invalid...)

Boundary Related Issue:

If we divide the subproblem this way,

	k = i -> j,

		(i, k-1), k, (k+1, j)

	when k = i

		first subproblem => (i, i-1) (which is invalid, i < j)

	For recursive solution, it is handled in base case..but facing issue in bottom-up approach to manging boundary....


Instead,

If we divide the subproblem this way,

	k = i+1 -> j-1,

		(i, k), k, (k, j)

	when k = i + 1,

		first subproblem => (i, i+1)...which is valid.

	But see when I'm referring the subproblem range as (i, j).... that time ith and jth index is not considered in range...they are outsider...

	so cost caluation also will be changed from,

			A[i-1] * A[k] * A[j+1],

	To,

			A[i] * A[k] * A[j] (because i and j which are not part of range, will become neighbors after ballon got bursted)...


MCM pattern...alwasys choose this #2 appraoch when divding boundary....

==============================> Approach and Time Complexity <============================

0) Brute Force:
Time: O(N * N!)
Space: O(N)


1) DP
Time: O(N^3)
Space: O(N^2)

 */



// Please check, Boundary Apporach #2 Solution only.....


// Recursive (boundary approach #1, use apporach #2)
class Solution {
public:

	int maxCoins(vector<int>& nums, int i, int j) {

		if (i > j) return 0;

		int maxCost = 0;

		for (int k = i; k <= j; k++) {

			// direct cost
			int cost = nums[k];

			// range: (i, k-1), k, (k+1, j)

			// kth is last ballon we are bursting in range(i, j), indicate we have already bursted (i, k-1) & (k+1, j) ballons.
			// so adjancent element of kth element is (i-1) and (j+1) which are still left to burst. That's why we are taking those to calculate direct cost.
			if (i - 1 >= 0)
				cost *= nums[i - 1];

			if (j + 1 < nums.size())
				cost *= nums[j + 1];

			cost += maxCoins(nums, i, k - 1) + maxCoins(nums, k + 1, j);

			maxCost = max(maxCost, cost);
		}
		return maxCost;
	}

	int maxCoins(vector<int>& nums) {

		// using boundary nums {1, nums, 1}... to avoid handling edge case.
		// Because when we burst 0th & last ballon we need to handle that case...better to use boundary array.
		vector<int> numsWithBoundary = {1};
		for (int num : nums) {
			numsWithBoundary.push_back(num);
		}
		numsWithBoundary.push_back(1);

		int m = numsWithBoundary.size();

		return maxCoins(numsWithBoundary, 1, m - 2);
	}
};

// Top-down (boundary approach #1)

class Solution {
public:

	int t[302][302];

	int maxCoins(vector<int>& nums, int i, int j) {

		if (i > j) return 0;

		if (t[i][j] != -1)
			return t[i][j];

		int maxCost = 0;

		for (int k = i; k <= j; k++) {

			// direct cost
			int cost = nums[k];

			// range: (i, k-1), k, (k+1, j)

			// kth is last ballon we are bursting in range(i, j), indicate we have already bursted [i, k-1] & [k+1, j] ballons.
			// so adjancent element of kth element is (i-1) and (j+1) which are still left to burst. That's why we are taking those to calculate direct cost.
			if (i - 1 >= 0)
				cost *= nums[i - 1];

			if (j + 1 < nums.size())
				cost *= nums[j + 1];

			cost += maxCoins(nums, i, k - 1) + maxCoins(nums, k + 1, j);

			maxCost = max(maxCost, cost);
		}
		return t[i][j] = maxCost;
	}

	int maxCoins(vector<int>& nums) {

		memset(t, -1, sizeof(t));

		// using boundary nums {1, nums, 1}... to avoid handling edge case.
		// Because when we burst 0th & last ballon we need to handle that case...better to use boundary array.
		vector<int> numsWithBoundary = {1};
		for (int num : nums) {
			numsWithBoundary.push_back(num);
		}
		numsWithBoundary.push_back(1);

		int m = numsWithBoundary.size();

		return maxCoins(numsWithBoundary, 1, m - 2);
	}
};







// Top-down (Boundary Apporach-2)
class Solution {
public:

	int t[302][302];

	int maxCoins(vector<int>& nums, int i, int j) {

		if (i > j) return 0;

		if (t[i][j] != -1)
			return t[i][j];

		int maxCost = 0;

		for (int k = i + 1; k < j; k++) {			// (i, j) is exclusive boundary...

			// direct cost
			int cost = nums[k];

			// range: (i, k), k, (k, j)			// (i, k) & (k, j) is exclusive boundary..they are not added in that range...

			// kth is last ballon we are bursting in range(i, j), indicate we have already bursted [i+1 k-1] & [k+1, j-1] ballons.
			// so adjancent element of kth element are ith and jth, which are still left to burst. That's why we are taking those to calculate direct cost.
			if (i >= 0)
				cost *= nums[i];

			if (j < nums.size())
				cost *= nums[j];

			cost += maxCoins(nums, i, k) + maxCoins(nums, k, j);

			maxCost = max(maxCost, cost);
		}
		return t[i][j] = maxCost;
	}

	int maxCoins(vector<int>& nums) {

		memset(t, -1, sizeof(t));

		// using boundary nums {1, nums, 1}... to avoid handling edge case.
		// Because when we burst 0th & last ballon we need to handle that case...better to use boundary array.
		vector<int> numsWithBoundary = {1};
		for (int num : nums) {
			numsWithBoundary.push_back(num);
		}
		numsWithBoundary.push_back(1);

		int m = numsWithBoundary.size();

		return maxCoins(numsWithBoundary, 0, m - 1);	// (i, j) is exclusive boundary
	}
};

// Bottom-up approach (Boundary Apporach-2)
class Solution {
public:

	int maxCoins(vector<int>& nums) {

		vector<int> numsWithBoundary = {1};
		for (int num : nums) {
			numsWithBoundary.push_back(num);
		}
		numsWithBoundary.push_back(1);

		int m = numsWithBoundary.size();

		// dp table
		vector<vector<int>> dp(m + 1, vector<int>(m + 1, 0));

		for (int i = m - 1; i >= 0; i--) {				// (i, j) is exclusive boundary... (k will be choose between them)...dp[i][j] = dp[i][k] + dp[k][j] + direct_cost
			for (int j = i + 1; j <= m - 1; j++) {
				int maxCost = 0;
				for (int k = i + 1; k < j; k++) {
					int cost = numsWithBoundary[k];
					if (i >= 0)
						cost *= numsWithBoundary[i];
					if (j < m)
						cost *= numsWithBoundary[j];
					cost += dp[i][k] + dp[k][j];
					maxCost = max(maxCost, cost);
				}
				dp[i][j] = maxCost;
			}
		}

		return dp[0][m - 1];
	}
};



// Bottom-up (MCM Pattern Template)
class Solution {
public:
	int maxCoins(vector<int>& nums) {
		//including the nums[-1] and nums[n]
		int n = nums.size() + 2;
		vector<vector<int>> dp(n, vector<int>(n));
		vector<int> new_nums(n, 1);
		int i = 1;
		for (auto num : nums) {
			new_nums[i++] = num;
		}
		for (int len = 2; len <= n; len++) { 				// start with small range length of 2...
			//iterate from interval length from 2 to n
			for (int i = 0; i <= n - len; i++) {				// (i, i+len-1) (exclusive boundary)
				int j = i + len - 1;
				//select between left and right boundary (i, j)
				for (int k = i + 1; k < j; k++) { 				// (i, j) work as boundary of range... exclusive
					dp[i][j] = max(dp[i][j], dp[i][k] + dp[k][j] + new_nums[i] * new_nums[k] * new_nums[j]);
				}
			}
		}
		return dp[0][n - 1];
	}
};