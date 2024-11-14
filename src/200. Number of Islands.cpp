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
==============================> Description <=============================================

Question : 200. Number of Islands
Topic : Graph
Problems : https://leetcode.com/problems/number-of-islands/description/
==============================> Explanation <=============================================

Pattern: BFS on Maze

Basically, I need to find number of components in graph. I can apply DFS/BFS to count that. But BFS on Maze
Question is easy so apply that one.

==============================> Approach and Time Complexity <============================

1) Graph
Time: O(N+M)
Space: O(N+M)

 */

// Using Extra Space
class Solution {
public:
	int dx[4] = { -1, 1, 0, 0};
	int dy[4] = {0, 0, -1, 1};

	void bfs(int x, int y, vector<vector<char>>& grid,
	         vector<vector<int>>& visited) {

		int N = grid.size();
		int M = grid[0].size();

		visited[x][y] = 1;
		queue<pair<int, int>> q;
		q.push({x, y});

		while (!q.empty()) {

			int x_ = q.front().first;
			int y_ = q.front().second;
			q.pop();

			for (int i = 0; i < 4; i++) {

				int xx = x_ + dx[i];
				int yy = y_ + dy[i];

				if (xx < 0 || yy < 0 || xx >= N || yy >= M)
					continue;

				if (visited[xx][yy] || grid[xx][yy] == '0')
					continue;

				q.push({xx, yy});
				visited[xx][yy] = 1;
			}
		}
	}

	int numIslands(vector<vector<char>>& grid) {

		int N = grid.size();
		int M = grid[0].size();

		vector<vector<int>> visited(N, vector<int>(M, 0));

		int noOfComp = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (grid[i][j] == '1' && !visited[i][j]) {
					bfs(i, j, grid, visited);
					noOfComp++;
				}
			}
		}

		return noOfComp;
	}
};


// In-place Maze(grid) Used to keep track of node is visited or not.
// grid[x][y] = '2' (visited, so next time we can skip it)
// grid[x][y] = '1' (stone, we can use it to go next stone/land node)
// grid[x][y] = '0' (water, boundary we need to stop it here)
class Solution {
public:
	int dx[4] = { -1, 1, 0, 0};
	int dy[4] = {0, 0, -1, 1};

	void bfs(int x, int y, vector<vector<char>>& grid) {

		int N = grid.size();
		int M = grid[0].size();

		grid[x][y] = '2';
		queue<pair<int, int>> q;
		q.push({x, y});

		while (!q.empty()) {

			int x_ = q.front().first;
			int y_ = q.front().second;
			q.pop();

			for (int i = 0; i < 4; i++) {

				int xx = x_ + dx[i];
				int yy = y_ + dy[i];

				if (xx < 0 || yy < 0 || xx >= N || yy >= M)
					continue;

				if (grid[xx][yy] != '1')
					continue;

				q.push({xx, yy});
				grid[xx][yy] = '2';
			}
		}
	}

	int numIslands(vector<vector<char>>& grid) {

		int N = grid.size();
		int M = grid[0].size();

		int noOfComp = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (grid[i][j] == '1') {
					bfs(i, j, grid);
					noOfComp++;
				}
			}
		}

		return noOfComp;
	}
};
