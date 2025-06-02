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

Problem: NC_28_Max Area of Island
Topic: BFS
Link: https://neetcode.io/problems/max-area-of-island

================================================================================
                                Problem Summary
================================================================================

Given a 2D binary matrix, the task is to find the largest island (i.e., the
maximum area of connected 1's). An island is surrounded by water (0's) and is
formed by connecting adjacent 1's horizontally or vertically.

================================================================================
                           Intuition & Explanation
================================================================================

Related Problem: Number of Islands

This problem involves finding the largest connected component in a grid, which
is a common use case for graph traversal algorithms like BFS, DFS, or Disjoint Set.

We iterate through each cell in the matrix. For every cell with a value of 1
that hasn't been visited, we perform a BFS (or DFS) to explore the full extent
of the island. While traversing, we mark visited cells to avoid reprocessing
them and count the size of the current island. Throughout the process, we
maintain a variable to track the maximum area encountered.

**Key Insight:**
Whenever dealing with connected components in a grid, consider using BFS, DFS,
or Disjoint Set.

================================================================================
                          Approach & Time/Space Complexity
================================================================================

Approach: BFS
Time Complexity: O(N * M), where N is the number of rows and M is the number of columns
Space Complexity: O(1) (excluding recursion/queue stack which can go up to O(N * M) in worst case)

*/

class Solution {
public:

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    int bfs(int x, int y, vector<vector<int>> &grid) {

        queue<pair<int, int>> q;
        q.push({x, y});

        // mark as visited
        grid[x][y] = 2;

        // keep track of area covered.
        int area = 0;

        while (!q.empty()) {

            int x_ = q.front().first;
            int y_ = q.front().second;

            area++;

            q.pop();

            for (int i = 0; i < 4; i++) {

                int xx = x_ + dx[i];
                int yy = y_ + dy[i];

                if (xx < 0 || yy < 0 || xx >= grid.size() || yy >= grid[0].size())
                    continue;

                if (grid[xx][yy] == 2 || grid[xx][yy] == 0)
                    continue;

                q.push({xx, yy});

                // mark as visited, so other can't push same (xx, yy) in queue.
                grid[xx][yy] = 2;

            }

        }

        return area;
    }


    int maxAreaOfIsland(vector<vector<int>>& grid) {

        int maxArea = 0;

        for (int i = 0; i < grid.size(); i++) {

            for (int j = 0; j < grid[0].size(); j++) {

                if (grid[i][j] == 1) {
                    maxArea = max(maxArea, bfs(i, j, grid));
                }
            }
        }

        return maxArea;

    }
};
