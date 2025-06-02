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

Problem: NC_27_Longest Increasing Path in Matrix*
Topic: DP, Kahn's Algorithm
Link: https://neetcode.io/problems/longest-increasing-path-in-matrix

================================================================================
                                Problem Summary
================================================================================

You're given an M x N integer matrix. From each cell, you can move in 4 directions
(up, down, left, right), but only to a cell with a strictly **greater** value.

Return the **length of the longest increasing path** in the matrix.


================================================================================
                                Intuition & Explanation
================================================================================

The path must be increasing, so from each cell, you can move only to neighbors
with **greater** values. This leads to a natural **recursive** solution. From each
cell, you try all 4 directions, and recursively compute the longest path starting
from there. Use **memoization** to avoid recomputation.


1. Recursive (Naive DFS)

Idea: From each cell, try all increasing paths using DFS.
Problem: Very slow due to repeated work and exponential time.
Time Complexity: O(4^(M*N)) — too large.
Space Complexity: O(M*N) due to recursive call stack.

2. Top-down DP (Memoized DFS)

Idea:
DFS from every cell.
Use a memoization table dp[i][j] to store the longest increasing path from cell (i, j).
Avoid visiting the same state multiple times.
Key Point: You do not need to track "visited" since movement is only allowed to increasing neighbors (no cycles).
Time Complexity: O(M*N) — each cell is visited once.
Space Complexity: O(M*N) for memoization + recursion stack.

3. Bottom-up DP

Idea:
Build a list of all cells along with their values.
Sort them in increasing order.
Iterate over the sorted list and for each cell, update the DP value by checking all 4 neighbors that are smaller than the current cell.
Since we're building up from smaller values, dependencies are already computed.
Key Insight: Reverse thinking — instead of starting from larger values, start from smaller ones and propagate the path lengths forward.
Time Complexity: O(M*N*log(M*N)) (for sorting)
Space Complexity: O(M*N) for the DP ta

heart of algorithm:
        for (auto& [val, r, c] : cells) {

            for (auto& d : dirs) {

                int nr = r + d[0];
                int nc = c + d[1];

                if (nr >= 0 && nr < ROWS && nc >= 0 && nc < COLS && matrix[nr][nc] < matrix[r][c]) {
                    dp[r][c] = max(dp[r][c], dp[nr][nc] + 1);
                }
            }
        }


4. Topological Sort (Kahn’s Algorithm)

Idea:

Treat each cell as a node in a graph.
Add a directed edge from cell (i, j) to (x, y) only if matrix[x][y] > matrix[i][j].
This ensures a Directed Acyclic Graph (DAG).
Compute in-degrees and perform BFS level by level.
Longest path = number of BFS levels.
Key Point: All nodes with in-degree = 0 are the smallest cells and get processed first.
Time Complexity: O(M*N)
Space Complexity: O(M*N) for graph and queue.


Idea is that, we add the edge (i, j) -> (x, y) if.... mat[i, j] < mat[x, y].... so now when we start
unwind first all the nodes which are smallest in value unwind first(which have indegree 0)... so that
way we create the chain for all the nodes...and we keep track of maximum.


================================================================================
                          Approach & Time/Space Complexity
================================================================================

Approach: Recursion
Time Complexity: O(4^(M*N))
Space Complexity: O(M*N)

Approach: Top-down
Time Complexity: O((M*N))
Space Complexity: O(M*N)

Approach: Bottom-up
Time Complexity: O((M*N))
Space Complexity: O(M*N)

Approach: Recursion
Time Complexity: O((M*N))
Space Complexity: O(M*N)

*/


// Recurssion Approach
class Solution {
public:

    int MIN = -1e6;

    int dx[4] = { -1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    int support(vector<vector<int>>& matrix, int i, int j, int prev) {

        // out of bound
        if (i < 0 || j < 0 || i >= matrix.size() || j >= matrix[0].size())
            return 0;

        int current = matrix[i][j];

        // if current element less than prev, we can't get longest increasing path.
        if (current <= prev)
            return 0;

        // (i, j) doesn't get added in path in future, so we put negative value. (other way to mark as visited)
        matrix[i][j] = MIN;

        int maxi = 0;

        // max 4 neighbors we can have, so we get the maximum path out of them
        for (int k = 0; k < 4; k++) {

            int xx = i + dx[k];
            int yy = j + dy[k];

            maxi = max(maxi, support(matrix, xx, yy, current) + 1);
        }

        // backtracking: set the initial value again
        matrix[i][j] = current;

        return maxi;
    }


    int longestIncreasingPath(vector<vector<int>>& matrix) {

        int maxi = 0;
        int prev = -1;

        // we can start out path from each (i, j).... so we keep track of maxi...
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[0].size(); j++) {
                maxi = max(maxi, support(matrix, i, j, prev));
            }
        }

        return maxi;
    }
};


// Top-down Approach
class Solution {
public:

    int t[102][102];

    int MIN = -1e6;

    int dx[4] = { -1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    int support(vector<vector<int>>& matrix, int i, int j, int prev) {

        // out of bound
        if (i < 0 || j < 0 || i >= matrix.size() || j >= matrix[0].size())
            return 0;

        int current = matrix[i][j];

        // if current element less than prev, we can't get longest increasing path.
        if (current <= prev)
            return 0;

        // t[i][j] hold the longest increasing path starting from (i, j).... so this condition
        // needs to be check after above one, because it possible prev > current and still we return
        // t[i][j] if we put it above condition
        if (t[i][j] != -1)
            return t[i][j];

        // (i, j) doesn't get added in path in future, so we put negative value. (other way to mark as visited)
        // matrix[i][j] = MIN;

        int maxi = 1;

        // max 4 neighbors we can have, so we get the maximum path out of them
        for (int k = 0; k < 4; k++) {

            int xx = i + dx[k];
            int yy = j + dy[k];

            maxi = max(maxi, support(matrix, xx, yy, current) + 1);
        }

        // backtracking: set the initial value again
        // matrix[i][j] = current;

        return t[i][j] = maxi;
    }


    int longestIncreasingPath(vector<vector<int>>& matrix) {

        memset(t, -1, sizeof(t));

        int maxi = 0;
        int prev = -1;

        // we can start out path from each (i, j).... so we keep track of maxi...
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[0].size(); j++) {
                maxi = max(maxi, support(matrix, i, j, prev));
            }
        }

        return maxi;
    }
};


// Bottom-up Approach (Not in standard Way we do!!)
class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {

        int ROWS = matrix.size();
        int COLS = matrix[0].size();

        vector<vector<int>> dp(ROWS, vector<int>(COLS, 1));
        vector<tuple<int, int, int>> cells;

        // Store all cells with value and coordinates
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                cells.push_back({matrix[i][j], i, j});
            }
        }

        // Sort the cells in increasing order of their values
        sort(cells.begin(), cells.end());

        // Directions for 4 neighbors
        vector<vector<int>> dirs = {{ -1, 0}, {1, 0}, {0, -1}, {0, 1}};

        for (auto& [val, r, c] : cells) {

            for (auto& d : dirs) {

                int nr = r + d[0];
                int nc = c + d[1];

                if (nr >= 0 && nr < ROWS && nc >= 0 && nc < COLS && matrix[nr][nc] < matrix[r][c]) {
                    dp[r][c] = max(dp[r][c], dp[nr][nc] + 1);
                }
            }
        }

        int ans = 0;
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                ans = max(ans, dp[i][j]);
            }
        }

        return ans;
    }
};


// Kahns' Algorithm

// Idea is that, we add the edge (i, j) -> (x, y) if.... mat[i, j] < mat[x, y].... so now when we start
// unwind first all the nodes which are smallest in value unwind first(which have indegree 0)... so that
// way we create the chain for all the nodes...and we keep track of maximum.

class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {

        int ROWS = matrix.size(), COLS = matrix[0].size();

        vector<vector<int>> indegree(ROWS, vector<int>(COLS, 0));

        vector<vector<int>> directions = {{ -1, 0}, {1, 0},
            {0, -1}, {0, 1}
        };

        for (int r = 0; r < ROWS; ++r) {

            for (int c = 0; c < COLS; ++c) {

                for (auto& d : directions) {

                    int nr = r + d[0], nc = c + d[1];


                    // consider it as incoming edge for (r, c)
                    if (nr >= 0 && nr < ROWS && nc >= 0 && nc < COLS && matrix[nr][nc] < matrix[r][c]) {
                        indegree[r][c]++;
                    }
                }
            }
        }

        queue<pair<int, int>> q;
        for (int r = 0; r < ROWS; ++r) {
            for (int c = 0; c < COLS; ++c) {
                if (indegree[r][c] == 0) {  // push all the nodes with indegree 0... smallest nodes
                    q.push({r, c});
                }
            }
        }

        int LIS = 0;
        while (!q.empty()) {

            int size = q.size();

            for (int i = 0; i < size; ++i) {

                auto [r, c] = q.front();

                q.pop();

                // unwind
                for (auto& d : directions) {

                    int nr = r + d[0], nc = c + d[1];

                    // check the LIS condition
                    if (nr >= 0 && nr < ROWS && nc >= 0 && nc < COLS && matrix[nr][nc] > matrix[r][c]) {
                        if (--indegree[nr][nc] == 0) {
                            q.push({nr, nc});
                        }
                    }
                }
            }

            LIS++; // until while loop runs we are getting bigger and bigger longest path(BFS), nothing but level based traversing
        }
        return LIS;
    }
};