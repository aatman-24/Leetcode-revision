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

Question : 210. Course Schedule II
Topic : Graph
Problems : https://leetcode.com/problems/course-schedule-ii/description/?envType=problem-list-v2&envId=graph
==============================> Explanation <=============================================

Parent: 207. Course Schedule

Same as above one, here we need order as well, along with validation.

Applied Kahn's algorithm for topo sort.

==============================> Approach and Time Complexity <============================

1) Graph
Time: O(N+E)
Space: O(N+E)

 */


class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {

        int N = numCourses;

        // create a adjList, for easy relexation step.
        vector<int> adjList[N];
        for (auto it : prerequisites) {
            adjList[it[0]].push_back(it[1]);
        }

        // count indegree
        vector<int> indegree(N, 0);
        for (int i = 0; i < N; i++) {
            for (auto it : adjList[i]) {
                indegree[it]++;
            }
        }

        // push all nodes, whose indegree is zero.... (this node can be visited first)
        queue<int> q;
        for (int node = 0; node < N; node++) {
            if (indegree[node] == 0) {
                q.push(node);
            }
        }

        // get order, by performing relexation of visited node.
        vector<int> order;
        while (!q.empty()) {
            int node = q.front(); q.pop();
            order.push_back(node);
            // relexation
            for (auto it : adjList[node]) {
                indegree[it]--;
                if (indegree[it] == 0) {
                    q.push(it);
                }
            }
        }

        // edge case, only return array if there is no cycle(all nodes got visited)
        if (order.size() != N) {
            return {};
        }

        // reverse the order, because we first get last nodes of order first... in this question..
        reverse(order.begin(), order.end());


        return order;

    }
};