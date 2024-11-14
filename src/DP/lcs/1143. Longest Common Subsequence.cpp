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

Question : 1143. Longest Common Subsequence
Topic : DP
Problems : https://leetcode.com/problems/longest-common-subsequence/description/
==============================> Explanation <=============================================

Pattern: LCS

Standard Problem.

solve(i, j) => s1[i] == s2[j] => (match) => 1 + solve(i-1, j-1) (if match then we move to next character in both string)
            => s1[i] != s2[j] => (unmatch) => max(solve(i-1, j), solve(i, j-1)) (if not match then we try both combination)

            combination_1:  abcde => cdfg ====> solve(abcde, cdf)
            combination_2:  solve(abcd, cdf)

Means, we remove last unmatched character from both string one by one and try to match other string. (Which is brute force).

Base case: i == 0 || j == 0, one of the string is visited entirely, and no string left for comparision we return 0(lcs).

Then we apply the top-down, bottom-up and space optimization.

==============================> Approach and Time Complexity <============================


1) DP
Time: O(2^N) -> O(M*N)
Space: O(M*N) => O(M+N)

Time Complexity Calculation:

Depth => max(m, n) => m
Breadth => 2

=> Breadth^Depth => 2^m

 */



// Recursion
class Solution {
public:

    int longestCommonSubsequenceHelper(int i, int j, string s1, string s2) {

        // If one the string is empty, we don't get common subsequence so return it 0.
        if (i == 0 || j == 0)
            return 0;

        if (s1[i - 1] == s2[j - 1]) {
            return 1 + longestCommonSubsequenceHelper(i - 1, j - 1, s1, s2);
        }
        else {
            return max(longestCommonSubsequenceHelper(i - 1, j, s1, s2), longestCommonSubsequenceHelper(i, j - 1, s1, s2));
        }
    }


    int longestCommonSubsequence(string s1, string s2) {
        return longestCommonSubsequenceHelper(s1.size(), s2.size(), s1, s2);
    }
};

// Top-Down

class Solution {
public:

    int t[1001][1001];

    int longestCommonSubsequenceHelper(int i, int j, string s1, string s2) {

        // If one the string is empty, we don't get common subsequence so return it 0.
        if (i == 0 || j == 0)
            return 0;

        if (t[i][j] != -1)
            return t[i][j];

        int longest = 0;

        if (s1[i - 1] == s2[j - 1]) {
            longest = 1 + longestCommonSubsequenceHelper(i - 1, j - 1, s1, s2);
        }
        else {
            longest = max(longestCommonSubsequenceHelper(i - 1, j, s1, s2), longestCommonSubsequenceHelper(i, j - 1, s1, s2));
        }

        return t[i][j] = longest;
    }


    int longestCommonSubsequence(string s1, string s2) {
        memset(t, -1, sizeof(t));
        return longestCommonSubsequenceHelper(s1.size(), s2.size(), s1, s2);
    }
};


// Bottom-up

class Solution {
public:
    int longestCommonSubsequence(string s1, string s2) {
        int m = s1.size(), n = s2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        // base case, (i == 0, j == 0) covered during initialization dp[i][0] = 0, dp[0][j] = 0.
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                }
                else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[m][n];
    }
};


// Space Optimization
class Solution {
public:
    int longestCommonSubsequence(string s1, string s2) {
        int m = s1.size(), n = s2.size();
        vector<int> pre(n + 1, 0), cur(n + 1, 0);
        // base case, (i == 0, j == 0) pre = {0, 0, 0....} and curr = {0, 0, 0..} which covered. .
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    cur[j] = 1 + pre[j - 1];
                }
                else {
                    cur[j] = max(pre[j], cur[j - 1]);
                }
            }
            swap(pre, cur);
        }
        return pre[n];
    }
};
