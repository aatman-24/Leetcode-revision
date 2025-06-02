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

Problem: NC_31_Rotting Fruit
Topic: BFS
Link: https://neetcode.io/problems/rotting-fruit

================================================================================
                                Problem Summary
================================================================================

Given a grid, determine the **minimum number of minutes** that must elapse until all
fresh oranges become rotten. Each minute, any fresh orange adjacent to a rotten one becomes rotten.

================================================================================
                                Intuition & Explanation
================================================================================

🔗 Related Algorithm: Single Source Shortest Path (SSSP) in an unweighted graph
📌 Reference:
https://github.com/aatman-24/Leetcode-revision/blob/main/src/Graph/9_SSSP_Unweighted_Graph_Using_BFS.cpp

This problem is essentially asking for the **maximum distance (in minutes)** from any
initial rotten orange to the farthest fresh orange — since that's the last one to rot.

We model this as a graph where:
- Each cell is a node.
- Valid adjacent moves (up/down/left/right) are edges.
- We apply **multi-source BFS** starting from all rotten oranges (value `2`).

How timer we are counting ?

Basically, given that we have to return the minimum number of minutes elapse, to convert all
into the rotten ones. It means, if we start at 0th second, and in first round all are become
rottens, then it means 0th minutes must be elpased to convert all....

Same way, if we are 2nd minutes, and all are rotten at 2nd minutes, then our ans is 2, we don't need
to perform timer++.

Acutally, if there is someting in queue for that we do the timer++, if nothing then dont inc timer.
This logic aligns with how time propagates in BFS level-by-level.

================================================================================
                          Approach & Time/Space Complexity
================================================================================

Approach: Multi-source BFS
Time Complexity: O(N * M) — each cell is visited once
Space Complexity: O(N * M) — for the queue and visited states

*/


class Solution {
public:

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    int orangesRotting(vector<vector<int>>& grid) {

        int M = grid.size(), N = grid[0].size();

        int freshOrange = 0;

        queue<pair<int, int>> q;

        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == 2) {
                    q.push({i, j});         // pushed all rotten orange
                }
                if (grid[i][j] == 1) freshOrange++;
            }
        }

        // Edge case
        if (freshOrange == 0)
            return 0;

        // no of minutes, starting from 0th minutes
        int timer = 0;

        while (!q.empty()) {

            int size = q.size();

            for (int k = 0; k < size; k++) {

                int x = q.front().first;
                int y = q.front().second; q.pop();

                for (int d = 0; d < 4; d++) {

                    int xx = x + dx[d];
                    int yy = y + dy[d];

                    if (xx < 0 || yy < 0 || xx >= M || yy >= N)
                        continue;

                    // if cell is empty || already rotten we are going to skip it.
                    if (grid[xx][yy] == 0 || grid[xx][yy] == 2)
                        continue;

                    q.push({xx, yy});
                    grid[xx][yy] = 2; // make it rotten (mark as visited)
                    freshOrange--;    // we are making the fresh orange to rotten one.
                }

            }

            // You only increment the timer after processing a level if there are still oranges left to process in the next minute. That’s why this line is there:
            // this for the next round
            if (!q.empty()) timer++;
        }

        return freshOrange != 0 ? -1 : timer;
    }
};