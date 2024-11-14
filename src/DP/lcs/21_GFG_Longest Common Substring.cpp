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

Question : 21_GFG_Longest Common Substring
Topic : DP
Problems : https://www.geeksforgeeks.org/problems/longest-common-substring1452/1
==============================> Explanation <=============================================

Pattern: LCS

Longest Common Substring,

When we are finding the LCS(subsequence) that time seq is not required to be in consecutive manner, but for the
LCS(substring) we need in consecutive manner.

So there is change only.

Previously, when the s1[i] != s2[j], that time we return the max length from either call (i-1, j) || (i, j-1)... But
here such mismatch break the substring...so we need to return zero. (check the code)

Also, due to that.... we need to keep track of maxLen... because we are getting hte maximum length substring at subproblem not at global level.

==============================> Approach and Time Complexity <============================


1) DP
Time: O(2^N) -> O(M*N)
Space: O() => O(N) (stack space)
 */



// Top-down Approach
class Solution {
public:

    int t[1001][1001];

    // keep track of longest common substring.
    int longestCommSubstr = 0;

    int longestCommonSubstrHelper(int i, int j, string s1, string s2) {

        if (i == 0 || j == 0)
            return 0;

        if (t[i][j] != -1)
            return t[i][j];

        int countOfLen = 0;

        if (s1[i - 1] == s2[j - 1]) {
            countOfLen = 1 + longestCommonSubstrHelper(i - 1, j - 1, s1, s2);   // Here only, we get the maxLen due to consecutive match.
            if (longestCommSubstr < countOfLen) {
                longestCommSubstr = countOfLen;
            }
        } else {                                        // mismatch break the lcs... so we return 0.
            longestCommonSubstrHelper(i - 1, j, s1, s2);
            longestCommonSubstrHelper(i, j - 1, s1, s2);
            countOfLen = 0;
        }

        return t[i][j] = countOfLen;
    }

    int longestCommonSubstr(string s1, string s2) {

        memset(t, -1, sizeof(t));

        longestCommonSubstrHelper(s1.size(), s2.size(), s1, s2);

        return longestCommSubstr;
    }
};



// Bottom-up Approach
class Solution {
public:

    int longestCommonSubstr(string s1, string s2) {

        int m = s1.size(), n = s2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        int maxCommonSubstr = 0;

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                    maxCommonSubstr = max(maxCommonSubstr, dp[i][j]);
                }
            }
        }

        return maxCommonSubstr;
    }
};