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

Problem: NC_21_Longest Palindromic Substring
Topic: DP
Link: https://neetcode.io/problems/longest-palindromic-substring

================================================================================
                                Problem Summary
================================================================================

We need to find the maximum palindromic substring in given string.


================================================================================
                                Intuition & Explanation
================================================================================

Brute Force:
We can generate all possible substrings s(i, j) in O(N^2) time. For each substring,
we check if it is a palindrome, which takes O(N) time. So the total time complexity
is O(N^3), with no extra space used.

Two-Pointer Approach:
This is an optimization over the brute-force method. Instead of checking all substrings,
we start from each index and expand outward using two pointers (left and right) as long
as the characters match. This allows us to check for palindromes more efficiently.

Dynamic Programming (DP):
We use a 2D DP table to store whether the substring s(i, j) is a palindrome. If s(i+1, j-1)
is a palindrome and s[i] == s[j], then s(i, j) is also a palindrome. This avoids redundant
computations by reusing previously computed results.


================================================================================
                          Approach & Time/Space Complexity
================================================================================

Approach: Brute Force
Time Complexity: O(N^3) – O(N^2)*O(N)
Space Complexity: O(1)

Approach: Two-Pointer Approach
Time Complexity: O(N^2)
Space Complexity: O(1)

Approach: Dynamic Programming (DP)
Time Complexity: O(N^3)
Space Complexity: O(N^2)

*/


// Two Pointer
class Solution {
public:
    string longestPalindrome(string s) {

        int N = s.size();

        int maxLen = 0;
        int startOfString = 0;

        for (int i = 0; i < N; i++) {

            // odd palindromic match, staring from center pointer => s: "aba", startPoint = "b"
            int lft = i, rht = i;

            while (lft >= 0 && rht < N && s[lft] == s[rht]) {

                int len = rht - lft + 1;
                if (len > maxLen) {
                    startOfString = lft;
                    maxLen = len;
                }

                lft--;
                rht++;
            }

            // even palindromic string like => "abba"
            if (i - 1 >= 0 && s[i - 1] == s[i]) {

                // even palindromic match, staring from center pointer => "bb": "abba", startPoint = "bb"
                lft = i - 1, rht = i;

                while (lft >= 0 && rht < N && s[lft] == s[rht]) {

                    // keep track of maxLen
                    int len = rht - lft + 1;
                    if (len > maxLen) {
                        startOfString = lft;
                        maxLen = len;
                    }

                    lft--;
                    rht++;
                }

            }

        }

        return s.substr(startOfString, maxLen);

    }
};

// DP
class Solution {
public:
    string longestPalindrome(string s) {

        int N = s.size();

        // keep track of starting point of longest palindrome, so at the end we can get result string
        int maxLen = 0, startOfString = 0;

        // dp table is used to check if s[i, j]... is palindrome or not
        vector<vector<int>> dp(N, vector<int>(N, 0));

        // remember, we need to start from the end only... because we will use dp[i+1]"[j-1]" to check internal substring...
        for (int i = N - 1; i >= 0; i--) {

            // remember, we need to go from i -> N, because we will use dp[i+1]"[j-1]" to check internal substring...
            for (int j = i; j < N; j++) {

                // goal is that => if substring(i+1, j-1) is already marked as palindrome, then we will use that.

                // case-1: string is like "a", "aa" then we return true....
                // case-2: string like: "cabac".... in which "aba" => already marked as palindrome,
                if (s[i] == s[j] && (j - i <= 2 || dp[i + 1][j - 1])) {

                    // marked current substring as (i, j) as palindrome..
                    dp[i][j] = 1;

                    // calculate length and keep track of maxLen and startOfString
                    int len = j - i + 1;

                    if (len > maxLen) {
                        maxLen = len;
                        startOfString = i;
                    }
                }

            }

        }

        return s.substr(startOfString, maxLen + 1);

    }
};
