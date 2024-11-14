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

Question : 1_BFS
Topic : Graph-BFS
Problems :
==============================> Explanation <=============================================

BFS is Graph Traversal Algorithm, simliar to DFS.

Here Focus is on to visit all neighbors nodes first, compare to DFS.

==============================> Approach and Time Complexity <============================

1) BFS
Time: O(V+E) + O(V+E) = O(V+E)
Space: O(V) + O(V) = O(V)

 */



// Version-2

vector<int> breadthFirstSearch(vector<int> adj[], int V) {

    // keep track of visited node, we don't visit the visited node again
    vector<int> visited(N + 1, 0);

    vector<int> bfsOrder;

    // Need to check for each node, due to disconnect componet is possible in graph.
    for (int i = 1; i <= V; i++) {
        // perform traversal on not visited node only.
        if (!visited[i]) {
            queue<int> q;
            q.push(i);
            visited[i] = 1;
            while (!q.empty()) {
                int node = q.front(); q.pop();
                bfsOrder.push_back(node);
                for (auto it : adj[node]) {
                    // only add if that node is not visited. (To avoid cycle trapping)
                    if (!visited[it]) {
                        q.push(it);
                        visited[it] = 1;
                    }
                }
            }
        }
    }
}