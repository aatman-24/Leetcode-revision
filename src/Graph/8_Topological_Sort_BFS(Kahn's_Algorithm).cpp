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

Question : 8_Topological_Sort_BFS(Kahn's_Algorithm)
Topic : Graph
Problems :
==============================> Explanation <=============================================

Topological Sort:
For the DAG(Directed Acycalic Graph), if there is edge U -> V then topological sort of that nodes is {U, V}.

Don't confuse here:
U -> V, it means V(build) have dependency of U(build). To resolve this dependency we need to make build for U first then V.
So in topological order will be {U, V}.

Intuition behind it is,
When we use the DFS, and reach the dead end, that time we add that last
visisted node first into topo_stack before it's parent node. While doing that we are
making sure that u -> {v1, v2, v3}.. all the neighbors {v1, v2, v3} must be visited
and in stack..only after parent(u) can be puhsed to the stack.

So when we popped elements out of stack and put into the array, that time seq looks
like: {u, v1, v2, v3}.

Getting Topoorder using BFS known as Kahn's Algorithm(IMP).

Intuition behind this algorithm is that,

We calculate the indegree of each node, which indicate how many nodes(dependency)
which needs to be resolved before, we mark the current node as visited.

Indrgree is 0, indicate node become free(It doesn't have any dependency on other node to be resolved).
So we can visit and remove that node from graph and its edges(I mean add in topological order).

We maintain one queue which hold the nodes which have 0 indegree. And apply BFS.

==============================> Approach and Time Complexity <============================

1) Graph
Time: O(V+E)
Space: O(V)

 */

// 7. Topoloical sort using BFS (Kahn's algorithm) + Cycle Detecation
vector<int> topoSort(vector<int> adjList[], int V) {


    vector<int> indegree(V + 1, 0);
    for (int i = 1; i <= V; i++) {
        for (auto it : adjList[i]) {    // i -> it... indegree[it]++;
            indegree[it]++;
        }
    }

    // keep track of visited node.
    int visitedNode_count = 0;

    // topo order sequence.
    vector<int> topologicalOrder;

    // Declare queue and put all the initial nodes who has indegree zero.
    queue<int> q;
    for (int i = 1; i <= V; i++) {
        if (indegree[i] == 0)
            q.push(i);
    }

    while (!q.empty()) {

        int node = q.front(); q.pop();
        visitedNode_count++;
        topologicalOrder.push_back(node);

        // remove the edges, by decreasing the indegree node->it.
        for (auto it : adjList[node]) {
            indegree[it]--;
            if (indegree[it] == 0) {
                q.push(it);
            }
        }
    }

    // All nodes visited then and only return topo order, otherwise graph have cycle.
    // Due to that, some node indegree > 0, and can not be reduced to 0.
    if (visitedNode_count == V)
        return topologicalOrder;
    else
        return {};      // graph contains cycle
    // visitedNode_count != V => Indicate that there are some nodes whose indegree doesn't become zero and it is only possible if there is cycle.
}
