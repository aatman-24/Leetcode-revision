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
================================================================================
                               Problem Description
================================================================================

🔹 Problem: NC_26_Interleaving String
🔹 Topic: Dynamic Programming (Similar to LCS)
🔹 Link: https://neetcode.io/problems/interleaving-string

================================================================================
                               Problem Summary
================================================================================

Given two strings `s1` and `s2`, determine whether they can be interleaved to form
a third string `s3`. You may use all characters from `s1` and `s2` in order, but
you cannot change the relative order of characters within either `s1` or `s2`.

Example:
    s1 = "abc", s2 = "efg"
    s3 = "abegcf" ❌ (Invalid: 'g' appears before 'f' from s2)

================================================================================
                         Intuition & Explanation
================================================================================

This is a variant of the Longest Common Subsequence (LCS) problem. We're given two
source strings (`s1`, `s2`) and need to check if their characters, in order, can
construct the target string (`s3`).

At each position `k` in `s3` (where `k = i + j`), the character must match:
    - Either `s1[i - 1]` if we choose a character from `s1`
    - Or `s2[j - 1]` if we choose from `s2`

We recursively explore both options while maintaining the character order in both
strings.

Recurrence relation:
    solve(i, j):
        k = i + j
        return (
            (i > 0 && s1[i-1] == s3[k-1] && solve(i-1, j)) ||
            (j > 0 && s2[j-1] == s3[k-1] && solve(i, j-1))
        )

NOTE: In code I have used i == 0 and j == 0, k == 0 as base case...that's why we match s[i-1] insted of s[i]...

================================================================================
                    Approach & Time/Space Complexity
================================================================================

🔸 Approach 1: Recursion (Brute-force)
    - Time: O(2^K) where K = s3.length()
    - Space: O(K) (due to recursion stack)

🔸 Approach 2: Top-Down DP (Memoization)
    - Time: O(M * N), where M = s1.length(), N = s2.length()
    - Space: O(M * N) for memoization table

🔸 Approach 3: Bottom-Up DP (Tabulation)
    - Time: O(M * N)
    - Space: O(M * N) (can be optimized to O(N))
*/

// Recursive solution
class Solution {
public:

    bool support(string s1, int i, string s2, int j, string t, int k) {

        if (k == 0) return true;

        bool isMatched = false;

        if (i > 0 && s1[i - 1] == t[k - 1]) {
            isMatched = support(s1, i - 1, s2, j, t, k - 1);
        }

        if (j > 0 && !isMatched && s2[j - 1] == t[k - 1]) {
            isMatched = support(s1, i, s2, j - 1, t, k - 1);
        }

        return isMatched;
    }


    bool isInterleave(string s1, string s2, string s3) {

        // edge case
        if (s1.size() + s2.size() != s3.size())
            return false;

        return support(s1, s1.size(), s2, s2.size(), s3, s3.size());
    }
};


// Top-down solution
class Solution {
public:

    int memo[52][52];

    bool support(string s1, int i, string s2, int j, string t, int k) {

        if (i == 0 && j == 0) return true;  // if(k == 0) return true; bcz we have added edge case

        if (memo[i][j] != -1)
            return memo[i][j];

        // t[k] must match with one of string....
        bool isMatched = false;

        if (i > 0 && s1[i - 1] == t[k - 1]) {
            isMatched = support(s1, i - 1, s2, j, t, k - 1);
        }

        if (j > 0 && !isMatched && s2[j - 1] == t[k - 1]) {
            isMatched = support(s1, i, s2, j - 1, t, k - 1);
        }

        return memo[i][j] = isMatched;
    }


    bool isInterleave(string s1, string s2, string s3) {

        // edge case
        if (s1.size() + s2.size() != s3.size())
            return false;

        memset(memo, -1, sizeof(memo));

        return support(s1, s1.size(), s2, s2.size(), s3, s3.size());
    }
};



// Bottom-up
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int n1 = s1.size(), n2 = s2.size(), n3 = s3.size();

        // Edge case: lengths must match
        if (n1 + n2 != n3) return false;

        // dp[i][j] = true if s3[0..i+j-1] can be formed by interleaving s1[0..i-1] and s2[0..j-1]
        vector<vector<bool>> dp(n1 + 1, vector<bool>(n2 + 1, false));

        // Base case: all strings empty
        dp[0][0] = true;

        for (int i = 0; i <= n1; ++i) {

            for (int j = 0; j <= n2; ++j) {

                int k = i + j;  // derived kth from ith and jth index....

                if (i > 0 && s1[i - 1] == s3[k - 1]) {
                    dp[i][j] = dp[i][j] || dp[i - 1][j];
                }
                if (j > 0 && s2[j - 1] == s3[k - 1]) {
                    dp[i][j] = dp[i][j] || dp[i][j - 1];
                }

            }
        }

        return dp[n1][n2];
    }
};