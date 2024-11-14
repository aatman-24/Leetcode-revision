## Graphs Algorithm Short Notes

### 

### 1. Depth First Search [O(V+E), O(V)]

```c
void dfs(int node, vector<int> adj[], vector<int> &visited, vector<int> &dfsOrder) {
    visited[node] = 1;              // mark the unvisited node, as visited
    dfsOrder.push_back(node);       // store in dfsOrder
    for (auto it : adj[node]) {     // iterate over all the neighbors node
        if (!visited[it]) {         // If neighbors nodes are not visited perform dfs on that, otherwise skip it, we don't visit the visited node
            dfs(it, adj, visited, dfsOrder);
        }
    }
}

vector<int> depthFirstSearch(int V, vector<int> adj[]) {
    vector<int> visited(V + 1, 0);
    vector<int> dfsOrder;
    for (int i = 1; i <= V; i++) {          // If there are many components in graph, then we need to check for each node.
        if (!visited[i]) {                  // If node is not visited, it means it is from isolated component's node.
            dfs(i, adj, visited, dfsOrder);
        }
    }
    return dfsOrder;
}
```

### 2. Breadth First Search[O(V+E), O(V)]

```c
vector<int> breadthFirstSearch(vector<int> adj[], int V) {

    // keep track of visited node, we don't visit the visited node again
    vector<int> visited(N + 1, 0);

    vector<int> bfsOrder;

    // Need to check for each node, due to disconnect componet is possible in graph.
    for (int i = 1; i <= V; i++) {
        // perform traversal on not visited node only.
        if (!visited[i]) {
            queue<int> q;
            q.push(i);
            visited[i] = 1;
            while (!q.empty()) {
                int node = q.front(); q.pop();
                bfsOrder.push_back(node);
                for (auto it : adj[node]) {
                    // only add if that node is not visited. (To avoid cycle trapping)
                    if (!visited[it]) {
                        q.push(it);
                        visited[it] = 1;
                    }
                }
            }
        }
    }
}
```

### 3. Graph is bipartite using BFS + DFS [O(V+E), O(V)]

```c
 /* Intuition


Intuition behind the algorithm is that, 

    If Graph contain the cycle, and that cycle is odd length, It means one of two adjancents node
    have same color. It is not biparatite graph. 

    If Graph contain no cycle, or have even length cycle, we are find, and grpah is biparatite. 


 */
vector<int> breadthFirstSearch(vector<int> adj[], int V) {

    // keep track of visited node, we don't visit the visited node again
    vector<int> color(N + 1, -1);       // -1 -> not visited, 0 -> colored, 1 -> colored

    // Need to check for each node, due to disconnect componet is possible in graph.
    for (int i = 1; i <= V; i++) {

        // perform traversal on not visited node only.
        if (color[i] == -1) {

            queue<int> q;
            q.push(i);
            color[i] = 1;

            while (!q.empty()) {

                int node = q.front(); q.pop();

                for (auto it : adj[node]) {

                    // only add if that node is not visited. (To avoid cycle trapping)
                    if (color[it] == -1) {
                        q.push(it);
                        color[it] = 1 - visited[node]; // alternavtive color 0 and 1.
                    }
                    // already visited node have same color the current node have...
                    else if (color[it] == color[node]) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

 // Using DFS

bool bipartiteDfs(int node, vector<int> adjList, int color[]) {

    if (color[node] == -1) color[node] = 1;

    for (auto it : adjList[node]) {

        // If adjacent Node is not colored yet.
        if (color[it] == -1) {

            // color with oppsite color of current node.
            color[it] = 1 - color[node];

            if (!bipartiteDfs(it, adjList, color))
                return false;
        }

        // If it is already colored and color is same with current node. Means Grpah
        // cannot be Bipartite.
        else if (color[it] == color[node]) {
            return false;
        }

    }

    return true;
}


bool checkBipartite(vector<int> adjList[], int n) {

    int color[n];

    memset(color, -1, sizeof(color));

    for (int i = 0; i < n; i++) {

        if (color[i] == -1) {

            if (!bipartiteDfs(i, adj, color))
                return false;
        }
    }

    return true;
}
```

### 

### 4. Cycle Detection on Undirected Graph Using BFS[O(V+E), O(V)]

```c
 /* Intuition

When we apply bfs/dfs on the graph, during traversal, if we visit neighbors node, and
that is already visited by other node(except the parent), we found cycle.

In undirected graph, we have both edges(forward, reversal), so we don't consider reverse edge which again point to parent,
during travesal, so we keep track of parent, so we can ignore it during as potential neighbors.

 */
bool checkForCycle(int node, int V, vector<int> &visited, vector<int> adjList[]) {

    // Create queue for BFS. Here, <node, parent_node>
    queue<pair<int,int>> q;

    // Mark the first node where BFS start as visited and push into the queue.
    visited[node] = 1;
    q.push({node, -1});

    while(!q.empty()) {

        int node = q.front().first;
        int parent = q.front().second;
        q.pop();

        for(auto it : adjList[node]) {

            // If not visited. Visit it and add into the queue.
            if(!visited[it]) {

                // Here is Change from DFS.
                visited[it] = 1;
                q.push({it, node});
            }
            // While adjancent node of current node, is already visited and this is not 
            // parent means we found the cycle.
            else if(parent != it)
                return true;
        }
    }

    return false;
}

bool isCycle(int V, vector<int> adjList[]) {

    vector<int> vis(V+1,0);

    for(int i = 1; i <= V; i++) {

        if(!vis[i]) {
            if(checkForCycle(i, V, vis, adjList))
                return true;
        }

    }

    return false;
}
```

### 5. Cycle Detection on Undirected Graph Using DFS[O(V+E), O(V)]

```c
 /* Intuition

When we apply bfs/dfs on the graph, during traversal, if we visit neighbors node, and
that is already visited by other node(except the parent), we found cycle.

In undirected graph, we have both edges(forward, reversal), so we don't consider reverse edge which again point to parent,
during travesal, so we keep track of parent, so we can ignore it during as potential neighbors.

 */

bool checkForCycle(int node, int parent, vector<int> &vis, vector<int> adjList[]) {

    // Mark the current node as visited.
    vis[node] = 1;

    // Visit All the neighbour node of current node.
    for(auto it: adjList[node]) {

        // If it is not visited.
        if(!vis[it]){
            if(checkForCycle(it, node, vis, adjList))
                return true;
        }
        // If it is visited and not the previou(parent) node. Means there is cycle already visited
        // Nodes comes again and it is not node where we come from the current node.
        else if(it != parent)
            return true;
    }

    // Not Found.
    return false;
}


bool isCycle(int V, vector<int> adjList[]) {

    vector<int> vis(V+1,0);

    for(int i = 1; i <= V; i++) {

        if(!vis[i]) {
            if(checkForCycle(i, -1, vis, adjList))
                return true;
        }

    }

    return false;
}
```

### 6. Cycle Detection on Directed Graph Using DFS[O(V+E), O(V)]

```c
 /* Intuition

 What is major differnce between the DFS of Directed and Undirected Graph ?

-> So In Un-Directed Graph there is no direction on edge so we consider it as bidirectional. But in the Directed graph,
there is direction given (u, v) as edge, it means edge has direction from u -> v.

Due to that, if one node is visited and again other node try to visit that node doesn't mean that there is cycle...
Ex:

1 -> 2 -> 3
     |    |
     4 -> 5

2 -> 4 -> 5 -> 3(Visited) (DFS call 1)
2 -> 3 (Already Visited) but it is not cycle. (DFS call 2)

In directed Graph there is cycle if and only if current node is getting visited two times in same path. If the path is different
then there is no cycle.

Ex:

1 -> 2 <- 3
     |    |
     4 -> 5

Here you can see... 1->2->4->5->3->2(already visited)... in single path(single dfs call) we are getting the same node... it means there is cycle.


Due to that,

We need to keep one more array, pathVisited[] which tells us whether current node is repeated earlier in same path or not. And also
whenever we backtrack that time we also backtrack from pathVisited.

 */
bool dfs(int node, vector<int> adjList[], vector<int> &visited, vector<int> &pathVisited) {

    // mark the current node as visited.
    visited[node] = 1;
    pathVisited[node] = 1;  // also mark the current node as path visited.

    for (auto it : adjList[node]) {

        if (!visited[it]) {
            // check if any of its adjacent node leads to cycle, yes then return true there is cycle.
            if (dfs(it, adjList, visited, pathVisited)) {
                return true;
            }
        }
        // node is visited already, check it is visited in same path
        else if (pathVisited[it] == 1) {
            return true
        }
    }

    // backtrack
    pathVisited[node] = 0;  // unwind from pathVisited
    return false;   // cycle notf oudn
}



bool isCycle(vector<int> adjList[], int V) {

    vector<int> visited(V + 1, 0);
    vector<int> pathVisited(V + 1, 0);

    for (int i = 1; i <= V; i++) {
        if (!visited[i]) {
            // check if starting from node i, can lead to cycle
            if (dfs(i, adjList, visited, pathVisited))
                return true;
        }

    }
    return false;
}
```

### 7. BFS on Maze(2D Matrix)(Dungeon Problem)[O(V^2), O(V^2)]

```c
 /* Intuition

 Intuition behind this algo is that,

    We convert the given 2D Matrix(Maze) into the graph, so we can apply the BFS on that.

    Based upon question, we define which node can be neighbors,

        If we allow to move in 4 directions => we have 4 neighbors for any node maximum.

        If we allow to move in 8 directions(diagonal as well) => we have 8 neighbors.

    Simply, we will apply the BFS on maze(we don't convert it to graph), how(check on code).

 */

// We can also unwind the node from the queue based on level(the way we did in tree) whatever level we get when we
// reach the exit point can be consider as shortest distance. Check the code..()
bool ableToFindExit(int maze[][], int N, int start_x, int start_y) {

    // maze[i][j] = 1, it means there is rock.
    // maze[i][j] = 2, it means exit cell.

    // To keep track visited cell, so we don't again push to the queue.
    int visited[N + 1][N + 1];
    memset(visited, 0, sizeof(visited));

    // Give 4 direction only, if given diagonal direction then these arrays become size of 8. 
    int dx[] = { -1, 1, 0, 0};      
    int dy[] = {0, 0, 1, -1};

    queue<pair<int, int>> q;
    q.push({start_x, start_y});

    int level = 1;          // minimum_distance to reach the exit cell.

    while (!q.empty()) {

        int size = q.size();

        for (int k = 0; k < size; k++) {

            auto it = q.front(); q.pop();
            int x = it.first, y = it.second;

            // found the exit point.
            if (maze[x][y] == 2) {
                return true;        // if require minimum_distance then return level... (you get it right...)
            }


            for (int i = 0; i < 4; i++) {

                int xx = x + dx[i];
                int yy = y + dy[i];

                // out of bound any of parameter skip it.
                if (xx < 0 || yy < 0) continue;
                if (xx >= N || yy >= N) continue;

                // skip if there is rock or already visited cell.
                if (maze[xx][yy] == 1 || visited[xx][yy]) continue;

                // mark the current cell as visited, and into the queue for exploration.
                visited[xx][yy] = 1;
                q.push({xx, yy});

            }
        }

        level++;
    }

    return false;
}
```

### 8.  Topological sort using DFS [O(V+E), O(V)]

```c
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
```

### 9. Topological sort using BFS (Kahn's algorithm) + Cycle Detection [O(V+E), O(V)]

```c
vector<int> topoSort(vector<int> adjList[], int V) {

    vector<int> indegree(V + 1, 0);
    for (int i = 1; i <= V; i++) {
        for (auto it : adjList[i]) {    // i -> it... indegree[it]++;
            indegree[it]++;
        }
    }

    // keep track of visited node.
    int visitedNode_count = 0;

    // topo order sequence.
    vector<int> topologicalOrder;

    // Declare queue and put all the initial nodes who has indegree zero.
    queue<int> q;
    for (int i = 1; i <= V; i++) {
        if (indegree[i] == 0)
            q.push(i);
    }

    while (!q.empty()) {

        int node = q.front(); q.pop();
        visitedNode_count++;
        topologicalOrder.push_back(node);

        // remove the edges, by decreasing the indegree node->it.
        for (auto it : adjList[node]) {
            indegree[it]--;
            if (indegree[it] == 0) {
                q.push(it);
            }
        }
    }

    // All nodes visited then and only return topo order, otherwise graph have cycle.
    if (visitedNode_count == V)
        return topologicalOrder;
    else
        return {};      // graph contains cycle
    // visitedNode_count != V => Indicate that there are some nodes whose indegree doesn't become zero and it is only possible if there is cycle.
}
```

### 10. Single Source Shortest Path for Undirected Graph(BFS+ Relextion) [O(V+E), O(V)]

```c
 /*
 Intuition:
    We can get SSSP, by simply perforing BFS, starting from "src" node. As we know that, each edge cost 1 unit, BFS explore nodes which care close the node(compare to DFS),
    so we can peform simple relexation,
            dist[it] = 1 + dist[node], if we have edge "node -> it", where "node" is visited and "it" we are exploring..
 */

 void shortestPath(vector<int> adjList[], int V, int src) {

    // Initalize the distance array with maximum distance.
    vector<int> dist(V + 1, INT_MAX);

    // src -> src, distance is zero.
    dist[src] = 0;

    // Use queue to perform BFS.
    queue<int> q;

    // Add src node in queue.
    q.push(src);

    while (!q.empty()) {

        int node = q.front(); q.pop();

        for (auto it : adjList[node]) {

            // relxation
            if (dist[node] + 1 < dist[it]) {
                dist[it] = dist[node] + 1;
                q.push(it);
            }

        }
    }

    // print dist, hold the shortest distane for source node.
}
```

### 11. SSSP for Directed Acyclic Graph [O(V+E), O(V)]

```c
 /* Intuition:

     If there is graphs looks like, Z -> A -> B -> C, and we need to find SSSP with src node "A".

    So using topoOrder, we get the order in which we need to traverse the graph. Because it is
    obvious that, all the nodes who are reachable from src node "A", have dependency as src
    node "A", so in topoOrder src node "A" comes before these reachable nodes. and node Z is
    unreachable from A, so Z comes before A in topoOrder.

    Why It works ?
    - Toposort visit all the node first, which does not have any dependency on it. So by doing that we find
    all the nodes which can be reach from the source node. Because those node which are reachable from the source
    node, have dependency as source node... so first source node unwind during topo order iteration... later we can use
    the relaxation step to get shortest distnace.

    And node which can not reach by the source node is popped from the stack first(visited first in topo order) and have distane as INT_MAX(never relaxation happen on that).

    - And once any node distance is calculated(it is not INT_MAX) then we can use this node as intermidatory
    for others once. The node which is not reached by the source node distance is INT_MAX so it can never
    used as intermidatory node.



 */
vector<int> topologicalOrder(vector<pair<int, int>> adjList[], int V) {

    // calculate the inorder degree.
    vector<int> inorder(V + 1, 0);

    for (int node = 1; node <= V; node++) {
        for (auto it : adjList[node]) {
            inorder[it.first]++;
        }
    }

    // declare the queue.
    queue<int> q;
    for (int node = 1; node <= V; node++) {
        if (inorder[node] == 0)
            q.push(node);
    }

    vector<int> topoSort;

    while (!q.empty()) {

        int node = q.front(); q.pop();
        topoSort.push_back(node);

        for (auto it : adjList[node]) {
            inorder[it.first]--;
            if (inorder[it.first] == 0)
                q.push(it.first);
        }
    }

    return topoSort;
}


void shortestPath(vector<pair<int, int>> adjList[], int V, int src) {

    vector<int> topoOrders = topologicalOrder(adjList, V);

    // declare the dist array with MAX value, set src distance as zero.
    vector<int> dist(V + 1, INT_MAX);
    dist[src] = 0;

    // iterate over the topoOrders.
    for (int node : topoOrders) {

        // if dist[node] == INT_MAX, then this node is not reachable through src node, 
        // this node needs to process to become intermidate node.
        if (dist[node] != INT_MAX) {
            for (auto it : adjList[node]) {
                // relaxation
                if (dist[node] + it.second < dist[it]) {
                    dist[it] = dist[node] + it.second;
                }
            }
        }
    }

    // if still some node contains dist=INT_MAX, those are unreachable from the src node.
    // print dist, hold the shortest distane for source node.
}
```

### 12 .Dijkstra algorithm SSSP (non-negative-edge)[O(V+E)*logE, O(V)]

```c
 /* Intuition:


Similar to other SSSP Problem, We start visiting nodes from "src" node. To decide which node to visit next, we use the
priority_queue which holds all promising nodes, and return the most optimistic node which have shortest distance till that time,
so using that node we perform the relxation on its' neighbors nodes(it).

Main idea is that,

    IN Priority_queue we hold this pair => {dist, node}, dist => distToSource

    PQ return a node, which have shortest distance from "src" node at any moment, so we visit that node first among
    all potential nodes, which are in queue. Mark that node as visited.

    So when we explore the neighbors nodes(it), with "node" as intermidatory node(which have shortest dist from src),

        we check, distToSource[node] + edgeCost(node->it) < distToSource[node],

                    if it is true, then we got better route to reach (it) node from (src) node via "node".

                        update the distance of,

                                distToSource[node] = distToSource[node] + edgeCost(node->it)

Time: O((V+E)logE) => In the worst case, we visit entire graph during relexation O(V+E), and pq holds all the edges(considering duplicates as well), so pq.top() take O(E) time)




 */

 void shortestPath(vector<pair<int, int>> adjList[], int V, int src) {

    // keep track of shortest distance from src node.
    vector<int> distToSource(V + 1, INT_MAX);

    // keep track of visited node... dijkstra select most promising node at a time from pq.
    // so once the node is visited, we don't change it distance.
    vector<int> visited(V + 1, 0);

    // (optional) to construct shortest path....
    vector<int> prev(V + 1, -1);

    // set the dist for src node as zero.
    distToSource[src] = 0;

    // {dist, node} min heap.
    priority_queue < pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> pq;

    // Add src node into the pq.
    pq.push({0, src});

    while (!pq.empty()) {

        int dist = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        // mark the processed node as visited.
        visited[node] = 1;

        // (optional) in case end node is given....
        if (node == end)
            break;

        for (auto it : adjList[node]) {

            int nextNode = it.first;
            int edgeCost = it.second;

            // optimization... skip the visited node...
            if (visited[nextNode]) continue;

            // relexation....
            if (distToSource[node] + edgeCost < distToSource[nextNode]) {
                distToSource[nextNode] = distToSource[node] + edgeCost;
                pq.push({distToSource[nextNode], nextNode});        // push into the priority queue

                // (optional) set the curr node as previous node for nextNode.
                prev[nextNode] = node;
            }
        }
    }

    // distToSource contains shortest distance from source to all other nodes.

    // Construct path... For that end node is also given.... s
    vector<int> shortestPath;
    for (int at = end; at != src; at = prev[at]) {
        shortestPath.push_back(at);
    }
    reverse(shortestPath.begin(), shortestPath.end());

    // shortestPath hold the shortest path.....
}
```

### 13 MST - Prim [O(V+E)*logE, O(V)]

```c
/* Intuition:

In simple words, we are selecting minimum edge(u->v) such that, u is already part of mst and v is not part of most. 

*/

 int mstCost(vector<int> adjList[], int V) {

    // check node is part of MST or not.
    vector<int> visited(V + 1, 0);

    // min heap
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // We are staring with 1st node.
    pq.push({0, 1});

    int mstSum = 0;

    while (!pq.empty()) {

        auto vertex = pq.top(); pq.pop();
        int node = vertex.second;
        int cost = vertex.first;

        if (visited[node]) continue;

        // node is not part of MST, add it and mark as visited.
        mstSum += cost;
        visited[node] = 1;

        for (auto it : adjList[node]) {
            if (!visited[it.first]) {       // we are checking "v" is visited or not when we see edge u->v.
                pq.push({it.second, it.first});
            }
        }

    }

    return mstSum;
}
```

### 14 Disjoint Set [O(4*alpha), O(V)]

```c
 /* Intuition:

 DisjointSet is Data Strcuture, which basically peroform this operation,
    union(u, v) =>  make nodes u and v part of same set.
    isPartofSameSet(u, v) => check both are part of same set or not.

Path Compression(Optimization):
    - So when we are finding the ultimate parent that time, it takes O(logN) time to get the parent. But,
    using path compression each node in path points to ultimate parent directly.. so next time when we get parent of any node
    from tha path.. we can get in O(1) time.

Why connect to smaller set to larger one ? (Think without considering path compression)
    - If we connect larger set to smaller set, in that case that findParent will take more
    time, because larger tree already have greater height than smaller one... so it height won't be
    increase...but if we add larger to smaller... we are increasing the height... which directly affect into time complexity.

But we know optimization... so above one is not much create any impact.

But wait if that's the case.. can we use the size of set instead of rank.

We will add the smaller set(by size) to the larger set.

---

Most of time it take O(1) and but new path is explored first time that time it take O(logN).

So amarotized tiem complexity is = O(4*alpha) = O(1) (constant) we can consider.

Time = O(4*alpha) = O(4) = Constant (for any operation )
Space = O(N)


 */

class DisjointSet {

    // Declare the required array as private
    vector<int> rank;       // keep track of rank, rank(u) > rank(v).. means the set which contain u is bigger than v.
    vector<int> parent;     // keep track of ultimate parent.

public:

    DisjointSet(int V) {

        // Rank is set to zero.
        rank.resize(V + 1, 0);
        parent.resize(V + 1, 0);

        // Initially all node are parent of itself.
        for (int i = 1; i <= V; i++) {
            parent[i] = i;
        }
    }

    int findUltimateParent(int u) {
        if (parent[u] == u)
            return u;
        return parent[u] = findUltimateParent(parent[u]);       // Optimization: path compression
    }

    void unionByRank(int u, int v) {

        // Find the ultimate parent of both nodes.
        int ulp_u = findUltimateParent(u);
        int ulp_v = findUltimateParent(v);

        // Both are part of one set already.
        if (ulp_u == ulp_v) return;

        // Compare the ranks and make it union, by joining smaller set into bigger set.
        if (rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;      // join ulp_u -> ulp_v
        }
        else if (rank[ulp_v] < rank[ulp_u]) {
            parent[ulp_v] = ulp_u;  // join ulp_v -> ulp_u
        }
        else {
            parent[ulp_v] = ulp_u; // rank are same, you can pick up any one.
            rank[ulp_u]++;         // increaes the rank of ulp_u, because you joint ulp_v -> ulp_u
        }
    }

    // Check both u and v are part of same union set or not.
    bool isPartOfSameSet(int u, int v) {
        int up = findUltimateParent(u);
        int uv = findUltimateParent(v);
        return up == uv;
    }
}
```

### 15. MST - Kruskal Algorithm[O(E*logE), O(V)]

```c
 /* Intuition:

Intuition behind algorithm is that, 

    We select all EDGEs from graph such that, we visit all the nodes of graph. 
    But constraint is that, whenever we pick up any edge (u -> v), 
    u and v are not part of same set(I mean, "u" is visited & "v" is not visited, or vice versa).

 */
int findMST(vector<vector<int>> adjList[], int V) {

    // convert the graph in {w, {u, v}} format.
    vector<pair<int, pair<int, int>>> edges;

    for (int u = 1; u <= V; u++) {
        for (auto it : adjList[u]) {
            int v = it[0];
            int w = it[1];
            edges.push_back({w, {u, v}})
        }
    }

    // sort the edges based on weight
    sort(edges.begin(), edges.end());

    // Create a Disjoint Set
    DisjointSet ds(V);

    // keep track of total weight
    int mstWeight = 0;

    // (optional) we can save the path as well...
    vector<pair<int, int>> mstEdges;

    for (auto it : edges) {

        int wt = it.first;
        int u = it.second.first;
        int v = it.second.second;

        // If U and V are not part of same set(it means we can add edge U->V)
        if (ds.findUParent(u) != ds.findUParent(v)) {
            mstWeight += wt;
            ds.unionByRank(u, v);
            mstEdges.push_back({u, v});
        }
    }

    // print mstEdges... which contains all the edges which are part of MST.

    return mstWeight;
}
```

### 16.  Kosaraju's Algorithm for Strongly Connected Components [O(N+E), O(N+E)]

```c

/* Intuition

The key idea is that the SCCs of the graph correspond to the SCCs of the graph's transpose.

With main graph we have scc likes; SCC1 -> SCC2 -> SCC3
With reverse graph we have scc likes: SCC1 <- SCC2 <- SCC3
So when we perform the DFS on transpose graph and start to explore the SCC2 nodes... all nodes of SCC1 are
visited because they are the first who popped out from the topo stack. So we can skip visited node(or we can say we can't update the low-link value(similar to tarjan algorithm))
And to achieve this behaviour, we start with node which explored at last(indirectly used that topo stack)


*/

void dfs(int node, vector<int> adjList[], vector<int> &visited, stack<int> &st) {
    visited[node] = 1;
    for (auto it : adjList) {
        if (!visited[it]) {
            dfs(i, adjList, visited, st);
        }
    }
    st.push(node);
}


void dfsRev(int node, vector<int> adjList[], vector<int> &visited) {
    visited[node] = 1;
    for (auto it : adjList) {
        if (!visited[it]) {
            dfs(i, adjList, visited, st);
        }
    }
}



int getTotalSCC(vector<int> adjList[], int V) {

    vector<int> visited(V + 1, 0);
    stack<int> st;  // topo stack. 
    for (int i = 1; i <= V; i++) {
        if (!visited[i]) {
            dfs(i, adjList, visited, st);
        }
    }

    // 2. Transpose of the graph as adjListT.
    vector<int> adjListT[V + 1];
    for (int node = 1; node <= V; node++) {
        for (auto it : adjList[node]) {
            adjListT[it].push_back(node);
        }
    }


    // 3. Again perform the DFS on adjListT
    int totalSCC = 0;
    visited.resize(V + 1, 0); // clear the visited array to peform DFS again.
    while (!st.empty()) {
        int node = st.top(); st.pop();
        if (!visited[node]) {
            //(optinal) we can pass new list in dfsRev()... to get all nodes of SCC if required.
            totalSCC++; // everytime new call happen to dfsRev.. it means it is new SCC.
            dfsRev(node, adjListT, visited);
        }
    }

    return totalSCC;
}
```

### 17. Tarjan's Algorithm for Strongly Connected Components[O(V+E), O(V)]

```c

/* Intuition

Tarjan's algorithm is a single-pass DFS-based algorithm that finds SCCs using a depth-first search tree.
It uses a stack to keep track of the visited vertices and an array to record the low-link node
reachable from each vertex.

Graph is: 1 -> 2 -> 3 -> 1
And when we are at 3 and again try to visit 1 which is already visited that time...3 can reach to 1 which is lowest_id for 3.
It means 2 can also reach to 1. In short all are part of SCC.. because there is cycle and all can reach to each other through that cycle.


And we already knew that for directed graph to get all nodes which are in same-path,
we need stack & on_stack(array)(here) which keep track of which elements are on stack.


Using these two, we make sure SCC2 does not use low link value of SCC1, because SCC1 are already visited,
and not on stack.

*/

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
```

### 18.  Detecting Bridge in graph[O(V+E), O(V)]

```c

/* Intuition

Bridge Found: When the current "node", adjacent node(it) cannot reach to any ("current node or previous nodes of current "node") without
using (node -> it) edge. Then if we break that edge... sub-graph got separated from the main graph.

low_link[it] > ids[node] => Found bridge (node->it). 

Note: Remember, "it" node is already visited. 

*/

void dfs(int node, int parent, int &timer, vector<int> adjList[], vector<int> &ids, vector<int> &low_link, int &countOfBridges) {

    // mark as visited and update all the ids and low_link.
    visited[node] = 1;
    ids[node] = low_link[node] = timer;
    timer++;

    for (auto it : adjList[node]) {

        // Skip the parent edge.
        if (it == parent) continue;

        if (!visited[it]) {

            // peform dfs first.
            dfs(it, timer, adjList, ids, low_link, countOfBridges);

            // update the low_link.. minimum among all children.
            low_link[node] = min(low_link[node], low_link[it]);

            // Check for bridge.
            if (low_link[it] > ids[node]) {
                // cout << node << "-->" << it << endl; (bridge)
                countOfBridges++;
            }
        }
        else {
            // already visited node, have the lowest_value so update the low_link by considering its id.
            low_link[node] = min(low_link[node], ids[it]);
        }
    }
}

int getTotalNumberOfBridges(vector<int> adjList[], int V) {

    // keep track of visited node.
    vector<int> visited(V + 1, 0);

    // Keep track of DFS order
    vector<int> ids(V + 1, 0);

    // keep track of lowest node can be reached by "ith" node witout passing through parent
    vector<int> low_link(V + 1, 0);

    int timer = 1;
    int countOfBridges = 0;

    for (int i = 1; i <= V; i++) {
        if (!visited[i]) {
            dfs(i, -1, timer, adjList, visited, ids, low_link, countOfBridges)
        }
    }

    return countOfBridges;
}
```

### 19. Detecting Articulation point in graph[O(V+E), O(V)]

```c

/* Intuition

Articulation point Found: When the current "node", adjacent node(it) cannot reach to any ("previous nodes of current "node") without
without going through "node". Then if we remove that node... sub-graph got separated from the main graph.

low_link[it] >= ids[node] => Found Articulation point (node). 

Edge case: parent node have more than one child, it is articulation point.

Note: Remember, "it" node is already explored then we are checking this condition. 

*/

void dfs(int node, int parent, int &timer, vector<int> adjList[], vector<int> &ids, vector<int> &low_link, int &countOfArticulationPoint) {

    // mark as visited and update all the ids and low_link.
    visited[node] = 1;
    ids[node] = low_link[node] = timer;
    timer++;

    // count the individual child.
    int child = 0;

    for (auto it : adjList[node]) {

        // Skip the parent edge.
        if (it == parent) continue;

        if (!visited[it]) {

            // peform dfs first.
            dfs(it, timer, adjList, ids, low_link, countOfArticulationPoint);

            child++;

            // update the low_link.. minimum among all children.
            low_link[node] = min(low_link[node], low_link[it]);

            // Check for articulation point.
            if (low_link[it] >= ids[node] && parent != -1) {
                // cout << node << endl; (Artiuclation point, we can save in array as well)
                countOfArticulationPoint++;
            }
        }
        else {
            // already visited node, have the lowest_value so update the low_link by considering its id.
            low_link[node] = min(low_link[node], ids[it]);
        }
    }

    if (parent == -1 && child > 1) {
        // cout << parent << endl;  (Articulation ponint)
        countOfArticulationPoint++;
    }
}


int getTotalNumberOfArticulationPoint(vector<int> adjList[], int V) {

    // keep track of visited node.
    vector<int> visited(V + 1, 0);

    // Keep track of DFS order
    vector<int> ids(V + 1, 0);

    // keep track of lowest node can be reached by "ith" node witout passing through parent
    vector<int> low_link(V + 1, 0);

    int timer = 1;
    int countOfArticulationPoint = 0;

    for (int i = 1; i <= V; i++) {
        if (!visited[i]) {
            dfs(i, -1, timer, adjList, visited, ids, low_link, countOfArticulationPoint)
        }
    }

    return countOfArticulationPoint;
}
```

### ### 20. Bellman Ford Algorithm (SSSP with negative cycle)[O(E * (N-1)), O(V)]

```c
/* Intuition

Why Bellman Ford Algorithm For SSSP, When there is already Dijkstra ?
- Dijkstras's Algorithm find SSSP correctly, if and only if there is no negative edge. There is chance that,
with negative edge as well, dijkstra give correct answer but not 100%. Another concern is that, if in graph
negative cycle is present then Dijkstrat won't work(each iteration we get the best node with negative dist).

Due to that, Bellman Ford Algorithm is used,
    - To get SSSP with negative edge
    - Detect negative cycle (if present we won't get SSSP for all nodes)

Intuition behind this algorithm is that,

    If there are V vertices in the graph, then shorest path from "src" node to any other node have maximum "V-1" edges.

    What we do is, we perform the edge relexations for all the edges, for V-1 times. Because in worst case, at each
    iteration we get one edge relexed and propagate that changes to last node, require V-1 iterations.

    After perform edge relexations V-1 times,

        We peform one more time, to check any of node dist[] got changed.

        If yes, then there is negative cycle present in graph.

        If no, we get the SSSP.

    If negative cycle present in graph,

        And to get all nodes affected due to that cycle, we can again perform V-1 times edge relexations, so
        changes of 1st edge relexations can reach to last node in worst case.


*/
vector<int> bellmanFordSSSP(vector<pair<int, int>> adjList[], int V, int src) {

    int inf = 1000000; // don't take INT_MAX due to addition operation

    // dist to source for all other nodes.
    vector<int> dist(V + 1, inf);

    // to reach src->src, take 0 efforts.
    dist[src] = 0;

    // step-1: N-1 time edge relexation
    for (int i = 0; i < N - 1; i++) {
        for (int node = 1; node <= V; node++) {
            for (auto it : adjList[node]) {
                // edge relexation
                if (dist[node] + it.second < dist[it.first]) {
                    dist[it.first] = dist[node] + it.second;
                }
            }
        }
    }

    // step-2: Detect negative cycle and find out all nodes whose is affected.
    bool isNegativeCyclePresent = false;
    for (int node = 1; node <= V; node++) {
        for (auto it : adjList[node]) {
            if (dist[node] + it.second < dist[it.first]) {
                dist[it.first] = -inf;
                isNegativeCyclePresent = true;
            }
        }
    }

    // negative cycle presetn find all the nodes who are got affected due ot that.
    if (isNegativeCyclePresent) {
        for (int i = 0; i < N - 2; i++) {           // 1 time we alread processed.
            for (int node = 1; node <= V; node++) {
                for (auto it : adjList[node]) {
                    if (dist[node] + it.second < dist[it.first]) {
                        dist[it.first] = - inf;
                    }
                }
            }
        }
    }


    // print all the nodes whose dist is <= -inf.

    return dist;
}
```

### 21. Floyd Warshall Algorithm (All pairs shortest path algorithm) [O(V^3), O(V^2)]

```c
/* Intuition


It use the "incremental path improvement".

=> Basically, It tell us that try every vertex as intermidatory node and choose the best one.

A1 -> A5 then I can try every vertex...
A1 -> A2 + A2 -> A5
A1 -> A3 + A3 -> A5
A1 -> A4 + A4 -> A5

Along with that,
The algorithm builds up the solution iteratively, improving path estimates step
by step by considering increasingly longer paths with more intermediate nodes.

It begins with no intermediate nodes and only considers direct paths. 
Then, it checks if adding one node as an intermediate node can improve 
the shortest path between pairs, then two nodes, and so forth.

iteration = 0 => direct edge (u -> v)
iteration = 1 => dp[u][v] => minimum((u -> i) -> (i -> v))
iteration = 2 => dp[u][v] => minimum((u->i->j) -> (j -> k -> v))
    What I mean is that, for iteration=2, when we again put all node as intermidatory
    node that time we are putting the chain of two nodes as intermidatory, because
    we are using the result of previous iteration. 
    Ex:
    A1 -> A3 => A1 -> A2 + A2 -> A3 => min(A1->A0->A2 , A1->A5->A2)(A1->A2)(This is already calculated and one of the lowest stored in A1->A2 so we use that) + A2->A3
  

And to propogate the change to every other node we need to peform same thing N(total_vertex) times. (incremental path build up)

A1 -> A2 -> A3 -> A4 -> A5... this is path.. okay during first iteration suppose A1 got updated with best value, which is
also works for all other nodes who is depend on that.. to propagate A1 change to A5 we need to peform same thing
5 times so each time one of the node got changes which can be propogate to next node during next iteration.


*/

vector<vector<int>> floydWarshallAlgo(vector<pair<int, int>> adjList[], int V) {

    // keep track of shortest distance from A->B
    vector<vector<int>> dp(V, vector<int>(V, 0));

    // Reused to construct path
    vector<vector<int>> next(V, vector<int>(V, 0));

    // 1) Setup the adjMat so we can use that....(base-iteration(k=0))
    for (int u = 0; u < V; u++) {
        for (auto v : adjList[u]) {
            dp[u][v.first] = v.second;      // (node, wt)
            next[u][v.first] = v.first;     // Visit (U->V) means go to V node after U.
        }
    }

    // 2) Heart of algorithm: Iterate V times to get the shortest distance between all nodes.. considering each node as intermidatory node
    for (int k = 0; k < V; k++) {
        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                // Relexation considring k as intermidatory node.
                if (dp[u][k] + dp[k][v] < dp[u][v]) {
                    dp[u][v] = dp[u][k] + dp[k][v];
                    next[u][v] = next[u][k];
                }
            }
        }
    }


    // (optional if asked) 3) Cycle Detecation (Propagate change to last node)
    bool isNegativeCycle = false;
    for (int k = 0; k < V; k++) {
        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                // Relexation considring k as intermidatory node. (if relexation happen there is cycle)
                if (dp[u][k] + dp[k][v] < dp[u][v]) {
                    isNegativeCycle = true;
                    dp[u][v] = -INF;
                    next[u][v] = -1;
                }
            }
        }
    }


    // (optional if asked) 4) Reconstruct path between two nodes.
    int start = u; // (given in question)
    int end = v; // (given in question)

    // there is negative cycle affected this node... no path found
    if (dp[start][end] == -INF) return {};

    vector<int> path;   // to store the path.

    for (int at = start; at != end, at = next[at][end]) {
        if (at == -1) return {}; // negative cycle affected this one
        path.push_back(at);
    }
    path.push_back(end);

    return path;

}
```
