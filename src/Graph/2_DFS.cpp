#include <bits/stdc++.h>
#define ll long long
#define REP(i,n) for(int i = 0; i < n; i++)
#define REP1(i,n) for(int i = 1; i <= n; i++)
#define debug cout << "Ok" << endl;
#define mod 1000000007

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

Question : 2_DFS
Topic : Graph
Problems :
==============================> Explanation <=============================================

DFS => Depth First Search Algorithm.

DFS & BFS is Graph Traversal Algorith.

DFS focus on, to visit the nodes in depth wise, compare to BFS(Breadth Wise).

==============================> Approach and Time Complexity <============================



1) Graph
Time: O(V+E)
Space: O(V)

 */

void dfs(int node, vector<int> adj[], vector<int> &visited, vector<int> &dfsOrder) {
    visited[node] = 1;              // mark the unvisited node, as visited
    dfsOrder.push_back(node);       // store in dfsOrder
    for (auto it : adj[node]) {     // iterate over all the neighbors node
        if (!visited[it]) {         // If neighbors nodes are not visited perform dfs on that, otherwise skip it, we don't visit the visited node
            dfs(it, adj, visited, dfsOrder);
        }
    }
}

vector<int> depthFirstSearch(int V, vector<int> adj[]) {
    vector<int> visited(V + 1, 0);
    vector<int> dfsOrder;
    for (int i = 1; i <= V; i++) {          // If there are many components in graph, then we need to check for each node.
        if (!visited[i]) {                  // If node is not visited, it means it is from isolated component's node.
            dfs(i, adj, visited, dfsOrder);
        }
    }
    return dfsOrder;
}