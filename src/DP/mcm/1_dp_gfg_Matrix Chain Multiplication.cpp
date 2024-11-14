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

Question : 1_dp_gfg_Matrix Chain Multiplication
Topic : DP=MCM
Problems : https://www.geeksforgeeks.org/problems/matrix-chain-multiplication0303
==============================> Explanation <=============================================

Pattern: MCM

Standard question.

Given the arr[] = {10, 20, 30, 40}

M1 = 10 X 20
M2 = 20 X 30
M3 = 30 X 40

We need to find minimum multiplication cost.

Ex: M1 * (M2 * M3) || (M1 * M2) * M3

For multiplying matrix we need atleast two matrix, for single matrix cost will be zero. (base case)

What we will do is, we try to make cut at every ith index starting from 1th index.

suppose we are making cut at kth index = {i....k...j}

cost = cost(i, k) + cost(k, j) + multiplication_cost(i, k, j)...

multiplication_cost = M1 * M2 => A[i-1] * A[K] * A[J]...considering(M1 = i-1 * K, M2 = K * j dimensions)

we are not sure what combination is best for (i..k) range so we again apply recursion there to find minimum cost.

Check, recursive and top-down approach...

Bottom-up approach: When we see mcm(1, 4) this calls to mcm(2, 4) | mcm(3, 4).... get idea from top-down.

In Bottom-up, we need to start i = N - 1 -> 0.... so when we compute mcm(1, 4) that time we have result of mcm(2, 4) and mcm(3, 4)

Check the code...

==============================> Approach and Time Complexity <============================

1) DP
Time: O(N^2)
Space: O(N^2)

 */


// Recursive Solution
int mcm(int arr[], int i, int j) {

    // base condition
    if (i == j || i > j)
        return 0;

    int minCost = INT_MAX;
    for (int k = i; k <= j - 1; k++) {
        int cost = mcm(arr, i, k) + mcm(arr, k + 1, j) + arr[i - 1] * arr[k] * arr[j];
        minCost = min(minCost, cost);
    }

    return minCost;
}


int matrixMultiplication(int N, int arr[]) {
    return mcm(arr, 1, N - 1);
}

// Top-down
int t[101][101];

int mcm(int arr[], int i, int j) {

    // base condition
    if (i == j || i > j)
        return 0;

    if (t[i][j] != -1)
        return t[i][j];

    int minCost = INT_MAX;
    // M1 = (i-1, i), M2 = (k, j)
    for (int k = i; k <= j - 1; k++) {
        int cost = mcm(arr, i, k) + mcm(arr, k + 1, j) + arr[i - 1] * arr[k] * arr[j];
        minCost = min(minCost, cost);
    }

    return t[i][j] = minCost;
}


int matrixMultiplication(int N, int arr[]) {
    memset(t, -1, sizeof(t));
    return mcm(arr, 1, N - 1);
}



// Bottom-up

int matrixMultiplication(int N, int arr[]) {

    vector<vector<int>> dp(N + 1, vector<int>(N + 1, 0));

    // base condition
    // dp[0][0] = dp[1][1] = dp[2][2] = 0; (covered during initalization)


    // Started with i = N-1, because if you see top-down approach.... it will
    // first solve (4, 5) and then (0, 4) because (0,4) needs (4, 5) as intermidatory result.
    for (int i = N - 1; i >= 0; i--) {
        for (int j = i + 1; j < N; j++) {   // j = i+1, because i < j
            int minCost = INT_MAX;
            for (int k = i; k <= j - 1; k++) {
                int cost = dp[i][k] + dp[k + 1][j] + arr[i - 1] * arr[k] * arr[j];
                minCost = min(minCost, cost);
            }
            dp[i][j] = minCost;
        }
    }

    return dp[1][N - 1];
}
