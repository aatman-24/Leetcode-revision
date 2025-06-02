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

Problem: NC_42_Sliding Window Template
Topic: Sliding Window
https://neetcode.io/problems/count-connected-components

================================================================================
                                Problem Summary
================================================================================

This is Sliding Window Template can be used to solve most of question of this pattern.

================================================================================
                                Intuition & Explanation
================================================================================





================================================================================
                          Approach & Time/Space Complexity
================================================================================

Approach: Sliding Window
Time Complexity: O(N+E)
Space Complexity: O(N+E)

*/

// Sliding Window Template - 1

int findSubstring(string s) {
    vector<int> map(128, 0);
    int counter; // check whether the substring is valid
    int begin = 0, end = 0; //two pointers, one point to tail and one  head
    int d; //the length of substring

    for () { /* initialize the hash map here */ }

    while (end < s.size()) {

        if (map[s[end++]]-- ? ) {  /* modify counter here */ }

        while (/* counter condition */) {

            /* update d here if finding minimum*/

            //increase begin to make it invalid/valid again

            if (map[s[begin++]]++ ? ) { /*modify counter here*/ }
        }

        /* update d here if finding maximum*/
    }
    return d;
}


// Sliding Window Template - 2

int findSubstring(string s) {

    vector<int> map(128, 0);

    int begin = 0;

    for (int end = 0; end < N; end++) {

        // expansion, it should be based on s[end]


        // shrink, it should be based on expansion, whatever you updated in expansion... based on that shrink happen.


        // update the result(ex: minWindow)

    }

}


// 3. Longest Substring Without Repeating Characters (Based on template)

class Solution {
public:
    int lengthOfLongestSubstring(string s) {

        int mp[128] = {0};  // mp for letters, digits, symbols and spaces.
        int begin = 0, end = 0, N = s.size();
        int max_window = 0, counter = 0;  // counter determine we need to expand or shrink the window.

        while (end < N) {

            // In window, s[end] got duplicated, that's why we updated coutner++;
            if (mp[s[end]] > 0) {
                counter++;
            }

            // Add current character frequency into map.
            mp[s[end++]]++;

            while (counter > 0) {

                // removed element from window.
                mp[s[begin]]--;

                // this mp[s[begin]] needs to be > 0, because we added frquency in mp[s[end]].
                if (mp[s[begin]] > 0) {
                    counter--;
                }

                begin++;
            }

            max_window = max(max_window, end - begin);
        }

        return max_window;
    }
};
