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

Problem: NC_36_Word Ladder
Topic: BFS
Link: https://neetcode.io/problems/word-ladder

================================================================================
                                Problem Summary
================================================================================

Given:
- A `beginWord`, a `endWord`, and a list of `wordList` (dictionary words).

Task:
Transform `beginWord` into `endWord` by changing **only one letter at a time**, such that each transformed word exists in the `wordList`.
Return the **minimum number of transformations** (hops) needed to reach `endWord` from `beginWord`.
If it is not possible, return 0.

================================================================================
                            Intuition & Explanation
================================================================================

A valid transformation:
- Only one character is changed at a time.
- The resulting word must exist in the given `wordList`.

### 🔹 Approach 1: Brute-force BFS

- For each word, try replacing each character with letters `a` to `z`.
- If the new word exists in the dictionary and hasn't been visited, enqueue it.
- Repeat this BFS process until `endWord` is found.

This approach checks all possible one-character transformations directly, which can be inefficient when the word list is large.

### 🔹 Approach 2: Optimized BFS using Word Patterns

- Instead of generating all 26 × M possibilities for each word:
    - Preprocess the word list to create a graph using patterns.
    - A pattern replaces one character with a wildcard `*`.
      E.g., "cat" → `*at`, `c*t`, `ca*`

- Build a mapping:
    - `pattern -> list of words` that match this pattern.
    - Example: `*at` → ["cat", "bat"]

- During BFS, for each word:
    - Generate its patterns (e.g., "c*t").
    - Look up all words that share that pattern and visit them next.

This skips over unnecessary character replacements and directly jumps to connected words.

================================================================================
                    Time & Space Complexity Analysis
================================================================================

Let:
- N = number of words in `wordList`
- M = average word length

🔸 Brute-force BFS:
- Time:  **O(N² × M)** — each word may lead to ~N valid transformations
- Space: **O(N)** — visited set and queue

🔸 Optimized BFS (using pattern graph):
- Time:  **O(N × M²)** — build pattern graph in O(N×M), and process M patterns per word during BFS
- Space: **O(N × M)** — storing pattern graph and visited map

*/

// Brute Force: BFS
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {

        // insert the word into the mp, so we can search in in O(1) time.
        unordered_map<string, int> dict;
        for (auto word : wordList) {
            dict[word] = 1;
        }

        // endWord is not given, then we cannot reach there.
        if (!dict.count(endWord)) return 0;

        // keep track of visited word.
        unordered_map<string, int> visited;

        // queue
        queue<string> q;

        // first lets add the beginWord and try out bfs.
        q.push(beginWord);
        visited[beginWord] = 1;

        int level = 1;

        while (!q.empty()) {                        // O(N^2) q size can grow upto O(N^2) in worst case.

            int size = q.size();

            for (int p = 0; p < size; p++) {

                string word = q.front(); q.pop();

                if (word == endWord) return level;

                // we are going to replace ith characters with [a-z]
                for (int i = 0; i < word.size(); i++) {         // 26 * M

                    for (char ch = 'a';  ch <= 'z'; ch++) {

                        string nextWord = word;
                        nextWord[i] = ch;

                        if (dict.count(nextWord) && !visited.count(nextWord)) {

                            visited[nextWord] = 1;

                            q.push(nextWord);
                        }

                    }

                }

            }

            level++;
        }

        // if we reach here, it means we haven't found target  word.
        return 0;
    }
};



// Brute Force: BFS
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {

        unordered_map<string, int> words;


        // pattern: [word1, word2], adjList graph
        unordered_map<string, vector<string>> patternGraph;
        for (auto word : wordList) {
            words[word] = 1;
            for (int i = 0; i < word.size(); i++) {
                string pattern = word;
                pattern[i] = '*';
                patternGraph[pattern].push_back(word);  // edge: *at => cat, bat
            }
        }

        // endWord is not given in list, then we cannot reach there.
        if (!words.count(endWord)) return 0;

        // keep track of visited word.
        unordered_map<string, int> visited;

        // queue
        queue<string> q;

        // first lets add the beginWord and try out bfs.
        q.push(beginWord);
        visited[beginWord] = 1;

        int level = 1;

        while (!q.empty()) {                                // q size can not grow more than O(N)

            int size = q.size();

            for (int p = 0; p < size; p++) {                // M => M * N

                string word = q.front(); q.pop();

                if (word == endWord) return level;

                // we are going to replace every ith characters with *, to form the pattern, and we get all those word which mathc the patern
                for (int i = 0; i < word.size(); i++) {    // M => M * M * N

                    string pattern = word;
                    pattern[i] = '*';

                    for (auto nextWord : patternGraph[pattern]) {

                        if (!visited.count(nextWord)) {

                            q.push(nextWord);

                            visited[nextWord] = 1;
                        }

                    }
                }

            }

            level++;
        }

        // if we reach here, it means we haven't found target  word.
        return 0;
    }
};