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

Problem: NC_32_Pacific Atlantic Water Flow
Topic: BFS, DFS
Link: https://neetcode.io/problems/pacific-atlantic-water-flow

================================================================================
                                Problem Summary
================================================================================

Given an `m x n` grid of heights, determine which cells can flow water to both the **Pacific** and **Atlantic** oceans.
- Water can only flow from a cell to its **neighboring cell (up/down/left/right)** if the neighbor's height is **less than or equal** to the current cell.
- The Pacific Ocean touches the **top and left edges**, while the Atlantic touches the **bottom and right edges** of the grid.

Return a list of coordinates where water can flow to **both** oceans.

================================================================================
                                Intuition & Explanation
================================================================================

💡 **Smart Insight**:
Instead of simulating water flowing **from each cell to the oceans**, reverse the process —
simulate the ocean **reaching inward**, flowing **from ocean borders** into the matrix wherever conditions allow.

We know that all the nodes which are close to the ocean, can easily pour the water into the ocean. (0th level nodes)
Now, if we think logically all the nodes which are meeting condition(regarding height) and close to those 0th level nodes,
are also meeting condition.
So we can apply the BFS | DFS, and mark such nodes.
And we will do for both oceans seperately, we are allowed to move 4 directions.

🌊 Water flows from higher to lower or equal height.
Thus, for each ocean:
- Start a **DFS/BFS** from the border cells.
- Move inward only to neighbors with **height ≥ current** cell (reverse flow).

Do this for both the Pacific and Atlantic oceans independently.
Finally, collect the cells that are reachable from **both** oceans — these are the required coordinates.

================================================================================
                          Approach & Time/Space Complexity
================================================================================

Approach: Reverse BFS/DFS from ocean borders
Time Complexity: O(M * N) — each cell visited up to twice (once per ocean)
Space Complexity: O(M * N) — for visited matrices

*/


// DFS
class Solution {
public:

    int xx[4] = {1, 0, -1, 0};
    int yy[4] = {0, 1, 0, -1};

    bool isValid(int x_, int y_, int x, int y, vector<vector<int>> &grid, vector<vector<int>> &mat) {
        if (x_ < 0 || y_ < 0 || x_ >= grid.size() || y_ >= grid[0].size() || mat[x_][y_] == 1)
            return false;
        // (x, y) -> (x_, y_)
        return grid[x_][y_] >= grid[x][y];
    }

    void dfs(int x, int y, vector<vector<int>> &grid, vector<vector<int>> &mat) {
        // mark as visited
        mat[x][y] = 1;
        for (int i = 0; i < 4; i++) {
            int x_ = x + xx[i];
            int y_ = y + yy[i];
            if (isValid(x_, y_, x, y, grid, mat)) {
                dfs(x_, y_, grid, mat);
            }
        }
    }


    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {

        int m = heights.size(), n = heights[0].size();

        vector<vector<int>> pacific(m, vector<int>(n, 0));
        vector<vector<int>> atlantic(m, vector<int>(n, 0));

        // 0th row (meet to pacific)
        for (int j = 0; j < n; j++) {
            if (pacific[0][j] == 0) {
                dfs(0, j, heights, pacific);
            }
        }

        // 0th col (meet to pacific)
        for (int i = 0; i < m; i++) {
            if (pacific[i][0] == 0) {
                dfs(i, 0, heights, pacific);
            }
        }


        // m-1th row (meet to atlantic)
        for (int j = 0; j < n; j++) {
            if (atlantic[m - 1][j] == 0) {
                dfs(m - 1, j, heights, atlantic);
            }
        }


        // n-1th col (meet to atlantic)
        for (int i = 0; i < m; i++) {
            if (atlantic[i][n - 1] == 0) {
                dfs(i, n - 1, heights, atlantic);
            }
        }

        // Till here we marked all nodes, how many meeting both oceans in seperate matrix....

        vector<vector<int>> ans;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                // meeting both, then it is our answer.
                if (atlantic[i][j] && pacific[i][j]) {
                    ans.push_back({i, j});
                }
            }
        }

        return ans;
    }
};

// BFS

class Solution {
public:

    int xx[4] = {1, 0, -1, 0};
    int yy[4] = {0, 1, 0, -1};

    bool isValid(int x_, int y_, int x, int y, vector<vector<int>> &grid, vector<vector<int>> &mat) {
        if (x_ < 0 || y_ < 0 || x_ >= grid.size() || y_ >= grid[0].size() || mat[x_][y_] == 1)
            return false;
        return grid[x_][y_] >= grid[x][y];
    }


    void bfs(queue<pair<int, int>> q, vector<vector<int>> &ocean, vector<vector<int>> &grid) {

        while (!q.empty()) {

            auto [x, y] = q.front(); q.pop();

            // skip already visited cell
            if (ocean[x][y] == 1)
                continue;

            // mark it as visited.
            ocean[x][y] = 1;


            for (int i = 0; i < 4; i++) {
                int x_ = x + xx[i];
                int y_ = y + yy[i];
                if (isValid(x_, y_, x, y, grid, ocean)) {
                    q.push({x_, y_});
                }
            }
        }
    }

    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {

        int m = heights.size(), n = heights[0].size();

        vector<vector<int>> pacific(m, vector<int>(n, 0));
        vector<vector<int>> atlantic(m, vector<int>(n, 0));

        queue<pair<int, int>> pacQ, atlQ;

        for (int j = 0; j < n; j++) {
            pacQ.push({0, j});
            atlQ.push({m - 1, j});
        }

        for (int i = 0; i < m; i++) {
            pacQ.push({i, 0});
            atlQ.push({i, n - 1});
        }

        bfs(pacQ, pacific, heights);
        bfs(atlQ, atlantic, heights);

        vector<vector<int>> ans;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (atlantic[i][j] && pacific[i][j]) {
                    ans.push_back({i, j});
                }
            }
        }

        return ans;
    }
};