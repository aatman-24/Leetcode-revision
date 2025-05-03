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

Question :310. Minimum Height Trees
Topic : Graph, DFS, BFS, Toposort
Problems : https://leetcode.com/problems/minimum-height-trees/

==============================> Explanation <=============================================
1) When single grpah path is given, the mst root is the middle of path if it is even then
two node and if it is odd then one node. How to find the middle of path... we use the
two pointer (fast and slow) increase fast by 2 and slow by 1.

Same concept we used here,

for node = 1 -> we return it.

for node = 2 -> 1 - 2 -> {1, 2} because mst length is 1. and both node have 1 size depth.

for node > 2,
    suppose 1 - 2 - 3 (Then 1 and 3(leaf) never become the mst root. Reason is that it's
    neighbor is always best choice(minimum depth mst) for the mst root(here 2).)

So Here we use that logic,

- We keep track of leaf of the current tree. And every step leaf move to the inside of tree(parent).
We peform this opreation until (1 0r 2) node left which is above condition.

- So Question is how to keep track of leaf node ?
->> Here comes toposort for rescue. We know that toposort(kahn's algorithm) visit all the
node which is indegree is 0 which is leaf node and every step new leaf is added to the queue.
So we used that logic.

Update in kahn's algorithm -> We learned kahn's algorithm for directed graph. But here
we have undirected graph. So node i -> j means we indegree for both i and j node. And also
on base when the indegree is 1 that time we add the node into the queue rathar than 0.


Both are same....

2) Suppose a tree has only one long linear path, in that case the minimum height tree's root
would be the middle value of the path when path length is odd or the two middle values of the
path when path length is even. So there can be at most two MHT and the root vlaues would be the
middle values of the longest path of the tree.

Tree: 0-1-2-3-4-5-6, middle values: [3] => Path Length Odd
Tree: 0-1-2-3-4-5, middle values: [2,3] => Path Length Even

Finding longest tree path by running DFS/BFS is quite hectic.

Instead we can find the middle values of the longest path by removing the leaf nodes from the tree
in each step which we implement by running BFS and counting degeree of node.

Longest path always starts with leaf nodes which has degree 1, so initially we can add all degree 1
leaf nodes in to queue and run BFS, while processing a node, we decrease degree of all its neighbour
nodes (as we are removing the current node from the tree) and add neighbours in to queue which has
degree 1 (leaf node). The nodes which exists at last are the middle nodes of the longest tree path.

Example: n = 6, edges = [[3,0],[3,1],[3,2],[3,4],[5,4]]

Push node 0,1,2,5 in to queue and run BFS and for each node, decrease it's neighbour's degree
at last only node 3 and 4 remains and they are the root nodes of MHT.

==============================> Apporach and Time Complexity <=============================================

1) Brute Force: O(N^2) - O(N)(aux)
- Peform the DFS for every child node of current node and take minimum depth from that. O(N)
- Peform this for every node. O(N)
So overall -> O(N^2)- O(N)(aux).



2) Optimized BFS Toposort(Kanh's algorithm):
Time = O(N+E)(AdjList)
Space = O(N)(Queue) + O(N)(color)
*/


class Solution {
public:

    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {

        if (n == 1) {
            return vector<int> {0};
        }

        vector<int> adjList[n];
        vector<int> indegree(n, 0);
        vector<int> answer;

        for (int i = 0; i < edges.size(); i++) {

            // Make AdjList.
            adjList[edges[i][0]].push_back(edges[i][1]);
            adjList[edges[i][1]].push_back(edges[i][0]);

            // Increase the Indegree for both node. (Undirected graph).
            indegree[edges[i][1]]++;
            indegree[edges[i][0]]++;
        }



        queue<int> q;


        // Adding all the leaf to the queue. leaf has indegree 1.
        for (int i = 0; i < n; i++) {
            if (indegree[i] == 1)
                q.push(i);
        }


        while (!q.empty()) {

            // keep track of last level node only.
            answer.clear();

            int size = q.size();

            for (int i = 0; i < size; i++) {

                int node = q.front(); q.pop();
                temp.push_back(node);

                for (auto it : adjList[node]) {

                    indegree[it]--;

                    if (indegree[it] == 1) {
                        q.push(it);
                    }
                }
            }
        }

        return answer;
    }
};



class Solution {
public:

    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {

        // Base case: only one node
        if (n == 1) return vector<int> {0};

        // graph adjacency list of nodes
        vector<vector<int>>graph(n);

        // degree count of nodes
        vector<int>degree(n, 0);

        // populate graph adjacency list and degree count of nodes
        for (int i = 0; i < edges.size(); i++)
        {
            int a = edges[i][0];
            int b = edges[i][1];

            graph[a].push_back(b);
            graph[b].push_back(a);

            degree[a]++;
            degree[b]++;
        }

        queue<int>Q;

        // push degree 1 nodes (leaf nodes) in to queue
        for (int i = 0; i < n; i++)
            if (degree[i] == 1)Q.push(i);

        // MHT root nodes
        vector<int>res;

        // run BFS until queue is empty
        while (!Q.empty())
        {
            int n = Q.size();

            // clear root nodes
            res.clear();

            // perform level order traverse
            while (n--)
            {
                int node = Q.front();
                Q.pop();

                // add current in to root node vector
                res.push_back(node);

                // process neighbour nodes
                for (int i = 0; i < graph[node].size(); i++)
                {
                    // decrease degree of neighbour nodes
                    degree[graph[node][i]]--;

                    // push leaf nodes in to queue
                    if (degree[graph[node][i]] == 1)
                    {
                        Q.push(graph[node][i]);
                    }
                }
            }
        }

        // root nodes of MHT
        return res;
    }
};