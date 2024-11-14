#include <bits/stdc++.h>
#define unsigned long long long long
#define REP(i,n) for(unsigned long long i = 0; i < n; i++)
#define REP1(i,n) for(unsigned long long i = 1; i <= n; i++)
#define debug cout << "Ok" << endl;
#define mod 1000000007

using namespace std;


/*
==============================> Description <=============================================

Question : 11_SSSP_DAG_Dijkstra_Algorithm
Topic : Graph
Problems :
==============================> Explanation <=============================================

Intuition behind algorithm is that,

Similar to other SSSP Problem, We start visiting nodes from "src" node. To decide which node to visit next, we use the
priority_queue which holds all promising nodes, and return the most optimistic node which have shortest distance till that time,
so using that node we perform the relxation on its' neighbors nodes(it).

Main idea is that,

    IN Priority_queue we hold this pair => {dist, node}, dist => distToSource

    PQ return a node, which have shortest distance from "src" node at any moment, so we visit that node first among
    all potential nodes, which are in queue. Mark that node as visited.

    So when we explore the neighbors nodes(it), with "node" as intermidatory node(which have shortest dist from src),

        we check, distToSource[node] + edgeCost(node->it) < distToSource[node],

                    if it is true, then we got better route to reach (it) node from (src) node via "node".

                        update the distance of,

                                distToSource[node] = distToSource[node] + edgeCost(node->it)

Time: O((V+E)logE) => In the worst case, we visit entire graph during relexation O(V+E), and pq holds all the edges(considering duplicates as well), so pq.top() take O(E) time)

=======================> Approach and Time Complexity <============================

1) Graph
Time:  O((V+E)logE)
Space: O(V)

 */


// 10: Dijkstra algorithm SSSP. (all edge weight should be non-negative)
void shortestPath(vector<pair<int, int>> adjList[], int V, int src) {

    // keep track of shortest distance from src node.
    vector<int> distToSource(V + 1, INT_MAX);

    // keep track of visited node... dijkstra select most promising node at a time from pq.
    // so once the node is visited, we don't change it distance.
    vector<int> visited(V + 1, 0);

    // (optional) to construct shortest path....
    vector<int> prev(V + 1, -1);

    // set the dist for src node as zero.
    distToSource[src] = 0;

    // {dist, node} min heap.
    priority_queue < pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> pq;

    // Add src node into the pq.
    pq.push({0, src});

    while (!pq.empty()) {

        int dist = pq.top().first;
        int node = pq.top().second;
        pq.pop();                                           // logE

        // mark the processed node as visited.
        visited[node] = 1;

        // (optional) in case end node is given....
        if (node == end)
            break;

        for (auto it : adjList[node]) {

            int nextNode = it.first;
            int edgeCost = it.second;

            // optimization... skip the visited node...
            if (visited[nextNode]) continue;

            // relexation....
            if (distToSource[node] + edgeCost < distToSource[nextNode]) {           // V+E => (V+E)*logE
                distToSource[nextNode] = distToSource[node] + edgeCost;
                pq.push({distToSource[nextNode], nextNode});        // push into the priority queue

                // (optional) set the curr node as previous node for nextNode.
                prev[nextNode] = node;
            }
        }
    }

    // distToSource contains shortest distance from source to all other nodes.

    // Construct path... For that end node is also given.... s
    vector<int> shortestPath;
    for (int at = end; at != src; at = prev[at]) {
        shortestPath.push_back(at);
    }
    reverse(shortestPath.begin(), shortestPath.end());

    // shortestPath hold the shortest path.....
}
