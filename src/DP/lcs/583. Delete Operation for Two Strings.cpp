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

Question : 583. Delete Operation for Two Strings
Topic : DP
Problems : https://leetcode.com/problems/delete-operation-for-two-strings/description/
==============================> Explanation <=============================================

Pattern: LCS

Given that,

We need to convert the S1 => S2, by doing one of operation (deletion-A, deletion-B(Insertion-A)). Each operation cost 1 unit.

First you need to identify problem is from LCS-Subset problems.

How ? 1) Given Two String 2) Asking minimum cost(optimization) 3) To get minimum cost you need to try all possible combination.

And if you notice carefully, you are not doing anything on LCS of them.

Let's jump to solution,

    S1 = HEAP
    S2 = PEA
    LCS = EA

    So what we do is, convert S1 => LCS, HEAP => EA (Required 2 Deletion from S1 (H, P))
                      convert S2 => LCS, PEA => EA  (Required 1 Deletion from S2 (P)) (Which is, Insertion in S1).

    We convert S1 => LCS and then LCS => S2... which result into S1 => S2.

    For pratical purpose, we convert s1 => lcs && s2 => lcs which is similar to above one.

    Opereation cost
        =  len(S1) - len(LCS) (Deletion from S1)
        +  len(S2) - len(LCS) (Deletion From S2 | Insertion in S1)

==============================> Approach and Time Complexity <============================


1) DP
Time: O(2^(M+N)) -> O(M*N)
Space: O(M*N) => O(N) (stack space)
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


    int minDistance(string word1, string word2) {


        int longestCommonSubseqLen = longestCommonSubseq(word1, word2);

        return word1.size() - longestCommonSubseqLen + word2.size() - longestCommonSubseqLen;
    }
};