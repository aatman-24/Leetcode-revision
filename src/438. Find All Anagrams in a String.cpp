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

Question : 438. Find All Anagrams in a String
Topic : Sliding Window
Problems : https://leetcode.com/problems/find-all-anagrams-in-a-string/description/

==============================> Explanation <=============================================

Sliding Window Technique:

Ask is that, we need to find p(substring) in s(string) but p's characters can be in any order.

- It means that, we need to find all p's size windows in s(string) and check that it is anagrams or not by checking both frequency. That is only way we can
check that window have same characters in s(string) which match whole p.

- We can use map to store that frequency, we manage the window, and for every valid window we check whether that window consist anagram of p or not.

Check the code!!

==============================> Approach and Time Complexity <============================

N = s.size()

1) Sliding Window
Time: O(26*N) = O(N)
Space: O(26) = O(1)

*/



class Solution {
public:

    // Take constant time, O(26)
    bool is_anangram(int mp1[], int mp2[]) {

        for (int i = 0; i < 26; i++) {
            if (mp1[i] != mp2[i])
                return false;
        }

        return true;
    }


    vector<int> findAnagrams(string s, string p) {

        // If we are finding p's anagram in S, then s should have length equal or more than p.
        if (s.size() < p.size()) {
            return {};
        }

        // Two map to store the frequency.
        int p_map[26] = {0};
        int s_map[26] = {0};

        // Source frequency.
        for (auto ch : p) {
            p_map[ch - 'a']++;
        }

        int begin = 0, N = s.size(), M = p.size();
        vector<int> initial_positions;

        for (int end = 0; end < N; end++) {

            // manage the window.
            if ((end - begin) >= M) {
                s_map[s[begin] - 'a']--;
                begin++;
            }

            s_map[s[end] - 'a']++;

            // Take O(26)
            if (is_anangram(p_map, s_map))
                initial_positions.push_back(end - M + 1);
        }

        return initial_positions;
    }
};
