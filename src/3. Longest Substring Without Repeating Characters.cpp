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

Question : 3. Longest Substring Without Repeating Characters
Topic : Sliding Window
Problems : https://leetcode.com/problems/longest-substring-without-repeating-characters/description/

==============================> Explanation <=============================================

Brute Force:
- To get substring we can iterate the string using two for loops(i, j).
- And for each(i, j) we can check, substring is valid(witout repeating characters). If yes, compare with max_substring_length.
- We keep track of that max_substring_length.

Sliding Window Technique:
- Intuition behind this apporach is that,
- Using two pointer we keep track of window which must be valid at any time. When we add new element we check the validity of this window and
based on that we perform some operation so to keep it valid. Here, in the problem given that substring(not subsequence) so we can think of this apporach.
- Check the code!! It is strightforward when we violate the window, we again make it valid by moving begin pointer.

==============================> Approach and Time Complexity <============================

N = s.size()

1) Brute Force
Time: O(N^2), Worst case: O(N^3) => O(N^2) to reach that window, and O(N) to validate the string(where whole string is valid).
Space: O(1)

1) Two Pointer
Time: O(N)
Space: O(1), Constant space.

*/
class Solution {
public:
    int lengthOfLongestSubstring(string s) {

        int lft = 0, rht = 0, N = s.size();
        unordered_map<char, int> mp;
        int max_window = 0;

        while (rht < N) {

            // Current window consist s[rht] ?
            if (mp.count(s[rht])) {

                // Yes, remove it by updating left pointer. mp[s[rht]] -> last position of s[rht], we move after that.
                lft = max(lft, mp[s[rht]] + 1);
            }

            // update new position of s[rht].
            mp[s[rht]] = rht;

            // window is valid so, we can take maximum of it. NOTE: +1 is offset we need to add. Ex: |a b(L) c a(R)| => R - L => 2, Expected = 3.
            max_window = max(max_window, (rht - lft + 1));

            rht++;
        }

        return max_window;
    }
};


class Solution {
public:
    int lengthOfLongestSubstring(string s) {

        int lft = 0, rht = 0, N = s.size();
        unordered_map<char, int> mp;
        int max_window = 0;

        for (int rht = 0; rht < N; rht++) {

            if (mp.count(s[rht])) {
                lft = max(lft, mp[s[rht]] + 1);         // mp[s[rht]] -> last position of s[rht] + 1
            }

            mp[s[rht]] = rht;
            max_window = max(max_window, (rht - lft + 1));
        }

        return max_window;
    }
};




class Solution {
public:
    int lengthOfLongestSubstring(string s) {

        int begin = 0, end = 0, N = s.size();
        int mp[128] = {0};  // mp for letters, digits, symbols and spaces.
        int max_window = 0;

        while (end < N) {

            // New character added in window, mark in map.
            if (mp[s[end]] == 0) {
                mp[s[end]] = 1;
                end++;
            }
            else {

                // Same character cannot be added in window, so we have to move left pointer after that position, so unset all positions in path.
                // Our main goal is to keep window valid.
                while (mp[s[end]] != 0) {
                    mp[s[begin]]--;
                    begin++;
                }
            }

            max_window = max(max_window, end - begin);
        }

        return max_window;
    }
};