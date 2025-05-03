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

Question : 841. Keys and Rooms
Topic : Graph, BFS
Problems : https://leetcode.com/problems/keys-and-rooms/description/?envType=problem-list-v2&envId=graph
==============================> Explanation <=============================================

Again whenever "src" and "target" is given you can think of BFS.... if iterative manner is required or
DFS for recursive manner whichever suit the problem. Here We just need to check all nodes are going to visited
or not ...so BFS is enough!!

==============================> Approach and Time Complexity <============================

1) Graph
Time: O(N+E)
Space: O(N+E)

 */

class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        vector<int> visited(rooms.size(), 0);
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int node = q.front(); q.pop();
            visited[node] = 1;
            for (auto it : rooms[node]) {
                if (!visited[it]) {
                    q.push(it);
                }
            }
        }
        for (int i = 0; i < rooms.size(); i++) {
            if (visited[i] == 0)
                return false;
        }
        return true;
    }
};
