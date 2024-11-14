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
Question : 1.graph Reprsentation
- Striver graph series

/*
==============================> Explanation <=============================================

*/


/*
==============================> Edge Case <=============================================

*/


int main() {


    int n, m;
    cin >> n >> m;          // Number Of Nodes, Number of Edge


    // Matrix Reprsentation for unweighted graph.
    int adj[n + 1][n + 1];

    for (int i = 0; i < n; i++) {
        int u, v;
        cin >> u >> v;

        adj[u][v] = 1;
        adj[v][u] = 1; // directed graph omits this line.
    }


    // Matrix Reprsentation for Weighted graph.
    int adj[n + 1][n + 1];

    for (int i = 0; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        adj[u][v] = w;
        adj[v][u] = w; // directed graph omits this line.
    }





    // UnWeighted Adjancency List.
    vector<int> adj[n + 1];             // N + 1 when the node is 1 based.
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;              // NodeU -> NodeV

        adj[u].push_back(v);
        adj[v].push_back(u); // directed graph omits this line.
    }




    // Weighted Adjancency List.
    vector<pair<int, int>> adj[n + 1];

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;             // nodeU -> nodeV -> Weight

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});  // directed then omits this line.
    }



    return 0;
}