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

Question : 7_Topological_Sort_Using_DFS
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

==============================> Approach and Time Complexity <============================

1) Graph
Time: O(V+E)
Space: O(V)

 */

void dfs(int node, vector<int> adjList[], vector<int> &visited, stack<int> &st) {
    visited[node] = 1;
    for (auto it : adjList[node]) {
        if (!visited[it]) {
            dfs(it, adjList, visited, st);
        }
    }
    st.push(node);  // after visting all the neighbours we are adding curr node in stack.
    // which make sure that.... If there is edge U -> V... then stack hold element in this order => U -> V
}

vector<int> topoSort(vector<int> adjList[], int V) {

    vector<int> visited(V + 1, 0);
    stack<int> st;          // contain topo order in right manner.

    for (int i = 1; i <= V; i++) {
        if (!visited[i]) {
            dfs(i, adjList, visited, st);
        }
    }

    // Add the element from the stack to the array....
    vector<int> topologicalOrder;
    while (!st.empty()) {
        topologicalOrder.push_back(st.top());
        st.pop();
    }

}