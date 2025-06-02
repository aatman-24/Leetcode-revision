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

Problem: NC_33_Surrounded Regions
Topic: BFS
Link: https://neetcode.io/problems/surrounded-regions

================================================================================
                                Problem Summary
================================================================================

In the given 2D board, we need to replace all regions of 'O' that are **completely surrounded** by 'X'.

Definitions:
- **Region**: A single 'O' or a group of connected 'O's.
- **Surrounded**: A region enclosed on all sides by 'X'.

However, if any cell in a region touches the **edge** of the matrix, then that region is **not** considered surrounded and should not be replaced.

Legend:
- 'X' → Surrounding boundary
- 'O' → Region to evaluate

================================================================================
                                Intuition & Explanation
================================================================================

This is similar to the idea used in **NC_32_Pacific Atlantic Water Flow** — we think in **reverse**.

If an 'O' is connected directly or indirectly to an edge, it cannot be surrounded. So:
1. Scan the boundary of the matrix (edges).
2. If an 'O' is found, perform a BFS/DFS from that cell to mark all connected 'O's as **safe** (i.e., cannot be converted).
3. After the BFS/DFS, iterate through the board:
   - Convert any remaining 'O' to 'X' (they are truly surrounded).
   - Restore marked safe 'O's to their original value.

================================================================================
                          Approach & Time/Space Complexity
================================================================================

Approach: BFS / DFS
Time Complexity: O(M * N) — each cell is visited at most once
Space Complexity: O(1) — if in-place; otherwise O(M * N) if visited matrix used

*/

class Solution {
public:

    int xx[4] = {1, 0, -1, 0};
    int yy[4] = {0, 1, 0, -1};

    void dfs(int x, int y, vector<vector<char>> &grid, char changeInto) {

        grid[x][y] = changeInto;

        for (int i = 0; i < 4; i++) {

            int x_ = x + xx[i];
            int y_ = y + yy[i];

            if (x_ < 0 || y_ < 0 || x_ >= grid.size() || y_ >= grid[0].size() || grid[x_][y_] != 'O')
                continue;

            dfs(x_, y_, grid, changeInto);
        }
    }


    void solve(vector<vector<char>>& board) {

        int m = board.size(), n = board[0].size();

        for (int j = 0; j < n; j++) {

            if (board[0][j] == 'O')
                dfs(0, j, board, 'Z');

            if (board[m - 1][j] == 'O')
                dfs(m - 1, j, board, 'Z');
        }

        for (int i = 0; i < m; i++) {

            if (board[i][0] == 'O')
                dfs(i, 0, board, 'Z');

            if (board[i][n - 1] == 'O')
                dfs(i, n - 1, board, 'Z');
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (board[i][j] == 'O') {
                    dfs(i, j, board, 'X');
                }
            }
        }


        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'Z')
                    board[i][j] = 'O';
            }
        }

    }
};