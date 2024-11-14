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

Question : 2_Frog_2
Topic : DP
Problems : https://atcoder.jp/contests/dp/tasks/dp_b
==============================> Explanation <=============================================

Pattern: DP-Fib

Parent Problem: 1_CN_Frog Jump

Here frog can jump to any next K stone instead of 1 & 2. So we need to find the minimum cost among all the possibilites at given index.

Recurrance Relation:

    For j = 1 -> K,
        f(i) = min_cost(f(i-1) + abs(h[i] - h[i-1-j]))

Choosing the minium cost among all possible ways.

==============================> Approach and Time Complexity <============================

1) DP
Time: O(K) * O(K^N) => O(K*N)
Space: O(N) => O(K)

O(K) => processing time take at each node.
K => breadth
N => depth.

 */


// TD

/* Intuition:

Here frog can jump to any next K stone instead of 1 & 2. So we need to find the minimum cost among all the possibilites at given index.

Recurrance Relation:

    For j = 1 -> K,
        f(i) = min_cost(f(i-1) + abs(h[i] - h[i-1-j]))

*/

int memo[100001];

int frogJump(vector<int> &heights, int index, int k) {          // index=N.

    if (index == 1)
        return 0;       // base case, standing at 1st and reaching to 1st stone, no energy required.

    if (memo[index] != -1)
        return memo[index];

    int minCost = INT_MAX;
    for (int j = 1; j <= k; j++) {
        if ((index - j) > 0) {
            minCost = min(minCost, frogJump(heights, index - j, k) + abs(heights[index - 1] - heights[index - 1 - j]));
        }
    }

    return memo[index] = minCost;

}

// BU
int frogJump(vector<int> &heights, int N, int k) {

    // Base Case
    if (N == 1)
        return 0;

    vector<int> dp(N + 1, -1);

    // base case.
    dp[1] = 0;

    for (int i = 2; i <= N; i++) {
        int minCost = INT_MAX;
        for (int j = 1; j <= k; j++) {      // can jump upto k stone.
            if ((i - j) > 0) {
                minCost = min(minCost, dp[i - j] + abs(heights[i - 1] - heights[i - 1 - j]));
            }
        }
        dp[i] = minCost;
    }

    return dp[N];
}


// BU-Space: We need to know the last K state only. Space:O(K)
// We need to override the kth state every time.. what I mean is that... state=1, k=3 then when we reach at
// state=4..then we store that result at dp[(state-k)=(4-3)=1]..got it ?
int frogJump2(vector<int> &heights, int N, int k) {

    // Base Case
    if (N == 1)
        return 0;

    vector<int> dp(k + 1, -1);

    // offset to adjust dp table index. As we are using the % operator for overriding we need to store result starting from 0th index for easiness.
    // but do this step later.. first write code and then offet the dp table index only.
    // you know why we need to use % K...right.
    int OFFSET = 1;

    // base case.
    dp[1 - OFFSET] = 0;

    for (int i = 2; i <= N; i++) {
        int minCost = INT_MAX;
        for (int j = 1; j <= k; j++) {      // can jump upto k stone.
            if ((i - j) > 0) {
                minCost = min(minCost, dp[(i - j - OFFSET) % k] + abs(heights[i - 1] - heights[i - 1 - j]));
            }
        }
        dp[(i - OFFSET) % k] = minCost;
    }

    return dp[(N - OFFSET) % k];
}