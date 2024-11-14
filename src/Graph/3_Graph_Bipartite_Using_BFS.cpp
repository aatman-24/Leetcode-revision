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
Question : 5. Bipartite Graph using BFS.

/*
==============================> Explanation <=============================================
Bipartite Graph: Using Two color if you colored the graph, such that no adjacent Node have
same color then it is called Bipartite Graph.


- LOGIC -> If graph contain the cycle and its length is odd it means your graph can not
be Bipartite Graph.

       -> If there is no cycle or length is even the graph is Bipartite Graph.

- Check on GFG more.



Time -> O(N+E). Visit all the nodes and Edge.
Space -> O(N+E)(adj List) + O(N)[color array] + O(N)[queue]  = O(N+E)

*/


/*
==============================> Edge Case <=============================================

*/


/*
==============================> Description <=============================================

Question : 3_Graph_Bipartite_Using_BFS_AND_DFS
Topic : Graph
Problems :
==============================> Explanation <=============================================

Pattern: BFS_APPLICATION

Bipartite Graph: Using Two color if you colored the graph, such that no adjacent Node have
same color then it is called Bipartite Graph.

Intuition behind the algorithm is that,

    If Graph contain the cycle, and that cycle is odd length, It means one of two adjancents node
    have same color. It is not biparatite graph.

    If Graph contain no cycle, or have even length cycle, we are find, and grpah is biparatite.

==============================> Approach and Time Complexity <============================
1) BFS
Time: O(V+E)
Space: O(V)

 */


vector<int> breadthFirstSearch(vector<int> adj[], int V) {

    // keep track of visited node, we don't visit the visited node again
    // -1 -> not visited, 0 -> colored, 1 -> colored
    vector<int> color(N + 1, -1);

    // Need to check for each node, due to disconnect componet is possible in graph.
    for (int i = 1; i <= V; i++) {

        // perform traversal on not visited node only.
        if (color[i] == -1) {

            queue<int> q;
            q.push(i);

            // color the starting node with any color.
            color[i] = 1;

            while (!q.empty()) {

                int node = q.front(); q.pop();

                for (auto it : adj[node]) {

                    // only add if that node is not visited. (To avoid cycle trapping)
                    if (color[it] == -1) {
                        q.push(it);
                        color[it] = 1 - visited[node]; // alternavtive color 0 and 1.
                    }
                    // already visited node have same color the current node have...
                    else if (color[it] == color[node]) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}