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

Problem: 49. Group Anagrams
Topic: Hashing
Link: https://leetcode.com/problems/group-anagrams/description/

================================================================================
                                Problem Summary
================================================================================

Given an array of strings, group the anagrams together.
An anagram is a word or phrase formed by rearranging the letters of another, such as "eat" and "tea".

================================================================================
                                Intuition & Explanation
================================================================================

### Brute Force Approach:
- For each string, compare it with every other string to check if they are anagrams.
- To check if two strings are anagrams:
  - Ensure they have the same length.
  - Count character frequencies or sort both strings and compare.
- Track visited strings to avoid redundant grouping.

⛔ Inefficient for large inputs due to O(N²) comparisons.

### Optimized Approach (Hashing):
- Key Insight: All anagrams, when sorted, produce the same string.
- Use a hash map where:
  - **Key** = sorted version of the string.
  - **Value** = list of original strings that map to this key.
- Iterate through the input list, sort each string, and group them into the map.

📌 Optimization Tip:
Instead of sorting (O(M log M)), a character frequency count (e.g., using a 26-size array or string key) can be used to reduce overhead — essentially acting as a custom bucket sort.

================================================================================
                          Approach & Time/Space Complexity
================================================================================

Let N = number of strings, M = maximum length of any string

🔸 Brute Force:
- Time Complexity: O(N² * M)
- Space Complexity: O(1) (excluding output)

🔸 Hashing (Sorted String Key):
- Time Complexity: O(N * M log M)
- Space Complexity: O(N * M)

🔸 Hashing (Frequency Count Key — Bucket Sort Idea):
- Time Complexity: O(N * M)
- Space Complexity: O(N * M)

*/


// Hashing
class Solution {

public:

    vector<vector<string>> groupAnagrams(vector<string>& strs) {

        // sorted_string => {anagrams}
        unordered_map<string, vector<string>> mp;

        for (auto s : strs) {

            string key = s;
            sort(key.begin(), key.end());

            mp[key].push_back(s);
        }


        vector<vector<string>> groups;

        for (auto it : mp) {

            groups.push_back(it.second);

        }

        return groups;

    }
};



// Optimization of Sorting using counter sort
class Solution {

public:

    // utils from counter sort
    static string strSort(string s) {

        int counter[26] = {0};
        for (char c : s)
            counter[c - 'a']++;

        string t;
        for (int c = 0; c < 26; c++)
            t += string(counter[c], c + 'a'); // t += (counter[c] times c+'a')

        return t;
    }

    vector<vector<string>> groupAnagrams(vector<string>& strs) {

        // sorted_string => {anagrams}
        unordered_map<string, vector<string>> mp;

        for (auto s : strs) {

            string key = strSort(s);

            mp[key].push_back(s);
        }


        vector<vector<string>> groups;

        for (auto it : mp) {

            groups.push_back(it.second);

        }

        return groups;

    }
};
