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

Question : 399. Evaluate Division
Topic : Graph, DFS, BFS
Problems : https://leetcode.com/problems/evaluate-division/description/?envType=problem-list-v2&envId=graph
==============================> Explanation <=============================================

So here, we have given couple of edges, and its cost. But edge is like if [a, b] is given it means a / b = 3 as experssion.

We have to find the cost for couple of query using above knowledge.

It is graph question due to trasitive property.... as we know => if we need a / c => a/b * b/c => a/c.....

So it means srcNode=a, targetNode=c... and it route whichever node we found we need to multipy that cost to get desired result.

So this question become (src->target) using dfs/bfs...

NOTE: given nodes are in string format so we can't use the normal representation of graph. So check that...

==============================> Approach and Time Complexity <============================

1) Graph
Time: O(N+E)
Space: O(N+E)

 */


// DFS Approach
class Solution {
public:

    double dfs(string src, string target, unordered_map<string, vector<pair<string, double>>> &graph, double currentValue, unordered_map<string, int> &visited) {

        // reached the target, whatever equation cost is, we return it directly.
        if (src == target) {
            return currentValue;
        }

        // mark the current node as visited.
        visited[src]++;

        for (auto it : graph[src]) {

            string node = it.first;
            double cost = it.second;

            if (!visited.count(node)) {

                double costFromitToTarget = dfs(node, target, graph, currentValue, visited);

                if (costFromitToTarget != -1) {
                    return cost * costFromitToTarget;
                }

            }

        }

        // remove from map.
        visited[src]--;
        if (visited[src] == 0) {
            visited.erase(src);
        }

        return -1;
    }

    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {

        // a: {b, 3}, edge a -> b, with cost 3
        unordered_map<string, vector<pair<string, double>>> graph;

        int N = equations.size();

        // build the graph
        for (int i = 0; i < N; i++) {

            string from = equations[i][0];
            string to = equations[i][1];
            double weight = values[i];

            // forward edge
            graph[from].push_back({to, weight});

            // reverse edge
            graph[to].push_back({from, 1 / weight});
        }

        // setup for the DFS
        unordered_map<string, int> visited;
        vector<double> result;

        for (auto it : queries) {
            string from = it[0];
            string to = it[1];

            // if both "to" and "from" are part of graph, then and only perform the dfs.
            if (graph.count(from) && graph.count(to)) {
                visited.clear();
                double cost = dfs(from, to, graph, 1, visited);
                result.push_back(cost);
            }
            else {
                result.push_back(-1);
            }
        }

        return result;
    }
};


// DFS + Memo
class Solution {
public:

    double dfs(string src, string target, unordered_map<string, vector<pair<string, double>>> &graph, double currentValue, unordered_map<string, int> &visited) {

        // reached the target, whatever equation cost is, we return it directly.
        if (src == target) {
            return currentValue;
        }

        // mark the current node as visited.
        visited[src]++;

        for (auto it : graph[src]) {

            string node = it.first;
            double cost = it.second;

            if (!visited.count(node)) {

                double costFromitToTarget = dfs(node, target, graph, currentValue, visited);

                // Memorization
                if (costFromitToTarget != -1) {

                    //  It means we have cost for: node -> target, so we add those direclty into graph so other
                    // query can be optimized.

                    // forward edge
                    graph[node].push_back({target, costFromitToTarget});

                    // reverse edge
                    graph[target].push_back({node, 1 / costFromitToTarget});

                    return cost * costFromitToTarget;
                }

            }

        }

        // remove from map.
        visited[src]--;
        if (visited[src] == 0) {
            visited.erase(src);
        }

        return -1;
    }

    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {

        // a: {b, 3}, edge a -> b, with cost 3
        unordered_map<string, vector<pair<string, double>>> graph;

        int N = equations.size();

        // build the graph
        for (int i = 0; i < N; i++) {

            string from = equations[i][0];
            string to = equations[i][1];
            double weight = values[i];

            // forward edge
            graph[from].push_back({to, weight});

            // reverse edge
            graph[to].push_back({from, 1 / weight});
        }

        // setup for the DFS
        unordered_map<string, int> visited;
        vector<double> result;

        for (auto it : queries) {
            string from = it[0];
            string to = it[1];

            // if both "to" and "from" are part of graph, then and only perform the dfs.
            if (graph.count(from) && graph.count(to)) {
                visited.clear();
                double cost = dfs(from, to, graph, 1, visited);
                result.push_back(cost);
            }
            else {
                result.push_back(-1);
            }
        }

        return result;
    }
};
