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

Question : 20_ASSP_Floyd_Warshall_Algorithm
Topic : Graph
Problems :
==============================> Explanation <=============================================

Floyd Warshall Algorithm is All pair shortest path algorithm.

Intuition:

It use the "incremental path improvement".

=> Basically, It tell us that try every vertex as intermidatory node and choose the best one.

A1 -> A5 then I can try every vertex...
A1 -> A2 + A2 -> A5
A1 -> A3 + A3 -> A5
A1 -> A4 + A4 -> A5

Along with that,
The algorithm builds up the solution iteratively, improving path estimates step
by step by considering increasingly longer paths with more intermediate nodes.

It begins with no intermediate nodes and only considers direct paths.
Then, it checks if adding one node as an intermediate node can improve
the shortest path between pairs, then two nodes, and so forth.

iteration = 0 => direct edge (u -> v)
iteration = 1 => dp[u][v] => minimum((u -> i) -> (i -> v))
iteration = 2 => dp[u][v] => minimum((u->i->j) -> (j -> k -> v))
    What I mean is that, for iteration=2, when we again put all node as intermidatory
    node that time we are putting the chain of two nodes as intermidatory, because
    we are using the result of previous iteration.
    Ex:
    A1 -> A3 => A1 -> A2 + A2 -> A3 => min(A1->A0->A2 , A1->A5->A2)(A1->A2)(This is already calculated and one of the lowest stored in A1->A2 so we use that) + A2->A3


And to propogate the change to every other node we need to peform same thing N(total_vertex) times. (incremental path build up)

A1 -> A2 -> A3 -> A4 -> A5... this is path.. okay during first iteration suppose A1 got updated with best value, which is
also works for all other nodes who is depend on that.. to propagate A1 change to A5 we need to peform same thing
5 times so each time one of the node got changes which can be propogate to next node during next iteration.

A1 -> A3 => A1 -> A2 + A2 -> A3 => min(A1->A0->A2 , A1->A5->A2)(A1->A2)(This is already calculated and one of the lowest stored in A1->A2 so we use that) + A2->A3

And also we are using the dp(memo) table to use the result we previsouly calculated...
A1 -> A3 => A1 -> A2 + A2 -> A3 => min(A1->A0->A2 , A1->A5->A2)(This is already calculated and one of the lowest stored in A1->A2 so we use that) + A2->A3

We can use the dp[k][V+1][V+1] as memo table... start from k = 0(base case) -> V.
Space: O(V^3)
(in-place)but we can reduce that, we know each time we are using previous state(k-1) to compute k state result... so it can be reduce to O(V^2).

How to detect negative cycle ?
From Bellman Ford we know that... propogate negative cycle to all nodes again we need to run same things one more time.

How to construct path to reach A -> B, C->D any nodes pair ?
(Check the code)

==============================> Approach and Time Complexity <============================


1) Floyd Warshall
Time: O(V^3)
Space: O(V^3) -> O(V^2) (We can use upto 100 vertex only.. to much heavy)

 */


vector<vector<int>> floydWarshallAlgo(vector<pair<int, int>> adjList[], int V) {

    // keep track of shortest distance from A->B
    vector<vector<int>> dp(V, vector<int>(V, 0));

    // Reused to construct path
    vector<vector<int>> next(V, vector<int>(V, 0));

    // 1) Setup the adjMat so we can use that....(base-iteration(k=0))
    for (int u = 0; u < V; u++) {
        for (auto v : adjList[u]) {
            dp[u][v.first] = v.second;      // (node, wt)
            next[u][v.first] = v.first;     // Visit (U->V) means go to V node after U.
        }
    }

    // 2) Heart of algorithm: Iterate V times to get the shortest distance between all nodes.. considering each node as intermidatory node
    for (int k = 0; k < V; k++) {
        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                // Relexation considring k as intermidatory node.
                if (dp[u][k] + dp[k][v] < dp[u][v]) {
                    dp[u][v] = dp[u][k] + dp[k][v];
                    next[u][v] = next[u][k];
                }
            }
        }
    }


    // (optional if asked) 3) Cycle Detecation (Propagate change to last node)
    bool isNegativeCycle = false;
    for (int k = 0; k < V; k++) {
        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                // Relexation considring k as intermidatory node. (if relexation happen there is cycle)
                if (dp[u][k] + dp[k][v] < dp[u][v]) {
                    isNegativeCycle = true;
                    dp[u][v] = -INF;
                    next[u][v] = -1;
                }
            }
        }
    }


    // (optional if asked) 4) Reconstruct path between two nodes.
    int start = u; // (given in question)
    int end = v; // (given in question)

    // there is negative cycle affected this node... no path found
    if (dp[start][end] == -INF) return {};

    vector<int> path;   // to store the path.

    for (int at = start; at != end, at = next[at][end]) {
        if (at == -1) return {}; // negative cycle affected this one
        path.push_back(at);
    }
    path.push_back(end);

    return path;

}