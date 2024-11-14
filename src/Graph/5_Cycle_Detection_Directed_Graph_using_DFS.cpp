#include <bits/stdc++.h>
#define ll long long
#define REP(i,n) for(int i = 0; i < n; i++)
#define REP1(i,n) for(int i = 1; i <= n; i++)
#define debug cout << "Ok" << endl;
#define mod 1000000007

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

Question : 5_Cycle_Detection_Directed_Graph_using_DFS
Topic : DFS
Problems :
==============================> Explanation <=============================================

What is major differnce between the DFS of Directed and Undirected Graph ?

-> So In Un-Directed Graph there is no direction on edge so we consider it as bidirectional. But in the Directed graph,
there is direction given (u, v) as edge, it means edge has direction from u -> v.

Due to that, if one node is visited and again other node try to visit that node doesn't mean that there is cycle...
Ex:

1 -> 2 -> 3
     |    |
     4 -> 5

2 -> 4 -> 5 -> 3(Visited) (DFS call 1)
2 -> 3 (Already Visited) but it is not cycle. (DFS call 2)

In directed Graph there is cycle if and only if current node is getting visited two times in same path. If the path is different
then there is no cycle.

Ex:

1 -> 2 <- 3
     |    |
     4 -> 5

Here you can see... 1->2->4->5->3->2(already visited)... in single path(single dfs call) we are getting the same node... it means there is cycle.


Due to that,

We need to keep one more array, pathVisited[] which tells us whether current node is repeated earlier in same path or not. And also
whenever we backtrack that time we also backtrack from pathVisited.

==============================> Approach and Time Complexity <============================

1) DFS
Time: O(V+E)
Space: O(V)

 */


bool dfs(int node, vector<int> adjList[], vector<int> &visited, vector<int> &pathVisited) {

    // mark the current node as visited.
    visited[node] = 1;
    pathVisited[node] = 1;  // also mark the current node as path visited.

    for (auto it : adjList[node]) {

        if (!visited[it]) {
            // check if any of its adjacent node leads to cycle, yes then return true there is cycle.
            if (dfs(it, adjList, visited, pathVisited)) {
                return true;
            }
        }
        // node is visited already, check it is visited in same path or not
        else if (pathVisited[it] == 1) {
            return true
        }
    }

    // backtrack
    pathVisited[node] = 0;  // unwind from pathVisited
    return false;   // cycle notf oudn
}

bool isCycle(vector<int> adjList[], int V) {

    vector<int> visited(V + 1, 0);
    vector<int> pathVisited(V + 1, 0);

    for (int i = 1; i <= V; i++) {
        if (!visited[i]) {
            // check if starting from node i, can lead to cycle
            if (dfs(i, adjList, visited, pathVisited))
                return true;
        }

    }
    return false;
}

