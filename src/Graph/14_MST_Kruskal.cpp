#include <bits/stdc++.h>
#define unsigned long long long long
#define REP(i,n) for(unsigned long long i = 0; i < n; i++)
#define REP1(i,n) for(unsigned long long i = 1; i <= n; i++)
#define debug cout << "Ok" << endl;
#define mod 1000000007

using namespace std;





/*
==============================> Description <=============================================

Question : 14_MST_Kruskal
Topic : Graph
Problems :
==============================> Explanation <=============================================

Pattern: MST

Intuition behind algorithm is that,

    We select all EDGEs from graph such that, we visit all the nodes of graph.

    But constraint is that, whenever we pick up any edge (u -> v),
    u and v are not part of same set(I mean, "u" is visited & "v" is not visited, or vice versa).

=======================> Approach and Time Complexity <============================

1) Graph
Time: O(E*logE)(sorting edges) + O(E)*O(4)
Space: O(V) (Disjoint set)

 */




// 12: Kruskal Algorithm to find MST

class DisjointSet {

    vector<int> rank;
    vector<int> parent;

public:

    DisjointSet(int V) {
        rank.resize(V + 1, 0);
        parent.resize(V + 1, 0);
        for (int i = 1; i <= V; i++) {
            parent[i] = i;
        }
    }

    int findUParent(int u) {
        if (parent[u] == u)
            return u;
        return parent[u] = findUParent(parent[u]);  // path compression
    }

    void unionByRank(int u, int v) {

        int ulp_u = findUParent(u);
        int ulp_v = findUParent(v);

        if (ulp_u == ulp_v) continue;

        if (rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
        }
        else if (rank[ulp_v] < rank[ulp_u]) {
            parent[ulp_v] = ulp_u;
        } else {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }
}

int findMST(vector<vector<int>> adjList[], int V) {

    // convert the graph in {w, {u, v}} format.
    vector<pair<int, pair<int, int>>> edges;

    for (int u = 1; u <= V; u++) {
        for (auto it : adjList[u]) {
            int v = it[0];
            int w = it[1];
            edges.push_back({w, {u, v}})
        }
    }

    // sort the edges based on weight
    sort(edges.begin(), edges.end());

    // Create a Disjoint Set
    DisjointSet ds(V);

    // keep track of total weight
    int mstWeight = 0;

    // (optional) we can save the path as well...
    vector<pair<int, int>> mstEdges;

    for (auto it : edges) {

        int wt = it.first;
        int u = it.second.first;
        int v = it.second.second;

        // If U and V are not part of same set(it means we can add edge U->V)
        if (ds.findUParent(u) != ds.findUParent(v)) {
            mstWeight += wt;
            ds.unionByRank(u, v);
            mstEdges.push_back({u, v});
        }

    }

    // print mstEdges... which contains all the edges which are part of MST.

    return mstWeight;
}

