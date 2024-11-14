#include <bits/stdc++.h>
#define unsigned long long long long
#define REP(i,n) for(unsigned long long i = 0; i < n; i++)
#define REP1(i,n) for(unsigned long long i = 1; i <= n; i++)
#define debug cout << "Ok" << endl;
#define mod 1000000007

using namespace std;

/*
==============================> Description <=============================================

Question : 17_bridge_in_graph
Topic : Graph
Problems :
==============================> Explanation <=============================================

Finding Bridge and Articulation point in graph, are application of Tarjan's Algorithm.

Bridge: Bridge in graph is the edge, if we break that, graph is divided more than one componenents.

Basically, It use the tarjan algorithm to find the bridges in graph.

As we know, Tarjan algorithm used these two array.
ids[], low_link[]

    ids[node] => It is just DFS order in which we visit the nodes.
    low_link[node] => lowest_id of node can be reached from current "node" without going through parent node.

Bridge Found: When the current "node" adjacent node cannot reach to any ("current node or previous nodes of current "node") without
using (node -> it) edge. Then if we break that edge... sub-graph contain it is separated from the main graph.

so we checking that,

    low_link[it] > timeofInsertion[node]. (Bridge) (Indicate that "it" doesn't have any other edge who is pointing to main graph, apart from (node->it) edge)

Perform DFS.

Time =
Space =


==============================> Approach and Time Complexity <============================

1. Graph
Time: O(N+E)(DFS)
Space: O(N)(insertionTime) + O(N)(low_link) + O(N)(visited) + O(N)(Aux) = O(N)

  */




// 15. Detecting Bridge in graph.. (Tarjan algorithm application)

void dfs(int node, int parent, int &timer, vector<int> adjList[], vector<int> &ids, vector<int> &low_link, int &countOfBridges) {

    // mark as visited and update all the ids and low_link.
    visited[node] = 1;
    ids[node] = low_link[node] = timer;
    timer++;

    for (auto it : adjList[node]) {

        // Skip the parent edge.
        if (it == parent) continue;

        if (!visited[it]) {

            // peform dfs first.
            dfs(it, timer, adjList, ids, low_link, countOfBridges);

            // update the low_link.. minimum among all children.
            low_link[node] = min(low_link[node], low_link[it]);

            // Check for bridge.
            if (low_link[it] > ids[node]) {
                // cout << node << "-->" << it << endl; (bridge)
                countOfBridges++;
            }
        }
        else {
            // already visited node, have the lowest_value so update the low_link by considering its id.
            low_link[node] = min(low_link[node], ids[it]);
        }
    }
}

int getTotalNumberOfBridges(vector<int> adjList[], int V) {

    // keep track of visited node.
    vector<int> visited(V + 1, 0);

    // Keep track of DFS order
    vector<int> ids(V + 1, 0);

    // keep track of lowest node can be reached by "ith" node witout passing through parent
    vector<int> low_link(V + 1, 0);

    int timer = 1;
    int countOfBridges = 0;

    for (int i = 1; i <= V; i++) {
        if (!visited[i]) {
            dfs(i, -1, timer, adjList, visited, ids, low_link, countOfBridges)
        }
    }

    return countOfBridges;
}
