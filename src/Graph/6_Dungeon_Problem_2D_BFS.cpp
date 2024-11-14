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

Question : 6_Dungeon_Problem_2D_BFS
Topic : BFS
Problems :
==============================> Explanation <=============================================

Pattern: BFS_Application

Intuition behind this algo is that,

	We convert the given 2D Matrix(Maze) into the graph, so we can apply the BFS on that.

	Based upon question, we define which node can be neighbors,

		If we allow to move in 4 directions => we have 4 neighbors for any node maximum.

		If we allow to move in 8 directions(diagonal as well) => we have 8 neighbors.

	Simply, we will apply the BFS on maze(we don't convert it to graph), how(check on code).

==============================> Approach and Time Complexity <============================

1) BFS
Time: O(V^2)
Space: O(V^2)

 */


// We can also unwind the node from the queue based on level(the way we did in tree) whatever level we get when we
// reach the exit point can be consider as shortest distance
bool ableToFindExit(int maze[][], int N, int start_x, int start_y) {

	// maze[i][j] = 1, it means there is rock.
	// maze[i][j] = 2, it means exit cell.

	// To keep track visited cell, so we don't again push to the queue.
	int visited[N + 1][N + 1];
	memset(visited, 0, sizeof(visited));

	// Give 4 direction only, if given diagonal direction then these arrays become size of 8.
	int dx[] = { -1, 1, 0, 0};
	int dy[] = {0, 0, 1, -1};

	queue<pair<int, int>> q;
	q.push({start_x, start_y});

	int level = 1;          // minimum_distance to reach the exit cell.

	while (!q.empty()) {

		int size = q.size();

		for (int k = 0; k < size; k++) {

			auto it = q.front(); q.pop();
			int x = it.first, y = it.second;

			// found the exit point.
			if (maze[x][y] == 2) {

				// if require minimum_distance then return level... (you get it right...)
				// return level;

				return true;
			}


			for (int i = 0; i < 4; i++) {

				int xx = x + dx[i];
				int yy = y + dy[i];

				// out of bound any of parameter skip it.
				if (xx < 0 || yy < 0) continue;
				if (xx >= N || yy >= N) continue;

				// skip if there is rock or already visited cell.
				if (maze[xx][yy] == 1 || visited[xx][yy]) continue;

				// mark the current cell as visited, and into the queue for exploration.
				visited[xx][yy] = 1;
				q.push({xx, yy});

			}
		}

		level++;
	}

	return false;
}