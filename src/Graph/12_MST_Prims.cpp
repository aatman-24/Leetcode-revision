#include <bits/stdc++.h>
#define unsigned long long long long
#define REP(i,n) for(unsigned long long i = 0; i < n; i++)
#define REP1(i,n) for(unsigned long long i = 1; i <= n; i++)
#define debug cout << "Ok" << endl;
#define mod 1000000007

using namespace std;



/*
==============================> Description <=============================================

Question : 12_MST_Prims
Topic : Graph
Problems :
==============================> Explanation <=============================================

Pattern: MST

Prim's/Krushkal algorithm is used to find the MST in Graph. MST(Minimum spanning tree) is tree in graph which
connect all the nodes (V) with (V-1) edges, such that summation of edge cost is minimum.

Approach-1(Brute Force):

Basiclly, in this approach we select V-1 edges which have minimum cost, one by one.

How we get the next edge ?

    key[i] => hold the minimum indegree edge, through ith node can be visited. It is map.

    => 1) Here, we first get node which have minimum edgeCost among all others edges. Then we mark that node as visited.
    => 2) Then we update map with minimum edgeCost to visit (it)th nodes,

            mstSet[it] == false(not visited) && (u->it)edgeCost < kev[it]
                key[v] =  (u->it)edgeCost

    That way, map key[] hold the edge, which have minCost to visit that ith node.


Approach-2:

    Simliar to above one, in this approach as well, we find V-1 edges which have minimum cost, one by one.

    How we get the next edge ?

    => previously, we keep track of map(which hold minimum edgeCost to visit particular node), and then we lookup in that
    and get the most optimistic node.

    Instead of that, we keep track of one priority_queue which do the same job by replacing above logic.

    Check the code...

Approach-3: (Use this directly)

    Similar to above one, We don't need to keep track of, V-1 nodes, we can simply ignore the node if it already visited.

    In simple words, we are selecting minimum edge(u->v) such that, u is already part of mst and v is not part of most.


    So we replace that countLogic with visited[].

=======================> Approach and Time Complexity <============================

1) Graph
Time: O(V+E)
Space: O(V)

 */



// O(N^2) - O(N).
void primsMST(int src, vector<pair<int, int>> adjList[], int N) {

    // Keep track of Parent.
    int parent[N];

    // Keep track of distance.
    int key[N];

    // Keep track of node is part of MST or not.
    int mstSet[N];

    // Summation of MST Path.
    int mstPathSum = 0;

    for (int i = 0; i < N; i++)
        key[i] = INT_MAX, mstSet[i] = false, parent[i] = -1;

    // Src node distance is zero and it parent is also -1.
    key[src] = 0;
    parent[src] = -1;

    // total N node and N-1 edge.
    for (int count = 0; count < N - 1; count++) {

        int u, min_dist = INT_MAX;

        for (int v = 0; v < N; v++)
            if (mstSet[v] == false && key[v] < min_dist)
                min_dist = key[v], u = v;


        mstSet[u] = 1;
        mstPathSum += min_dist;

        for (auto it : adjList[u]) {
            int v = it.first;
            int weight = it.second;

            if (mstSet[v] == false && weight < key[v])
                parent[v] = u; key[v] = weight;
        }

    }


    for (int i = 1; i < N; i++)
        cout << parent[i] << " - " << i << "\n";

    return 0;
}

// Optimized. Using Heap Data Structure we can efficently derive the min_dist node.
// O((V+E)*logE) - O(N).
void primsMST(int src, vector<pair<int, int>> adjList[], int N) {

    // Keep track of Parent.
    int parent[N];

    // Keep track of distance.
    int key[N];

    // Keep track of node is part of MST or not.
    int mstSet[N];

    // Summation of MST Path.
    int mstPathSum = 0;

    for (int i = 0; i < N; i++)
        key[i] = INT_MAX, mstSet[i] = false, parent[i] = -1;

    // minimum priority queue.
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;

    // Src node distance is zero and it parent is also -1.
    key[src] = 0;
    parent[src] = -1;
    pq.push({0, src});    // {weight, node}


    // total N node and N-1 edge. // N, Don't need to consider this.... because (N+E) we are already considering
    for (int count = 0; count < N - 1; count++) {

        int u = pq.top().second;
        int min_dist = pq.top().first;
        pq.pop();               // logN

        mstSet[u] = 1;
        mstPathSum += min_dist;

        for (auto it : adjList[u]) {    // (N + E)
            int v = it.first;
            int weight = it.second;

            if (mstSet[v] == false && weight < key[v]) {
                parent[v] = u; key[v] = weight;
                pq.push({key[v], v});
            }
        }

    }


    for (int i = 1; i < N; i++)
        cout << parent[i] << " - " << i << "\n";

    return 0;
}



// 11: Prim's algo for MST - O(V+E)*logE, O(V)
int mstCost(vector<int> adjList[], int V) {

    // check node is part of MST or not.
    vector<int> visited(V + 1, 0);

    // min heap
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // We are staring with 1st node.
    pq.push({0, 1});

    int mstSum = 0;

    while (!pq.empty()) {

        auto vertex = pq.top(); pq.pop();
        int node = vertex.second;
        int cost = vertex.first;

        if (visited[node]) continue;

        // node is not part of MST, add it and mark as visited.
        mstSum += cost;
        visited[node] = 1;

        for (auto it : adjList[node]) {
            if (!visited[it.first]) {       // we are checking "v" is visited or not when we see edge u->v.
                pq.push({it.second, it.first});
            }
        }

    }

    return mstSum;
}
