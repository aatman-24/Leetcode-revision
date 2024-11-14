#include <bits/stdc++.h>
#define unsigned long long long long
#define REP(i,n) for(unsigned long long i = 0; i < n; i++)
#define REP1(i,n) for(unsigned long long i = 1; i <= n; i++)
#define debug cout << "Ok" << endl;
#define mod 1000000007

using namespace std;


/*
==============================> Description <=============================================

Question : 16_SCC_Tarjan
Topic : Graph
Problems :
==============================> Explanation <=============================================

To find the SCC we have two algorithms:
    1) Kosaraju's algorithm
    2) Tarjan algorithm

Tarjan's algorithm is a single-pass DFS-based algorithm that finds SCCs using a depth-first search tree.
It uses a stack to keep track of the visited vertices and an array to record the low-link node
reachable from each vertex.

Algorithm:

- Mark the id of each node as unvisited.
- Start DFS. Keep track of ids(time) and low_link for each node and push the node in stack.
    ids(time)=> At what time or sequence the current node got visited during DFS.
    low_link => What is lowest_id can be reachable from this node.
-  During backtrack in DFS,
     Check, If previous node is on the stack then low_link[node] = min(low_link[node], low_link[it]).
     (Doing that we are spreading the low_link value among all the nodes in the path, who can reach to that node)
    And any time,
        if low_link[node] == id[node]..
            then popped_out all the element from stack until st.top() != id[node]... and all these nodes are part of one SCC.

Intution is that,
    Graph is: 1 -> 2 -> 3 -> 1
    And when we are at 3 and again try to visit 1 which is already visited that time...3 can reach to 1 which is lowest_id for 3.
    It means 2 can also reach to 1. In short all are part of SCC.. because there is cycle and all can reach to each other through that cycle.
    And we already knew that for DAG graph to get all nodes which are in same-path,
    we need stack & on_stack(array) which keep track of which elements are on stack.
    Using these two, we make sure SCC2 does not use low link value of SCC1, because SCC1 are already visited,
    and not on stack.

Purpose of stack ?
    => To get all nodes in single path, due to directed grpah.
    => DFS can visit neighbors in any random order..due to that low_link values can be different which could be wrong for this algorithm.
    Ex: SCC1(1,2,3) -> SCC2(4,5,6) and there is edge between (6->2).
    low_link[6]=2... which should not be valid(for this algorithm) because SCC1 is already visited and explored.
    That's why we maintain one stack.. and check if node is present in stack then and only we update the low_link of that node.

What is purpose of low_link ? (Not just for this algorithm) (Useful in bridge, articulation_point)
=> It tells us what is lowest id node can be reached from current node.

Similarity Between Kosaraju & Tarjan algorithm:
=> Both algorithm, skip the already visited node(I mean part of othere SCC).
Kosaraju use the topo stack to handle this case.
Tarjan use on_stack behaviour to detect that.

==============================> Approach and Time Complexity <============================

1. Graph
Time: O(N+E)
Space: O(N)

*/



// 14: Tarjan algortithm for strongly connected components

int sccCount = 0;   // Keep track of sccCount.

void dfs(int node, int &runner, vector<int> adjList[], vector<int> &ids, vector<int> &low_link, stack<int> &st, vector<int> &onStack) {

    // Add current node into the stack.
    st.push(node);

    // Mark on stack the current element.
    onStack[node] = 1;

    // Assign id and low_link value as runner.
    ids[node] = low_link[node] = runner;

    // Increase the runner
    runner++;

    for (auto it : adjList) {

        if (!ids[it]) {             // not visited
            dfs(i, runner, adjList, ids, low_link, st, onStack);
        }

        // Heart of algorithm. (update the low_link if "it" is in stack.)
        if (onStack[it]) {
            low_link[node] = min(low_link[node], low_link[it]);
        }

    }

    // Indicate starting point of SCC
    if (ids[node] == low_link[node]) {
        sccCount++;

        // Popped out all element from stack until current "node" get out of stack.
        while (!st.empty()) {
            int popped_node = st.top(); st.pop();
            onStack[popped_node] = 0;
            if (popped_node == node)
                break;
        }

    }
}


// Tarjan algorithm
int getTotalSCC(vector<int> adjList[], int V) {

    vector<int> ids(V + 1, 0);      // ids[i] = 0, indicate node is not visited yet. Apart from 0 value, indicate the id.
    vector<int> low_link(V + 1, 0);
    vector<int> onStack(V + 1, 0);   // Check given element is on stack or not.
    stack<int> st;                  // To keep track of boundary between SCC, when we are updating low_link.
    int runner = 1;                 // It is just time runner which keep increasing once assigned to any node.
    for (int i = 1; i <= V; i++) {
        if (!ids[i]) {
            dfs(i, runner, adjList, visited, low_link, st, onStack);
        }
    }


    return totalSCC;
}


