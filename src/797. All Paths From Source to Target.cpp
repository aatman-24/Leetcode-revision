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

Question : 797. All Paths From Source to Target
Topic : Graph
Problems : https://leetcode.com/problems/all-paths-from-source-to-target/description/?envType=problem-list-v2&envId=graph
==============================> Explanation <=============================================

Basically, you have given "src" and "target" node, you just have to find all paths. We can apply the DFS direclty,
which give you all paths, just make sure during backtracking you unset the node which got visited so other path can
use it same node again.

==============================> Approach and Time Complexity <============================

1) Graph
Time: O(2^N) (You either add the node in path or don't add)
Space: O(N) (Stack depth)

 */

class Solution {
public:

    vector<vector<int>> allPaths;

    void dfs(int node, vector<vector<int>> adjList, vector<int> &pathVisited, vector<int> &curPath) {

        pathVisited[node] = 1;
        curPath.push_back(node);

        // reached target.
        if (node == adjList.size() - 1) {
            allPaths.push_back(curPath);
        }

        for (auto it : adjList[node]) {
            if (!pathVisited[it]) {
                dfs(it, adjList, pathVisited, curPath);
            }
        }

        pathVisited[node] = 0;
        curPath.pop_back();
    }


    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        int N = graph.size();
        vector<int> pathVisited(N, 0);
        vector<int> curPath;
        dfs(0, graph, pathVisited, curPath);
        return allPaths;
    }
};
