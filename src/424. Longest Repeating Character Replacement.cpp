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

Question : 424. Longest Repeating Character Replacement
Topic :Sliding Window
Problems : https://leetcode.com/problems/longest-repeating-character-replacement/description/

==============================> Explanation <=============================================

1) Brute Force:
- Find all substring using two for loops(i, j)... and for each substing create frquency map, and see, T(count) = L(size_of_substring) - (maxInsubstring), T <= K.. then it can be consider as valid substring.
Find maximum of such substring.


2) Sliding Window:
- We need to find longest substring in which K characters can be replaced with any characters.

Idea is that, At any moment current window have L characters, then to make it longest substring we need to replace the those characters which are in
minorites. Means, What we can replace is minorites which count is T(count) = L(size_of_window ) - (maxInWindow) ex: aabaac -> k = 1, "aabaa", b is minority for that window.

Expand: T < K (we can allow more minorites in current window, which can be replaced with maxInWindow). Here we can keep track of maxInWindow.

Shrink: T > K (We allowed more minorites, so we need to shrink the window, means maxInWindow need to decreased). Here, we can't know what is next maxInWindow, so we need to lookup in map. Because it
is not necessary that s[begin] reduced maxInWindow, is the correct maxInWindow. It can be anything else in that window.

For ex: aabbc => when we reach c, map(a->2, b->2), if shrink the window map(a->1, b->2), maxInWindow can't be same poiniting count of 'a'. It is still 2, pointing to 2. Tha't why look up is requried.


Check the code!!

==============================> Approach and Time Complexity <============================

N = s.size()

1) Brute Force
Time: O(N*K) = O(N) * O(26*N) = O(N^2)
Space: O(26)

2) Sliding Window
Time: O(N)
Space: O(26)


*/



class Solution {
public:

    int findMaximum(int map[]) {
        int N = 128, max_size = INT_MIN;
        for (int i = 0; i < 128; i++) {
            max_size = max(max_size, map[i]);
        }
        return max_size;
    }


    int characterReplacement(string s, int k) {

        int map[128] = {0};
        int begin = 0, end = 0, N = s.size(), maximumInWindow = 0, d = INT_MIN;

        while (end < N) {

            // add freq of current s[end].
            map[s[end]]++;

            // Keep track of maximum character in window.
            if (map[s[end]] > maximumInWindow) {
                maximumInWindow = map[s[end]];
            }

            // Shrink Window: sizeOfWindow - maxCharacterOfWindow > k -> It means that there are diff characters more than k, which can't be replaced.
            // Need to keep this <= K (so our window can't violate)
            while ((end - begin + 1) - maximumInWindow > k ) {
                map[s[begin++]]--;
                maximumInWindow = findMaximum(map);
            }

            d = max(d, (end - begin + 1));
            end++;
        }

        return d;
    }
};


// Template
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
