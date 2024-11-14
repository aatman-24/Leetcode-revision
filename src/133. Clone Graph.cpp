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

Question : 133. Clone Graph
Topic : Graph
Problems : https://leetcode.com/problems/clone-graph/description/
==============================> Explanation <=============================================

Basically, We need to keep deep copy of given graph.

We can apply DFS to create copy, but remember we need to create a new node and edge everytime in new graph.

How we keep track of visited node && how we get duplicate_node(new graph node) using node->val is heart of algorithm.

We basically use one map(key=value, value=new_node)... (check the code!!)

==============================> Approach and Time Complexity <============================

1) DFS
Time: O(N+E)
Space: O(N+E)

 */


class Solution {
public:

	Node* cloneGraph(Node* curNode, vector<Node*> &visited) {

		if (curNode == nullptr) return curNode;

		// Create duplicate node, of "curNode".
		Node* dup_node = new Node(curNode->val);

		// mark it as visited && map newly created duplicated node with its value.
		visited[curNode->val] = dup_node;

		for (auto it : curNode->neighbors) {

			// If "it" node is not yet visited, it means we have to create in new graph.
			if (!visited[it->val]) {
				Node* neighbor_it = cloneGraph(it, visited);
				dup_node->neighbors.push_back(neighbor_it);			// create edge
			}
			else {	// if "it" is already visited, then still we need to add edge (curNode->it)
				Node* neighbor_it = visited[it->val];
				dup_node->neighbors.push_back(neighbor_it);
			}

		}

		return dup_node;
	}


	Node* cloneGraph(Node* node) {

		// We keep track of newlyCreatedNode using this map.
		vector<Node*> vis(101, nullptr);

		return cloneGraph(node, vis);
	}
};