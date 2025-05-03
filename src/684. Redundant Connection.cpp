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

Question : 684. Redundant Connection
Topic : Graph
Problems : https://leetcode.com/problems/redundant-connection/description/?envType=problem-list-v2&envId=graph
==============================> Explanation <=============================================

Idea is that, to get that additional edge, we need to find node which is visited two times, because in tree every
node can be visited one time with one incoming edge..so we use that knowledge on our benefit.

So such kind of feature DisjointSet provide, as we are taking one edge at time and making disjoint set.. if we get
two nodes which are already part of same set.. it means that edge is extra...because we are visiting..node which are already
part of tree...

Also, given that.. if multiple answer possible we need to select last edge...so we just override the additionEdge variable.

==============================> Approach and Time Complexity <============================

1) Graph
Time: O(N+E)
Space: O(N+E)

 */

class DisjointSet {

    vector<int> parent, rank;

public:

    DisjointSet(int N) {
        parent.resize(N + 1, 0);
        rank.resize(N + 1, 1);
        for (int i = 1; i <= N; i++) {
            parent[i] = i;
        }
    }

    int findParent(int u) {
        if (parent[u] == u)
            return u;
        return parent[u] = findParent(parent[u]);
    }

    // return true, if both are not part of same set.
    // return false, if both are part of same set.
    bool union_(int u, int v) {

        int ulp_u = findParent(u);
        int ulp_v = findParent(v);

        if (ulp_u == ulp_v)
            return false;

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
        return true;
    }
};

class Solution {
public:

    int MAX_N = 1000;

    vector<int> findRedundantConnection(vector<vector<int>>& edges) {

        DisjointSet ds(MAX_N);

        vector<int> additionalEdge;

        for (auto it : edges) {

            if (!ds.union_(it[0], it[1])) {
                additionalEdge = it;
            }

        }

        return additionalEdge;
    }
};