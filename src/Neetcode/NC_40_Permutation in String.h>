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

Problem: NC_40_Permutation in String
Topic: Sliding Window
Link: https://neetcode.io/problems/permutation-string

================================================================================
                                Problem Summary
================================================================================

Given two strings `s1` and `s2`, check if any permutation of `s1` exists as a substring in `s2`.

================================================================================
                                Intuition & Explanation
================================================================================

### Brute Force:
- Generate all permutations of `s1` (O(N!)), and check each against all substrings of `s2` (O(M)).
- Total Time: O(N! * M) — clearly inefficient for large N.

### Optimized (Sliding Window + Frequency Map):
- Any permutation of `s1` will have the same character frequency.
- We slide a window of length equal to `s1.length()` over `s2` and compare frequency maps.

Steps:
1. Build frequency map of `s1`.
2. Move a window of size `s1.length()` across `s2`.
3. At each step, update the window frequency map and compare it with the frequency of `s1`.
4. If both maps match → return true (a permutation is found).
5. Otherwise, continue sliding the window.

================================================================================
                          Approach & Time/Space Complexity
================================================================================

Let N = length of `s2`, M = length of `s1`

Approach: Sliding Window
Time Complexity: O(N)
Space Complexity: O(1) — since character space is constant (26 lowercase letters)

*/

// Sliding Window => Expand & Shrink
class Solution {
public:
    bool checkInclusion(string s1, string s2) {

        // first calculate the freq of s1
        int freqOfTarget[26] = {0};
        for (char ch : s1) freqOfTarget[ch - 'a']++;

        int freqOfSource[26] = {0};

        int begin = 0;

        for (int end = 0; end < s2.size(); end++) {

            char ch = s2[end];

            // expand window
            freqOfSource[ch - 'a']++;

            // shrink window
            while (begin <= end && freqOfSource[ch - 'a'] > freqOfTarget[ch - 'a'] ) {

                freqOfSource[s2[begin] - 'a']--;

                begin++;
            }

            // current window have same length of s1
            if ((end - begin + 1) == s1.size()) return true;
        }

        return false;
    }
};


// Sliding Window => Shrink & Expand
class Solution {
public:
    bool checkInclusion(string s1, string s2) {

        // first calculate the freq of s1
        int freqOfTarget[26] = {0};
        for (char ch : s1) freqOfTarget[ch - 'a']++;

        int freqOfSource[26] = {0};

        int begin = 0;

        for (int end = 0; end < s2.size(); end++) {

            char ch = s2[end];

            // shrink window
            while (begin <= end && freqOfSource[ch - 'a'] >= freqOfTarget[ch - 'a'] ) {

                freqOfSource[s2[begin] - 'a']--;

                begin++;
            }

            // expand window
            freqOfSource[ch - 'a']++;

            // current window have same length of s1
            if ((end - begin + 1) == s1.size()) return true;
        }

        return false;
    }
};