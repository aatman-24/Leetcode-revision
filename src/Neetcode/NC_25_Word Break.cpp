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

Problem: NC_25_Word Break
Topic: DP
Link: https://neetcode.io/problems/word-break

================================================================================
                                Problem Summary
================================================================================

Given a string `s` and a word dictionary `wordDict`, determine whether `s` can be
segmented into a space-separated sequence of one or more dictionary words.

You can reuse dictionary words as many times as needed.

================================================================================
                             Intuition & Explanation
================================================================================

The idea is to recursively check whether we can break the string `s` into valid
dictionary words:

- Start from index `0` and try all substrings `s(i, j)`.
- If the current substring exists in the dictionary, recursively check the rest
  of the string from index `j`.
- If we reach the end of the string, it means the entire string can be segmented
  successfully, so we return `true`.

We use **top-down recursion** with memoization or **bottom-up DP** to avoid
recomputing subproblems.

Although a **Trie** can be used for efficient prefix matching (in `O(L)` time per
lookup), we use an `unordered_map` here for `O(1)` average-case lookups due to hashing.

If hash-based lookup isn't allowed, a Trie is a good alternative.

================================================================================
                          Approach & Time/Space Complexity
================================================================================

Approach: Recursion
Time Complexity: O(2^N) (each position at ith, you take or don't take)
Space Complexity: O(N)

Approach: Top-Down
Time Complexity: O(N^2)
Space Complexity: O(N)

Approach: Bottom-up
Time Complexity: O(N^2)
Space Complexity: O(N)


NOTE:

So the total number of recursive calls is exponential in the worst case.

🔹 Worst-case time complexity (without memoization):

O(2^N)
- Every character may or may not form a word, leading to a decision tree with 2^N possibilities.

With Memoization
- O(N²)  // since there are N positions, and from each you try up to N substrings

*/

// Recursion
class Solution {
public:

    unordered_map<string, int> mp;

    bool helper(string s, int index) {

        if (index >= s.size()) return true;

        for (int j = index; j <= s.size(); j++) {

            string t = s.substr(index, j - index);

            if (mp.count(t)) {

                if (helper(s, j))
                    return true;

            }
        }

        return false;
    }


    bool wordBreak(string s, vector<string>& wordDict) {

        // place all the words into the map, so we can search in O(1)
        for (auto word : wordDict) {
            mp[word] = 1;
        }

        return helper(s, 0);
    }
};

// Top-Down
class Solution {
public:

    unordered_map<string, int> mp;

    int memo[201];

    bool helper(string s, int index) {

        if (index >= s.size()) return true;

        if (memo[index] != -1)
            return memo[index];

        for (int j = index; j <= s.size(); j++) {

            string t = s.substr(index, j - index);

            if (mp.count(t)) {

                if (helper(s, j))
                    return memo[index] = true;

            }
        }

        return memo[index] = false;
    }


    bool wordBreak(string s, vector<string>& wordDict) {

        // place all the words into the map, so we can search in O(1)
        for (auto word : wordDict) {
            mp[word] = 1;
        }

        memset(memo, -1, sizeof(memo));

        return helper(s, 0);
    }
};


// Bottom-up

class Solution {
public:

    unordered_map<string, int> mp;

    bool wordBreak(string s, vector<string>& wordDict) {

        // place all the words into the map, so we can search in O(1)
        for (auto word : wordDict) {
            mp[word] = 1;
        }

        int N = s.size();

        vector<bool> dp(N + 1, false);

        // base case
        dp[N] = true;

        for (int index = N - 1; index >= 0; index--) {

            for (int j = index; j <= N; j++) {

                string t = s.substr(index, j - index);

                if (mp.count(t)) {          // this can be done with trie in O(len(S))......

                    if (dp[j]) {
                        dp[index] = true;
                        break;
                    }

                }
            }

            // already done
            // dp[index] = false;
        }

        return dp[0];
    }
};



// DP + Trie (Used our Trie, this is for reference only)


class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool is_word = false;
};

class Trie {
public:
    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }

    void insert(string word) {
        TrieNode* node = root;
        for (char c : word) {
            if (!node->children.count(c)) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        node->is_word = true;
    }

    bool search(string& s, int i, int j) {
        TrieNode* node = root;
        for (int idx = i; idx <= j; ++idx) {
            if (!node->children.count(s[idx])) {
                return false;
            }
            node = node->children[s[idx]];
        }
        return node->is_word;
    }
};

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        Trie trie;
        for (string word : wordDict) {
            trie.insert(word);
        }

        int n = s.length();
        vector<bool> dp(n + 1, false);
        dp[n] = true;

        int maxLen = 0;
        for (string w : wordDict) {
            maxLen = max(maxLen, (int)w.size());
        }

        for (int i = n - 1; i >= 0; --i) {
            for (int j = i; j < min(n, i + maxLen); ++j) {
                if (trie.search(s, i, j)) {         // NOTE: Lookup of string can be done in O(len(S)) if we use trie..... apart from that it is dp.
                    dp[i] = dp[j + 1];
                    if (dp[i]) break;
                }
            }
        }

        return dp[0];
    }
};