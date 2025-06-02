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

Problem: NC_41_Minimum Window Substring
Topic: Sliding Window
Link: https://neetcode.io/problems/minimum-window-with-characters

================================================================================
                                Problem Summary
================================================================================

Need ot find the minimum window from string "s" such that it contains the string "t".

================================================================================
                                Intuition & Explanation
================================================================================

1) Brute Force:
- Using two for loops we can have all the substring of S, we can match it with T (in terms of frequency mathching) and determine the minimum
substring.

2) Sliding Window
- you will get idea by reading the question it can be solved using the sliding window ?
then, how you will expand and shrink the window ?
- before that, we know that in sliding window with string question we use the map to determine the frequency and take decision, which is also required in these question.
now comes to the answer:
- first calculate the T's frequency. we have one counter, which determine how many characters we accomodate of T at any moment. counter = 3, 3 charaters of T is in the current window.
Expand window until we get counter == T.size(), so atleast we have one answer for it.
Shrink window: Any time string can have characters from T and not from T(garbage).
1) So if the garbage characters in start we need to reduce that.
2) if current window have more character which is also part of T, we can reduce that..., But we can't allow the window to loss any required character from T which can cause this (I mean counter < T.size())
ex::: aaaaaabc, T = abc... then current window have "aaaaaabc" we can reduce this starting "a...". For that we need keep track of frequency and decide...


Check the code!!



================================================================================
                          Approach & Time/Space Complexity
================================================================================

N = s.size()

1) Brute Force using priority_queue
Time: O(N^2*26)
Space: O(26)


2) Sliding Window
Time: O(N+M)
Space: O(26)

*/



class Solution {
public:
    string minWindow(string s, string t) {

        // base case
        if (s.size() < t.size())
            return "";

        int begin = 0, end = 0, N = s.size(), counter = 0; // Here, counter check if it contains all the element of t at a moment.
        int min_length = INT_MAX;
        int head = 0;       // head points to the start of substring which can be answer.

        // T's Frequenecy map
        int t_freq_map[128] = {0};
        for (auto ch : t) {
            t_freq_map[ch]++;
        }

        // S frequency map
        int f_freq_map[128] = {0};

        while (end < N) {

            // Expansion

            // current character
            char ch = s[end++];

            // ch is part of T then and only.
            if (t_freq_map[ch] > 0) {

                f_freq_map[ch]++;

                // Current addition will be part of the T then and only we increase counter. Ex: T = aab, S = aaaaaac.. we increase counter until first two a.
                if (f_freq_map[ch] <= t_freq_map[ch]) {
                    counter++;
                }
            }

            // Shrink the window

            // We have entire T in current window. counter determine to shrink the window or not.
            if (counter >= t.size()) {

                // Shrink based on the, freq matching.
                // Case 1: We remove all unecessary characters which are not part of T. t_freq_map[s[begin]] == 0
                // Case 2: Current window contains more than required element of T, then we start to shrink from begin to reduce the length.
                //         But at any cost, our reduced window should contain entire T.
                while (t_freq_map[s[begin]] == 0 || f_freq_map[s[begin]] > t_freq_map[s[begin]]) {
                    f_freq_map[s[begin]]--;
                    begin++;
                }

                // check window size and decide it.
                if (min_length > (end - begin)) {
                    min_length = (end - begin);
                    head = begin;
                }

            }

        }

        // base case, if no substring found return "".
        return min_length == INT_MAX ? "" : s.substr(head, min_length);
    }
};




// Sliding Window Template

int findSubstring(string s) {
    vector<int> map(128, 0);
    int counter; // check whether the substring is valid
    int begin = 0, end = 0; //two pointers, one point to tail and one  head
    int d; //the length of substring

    for () { /* initialize the hash map here */ }

    while (end < s.size()) {

        // expansion
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

