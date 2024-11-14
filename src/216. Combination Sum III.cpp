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

Question : 216. Combination Sum III
Topic : Backtracking
Problems : https://leetcode.com/problems/combination-sum-iii/description/
==============================> Explanation <=============================================

Parent: 40. Combination Sum II

Similar to above one with some modification. Here, we have given limit how many element we can choose(k).

Rest is same.

==============================> Approach and Time Complexity <============================

1) Backtracking
Time: O(9 * (9^N^2))
Space: O(N^2) (stack space)

Each node can have maximum 9 children(to test out number is valid or not) => Breadth = 9
Depth => In the worst case... we tried out all the cell of board in terms of depth(decision) which is O(N^2) => depth = O(N^2) (because it is decision based tree(true/falsse)...suppose when we find out
our solution(each N^2 block return true, that path) that time we made the right decision for each of block...so recursion tree length go upto O(N^2)).
Each node processing time => isValid() => O(9)

Formula => processing_time_for_each_node * (breadth^depth) => O(9) * O(9^(N^2))
Space => O(N^2) (maximum_depth)(stack space)

 */





class Solution {
public:

	// Given that, [1-9] numbers can be used for single time only.
	vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9};

	// To store the result.
	vector<vector<int>> combinations;

	void helper(int startIndex, int curSum, int target, int count, int k, vector<int> curCombination) {

		// selected required numbers and sum of them is equal to target, choose the curCombination. (Base condition)
		if (count == k && curSum == target) {
			combinations.push_back(curCombination);
			return;
		}

		// Base condition... In case we are holding more element then required || curSum > target.
		// We don't find required result exploring more elements with curCombination.
		if (count > k || curSum > target)
			return;

		for (int i = startIndex; i < arr.size(); i++) {

			// Add it
			curCombination.push_back(arr[i]);
			curSum += arr[i];
			count++;

			helper(i + 1, curSum, target, count, k, curCombination);

			// Backtracking (Skip it)
			count--;
			curSum -= arr[i];
			curCombination.pop_back();

		}
	}



	vector<vector<int>> combinationSum3(int k, int n) {
		int curSum = 0, count = 0;
		vector<int> curCombination;
		helper(0, curSum, n, count, k, curCombination);
		return combinations;
	}
};
