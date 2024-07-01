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

Question : 395. Longest Substring with At Least K Repeating Characters
Topic : Sliding Window
Problems : https://leetcode.com/problems/longest-substring-with-at-least-k-repeating-characters/description/

==============================> Explanation <=============================================

1) Brute Force: Using two for loops we can generate the all substring and using frquency table we can find the longest substring in which all characters got repeated k times.

2) Sliding Window: (Doesn't easy to pick it up, remember this question and approach)
- You can guess it how to use the sliding window but don't get idea how to shrink/expand window.
- Idea is that, whatever answer is, that substring have [1 -> 26] uniqe characters, repeatead k times.
- So we check from uniqueCharacter=1 -> 26, and based on that we expand and shrink the window. Using few others variables we can check how many of elements
got repeated k times, and based on that we can find substring.



Check the code!!

==============================> Approach and Time Complexity <============================

N = s.size()

1) Brute Force using priority_queue
Time: O(N*K) = O(N^2)
Space: O(K)

*/


class Solution {
public:

    // Return max length substring which have distinct characters=uniqueChar, and each character can must be repeatd for mustRepeated(k) times.
    int longestSubstring(string s, int uniqChar, int mustRepeated) {

        // uniqueInWindow; how many unique characters in current window.
        // counter; how many uniqueInWindow have frequency > mustRepeated
        int uniqueInWindow = 0, counter = 0, N = s.size();
        int begin = 0, end = 0;
        int map[128] = {0};
        int max_length = 0;


        while (end < N) {

            // expand: count < uniqChar

            // Fresh Entry of new Character
            if (map[s[end]] == 0) {
                uniqueInWindow++;
            }

            map[s[end]]++;

            if (map[s[end++]] == mustRepeated) {
                counter++;
            }

            // shrink: count > uniqChar

            while (uniqueInWindow > uniqChar) {

                if (map[s[begin]] == mustRepeated) {
                    counter--;
                }

                // reduce the frequency.
                map[s[begin]]--;

                if (map[s[begin]] == 0) {
                    uniqueInWindow--;
                }

                begin++;
            }

            // we are checking, uniqueInWindow must be same to uniqChar, and all of them must be repeated k times.
            if (uniqueInWindow == uniqChar && uniqueInWindow == counter ) {
                max_length = max(max_length, end - begin);
            }
        }

        return max_length;
    }

    int longestSubstring(string s, int k) {
        int max_size = 0;
        for (int uniqChar = 1; uniqChar <= 26; uniqChar++) {
            max_size = max(max_size, longestSubstring(s, uniqChar, k));
        }
        return max_size;
    }
};