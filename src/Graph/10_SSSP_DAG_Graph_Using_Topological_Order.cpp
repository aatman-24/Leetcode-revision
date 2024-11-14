#include <bits/stdc++.h>
#define unsigned long long long long
#define REP(i,n) for(unsigned long long i = 0; i < n; i++)
#define REP1(i,n) for(unsigned long long i = 1; i <= n; i++)
#define debug cout << "Ok" << endl;
#define mod 1000000007

using namespace std;
/*
==============================> Description <=============================================

Question : 10_SSSP_DAG_Graph_Using_Topological_Order
Topic : Graph
Problems :
==============================> Explanation <=============================================

Pattern: SSSP

Intuition behind this algorithm is that,

If there is graphs looks like, Z -> A -> B -> C, and we need to find SSSP with src node "A".

So using topoOrder, we get the order in which we need to traverse the graph. Because it is
obvious that, all the nodes who are reachable from src node "A", have dependency as src
node "A", so in topoOrder src node "A" comes before these reachable nodes. and node Z is
unreachable from A, so Z comes before A in topoOrder.

Why It works ?
- Toposort visit all the node first, which does not have any dependency on it. So by doing that we find
all the nodes which can be reach from the source node. Because those node which are reachable from the source
node, have dependency as source node... so first source node unwind during topo order iteration... later we can use
the relaxation step to get shortest distnace.

And node which can not reach by the source node is popped from the stack first(visited first in topo order) and have distane as INT_MAX(never relaxation happen on that).

- And once any node distance is calculated(it is not INT_MAX) then we can use this node as intermidatory
for others once. The node which is not reached by the source node distance is INT_MAX so it can never
used as intermidatory node.

=======================> Approach and Time Complexity <============================

1) Graph
Time: O(V+E)
Space: O(V)

 */

// 1. Using TopoStack.
// pair<int,int> = {neighbour_node, edge_weight}
void findTopoSort(int node, int vis[], stack<int> &st, vector<pair<int, int>> adjList[]) {

    // Mark the current node as visited.
    vis[node] = 1;

    for (auto it : adjList[node]) {

        // If its neighbour is not visited.
        if (!vis[it.first]) {
            findTopoSort(it.first, vis, st, adjList);
        }
    }

    // add into stack after all its adjancent node inserted into the stack.
    st.push(node);

}




void shortestPath(int src, int N, vector<pair<int, int>> adjList[]) {

    // Find the toposort. So we can use its stack for finding the shortest path.
    int vis[N] = {0};
    stack<int> st;
    for (int i = 0; i < N; i++)
        if (!vis[i])
            findTopoSort(i, vis, st, adjList)



            // Finding the shortest path using that stack.
            int dist[N];
    for (int i = 0; i < N; i++) dist[i] = INT_MAX;

    // source node distance zero.
    dist[src] = 0;

    while (!st.empty()) {

        int node = st.top(); st.pop();

        // If current node is already visited first then and only it can be intermidatory node for others.
        if (dist[node] != INT_MAX) {

            for (auto it : adjList[node]) {

                // distance relaxing.
                if (dist[node] + it.second < dist[it.first])
                    dist[it.first] = dist[node] + it.second;
            }
        }



    }

    // print the distance.
    for (int i = 0; i < N; i++)
        cout << dist[i] << ' ';

}



// 2. Using BFS(Kahn's Algorithm)
vector<int> topologicalOrder(vector<pair<int, int>> adjList[], int V) {

    // calculate the inorder degree.
    vector<int> inorder(V + 1, 0);

    for (int node = 1; node <= V; node++) {
        for (auto it : adjList[node]) {
            inorder[it.first]++;
        }
    }

    // declare the queue.
    queue<int> q;
    for (int node = 1; node <= V; node++) {
        if (inorder[node] == 0)
            q.push(node);
    }

    vector<int> topoSort;

    while (!q.empty()) {

        int node = q.front(); q.pop();
        topoSort.push_back(node);

        for (auto it : adjList[node]) {
            inorder[it.first]--;
            if (inorder[it.first] == 0)
                q.push(it.first);
        }
    }

    return topoSort;
}


void shortestPath(vector<pair<int, int>> adjList[], int V, int src) {

    vector<int> topoOrders = topologicalOrder(adjList, V);

    // declare the dist array with MAX value, set src distance as zero.
    vector<int> dist(V + 1, INT_MAX);
    dist[src] = 0;

    // iterate over the topoOrders.
    for (int node : topoOrders) {

        // if dist[node] == INT_MAX, then this node is not reachable through src node, this node needs to process to become intermidate node.
        if (dist[node] != INT_MAX) {

            for (auto it : adjList[node]) {

                // relaxation
                if (dist[node] + it.second < dist[it]) {
                    dist[it] = dist[node] + it.second;
                }

            }

        }

    }

    // if still some node contains dist=INT_MAX, those are unreachable from the src node.
    // print dist, hold the shortest distane for source node.
}