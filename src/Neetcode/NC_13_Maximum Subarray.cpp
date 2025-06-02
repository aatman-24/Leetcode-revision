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

Question : NC_13_Maximum Subarray
Topic : Kaden Algorithm
Problems : https://neetcode.io/problems/maximum-subarray

==============================> Explanation <=============================================

Idea is that, we have to find maxSum of subarray, given that array can have both positive and negative numbers.

We apply the kadane's algorithm,

need to keep track of curSum, maxSum and maxNum from the array.

anytime, curSum < 0 => we set it to curSum = 0, because we need maxSum of subarray, which is possible with positive numbers only.

Edge case: If numbers are negative in that case curSum = 0, so we return largest number from the subarray, which is smallest negative numbers.


==============================> Approach and Time Complexity <============================

1) Trie
Time: O(N)
Space: O(1)

*/

// kadane algorithm
class Solution {
public:
	int maxSubArray(vector<int>& nums) {

		int curSum = 0, maxSum = 0;

		int maxEle = nums[0];

		for (int num : nums) {
			curSum += num;
			if (curSum < 0) curSum = 0;
			maxSum = max(maxSum, curSum);
			maxEle = max(maxEle, num);
		}

		return maxSum == 0 ? maxEle : maxSum;
	}
};
