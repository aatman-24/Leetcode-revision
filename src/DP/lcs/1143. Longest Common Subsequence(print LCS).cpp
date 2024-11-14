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

Question : 1143. Longest Common Subsequence(print LCS)
Topic : DP
Problems :
==============================> Explanation <=============================================

Pattern: LCS

To print LCS,

We basically perform the backtracking, we start at right most corner (m, n). And do the backtracking of original alogrithm.

1) s1[i] == s2[j] => add s1[i] into LCS, move to (i-1, j-1).

2) s1[i] != s2[j],

    max(dp[i-1][j], dp[i][j-1]) => whichever comp return maximum value...there we move either (i-1,j) | (i, j-1)... in case both are maximum then...
..we can move to anyone... but such case indicate multiple same length LCS present...

==============================> Approach and Time Complexity <============================

1) DP
Time: O(2^N) -> O(M*N)
Space: O(M*N) => O(M+N)
 */



class Solution {

public:

    string printLCS(int i, int j, vector<vector<int>> dp, string s, string t) {

        // first create, longest_common_subseq length temp string.
        string str = "";
        int len = dp[i][j];
        for (int i = 1; i <= len; i++) {
            str += "$";
        }
        int index = len - 1;

        // Perform backtracking..
        while (i > 0 && j > 0) {

            if (s[i - 1] == t[j - 1]) { // both character match, add it in LCS
                str[index] = s[i - 1];
                index--;
                i--;
                j--;
            }
            else if (dp[i - 1][j] > dp[i][j - 1]) { // Otherwise pick up the maximum(where we came from)
                i--;
            }
            else {
                j--;
            }
        }

        return str;
    }

    string all_longest_common_subsequences(string s, string t) {
        int m = s1.size(), n = t.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s[i - 1] == t[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                }
                else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        int longestSubLen = dp[m][n];

        return printLCS(i, j, dp, s, t);
    }
};
