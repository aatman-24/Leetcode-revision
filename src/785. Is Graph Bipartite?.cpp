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

Question : 785. Is Graph Bipartite?
Topic : DP
Problems : https://leetcode.com/problems/is-graph-bipartite/description/
==============================> Explanation <=============================================

Standard problem on checking graph is Bipartite or not.

We can solve this using BFS | DFS.

Here I used BFS.

==============================> Approach and Time Complexity <============================

1) BFS
Time: O(N+E)
Space: O(N)

 */


// Checking BiPartite using the, BFS
class Solution {
public:

    bool isBipartiteSupport(int node, vector<vector<int>> graph, vector<int> &visited) {
        color[node] = 1;
        queue<int> q;
        q.push(node);
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            for (auto it : graph[node]) {
                if (color[it] == -1) {
                    q.push(it);
                    color[it] = 1 - color[node];
                }
                else if (color[node] == color[it]) {        // "it" is already color, checking have same/diff color than current node.
                    return false;
                }
            }
        }
        return true;
    }

    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> color(n, -1);
        for (int i = 0; i < n; i++) {
            if (color[i] == -1) {
                if (!isBipartiteSupport(i, graph, color)) {
                    return false;
                }
            }
        }

        return true;
    }
};