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

Problem: NC_35_Number of Connected Components in an Undirected Graph
Topic: BFS
https://neetcode.io/problems/count-connected-components

================================================================================
                                Problem Summary
================================================================================

Need to find total Number of Connected Components in an Undirected Graph.


================================================================================
                                Intuition & Explanation
================================================================================

Need to find total no connected comp of graph, we can use the dfs/bfs to do that.

================================================================================
                          Approach & Time/Space Complexity
================================================================================

Approach: DFS
Time Complexity: O(N+E)
Space Complexity: O(N+E)

*/


class Solution {
public:

    void dfs(int node, int parent, vector<int> adjList[], vector<int> &visited) {
        visited[node] = 1;
        for (auto it : adjList[node]) {
            if (it == parent) continue;
            if (!visited[it]) {
                dfs(it, node, adjList, visited);
            }
        }
    }

    int countComponents(int n, vector<vector<int>>& edges) {
        vector<int> adjList[n];
        for (auto it : edges) {
            int u = it[0];
            int v = it[1];
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }
        vector<int> visited(n, 0);
        int comp = 0;
        for (int node = 0; node < n; node++) {
            if (!visited[node]) {
                comp++;
                dfs(node, -1, adjList, visited);
            }
        }
        return comp;
    }
};
