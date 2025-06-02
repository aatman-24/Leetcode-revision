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

Problem: NC_38_Longest Substring Without Repeating Characters
Topic: Sliding Window
Link: https://neetcode.io/problems/longest-substring-without-duplicates

================================================================================
                                Problem Summary
================================================================================

Given a string `s`, find the length of the longest substring without repeating characters.

================================================================================
                                Intuition & Explanation
================================================================================

To solve this problem, we use the **sliding window** technique to maintain a dynamic window
of unique characters.

### Approach 1: Using Character Frequency
- Maintain a hash map to track the frequency of each character in the current window.
- If a duplicate character is added (frequency > 1), shrink the window from the left
  until the duplicate is removed.
- Update the max length whenever a valid window is found.

### Approach 2: Using Last Seen Index
- Keep a hash map that stores the last index where a character was seen.
- If a character is repeated within the current window, move the `start` pointer to
  `lastSeen[ch] + 1`.
- Always ensure the window contains only unique characters.

Both approaches ensure we process each character at most twice, so the time complexity remains linear.

================================================================================
                          Approach & Time/Space Complexity
================================================================================

Approach: Sliding Window
Time Complexity: O(N)
Space Complexity: O(N)

*/

class Solution {
public:
    int lengthOfLongestSubstring(string s) {

        // {'ch' -> count}
        unordered_map<char, int> mp;

        int maximumWindow = 0;

        int begin = 0;

        for (int end = 0; end < s.size(); end++) {

            // validate the window first,
            while (begin < end && mp[s[end]] != 0) {
                mp[s[begin]]--;
                begin++;
            }

            mp[s[end]]++;

            // valid window

            maximumWindow = max(maximumWindow, (end - begin + 1));
        }

        return maximumWindow;
    }
};



class Solution {
public:
    int lengthOfLongestSubstring(string s) {

        // {ch -> last_position}
        unordered_map<char, int> mp;

        int maximumWindow = 0;

        int begin = 0;

        for (int end = 0; end < s.size(); end++) {

            // validate the window first,
            if (mp.count(s[end])) {
                begin = max(begin, mp[s[end]] + 1); // why max ? because it is possible..begin is already jumped above mp[s[end]] position, "abba" for last "a"... mp[s[end]] = 0, begin = 2...
            }

            mp[s[end]] = end;

            // valid window

            maximumWindow = max(maximumWindow, (end - begin + 1));
        }

        return maximumWindow;
    }
};
