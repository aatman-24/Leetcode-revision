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

Question : 132. Palindrome Partitioning II
Topic : DP-MCM
Problems : https://leetcode.com/problems/palindrome-partitioning-ii/description/
==============================> Explanation <=============================================

Pattern: MCM Pattern

We need to find minimum cut to make all substring Palindrome.

Brute Force: We can apply recursion to check (i, j) is Palindrome and if yes then we can check (i+1, j)...
And keep track of minimum cut. Which is done in #1 Solution.

DP(MCM): On the brute force, applied the memorziation to avoid duplicate computation of subproblems.

But problem is that, DP(MCM) take O(N^3) Time... Given N = 2000.. we are getting TLE. Main issue is that,
In other MCM Problem we don't need to check whether(i, j) satisfy some condition, but here we need to check s[i..j]
is Palindrome which costing us O(N) time... leads to O(N^3).

There are 2 Specific solution of this question, both are following MCM pattern(but twisted way)...

#1: We try to find minCut and Palindrome substr, both at same time rathar than checking every time.
Idea is that,

		For s[i...j] substr....if s[i] == s[j] && s[i+1...j-1] (insider substr) is also palindrome,

		It menas s[i..j] is also palindrome.

		minimum cutting is required from (0, j) => minCut[i-1] + 1

		Cuts are => {0, i-1}, {i, j]}

Problems, here is that...we are chekcing for each(i, j) substr through loops which can be optimized.

#2: We put "ith" character as center of Palindrome and try to increase as much as its length so we get bigger
Palindrome so cuts will be reduced. That way we don't need to check for each (i, j) range...once range of substr
stopped widening due to mismatch of (s[i], s[j]) we don't check for (i-1, j+1)..
In this we have to check for both odd and even length string..putting "i" as center.

Check the code!!

==============================> Approach and Time Complexity <============================



1) DP
Time:
Space:

 */

// Recursive Solution
class Solution {
public:

	int MAX = 1e6;

	bool isPalindrome(string s, int i, int j) {
		while (i <= j) {
			if (s[i] != s[j]) return false;
			i++; j--;
		}
		return true;
	}

	int minCut(string s, int i, int j) {

		if (i == j) return 0;

		if (isPalindrome(s, i, j))
			return 0;

		int minCost = MAX;
		for (int k = i; k < j; k++) {
			int cost = minCut(s, i, k) + minCut(s, k + 1, j) + 1;
			minCost = min(minCost, cost);
		}

		return minCost;
	}

	int minCut(string s) {
		return minCut(s, 0, s.size() - 1);
	}
};


// Top-Down (Memorization)

class Solution {
public:

	int MAX = 1e6;

	int t[2001][2001];

	bool isPalindrome(string s, int i, int j) {
		while (i <= j) {
			if (s[i] != s[j]) return false;
			i++; j--;
		}
		return true;
	}

	int minCut(string s, int i, int j) {

		if (i == j) return 0;

		if (isPalindrome(s, i, j))
			return t[i][j] = 0;

		int minCost = MAX;
		for (int k = i; k < j; k++) {
			int cost = minCut(s, i, k) + minCut(s, k + 1, j) + 1;
			minCost = min(minCost, cost);
		}

		return t[i][j] = minCost;
	}

	int minCut(string s) {
		memset(t, -1, sizeof(t));
		return minCut(s, 0, s.size() - 1);
	}
};

// Bottom-up

class Solution {
public:

	int MAX = 1e6;

	bool isPalindrome(string s, int i, int j) {
		while (i <= j) {
			if (s[i] != s[j]) return false;
			i++; j--;
		}
		return true;
	}

	int minCut(string s) {

		int n = s.size();

		// dp table
		vector<vector<int>> dp(n, vector<int>(n, 0));

		// base case (covered)

		for (int i = n - 1; i >= 0; i--) {
			for (int j = i + 1; j < n; j++) {
				if (isPalindrome(s, i, j)) {
					dp[i][j] = 0;
				}
				else {
					int minCost = MAX;
					for (int k = i; k < j; k++) {
						int cost = dp[i][k] + dp[k + 1][j] + 1;
						minCost = min(minCost, cost);
					}
					dp[i][j] = minCost;
				}
			}
		}

		return dp[0][n - 1];
	}
};




// Specific solution - 1

class Solution {
public:
	/* Intuition:

		For s[i...j] substr....if s[i] == s[j] && s[i+1...j-1] inside string is also palindrome,

		minimum cutting is from (0, j) => minCut[i-1] + 1

		Cuts are => {0, i-1}, {i, j]}

		Again, when we have longer substr of k length(0, k) that time we will use this computed result from (0, j) to get minCuts.

		See how subproblems order got resolved...

			(4, 4) => (3, 4) => (2, 4) => (1, 4)

			(5, 5) => (4, 5)(here we check (3, 4) is palindrome or not) => (3, 5) => (2, 5) => (1, 5)
	*/
	int minCut(string s) {

		int N = s.size();

		if (N <= 1)
			return 0;

		// Taking every s[i...j] as not palindrome.
		vector<vector<int>> isPalindrome(N, vector<int>(N, 0));

		// minCuts require for s[0...j], will be stored dp[j+1].
		vector<int> dp(N + 1, 0);

		// Worst case, ith length string require (i-1) cuts, with single digit as pal
		for (int i = 0; i <= N; i++)
			dp[i] = i - 1;

		for (int j = 1; j < N; j++) {
			for (int i = j; i >= 0; i--) {

				// characters are matchings..
				// 1) (i, i) || (i-1, j) with s[i-1] == s[j]
				// 2) s[i] == s[j] && s[i+1...j-1] is pal
				if ((s[i] == s[j]) && ((j - i < 2) || isPalindrome[i + 1][j - 1])) {
					isPalindrome[i][j] = 1;
					dp[j + 1] = min(dp[j + 1], 1 + dp[i]);
				}
			}
		}

		return dp[N];
	}
};


// Specific solution - 2: Manancher-like solutiion


class Solution {
public:

	/* Intuition:

		With this solution, we are not checking every (i, j) as palindrome, but we try to increase the length
		of palindrome from the center as much as we can.

		Similar to #1 Specific solution.

		But in this, we consider (ith) character as center of palindrome and increase the length.

		we check, (i-1, i, i+1), (i-2, i-1, i, i+1, i+2)... this way

		And again for this substr [(i-2, i-1, i, i+1, i+2)], we need intermidate result of [(i-1, i, i+1)].

		As we are using centric apporach, we need to check for both even and odd length substr at mid.

		Apart from that, Recurrent Relation remain same but twisted with new indexes,

			Recurrent Relation:

				minCut[j] = min(minCut[j], 1 + minCut[i]]

	*/
	int minCut(string s) {

		int N = s.size();

		if (N <= 1)
			return 0;

		// minCuts require from (0, j) will be stored dp[j+1] location...
		vector<int> dp(N + 1, 0);

		// Worst case, ith length string require (i-1) cuts
		for (int i = 0; i <= N; i++)
			dp[i] = i - 1;


		for (int i = 1; i < N; i++) {

			// Odd length center
			for (int j = 0; (i - j) >= 0 && (i + j) < N && s[i - j] == s[i + j]; j++) {
				dp[i + j + 1] = min(dp[i + j + 1], 1 + dp[i - j]);
			}

			// Even length center.. [a,b,b,a]... we are checking form 2nd "b"... for i = 2..first comparision will be (0, 3)
			for (int j = 0; (i - j - 1) >= 0 && (i + j) < N && s[i - j - 1] == s[i + j]; j++) {
				dp[i + j + 1] = min(dp[i + j + 1], 1 + dp[i - j - 1]);
			}
		}

		return dp[N];
	}
};