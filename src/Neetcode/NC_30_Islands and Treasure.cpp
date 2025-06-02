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

Problem: NC_30_Islands and Treasure
Topic: BFS
Link: https://neetcode.io/problems/islands-and-treasure

================================================================================
                                Problem Summary
================================================================================

Given a 2D grid containing:
- **Blockers (walls or water cells)** that cannot be traversed,
- **Treasure nodes (source nodes)**,
- **Empty/common cells**,

The task is to update each common cell with the minimum distance to its nearest
treasure node. Movement is allowed only in four directions (up, down, left, right),
and we cannot pass through blocker cells.

================================================================================
                             Intuition & Explanation
================================================================================

Related Algorithm: Single Source Shortest Path (SSSP) in an unweighted graph
Reference:
https://github.com/aatman-24/Leetcode-revision/blob/main/src/Graph/9_SSSP_Unweighted_Graph_Using_BFS.cpp

This is a classic **SSSP** problem but with a twist: we are given **multiple source nodes** (treasure nodes).

Since the cost to move from one cell to another is fixed (= 1), we can efficiently apply
**multi-source BFS**, starting from all treasure nodes at once.

### Steps:
1. Identify all treasure nodes and add them to the BFS queue initially.
2. Start the BFS traversal:
   - For each neighboring cell, update its distance **only if**:
     - It's a common (non-blocker) cell, and
     - It hasn’t already been assigned a smaller distance.
3. This ensures all cells are filled with the minimum distance from the nearest treasure node.

This approach is optimal and avoids redundant BFS calls for each treasure node individually.

================================================================================
                          Approach & Time/Space Complexity
================================================================================

Approach 1: BFS from each treasure node individually
- Time Complexity: O((M * N)²)
- Space Complexity: O(1)

Approach 2: **Multi-Source BFS** (Recommended)
- Time Complexity: O(M * N)
- Space Complexity: O(1) (excluding queue and visited structures)

*/

// BFS
class Solution {
public:

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    int visited = -1 * 1e6;

    void bfs(int i, int j, vector<vector<int>> &grid) {

        queue<pair<int, int>> q;

        q.push({i, j});
        int dist = 0;

        while (!q.empty()) {

            int size = q.size();

            for (int k = 0; k < size; k++) {

                int x = q.front().first;
                int y = q.front().second;
                q.pop();

                for (int p = 0; p < 4; p++) {

                    int xx = dx[p] + x;
                    int yy = dy[p] + y;

                    // out of bound
                    if (xx < 0 || yy < 0 || xx >= grid.size() || yy >= grid[0].size())
                        continue;

                    // water cell OR treasure cell
                    if (grid[xx][yy] == -1 || grid[xx][yy] == 0)
                        continue;

                    // closer treasure chest
                    if (grid[xx][yy] > grid[x][y] + 1) {
                        grid[xx][yy] = 1 + grid[x][y];
                        q.push({xx, yy});
                    }
                }

            }

            dist++;
        }

    }


    void islandsAndTreasure(vector<vector<int>>& grid) {

        int N = grid.size(), M = grid[0].size();

        for (int i = 0; i < N; i++) {

            for (int j = 0; j < M; j++) {

                if (grid[i][j] == 0) {

                    bfs(i, j, grid);

                }


            }
        }

    }
};




// multi source BFS
class Solution {
public:

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    void islandsAndTreasure(vector<vector<int>>& grid) {

        int N = grid.size(), M = grid[0].size();

        queue<pair<int, int>> q;

        for (int i = 0; i < N; i++) {

            for (int j = 0; j < M; j++) {

                if (grid[i][j] == 0) {

                    // push all the treasures nodes together
                    q.push({i, j});

                }
            }
        }


        while (!q.empty()) {

            int x = q.front().first;
            int y = q.front().second;
            q.pop();

            for (int p = 0; p < 4; p++) {

                int xx = dx[p] + x;
                int yy = dy[p] + y;

                // out of bound
                if (xx < 0 || yy < 0 || xx >= grid.size() || yy >= grid[0].size())
                    continue;

                // water cell[blockers] OR treasure cell[we can't update the source node distance]
                if (grid[xx][yy] == -1 || grid[xx][yy] == 0)
                    continue;

                // relexation
                if (grid[xx][yy] > grid[x][y] + 1) {
                    grid[xx][yy] = 1 + grid[x][y];
                    q.push({xx, yy});
                }
            }
        }

    }
};
