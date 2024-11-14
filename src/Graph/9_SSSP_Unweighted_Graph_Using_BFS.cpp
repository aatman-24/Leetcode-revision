#include <bits/stdc++.h>
#define unsigned long long long long
#define REP(i,n) for(unsigned long long i = 0; i < n; i++)
#define REP1(i,n) for(unsigned long long i = 1; i <= n; i++)
#define debug cout << "Ok" << endl;
#define mod 1000000007

using namespace std;



/*
==============================> Description <=============================================

Question : 9_SSSP_Unweighted_Graph_Using_BFS
Topic : Graph
Problems :
==============================> Explanation <=============================================

Pattern: SSSP-Unweighted Graph

In this question, we have given the graph and src, we have to find distance from "src" node to all other nodes.

Intuition behind this algorithm is that,

    We can get SSSP, by simply perforing BFS, starting from "src" node. As we know that, each edge cost 1 unit, BFS explore nodes which care close the node(compare to DFS),
    so we can peform simple relexation,

            dist[it] = 1 + dist[node], if we have edge "node -> it", where "node" is visited and "it" we are exploring..

=======================> Approach and Time Complexity <============================

1) Graph
Time: O(V+E)
Space: O(V)

 */


// A) Single Source Shortest Path for Undirected Graph (Use BFS + Relaxation)
// SSSP indicate we are finding shortest distance for src node to all nodes.
void shortestPath(vector<int> adjList[], int V, int src) {

    // Initalize the distance array with maximum distance.
    vector<int> dist(V + 1, INT_MAX);

    // src -> src, distance is zero.
    dist[src] = 0;

    // Use queue to perform BFS.
    queue<int> q;

    // Add src node in queue.
    q.push(src);

    while (!q.empty()) {

        int node = q.front(); q.pop();

        for (auto it : adjList[node]) {

            // relaxation
            if (dist[node] + 1 < dist[it]) {
                dist[it] = dist[node] + 1;
                q.push(it);
            }

        }
    }

    // print dist, hold the shortest distane for source node.
}