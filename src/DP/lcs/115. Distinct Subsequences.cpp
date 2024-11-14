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

Question : 115. Distinct Subsequences
Topic : DP
Problems : https://leetcode.com/problems/distinct-subsequences/description/
==============================> Explanation <=============================================

Pattern: LCS+Knapsack

Given two strings s and t(target), we have to find all unique subsequence from "s" which match to "t".

So this problem is not exactly LCS Pattern, but we can take the idea from it,

We do comparsion, same way we do in LCS.

    s[i] == t[j] (matched) => That time we have two choice (consider as match) OR (Unmatched, Expecting simliar character forward)
    s[i] != t[j] => Unmatched

When we consider match that time we jump to (i-1, j-1) and for unmatch(i-1, j)... (j will be same... we are not finding LCS).

Base case,

    T = ""(j==0)... that time any sub-seq of S will match. So return 1. (count)
    S = ""(i==0,j!=0)...it means still T have some character left, but we reach End of String for "s". So we return 0 (don't able to find entire T in S)

Check the code!!


WE can do space optimization as well.....

==============================> Approach and Time Complexity <============================



1) DP
Time: O(2^M -> O(M*N)
Space: O(M*N) => O(N) (stack space)


Breadth => 2
Depth => len(S)

 */



// Top-down
class Solution {
public:

    int memo[1001][1001];

    int numDistinctHelper(int i, int j, string s, string t) {

        // End of target String.
        if (j == 0)
            return 1;

        // Don't able to match string "s" entirely with target string "t"
        if (i == 0)
            return 0;

        if (memo[i][j] != -1) {
            return memo[i][j];
        }

        int count = 0;
        if (s[i - 1] == t[j - 1]) {
            // two choice, match and don't match
            count = numDistinctHelper(i - 1, j - 1, s, t) + numDistinctHelper(i - 1, j, s, t);
        }
        else {
            count = numDistinctHelper(i - 1, j, s, t);
        }


        return memo[i][j] = count ;
    }


    int numDistinct(string s, string t) {

        memset(memo, -1, sizeof(memo));

        return numDistinctHelper(s.size(), t.size(), s, t);
    }
};



// Bottom-up
class Solution {
public:

    int numDistinct(string s, string t) {

        int m = s.size(), n = t.size();
        vector<vector<unsigned int>> dp(m + 1, vector<unsigned int>(n + 1, 0));

        // base case
        for (int i = 0; i <= m; i++)
            dp[i][0] = 1;

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s[i - 1] == t[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j]; // (match + don't match)
                }
                else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }

        return dp[m][n];
    }
};