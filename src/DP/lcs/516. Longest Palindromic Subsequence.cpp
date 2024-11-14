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

Question : 516. Longest Palindromic Subsequence
Topic : DP
Problems : https://leetcode.com/problems/longest-palindromic-subsequence/description/
==============================> Explanation <=============================================

Pattern: LCS

Intuition behind this apporach is that,

To find the LPS(Longest Palindrome Subseq), we have to reverse(S) and find LCS(S, reverse(S)).

Because, When we reverse the String=S, that time seq which is part of Palindrome remain same in terms of order.

And later, when we find the LCS between them, we get entire palindrome subseq as result.

Ex:

1) a c b d a  => a d b c a
as you can see, when we reverse the string the palindrome seq(aba) which remain as it is. That's concept we used
to derive the palindrome seq.

==============================> Approach and Time Complexity <============================


1) DP
Time: O(2^(M+N)) -> O(M*N)
Space: O(M*N) => O(M+N) (stack space)
 */


class Solution {
public:


    int longestCommonSubseq(string s1, string s2) {

        int m = s1.size(), n = s2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        // base case
        // dp[i][0] = 0, dp[0][j] = 0 (already covered).

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



    int longestPalindromeSubseq(string s) {

        // Base case, len(s) <= 1 for such string, longest palindrome of string is itself.
        if (s.size() <= 1)
            return s.size();

        string s2 = s;
        reverse(s2.begin(), s2.end());

        return longestCommonSubseq(s, s2);
    }
};