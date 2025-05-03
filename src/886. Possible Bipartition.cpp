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

Question : 886. Possible Bipartition
Topic : Graph
Problems : https://leetcode.com/problems/possible-bipartition/description/?envType=problem-list-v2&envId=graph
==============================> Explanation <=============================================

Again, DFS+BFS Application to check the graph is bipararite.. (split nodes in two group)..

Edge case is that, if person A dislike personB, then we need to add the reverse edge as well to make sure that
they don't go in same group....

==============================> Approach and Time Complexity <============================

1) Graph
Time: O(N+E)
Space: O(N+E)

 */

class Solution {
public:
    bool isBipartite(int node, vector<int> adjList[], vector<int> &color) {

        if (color[node] == -1) color[node] = 0;

        for (auto it : adjList[node]) {

            if (color[it] == -1) {
                color[it] = 1 - color[node];
                if (!isBipartite(it, adjList, color))
                    return false;
            }
            else if (color[node] == color[it]) {
                return false;
            }
        }

        return true;
    }

    bool possibleBipartition(int n, vector<vector<int>>& dislikes) {

        vector<int> adjList[n + 1];

        for (auto edge : dislikes) {
            adjList[edge[0]].push_back(edge[1]);
            adjList[edge[1]].push_back(edge[0]);
        }

        vector<int> color(n + 1, -1);

        for (int i = 1; i <= n; i++) {

            if (color[i] == -1) {

                if (!isBipartite(i, adjList, color)) {
                    return false;
                }
            }

        }
        return true;
    }
};