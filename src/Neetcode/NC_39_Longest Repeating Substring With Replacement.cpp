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

Problem: NC_39_Longest Repeating Substring With Replacement
Topic: Sliding Window
Link: https://neetcode.io/problems/longest-repeating-substring-with-replacement

================================================================================
                                Problem Summary
================================================================================

Given a string `s` and an integer `k`, return the length of the longest substring
containing the same letter you can get after performing at most `k` character replacements.

================================================================================
                                Intuition & Explanation
================================================================================

We use the sliding window technique to expand the window by adding one character at a time.
We maintain a frequency map of characters in the current window and track the maximum frequency.

**The idea is that if the window size minus the count of the most frequent character is greater than `k`,
we need to shrink the window from the left. This ensures we only replace at most `k` characters.

In the correct solution (Solution 1), the new character is always added first and the frequency map
is updated before we check if the window is valid. This ensures the window is evaluated using accurate
and current data. [In Solution 2,] the window shrinking condition is checked before updating the frequency
map and max frequency, leading to incorrect window management.

================================================================================
                          Approach & Time/Space Complexity
================================================================================

Approach: Sliding Window with Frequency Map
Time Complexity: O(N), where N is the length of the string
Space Complexity: O(26) => O(1), since the input consists of only uppercase English letters
*/

class Solution {
public:

    int characterReplacement(string s, int k) {

        unordered_map<char, int> mp;

        int begin = 0;

        int maxFreq = 0, res = 0, curWindow = 0;

        for (int end = 0; end < s.size(); end++) {

            // expand
            mp[s[end]]++;

            // upto date maxFreq
            maxFreq = max(maxFreq, mp[s[end]]);

            curWindow = end - begin + 1;

            // shrink the window, if we have more characters (unique + others < windowSize) than allowed ...
            while (begin < end && (maxFreq + k) < curWindow) {

                mp[s[begin]]--;

                begin++;

                curWindow--;

                // why we are not updating this maxFreq ?? => Because until the next character have higher freq than current one, it won't create any problem.
                // and also shrinking window is based on window size(begin, end), rathar than maxFreq.
            }

            res = max(res, curWindow);
        }

        return res;

    }

};



// Solution-2, Wrong one...

class Solution {
public:

    int characterReplacement(string s, int k) {

        unordered_map<char, int> mp;

        int begin = 0;

        int maxFreq = 0, res = 0, curWindow = 0;

        for (int end = 0; end < s.size(); end++) {


            // Again question is, in our template we are shrinking the window based on s[end], right ?
            // But why we don't here =>
            // If u see, the condition we are using "(maxFreq + k) < curWindow" does not have anything computed based on s[end]...
            // And that is reason it may shrink unecessary..

            // Above solution(right), we expand the window first adding s[end], due to that... maxFreq also got updated...
            // And after we are shrinking based on "maxFreq" which is correct. Hope you get it why, we need to expand first.

            // shrink the window
            while (begin < end && (maxFreq + k) < curWindow) {

                mp[s[begin]]--;

                begin++;

                curWindow--;
            }

            // expand
            mp[s[end]]++;

            maxFreq = max(maxFreq, mp[s[end]]);

            curWindow = end - begin + 1;

            res = max(res, curWindow);
        }

        return res;

    }

};
