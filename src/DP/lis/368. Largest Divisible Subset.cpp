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

Question: 368. Largest Divisible Subset
Topic : Bottom-up Pattern=LIS
Problems : https://leetcode.com/problems/largest-divisible-subset/

==============================> Explanation <=============================================

Pattern = LIS

Here, we need to find largest divisible subset of given set, such that every elements
in that set is divisible by other elements of set or vice versa. Which is possible, there is transitive property
exist in set. What I mean is that,

- If given numbers is A -> B -> C, if B % A == 0 and C % B == 0 then, automatic C % A == 0(which no need to check).
 (Transitive Property)

- So we sort the array, so i < j then nums[i] < nums[j] and nums[i] could become divisor.

- And we use LIS logic.... dp[i] = dp[j] + 1 if(nums[i] % nums[j] == 0)

- But Here problem is that we also need that subset not only size.. so we use dfs logic of keeping previous
elements...(from which is best for current i) and lastly we derive that subset see below code..

1) Choise Diagram: if(nums[i] % nums[j] == 0) then we can expand the nums[j] series but we look all the
                    possible divisor which gives maxlen subset. (0 < =j <= i-1).

2) Base Case: every number is divisible by itself. minimum value of dp[i] = 1.

3) Recurrance Relation:
        for(int j = i - 1; j >= 0; j--)
        	if(nums[i] % nums[j] == 0)
	            dp[i] = max(dp[i], dp[j]+1)


Check the code!!

Directly applying the LIS Bottom-up Approach. (Which is quite easy to remember, compare to top-down).

==============================> Approach and Time Complexity <============================

1) DP
Time: O(N^2)
Space: O(N)

 */


/* Intuition:

Given that, largest divisible subset which is simliar to LIS.

Because, LIS = nums[j] < nums[i] and follow transitive property. Here,

		 LDS = nums[i] % nums[j] == 0 && follow transitive property.

Both we need largest subsets. Directly using the Bottom-up approach(quite easy).


*/

class Solution {
public:

	vector<int> largestDivisibleSubset(vector<int>& nums) {

		int N = nums.size();

		// DP Table
		// Each element divisible by itself, make 1 length subset
		// previous of each element can be -1.
		vector<int> dp(N, 1), pre(N, -1);

		// Sort array, so we can form the transitive relation n1 < n2 < n3
		// n3 % n2 == 0 && n2 % n1 == 0 => n3 % n1 == 0.
		sort(nums.begin(), nums.end());

		// Atleast each element is divisible by itself
		int maxSubsetLIS = 1;

		for (int i = 1; i < N; i++) {

			// keep track of previous element for forming the path.
			int prev = -1;

			for (int j = i - 1; j >= 0; j--) {
				if (nums[i] % nums[j] == 0 && (dp[i] < dp[j] + 1)) {
					dp[i] = 1 + dp[j];
					prev = j;
				}
			}

			// keep track of maximum LIS (which we will use to get first element)
			maxSubsetLIS = max(maxSubsetLIS, dp[i]);

			pre[i] = prev;
		}

		// Find the subset using DFS Traversal in reverse manner
		vector<int> largestSubset;
		int index = 0;
		for (int i = 0; i < N; i++) {
			if (dp[i] == maxSubsetLIS) {
				index = i;
				break;
			}
		}

		while (index != -1) {
			largestSubset.push_back(nums[index]);
			index = pre[index];
		}

		// (doesn't require)
		reverse(largestSubset.begin(), largestSubset.end());

		return largestSubset;
	}
};