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

Question : 1312. Minimum Insertion Steps to Make a String Palindrome*
Topic : DP
Problems : https://leetcode.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/description/
==============================> Explanation <=============================================

Pattern: LCS

Given that, For string=s, you need to find minimum insertion/deletion steps to make it palindrome.

Hard to Identify Pattern, but you have to (no choice).

Remember, When Palindrome question is given you must derive LCS between (s, reverse(s)).

First,

1) Learn how to find the LPS(Longest Palindrome Subsequence) for given String s.

        LPS(S) = LCS(S, reverse(S))

2) How to convert String s1 => s2, by doing deletion/insertion.

If you know #2, then you get the idea is...

    To convert string s1 => palindromic(s1).... you need to add/delete some of characters from s1.

    And how many characters(steps) you need to perform is derived through LCS.

        = len(S1) - LCS (deletion) + len(S2) - LCS(Insertion)

But here only S1 is given and whatever we do in S1 is also reflect in S2, so if we do one of operation DeletionFromS1 OR DeletionFromS2 is okay.

Ultimatly, no # of insertion/deletion required is = len(S) - len(LPS)

==============================> Approach and Time Complexity <============================



1) DP
Time: O(2^(M+N)) -> O(M*N)
Space: O(M*N) => O(N) (stack space)
 */



class Solution {
public:

    int longestCommSubseq(string s1, string s2) {

        int m = s1.size(), n = s2.size();

        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

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




    int minInsertions(string s) {

        // Convert S1 => S2, Cost = (len(S1) - len(LCS)) + (len(S2) - len(LCS)) (But Here, s2 == rev(s1), both are same)
        // Convert S1 => S2, Cost = (len(S1) - len(LCS))
        // How to get LCS of S1 = LPS(S1) = LCS(S1, reverse(S1))
        string s2 = s;
        reverse(s2.begin(), s2.end());
        int lcsLen = longestCommSubseq(s, s2);
        return s.size() - lcsLen;
    }
};