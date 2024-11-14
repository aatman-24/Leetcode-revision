#include <bits/stdc++.h>
#define unsigned long long long long
#define REP(i,n) for(unsigned long long i = 0; i < n; i++)
#define REP1(i,n) for(unsigned long long i = 1; i <= n; i++)
#define debug cout << "Ok" << endl;
#define mod 1000000007

using namespace std;


/*
==============================> Description <=============================================

Question : 19_SSSP_Bellman_ford_Negative_Edge
Topic : Graph
Problems :
==============================> Explanation <=============================================

Why Bellman Ford Algorithm For SSSP, When there is already Dijkstra ?
- Dijkstras's Algorithm find SSSP correctly, if and only if there is no negative edge. There is chance that,
with negative edge as well, dijkstrat give correct answer but not 100%. Another concern is that, if in graph
negative cycle is present then Dijkstrat won't work(each iteration we get the best node with negative dist).

Due to that, Bellman Ford Algorithm is used,
    - To get SSSP with negative edge
    - Detect negative cycle (if present we won't get SSSP for all nodes)

Intuition behind this algorithm is that,

    If there are V vertices in the graph, then shorest path from "src" node to any other node have maximum "V-1" edges.

    What we do is, we perform the edge relexations for all the edges, for V-1 times. Because in worst case, at each
    iteration we get one edge relexed and propagate that changes to last node, require V-1 iterations.

    After perform edge relexations V-1 times,

        We peform one more time, to check any of node dist[] got changed.

        If yes, then there is negative cycle present in graph.

        If no, we get the SSSP.

    If negative cycle present in graph,

        And to get all nodes affected due to that cycle, we can again perform V-1 times edge relexations, so
        changes of 1st edge relexations can reach to last node in worst case.


Single Edge: (u, v) -> weight

Edge Relaxation:

    if dist[u] + weight < dist[v]:
        dist[v] = dist[u] + weight

Algorithm:
- Perform Edge Relaxation (N-1) times.
- After (N-1) Edge Relaxation you got the SSSP for given source vertex.
Checking Negative Edge Cycle,
- After that peform one more time, if dist array change then there is negative weight cycle.
- Else:
    print(Dist Array).


Why (N-1) times?
- If there is N nodes, then the longest path contain the (N-1) edge. So in worst case
propogate the negative weight to last node take (N-1) iteration.

Example;

dist = [0, INF, INF, INF]

1st Cycle
1 ->(1) -> 2 ->(7) -> 3 ->(8) -> 4.
dist = [0, 1, INF, INF]

2nd Cycle
dist = [0, 1, 8, INF]

3rd Cycle (N-1) Cycle.
dist = [0, 1, 8, 16]

If After in 4th Cycle. If still dist is change then there is negative cycle due to that
dist is minimized.

Finally In short,

- perform the Edge Relaxation in N-1 Times.
- Peform one more time if dist array change then there is cycle. If not print the dist array as SSSP.


==============================> Approach and Time Complexity <============================

1. Graph
Time: O((E * (N-1)) > O((V+E)*logE)
Space: O(V)

*/

// 17: Bellman Ford Alogrithm (SSSP with negative cycle detecation)

vector<int> bellmanFordSSSP(vector<pair<int, int>> adjList[], int V, int src) {

    int inf = 1000000; // don't take INT_MAX due to addition operation

    // dist to source for all other nodes.
    vector<int> dist(V + 1, inf);

    // to reach src->src, take 0 efforts.
    dist[src] = 0;


    // step-1: N-1 time edge relexation
    for (int i = 0; i < N - 1; i++) {
        for (int node = 1; node <= V; node++) {
            for (auto it : adjList[node]) {
                // edge relexation
                if (dist[node] + it.second < dist[it.first]) {
                    dist[it.first] = dist[node] + it.second;
                }
            }
        }
    }


    // step-2: Detect negative cycle and find out all nodes whose is affected.
    bool isNegativeCyclePresent = false;
    for (int node = 1; node <= V; node++) {
        for (auto it : adjList[node]) {
            if (dist[node] + it.second < dist[it.first]) {
                dist[it.first] = -inf;
                isNegativeCyclePresent = true;
            }
        }
    }

    // negative cycle presetn find all the nodes who are got affected due ot that.
    if (isNegativeCyclePresent) {
        for (int i = 0; i < N - 2; i++) {           // 1 time we alread processed.
            for (int node = 1; node <= V; node++) {
                for (auto it : adjList[node]) {
                    if (dist[node] + it.second < dist[it.first]) {
                        dist[it.first] = - inf;
                    }
                }
            }
        }
    }


    // print all the nodes whose dist is <= -inf.

    return dist;
}
