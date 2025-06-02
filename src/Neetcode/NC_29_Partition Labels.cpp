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
================================================================================
                                Problem Description
================================================================================

Problem: NC_29_Partition Labels
Topic: DFS
Link: https://neetcode.io/problems/partition-labels

================================================================================
                                Problem Summary
================================================================================

Given an undirected graph, return a **deep copy** (clone) of the graph.

================================================================================
                             Intuition & Explanation
================================================================================

The core idea is to traverse the graph using either **BFS** or **DFS** and clone
each node along with its neighbors.

The key challenge lies in correctly establishing the edges in the cloned graph,
especially when revisiting already visited nodes (i.e., handling backward edges).

To manage this, we maintain a cache (typically a hash map) that maps original
node values to their cloned counterparts. This ensures:

- Each node is only cloned once.
- When visiting neighbors (even in backward traversal), we can retrieve the
  corresponding cloned node from the cache.

Example:
If the original graph has:

1 → 2
2 → 1 (backward edge)

When processing node 2 and encountering neighbor 1 again, we don’t clone 1 again.
Instead, we retrieve it from the cache and establish the edge in the cloned graph.

================================================================================
                          Approach & Time/Space Complexity
================================================================================

Approach: DFS
Time Complexity: O(N + E), where N = number of nodes, E = number of edges
Space Complexity: O(N) for the cache/map to store cloned nodes

*/


/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/


class Solution {
public:

    // map, <node_val, Node*>
    vector<Node*> cloneNodes;

    Node* dfs(Node* node) {

        // if current node is null, return null.
        if (node == NULL)
            return NULL;

        // create copy of current node.
        Node* cloneNode = new Node(node->val);

        // store in the map, so we can retrieve it by node->val...
        cloneNodes[node->val] = cloneNode;

        // explore all the neighbors fo current node
        for (auto it : node->neighbors) {

            // if "it" not visited, visit it.
            if (cloneNodes[it->val] == NULL) {

                Node* clonedNeighbor = dfs(it);

                // add forward edge, node -> it
                cloneNode->neighbors.push_back(clonedNeighbor);

            }

            else {

                Node* clonedNeighbor = cloneNodes[it->val];

                // add backward edge, it -> node (note: node is already visited, but we didn't add backward edge previously)
                cloneNode->neighbors.push_back(clonedNeighbor);

            }

        }

        return cloneNode;
    }



    Node* cloneGraph(Node* node) {

        cloneNodes.resize(102, NULL);

        return dfs(node);
    }



};
