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

Question : 1547. Minimum Cost to Cut a Stick
Topic : DP-MCM
Problems : https://leetcode.com/problems/minimum-cost-to-cut-a-stick/
==============================> Explanation <=============================================

Pattern: MCM Pattern

Given that, one road of length N, and cuts[](where we can make cut)...we have to find minimum
cost to make all cuts...

How cost will be calcualted ?

suppose you are cutting 5 length rod... from ith point...

cost = remaining_cost_left_side + remaining_cost_right_side + 5(length of cost)

In short, whatever length rod you are cutting is direct cost.


Recursion:

In this, I am managing total 4 parameters.
rod_begin, rod_end => to calculate direct cost (length of rod)
i, j => which keep track of which cut we have applied in which range.

So based on which order we are making cuts...cost will be different..because if we make cut on 7th length rod and 3 length rod => direct cost can be 7 or 3...

Recurssion Relation is straightforward:

	minCost(begin, end, i, j) =>

		k: i -> j

			minCost(begin, cuts[k], i, k-1) + minCost(cuts[k], end, k+1, j) + (end - begin)(direct cost)

See how I changed begin & end...

	If I am making cut at cuts[k].... then left rod... end = cuts[k], and for
	right rod... begin=cuts[k]..

Top-Down Approach with managing begin & end pointers:

	Here, we just applied memorization apporach. Nothing else.

Bottom-up Approach with managing begin & end pointers:

	This one I tried, but I was not able to manage the begin & end boundary in this approach.


So I come up with one trick is that...

	we will push 0 and N... into the cuts[]... so we don't have to manage the boundary, edge cases.

	Because, if cuts[] = {10}.... only given then getting the left & right boundary which is 0 & N during
	counting rod length become diffcult...

	instead of we push cuts[] = {0, 10, 20}.... we can count it by "cuts[j] - cuts[i]". Only this is that
	we will iterate the k between (i, j)... indicate cutting between (i, j)...which is right & easy...

	Because ultimately...we are finding minCost of (0, N) length rod...applying given cuts[]....

	Check both top-down and bottom-up approach.

==============================> Approach and Time Complexity <============================



1) DP
Time: O(N^3)
Space: O(N^2)

 */


// Recursion Solution
class Solution {
public:

	int minCost(vector<int> &cuts, int begin, int end, int i, int j) {

		if (i > j) return 0;

		int minimumCost = INT_MAX;
		for (int k = i; k <= j; k++) {
			int cost = minCost(cuts, begin, cuts[k], i, k - 1) + minCost(cuts, cuts[k], end, k + 1, j) + abs(begin - end);
			minimumCost = min(minimumCost, cost);
		}

		return minimumCost;
	}


	int minCost(int n, vector<int>& cuts) {
		sort(cuts.begin(), cuts.end());
		return minCost(cuts, 0, n, 0, cuts.size() - 1);
	}
};

// Top-down Approach, managing the boundary separately...
class Solution {
public:

	int t[101][101];

	int minCost(vector<int> &cuts, int begin, int end, int i, int j) {

		if (i > j) return 0;

		if (t[i][j] != -1)
			return t[i][j];

		int minimumCost = INT_MAX;
		for (int k = i; k <= j; k++) {
			int cost = minCost(cuts, begin, cuts[k], i, k - 1) + minCost(cuts, cuts[k], end, k + 1, j) + abs(begin - end);
			minimumCost = min(minimumCost, cost);
		}

		return t[i][j] = minimumCost;
	}


	int minCost(int n, vector<int>& cuts) {
		memset(t, -1, sizeof(t));
		sort(cuts.begin(), cuts.end());
		return minCost(cuts, 0, n, 0, cuts.size() - 1);
	}
};

// Top-down Approach (With Boundary Addition)
class Solution {
public:

	int t[103][103];

	int minCost(vector<int> &cuts, int i, int j) {

		if (i > j) return 0;

		if (t[i][j] != -1)
			return t[i][j];

		int minimumCost = INT_MAX;
		for (int k = i + 1; k < j; k++) {
			int cost = minCost(cuts, i, k) + minCost(cuts, k, j) + abs(cuts[i] - cuts[j]);
			minimumCost = min(minimumCost, cost);
		}

		// (i, j) is irrelveant... keeping as "0" only, otherwise above cost calculation given out of range for int.
		return t[i][j] = minimumCost == INT_MAX ? 0 : minimumCost;
	}


	int minCost(int n, vector<int>& cuts) {
		memset(t, -1, sizeof(t));
		cuts.push_back(0);
		cuts.push_back(n);
		sort(cuts.begin(), cuts.end());
		return minCost(cuts, 0, cuts.size() - 1);
	}
};



// Bottom-up with boundary Addition
class Solution {
public:
	int minCost(int n, vector<int>& cuts) {

		// Adding,(0, N) to form the boundary.
		cuts.push_back(0);
		cuts.push_back(n);

		sort(cuts.begin(), cuts.end());

		int m = cuts.size();

		vector<vector<int>> dp(m, vector<int>(m, 0));

		for (int i = m - 1; i >= 0; i--) {
			for (int j = i + 1; j < m; j++) {
				int minimumCost = INT_MAX;
				for (int k = i + 1; k < j; k++) {
					int cost = dp[i][k] + dp[k][j] + abs(cuts[i] - cuts[j]);
					minimumCost = min(cost, minimumCost);
				}
				// don't confuse with this... I'm keeping dp[i][j] as "0" only, not assiging INT_MAX because (i, j) is irrevalnt
				// (i, j) subproblem can't be solution of any other range...
				// and during cost calcualtion given out of range for int.
				dp[i][j] = minimumCost == INT_MAX ? 0 : minimumCost;
			}
		}

		return dp[0][m - 1];
	}
};