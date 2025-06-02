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

Problem: NC_22_Palindromic Substrings
Topic: DP
Link: https://neetcode.io/problems/partition-labels

================================================================================
                                Problem Summary
================================================================================

Return number of Palindromic Substrings...

Parent: NC_21_Longest Palindromic Substring

Same above one, instead of getting the Longest Palindromic Substring, we need to
calculate total Palindromic Substring

================================================================================
                                Intuition & Explanation
================================================================================

Idea is that,

In the code of NC_21_Longest Palindromic Substring, wherever we see the condition
isPalindrome=True, we just increase the counter, nothing else....

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



class Solution {
public:
    int countSubstrings(string s) {

        int N = s.size();

        // keep track of count
        int count = 0;

        vector<vector<int>> dp(N, vector<int>(N, 0));

        for (int i = N - 1; i >= 0; i--) {

            // checking only... [i, j] range
            for (int j = i; j < N; j++) {

                // goal is that => substring(i+1, j-1) is already marked as palindrome then we will use that.

                // case-1: string is like "a", "aa" then we return true....
                // case-2: string like: "cabac".... in which aba" => already marked as palindrome,
                if (s[i] == s[j] && (j - i <= 2 || dp[i + 1][j - 1])) {

                    dp[i][j] = 1;

                    // we know that, if above condition match it means we found one of palindrome..
                    // so we just do count++
                    count++;
                }

            }

        }

        return count;

    }
};


// Two Pointer
class Solution {
public:
    int countSubstrings(string s) {

        int N = s.size();

        int count = 0;


        for (int i = 0; i < N; i++) {

            // odd palindromic match, staring from center pointer => s: "aba", startPoint = "b"
            int lft = i, rht = i;

            while (lft >= 0 && rht < N && s[lft] == s[rht]) {
                count++;
                lft--;
                rht++;
            }

            // even palindromic string like => "abba"
            if (i - 1 >= 0 && s[i - 1] == s[i]) {

                // even palindromic match, staring from center pointer => "bb": "abba", startPoint = "bb"
                lft = i - 1, rht = i;

                while (lft >= 0 && rht < N && s[lft] == s[rht]) {
                    count++;
                    lft--;
                    rht++;
                }

            }

        }

        return count;
    }
};