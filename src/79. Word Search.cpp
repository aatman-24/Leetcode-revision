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

Problem: 79. Word Search
Topic: Backtracking
Link: https://leetcode.com/problems/word-search/description/

================================================================================
                                Problem Summary
================================================================================

Given grind of characters, we have to find given word we can found in grid or not,

we allow to move horizontally and vertically....


================================================================================
                                Intuition & Explanation
================================================================================

Backtracking: Idea is that, we start with each (i, j) and try to match the word...

if we are able to match "ch" then we set it to "*" to mark that index as visited, so we won't
visit it again.... and again set it to "ch" when we backtrack...

we use the DFS_grind pattern to match the whole word....

Go through the code....

Just beware of the code style... to handle the case => [["a"]], word = "a"....

how we have put the // invalid case out of for loop....


================================================================================
                          Approach & Time/Space Complexity
================================================================================

Approach: Backtracking
Time Complexity: O(M*N*K)
Space Complexity: O(1)
*/



class Solution {
public:

    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    bool solve(int x, int y, int index, vector<vector<char>> &board, string word) {

        // it means we reached end of word...
        if (index == word.size())
            return true;

        // invalidate case, so we return false.
        if (x < 0 || y < 0 || x >= board.size() || y >= board[0].size() || board[x][y] != word[index]) {
            return false;
        }

        char ch = word[index];

        // mark as visited
        board[x][y] = '*';

        for (int i = 0; i < 4 ; i++) {

            int xx = dx[i] + x;
            int yy = dy[i] + y;

            if (solve(xx, yy, index + 1, board, word)) {
                return true;
            }
        }

        // backtrack
        board[x][y] = ch;

        return false;
    }

    bool exist(vector<vector<char>>& board, string word) {

        int N = board.size(), M = board[0].size();

        // try with each of the (i, j)
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (solve(i, j, 0, board, word)) {
                    return true;
                }
            }
        }
        return false;
    }
};