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

Question : 547. Number of Provinces
Topic : Graph, Pattern=Union-Find
Problems : https://leetcode.com/problems/number-of-provinces/description/?envType=problem-list-v2&envId=graph
==============================> Explanation <=============================================

Very clear that we have to find connected components of graph.

We can use the DFS, BFS and Union-Find as well to get that...

Check the code!!

==============================> Approach and Time Complexity <============================

1) Graph
Time: O(N+E)
Space: O(N+E)

 */


// approach-1, for DFS using extra space for visited array.
class Solution {
public:
    void dfs(int node, vector<vector<int>> &isConnected, vector<int> &vis) {
        vis[node] = 1;
        for (int it = 0; it < isConnected.size(); it++) {
            if (isConnected[node][it] == 1 && !vis[it]) {
                dfs(it, isConnected, vis);
            }
        }
    }

    int findCircleNum(vector<vector<int>>& isConnected) {
        int N = isConnected.size();
        vector<int> vis(N, 0);
        int count = 0;
        for (int node = 0; node < isConnected.size(); node++) {
            if (!vis[node]) {
                dfs(node, isConnected, vis);
                count++;
            }
        }
        return count;
    }
};

// approach-2, using DFS but using inplace memory for visited array.
class Solution {
public:
    void dfs(int node, vector<vector<int>> &isConnected) {
        isConnected[node][node] = 2;
        for (int it = 0; it < isConnected.size(); it++) {
            if (it != node && isConnected[node][it] == 1) {
                isConnected[node][it] = 2;
                isConnected[it][node] = 2;  // don't forget to mark the reverse edge as well, otherwise get TLE
                dfs(it, isConnected);
            }
        }
    }

    int findCircleNum(vector<vector<int>>& isConnected) {
        int count = 0;
        for (int node = 0; node < isConnected.size(); node++) {
            if (isConnected[node][node] != 2) {
                dfs(node, isConnected);
                count++;
            }
        }
        return count;
    }
};



// approach-3: Union Find
class UnionFind {

public:

    vector<int> parent;
    vector<int> rank;

    UnionFind(int n) {
        parent.resize(n, 0);
        rank.resize(n, 1);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int findParent(int u) {
        if (parent[u] == u)
            return u;
        return parent[u] = findParent(parent[u]);
    }

    int getParent(int u) {
        return parent[u];
    }

    void union_f(int u, int v) {
        int ulp_u = findParent(u);
        int ulp_v = findParent(v);
        if (ulp_u == ulp_v) return;
        if (rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
        }
        else if (rank[ulp_v] < rank[ulp_u]) {
            parent[ulp_v] = ulp_u;
        }
        else {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }
};




// union-find
class Solution {
public:

    int findCircleNum(vector<vector<int>>& isConnected) {

        int N = isConnected.size();

        UnionFind uf(isConnected.size());
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                // if (i, j) there is edge... then both must be part of single comp, so make it union.
                if (i != j && isConnected[i][j]) {
                    uf.union_f(i, j);
                }
            }
        }


        // Now count component, parent[u] == u.... all are diff comp
        int count = 0;
        for (int node = 0; node < N; node++) {
            if (uf.getParent(node) == node) {
                count++;
            }
        }

        return count;
    }
};