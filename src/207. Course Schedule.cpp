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

Question : 207. Course Schedule
Topic : Graph
Problems : https://leetcode.com/problems/course-schedule/description/
==============================> Explanation <=============================================

Pattern: Graph-Toposort

Basically, This question is application of topological sort: cycle detectation

As we know, toposort can only be applied to DAG, but if there is cycle then we won't able to visit all nodes because
of remaining node have internal dependency. Which we used as our benefit to decide there is cycle or not.

You just to have identify question in right way,

Given that there is some dependency ai -> bi... and we need to check if we can complete all the course or not... it is clear
indication toposort cycle detectation...

==============================> Approach and Time Complexity <============================

1) Topo-sort
Time: O(N+E)
Space: O(N)

 */

class Solution {
public:
	bool canFinish(int V, vector<vector<int>>& edges) {

		// Created an adjList, easy during edge relexation step.
		vector<int> adjList[V];
		for (auto it : edges) {
			adjList[it[0]].push_back(it[1]);
		}

		// Count Indegree.
		vector<int> indegree(V, 0);
		for (int i = 0; i < V; i++) {
			for (auto it : adjList[i]) {
				indegree[it]++;
			}
		}

		// Added initial node whose count is zero.
		int visitedNode_count = 0;
		queue<int> q;
		for (int i = 0; i < V; i++) {
			if (indegree[i] == 0) {
				q.push(i);
			}
		}

		while (!q.empty()) {
			int node = q.front(); q.pop();
			visitedNode_count++;
			for (auto it : adjList[node]) {
				indegree[it]--;
				if (indegree[it] == 0) {
					q.push(it);
				}
			}
		}

		// visitedNode_count != V, indicate there is cycle in graph and all nodes are not visited.
		return visitedNode_count == V;
	}
};

