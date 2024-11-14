#include <bits/stdc++.h>
#define unsigned long long long long
#define REP(i,n) for(unsigned long long i = 0; i < n; i++)
#define REP1(i,n) for(unsigned long long i = 1; i <= n; i++)
#define debug cout << "Ok" << endl;
#define mod 1000000007

using namespace std;


/*
==============================> Description <=============================================

Question : 15_SCC_Kosaraju
Topic : Graph
Problems :
==============================> Explanation <=============================================

- Strongly Connected Componets(SCC) of graph is set of nodes, if you pick any node from SCC,
you can visit all the nodes in SCC.

The key idea is that the SCCs of the graph correspond to the SCCs of the graph's transpose.

Ex: 1 -> 2 -> 1 (only 2 node).
-> DFS in Forward = 1 -> 2
-> DFS in Reverse = 2 -> 1.
Means 1 and 2 is in Single SCC.

Kosaraju's Algorithm works on the same idea,

1) Sort all nodes in order of finishing time. Last explored nodes comes first. So we use that topo stack.
2) Take Transpose of Graph. (if node u -> v edge, now v -> u).
3) Perform DFS again on transpose graph, Whatever you get in single path DFS that all are SCC.

Logic behind #1: With main graph we have scc likes; SCC1 -> SCC2 -> SCC3
    With reverse graph we have scc likes: SCC1 <- SCC2 <- SCC3
    So when we perform the DFS on transpose graph and start to explore the SCC2 nodes... all nodes of SCC1 are
    visited because they are the first who popped out from the topo stack. So we can skip visited node(or we can say we can't update the low-link value(similar to tarjan algorithm))
    And to achieve this behaviour, we start with node which explored at last(indirectly used that topo stack).

Similarity Between Kosaraju & Tarjan algorithm:
    => Both algorithm, skip the already visited node(I mean part of othere SCC).
    Kosaraju use the topo stack to handle this case.
    Tarjan use the low_link value and on_stack behaviour to detect that.

==============================> Approach and Time Complexity <============================

1. Graph
Time: O(N+E)(Topo sort) + O(N+E)(Transpose of Graph) + O(N+E)(Reverse Graph DFS) = O(N+E)
Space: O(N+E)(Transpose of Graph) + O(N)(Visited)

*/

void dfs(int node, vector<int> adjList[], vector<int> &visited, stack<int> &st) {
    visited[node] = 1;
    for (auto it : adjList) {
        if (!visited[it]) {
            dfs(i, adjList, visited, st);
        }
    }
    st.push(node);
}


void dfsRev(int node, vector<int> adjList[], vector<int> &visited) {
    visited[node] = 1;
    for (auto it : adjList) {
        if (!visited[it]) {
            dfs(i, adjList, visited, st);
        }
    }
}



int getTotalSCC(vector<int> adjList[], int V) {

    // 1. Get nodes in order of finishing time. Means Node which got finished at the end, should come first.
    vector<int> visited(V + 1, 0);
    stack<int> st;  // topo stack.
    for (int i = 1; i <= V; i++) {
        if (!visited[i]) {
            dfs(i, adjList, visited, st);
        }
    }

    // 2. Transpose of the graph as adjListT.
    vector<int> adjListT[V + 1];
    for (int node = 1; node <= V; node++) {
        for (auto it : adjList[node]) {
            adjListT[it].push_back(node);
        }
    }


    // 3. Again perform the DFS on adjListT
    int totalSCC = 0;
    visited.resize(V + 1, 0); // clear the visited array to peform DFS again.
    while (!st.empty()) {
        int node = st.top(); st.pop();
        if (!visited[node]) {
            //(optinal) we can pass new list in dfsRev()... to get all nodes of SCC if required.
            totalSCC++; // everytime new call happen to dfsRev.. it means it is new SCC.
            dfsRev(node, adjListT, visited);
        }
    }


    return totalSCC;
}
