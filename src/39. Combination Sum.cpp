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

Question : 39. Combination Sum
Topic : Array, Backtracking
Problems : https://leetcode.com/problems/combination-sum/

==============================> Explanation <=============================================

Backtracking we need to use, try out all possible combination.

NUMS = A1 A2 A3 A4, TARGET = T. Also given that we can use the same elements unlimited time, and return unique combination only.

Tp create combination...we can either pick up nums[i] or skip it. And once we picked it up.. we can also pick it up any times(consider this).

For duplicate case: If we add this set in our answer: A1 A3 A4...then we don't add A4 A3 A1 | A4 A1 A3..which is possible if we take the forward side element only.
During A1 visit I can add A3 and A4... but during A3 visit I can't add A1 (got it ?)

Apart from all elements are unique so we don't need to handle that nums[i] are duplicate case.


==============================> Approach and Time Complexity <============================

1) Backtracking
Time: O(2^N)
Space: O(N) (stack space) + O(2^N)(To store result)

Formula => processing_time_for_each_node * (breadth^depth) => O(1) * O(2^N)
Space => O(N) (maximum_depth)(stack space)

Again same, either we are adding element or not adding. Two choice... 2 recursive call.
Max depth possible is = 20 < N.....
Given that, 2 <= nums[i] <= 40 and target <= 40... so depth => 40 - 2(20(times)) = 20
 */



class Solution {
public:

	// store the answer.
	vector<vector<int>> ans;

	void helper(vector<int> &nums, int startIndex, int curSum, int target, vector<int> curSet) {

		// base condition
		if (curSum == target) {
			ans.push_back(curSet);
			return;
		}

		// base condition
		if (curSum > target)
			return;

		// iterative over the all elements from (startIndex, N)
		for (int i = startIndex; i < nums.size(); i++) {

			curSum += nums[i];
			curSet.push_back(nums[i]);

			// check here.. we can choose the same element again nums[i] (NOTE: we can't chose previous nums[i-1], nums[i-2] elements, otherwise we get duplicate set issue (1, 2, 3) => (3, 2, 1))
			helper(nums, i, curSum, target, curSet);

			// backtrack.
			curSum -= nums[i];
			curSet.pop_back();
		}
	}

	vector<vector<int>> combinationSum(vector<int>& nums, int target) {
		vector<int> curSet;
		sort(nums.begin(), nums.end());
		helper(nums, 0, 0, target, curSet);
		return ans;
	}
};