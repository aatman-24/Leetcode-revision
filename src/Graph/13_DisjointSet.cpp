#include <bits/stdc++.h>
#define unsigned long long long long
#define REP(i,n) for(unsigned long long i = 0; i < n; i++)
#define REP1(i,n) for(unsigned long long i = 1; i <= n; i++)
#define debug cout << "Ok" << endl;
#define mod 1000000007

using namespace std;



/*
==============================> Description <=============================================

Question : 13_DisjointSet
Topic : Graph
Problems :
==============================> Explanation <=============================================

DisjointSet is Data Strcuture, which basically peroform this operation,
    union(u, v) =>  make nodes u and v part of same set.
    isPartofSameSet(u, v) => check both are part of same set or not.

Path Compression(Optimization):
    - So when we are finding the ultimate parent that time, it takes O(logN) time to get the parent. But,
    using path compression each node in path points to ultimate parent directly.. so next time when we get parent of any node
    from tha path.. we can get in O(1) time.

Why connect to smaller set to larger one ? (Think without considering path compression)
    - If we connect larger set to smaller set, in that case that findParent will take more
    time, because larger tree already have greater height than smaller one... so it height won't be
    increase...but if we add larger to smaller... we are increasing the height... which directly affect into time complexity.

But we know optimization... so above one is not much create any impact.

But wait if that's the case.. can we use the size of set instead of rank.

We will add the smaller set(by size) to the larger set.

---

Most of time it take O(1) and but new path is explored first time that time it take O(logN).

So amarotized tiem complexity is = O(4*alpha) = O(1) (constant) we can consider.

Time = O(4*alpha) = O(4) = Constant (for any operation )
Space = O(N)

=======================> Approach and Time Complexity <============================

1) Graph
Time: O(4*alpha)
Space: O(V)

 */


// Using rank.
class DisjointSet {

    // Declare the required array as private
    vector<int> rank;       // keep track of rank, rank(u) > rank(v).. means the set which contain u is bigger than v.
    vector<int> parent;     // keep track of ultimate parent.

public:

    DisjointSet(int V) {

        // Rank is set to zero.
        rank.resize(V + 1, 0);
        parent.resize(V + 1, 0);

        // Initially all node are parent of itself.
        for (int i = 1; i <= V; i++) {
            parent[i] = i;
        }
    }

    int findUltimateParent(int u) {
        if (parent[u] == u)
            return u;
        return parent[u] = findUltimateParent(parent[u]);       // Optimization: path compression
    }

    void unionByRank(int u, int v) {

        // Find the ultimate parent of both nodes.
        int ulp_u = findUltimateParent(u);
        int ulp_v = findUltimateParent(v);

        // Both are part of one set already.
        if (ulp_u == ulp_v) return;

        // Compare the ranks and make it union, by joining smaller set into bigger set.
        if (rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;      // join ulp_u -> ulp_v
        }
        else if (rank[ulp_v] < rank[ulp_u]) {
            parent[ulp_v] = ulp_u;  // join ulp_v -> ulp_u
        }
        else {
            parent[ulp_v] = ulp_u; // rank are same, you can pick up any one.
            rank[ulp_u]++;         // increaes the rank of ulp_u, because you joint ulp_v -> ulp_u
        }
    }

    // Check both u and v are part of same union set or not.
    bool isPartOfSameSet(int u, int v) {
        int up = findUltimateParent(u);
        int uv = findUltimateParent(v);
        return up == uv;
    }
}


// Using size instead of rank.
class DisjointSet {

    // Declare the required array as private
    vector<int> size;       // keep track of size, size(u) > size(v).. means the set which contain u is bigger than v.
    vector<int> parent;     // keep track of ultimate parent.

public:

    DisjointSet(int V) {

        // Size is set to one... all nodes have its own set which has size 1.
        size.resize(V + 1, 1);
        parent.resize(V + 1, 0);

        // Initially all node are parent of itself.
        for (int i = 1; i <= V; i++) {
            parent[i] = i;
        }
    }

    int findUltimateParent(int u) {
        if (parent[u] == u)
            return u;
        return parent[u] = findUltimateParent(parent[u]);       // Optimization: path compression
    }

    void unionBySize(int u, int v) {

        // Find the ultimate parent of both nodes.
        int ulp_u = findUltimateParent(u);
        int ulp_v = findUltimateParent(v);

        // Both are part of one set already.
        if (ulp_u == ulp_v) return;

        // Compare the size and make it union, by joining smaller set into bigger set.
        if (size[ulp_u] < size[ulp_v]) {
            // join ulp_u -> ulp_v, increase the size of ulp_v.
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u]
        }
        else {
            // join ulp_v -> ulp_u, increase the size of ulp_u.
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v]
        }
    }

    // Check both u and v are part of same union set or not.
    bool isPartOfSameSet(int u, int v) {
        int up = findUltimateParent(u);
        int uv = findUltimateParent(v);
        return up == uv;
    }
}