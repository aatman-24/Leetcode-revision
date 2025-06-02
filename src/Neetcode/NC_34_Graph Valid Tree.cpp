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

Problem: NC_34_Graph Valid Tree
Topic: BFS
Link: https://neetcode.io/problems/valid-tree

================================================================================
                                Problem Summary
================================================================================

Given an undirected graph, determine whether it forms a valid tree.

================================================================================
                                Intuition & Explanation
================================================================================

We know that a tree is a type of graph with the following properties:
1. It must be **acyclic** (no cycles).
2. It must be **connected** (only one component).

So to validate the graph as a tree, we check:
1. If a **cycle** exists → it's **not** a valid tree.
2. If the graph is **not fully connected** (i.e., more than one component) → it's **not** a valid tree.

Since the graph is undirected, we can use **DFS or BFS** to check for cycles and connectivity.

Another approach:
We can also use **Disjoint Set Union (DSU)**.
If we attempt to union two nodes and find they already share the same parent, it indicates a **cycle**.

================================================================================
                          Approach & Time/Space Complexity
================================================================================

Approach: BFS / DFS / Union-Find
Time Complexity: O(N + E)
Space Complexity: O(N + E)

*/
class Solution {
public:

    // dfs to detect the cycle
    bool isCycle(int node, int parent, vector<int> adjList[], vector<int> &visited) {
        visited[node] = 1;
        for (auto it : adjList[node]) {
            if (it == parent) continue;
            if (!visited[it]) {
                if (isCycle(it, node, adjList, visited)) {
                    return true;
                }
            }
            else {
                return true;
            }
        }
        return false;
    }

    bool validTree(int n, vector<vector<int>>& edges) {
        vector<int> adjList[n];
        for (auto it : edges) {
            int u = it[0];
            int v = it[1];
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }

        vector<int> visited(n, 0);

        // if there is cycle, it is not valid tree
        if (isCycle(0, -1, adjList, visited)) return false;

        // if no cycle, but more than one comp because all are not visited in single time, it is not a cycle
        return accumulate(visited.begin(), visited.end(), 0) == n;
    }
};



class Solution {
public:


    // bfs to detect the cycle
    bool isCycle(int N, vector<int> adjList[]) {

        vector<int> visited(N, 0);

        queue<pair<int, int>> q;
        q.push({0, -1});        // we can start from any node
        visited[0] = 1;
        int visitedNode = 0;


        while (!q.empty()) {

            auto node = q.front(); q.pop();

            visitedNode++;

            for (auto it : adjList[node.first]) {

                if (it == node.second) continue;

                if (!visited[it]) {

                    q.push({it, node.first});

                    visited[it] = 1;
                }

                else {

                    return false;
                }

            }

        }
        // in single run, it needs to visit all the source node, to confirm as single comp.
        return visitedNode == N;
    }




    bool validTree(int n, vector<vector<int>>& edges) {
        vector<int> adjList[n];
        for (auto it : edges) {
            int u = it[0];
            int v = it[1];
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }
        return isCycle(n, adjList);
    }
};
