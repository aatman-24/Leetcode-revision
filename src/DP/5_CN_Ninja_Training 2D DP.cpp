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

Question : 5_CN_Ninja_Training 2D DP
Topic : DP
Problems : https://www.naukri.com/code360/problems/ninja-s-training_3621003
==============================> Explanation <=============================================

Pattern: 2D-DP-Grid

Basically I need to try all possible ways using backtesting and choose the best among them, what I mean is that

I can select any task at day=0 and then day=1, I make sure I won't select the same task, moving forward day=2.. I make sure I won't select the previous day selected task.

So there are many combination possible, which is backtesting and will apply DP to use as memory.

Check the code..

How to convert the 2D DP problem from Top Down => Bottom Up Apporach ?

Check top-down approach, you can see three different variable,
    1) day (running from 0 -> M)
    2) task (running from 0 -> N)
    3) nextTask (running form 0 -> N)

We are having three diff variables because we can't choose the same task in subsequent days.

Let me explain how recursion/backtraking will happen,

    1) ninjaTraining() function, we try to pick up every task at first day(0) and choose the maximum of that.
    2) ninjaTrainingHelper() function, we try to get next task at next day which maximize the cost.

    Basically, We are running loops, two directly in both function and one through recursion.





So It is obvious that, when we convert the TD -> BU, We need to three loops to keep track of each variable.

TD:

    int maxCost = 0;
    for(int task = 0; task < N; task++) {
        maxCost = max(maxCost, ninjaTrainingHelper(points, 0, task));
    }

    ninjaTrainingHelper(day, task) {

        for(int nextTask = 0; nextTask < points[0].size(); i++) {

            if(nextTask != task) {

                maxCost = max(maxCost, points[day][task] + ninjaTraining(points, day+1, nextTask));

            }
        }
    }

BU:

Why day is outer loop ? Because the decision of ith day is depend on decision of (i-1)th day, or next day(i+1)th. That is reason
it will be the outer loop.

So after all the empty cell is filled of day = M-2, then we can make decision for M-1 day based on that output.

    for(int day = M - 2; day >= 0; day--) {
        for(int task = 0; task < N; task++) {
            int maxCost = 0;
            for(int nextTask=0; nextTask < N; nextTask++) {
                if(task != nextTask) {
                    maxCost = max(maxCost, points[day][task] + dp[day+1][nextTask]);
                }
            }
            dp[d][task] = maxCost;
        }
    }


BUS:

    We know that dp[i][k] result is depend on dp[i+1][k] state.

    so instead of having entire 2D array we can have single array which can hold the previous calculated state.

    We can keep swap last previous calculated state with 1D DP to optimize the code check.



==============================> Approach and Time Complexity <============================

1) DP
Time: O(2^N) -> O(N^2), Given T = 3(constant)
Space: O(N) (stack space)

Backtesting:
- I can select or not select task at given day.. two choice.. breadth = 2, depth = N,

O(3) processing time at each node.

 */


// TD (0 -> N)
/* Intuition:
    Basically I need to try all possible ways using backtesting and choose the best among them, what I mean is that
    I can select any task at day=0 and then day=1, I make sure I won't select the same task, moving forward day=2.. I make sure I won't select the previous day selected task.
    So there are many combination possible, which is backtesting and will apply DP to use as memory.

    Recurrence Relation,
        f(day, task) =>
            nextTask: 1 => N,
                if(task != nextTask):
                    max(points[day][task] + f(day+1, nextTask)) // return maximum of this

*/

int t[100001][11];

int ninjaTrainingHelper(vector<vector<int>> &points, int day, int task) {

    // base case (reached at last day)
    if (day == points.size() - 1)
        return points[day][task];

    if (t[day][task] != -1)
        return t[day][task];

    int maxCost = 0;

    for (int nextTask = 0; nextTask < points[0].size(); i++) {

        if (nextTask != task) {

            maxCost = max(maxCost, points[day][task] + ninjaTraining(points, day + 1, nextTask));

        }
    }

    return t[day][task] = maxCost;
}


int ninjaTraining(int n, vector<vector<int>> &points) {

    int M = points.size(), N = points[0].size();
    memset(t, -1, sizeof(t));

    int maxCost = 0;
    for (int task = 0; task < N; task++) {

        // At day=0, I can pick one of task which give maximum cost.
        maxCost = max(maxCost, ninjaTrainingHelper(points, 0, task));
    }

    return maxCost;
}




// BU
int ninjaTraining(int n, vector<vector<int>> &points) {

    int M = points.size(), N = points[0].size();

    // dp table. [day][task]
    vector<vector<int>> dp(M + 1, vector<int>(N + 1, 0));

    // base case. (for day = M - 1)
    for (int t = 0; t < N; t++) {
        dp[M - 1][t] = points[M - 1][t];
    }

    for (int d = M - 2; d >= 0; d--) {
        for (int task = 0; task < N; task++) {
            int maxCost = 0;
            for (int nextTask = 0; nextTask < N; nextTask++) {
                if (task != nextTask) {
                    maxCost = max(maxCost, points[d][task] + dp[d + 1][nextTask]);
                }
            }
            dp[d][task] = maxCost;
        }
    }

    int bestCost = 0;
    for (int i = 0; i < N; i++) {
        bestCost = max(bestCost, dp[0][i]);
    }

    return bestCost;
}


// BUS

int ninjaTraining(int n, vector<vector<int>> &points) {

    int M = points.size(), N = points[0].size();

    // dp row only. (Which hold ith state result)
    vector<int> dp(N + 1, 0);

    // base case.
    for (int t = 0; t < N; t++) {
        dp[t] = points[M - 1][t];
    }

    // Use three variable to compute task.
    for (int d = M - 2; d >= 0; d--) {

        // Storing the current state resutl into new array.
        vector<int> curr_dp(N + 1, 0);

        for (int task = 0; task < N; task++) {

            // same as recursion.
            int maxCost = 0;
            for (int nextTask = 0; nextTask < N; nextTask++) {
                if (task != nextTask) {
                    maxCost = max(maxCost, points[d][task] + dp[nextTask]);
                }
            }
            curr_dp[task] = maxCost;
        }

        // forwarding ith state result to dp array.
        dp = curr_dp;
    }

    // At the dp[0][i] containts the max cost, if we started from that 0th day. So we need to take maximum of that.
    // This also work as base case when N = 1.
    int bestCost = 0;
    for (int i = 0; i < N; i++) {
        bestCost = max(bestCost, dp[i]);
    }

    return bestCost;
}
