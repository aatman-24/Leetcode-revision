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

Question : 4_Cycle_detection_on_undirected_graph_using_DFS_BFS
Topic : Graph
Problems :
==============================> Explanation <=============================================

Pattern: BFS_DFS_Application

Intuition behind this algorithm is that,

When we apply bfs/dfs on the graph, during traversal, if we visit neighbors node, and
that is already visited by other node(except the parent), we found cycle.

In undirected graph, we have both edges(forward, reversal), so we don't consider reverse edge which again point to parent,
during travesal, so we keep track of parent, so we can ignore it during as potential neighbors.

==============================> Approach and Time Complexity <============================

1) Graph
Time: O(V+E)
Space: O(V)

 */



// DFS - Cycle Detection
bool checkForCycle(int node, int parent, vector<int> &vis, vector<int> adjList[]) {

    // Mark the current node as visited.
    vis[node] = 1;

    // Visit All the neighbour node of current node.
    for (auto it : adjList[node]) {

        // If it is not visited.
        if (!vis[it]) {
            if (checkForCycle(it, node, vis, adjList))
                return true;
        }
        // If it is visited and not the previou(parent) node. Means there is cycle already visited
        // Nodes comes again and it is not node where we come from the current node.
        else if (it != parent)
            return true;
    }

    // Not Found.
    return false;
}


bool isCycle(int V, vector<int> adjList[]) {

    vector<int> vis(V + 1, 0);

    for (int i = 1; i <= V; i++) {

        if (!vis[i]) {
            if (checkForCycle(i, -1, vis, adjList))
                return true;
        }

    }

    return false;
}

// BFS Cycle Detection
bool checkForCycle(int node, int V, vector<int> &visited, vector<int> adjList[]) {

    // Create queue for BFS. Here, <node, parent_node>
    queue<pair<int, int>> q;

    // Mark the first node where BFS start as visited and push into the queue.
    visited[node] = 1;
    q.push({node, -1});

    while (!q.empty()) {

        int node = q.front().first;
        int parent = q.front().second;
        q.pop();

        for (auto it : adjList[node]) {

            // If not visited. Visit it and add into the queue.
            if (!visited[it]) {

                // Here is Change from DFS.
                visited[it] = 1;
                q.push({it, node});
            }
            // While adjancent node of current node, is already visited and this(current_node) is not
            // parent means we found the cycle.
            else if (parent != it)
                return true;
        }
    }

    return false;
}

bool isCycle(int V, vector<int> adjList[]) {

    vector<int> vis(V + 1, 0);

    for (int i = 1; i <= V; i++) {

        if (!vis[i]) {
            if (checkForCycle(i, V, vis, adjList))
                return true;
        }

    }

    return false;
}