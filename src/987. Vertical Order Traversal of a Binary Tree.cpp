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

Question : 987. Vertical Order Traversal of a Binary Tree
Topic : BT
Problems : https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/description/
==============================> Explanation <=============================================

Parent: 6667. Top View of Binary Tree

So It is very similar to the top view of Binary Tree. Where we only add the nodes which encounterd first time at new "dist" and all the nodes
after whose dist also is same, we skip those...right ? Becasue of top view.

So we can modify this approach, instead of skipping those we can store them at same level.

	key(dist) => {node1, node2}

This what our map looks like. But there is one ask is that, if nodes have same cordinate that time, we have to sort based on its value.

First question,

	how we can differentiate nodes at level wise, because if one node A coming at level_0 and have dist = 5.
														  if second node B coming at level_1 and have dist = 5

	That time we cannot sort based on its value and then add... (#1 Wrong Apporach). Because we can sort nodes only whose both coordinate are same (x, y).

	=> Answer is Easy, We consider the level order traversal so atleast we can differentiate nodes based on y axis.

	=> To handle that sorting case, we can have one internal map for each level... so at any level if any "dist"(key) have more than one nodes,
	it means (x,y) both are same then we can sort that vector then add it in global map.

	Check the code!! You get it.


	Time: O(N * logN * logN) + O(N * log(N)) => O(2N*logN) around this.... (check in code)

	O(N*logN*logN) => visiting each node and performing lookup in both map + adding the answer in final array(lookup for each of key(dist))

		total K key => K * total_node_stored
	Space: O(K*N)(global_map) + O(K*N)(level_map)(in worst case, similar to global_map not possible) + queue(O(N/2)) => O(K*N) which comes around O(N)

	Worst case, queue can have O(N/2) at a single level... last level can hold N/2 if it balanced binary tree...





Brute Force:  (you can use any treversal method with this approach)

	In above solution we try to minimize the y-axis using the level order traversal. But if we don't want to do that... then this is solution.

	map<int, map<int, multiset<int>>> nodes;

	nodes[x][y] = {};		this multiset... holds the value in sorted order only....

	in our solution we need to maintain both (x, y) inside queue, instead of single value.

	queue<pair<Node*, pair<int, int>>> todo;

	Check the solution here: https://takeuforward.org/data-structure/vertical-order-traversal-of-binary-tree/






==============================> Approach and Time Complexity <============================


1) Binary Tree
Time: O(N)
Space: O(l)


 */




/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
// NOT RIGHT SOLUTION: If multiple nodes are at same vertical level, then we can sort all nodes based on value. But I'm wrong nodes can be sorted if both (x, y) are same.
class Solution {
public:
	vector<vector<int>> verticalTraversal(TreeNode* root) {
		map<int, vector<int>> mp;
		queue<pair<TreeNode*, int>> q;
		q.push({root, 0});
		while (!q.empty()) {
			int size = q.size();
			for (int i = 0; i < size; i++) {
				auto it = q.front(); q.pop();
				TreeNode* curr = it.first;
				int dist = it.second;
				mp[dist].push_back(curr->val);
				if (curr->left)
					q.push({curr->left, dist - 1});
				if (curr->right)
					q.push({curr->right, dist + 1});
			}
		}

		vector<vector<int>> vertical_traversal_seq;
		for (auto it : mp) {
			vector<int> nodesAtSameDistance = it.second;
			sort(nodesAtSameDistance.begin(), begin.end());
			vertical_traversal_seq.push_back(nodesAtSameDistance);
		}
		return vertical_traversal_seq;
	}
};

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
public:
	vector<vector<int>> verticalTraversal(TreeNode* root) {

		map<int, vector<int>> global_map;

		queue<pair<TreeNode*, int>> q;

		q.push({root, 0});

		while (!q.empty()) {								// O(N)
			int size = q.size();

			map<int, vector<int>> levelOrderMp;

			for (int i = 0; i < size; i++) {
				auto it = q.front();
				q.pop();
				TreeNode* curr = it.first;
				int dist = it.second;
				levelOrderMp[dist].push_back(curr->val);			// add the node first in level order map. + O(logN)(lookup in internal map)

				if (curr->left)
					q.push({curr->left, dist - 1});
				if (curr->right)
					q.push({curr->right, dist + 1});
			}

			for (auto it : levelOrderMp) {							// move element level_order_map -> global_map
				int dist = it.first;
				vector<int> nodesOfLevels = it.second;
				if (nodesOfLevels.size() > 1)						// more than one elements means (x,y) are same, sort that list first.
					sort(nodesOfLevels.begin(), nodesOfLevels.end());
				global_map[dist].insert(global_map[dist].end(), nodesOfLevels.begin(),		// arr.insert(arr.end(), arr2.begin(), arr2.end())	+ O(logN)(lookup in global map)
				                        nodesOfLevels.end());
			}
		}

		vector<vector<int>> vertical_traversal_seq;
		for (auto it : global_map) {
			vertical_traversal_seq.push_back(it.second);			// O(logN)(lookup) * O(N)(maximum N element can be added behind one list in worst case)
		}
		return vertical_traversal_seq;
	}
};