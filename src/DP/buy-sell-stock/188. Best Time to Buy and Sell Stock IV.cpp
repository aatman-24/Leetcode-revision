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

Question : 188. Best Time to Buy and Sell Stock IV
Topic : DP
Problems : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/description/
==============================> Explanation <=============================================

Pattern: Buy-Sell-Stocks
Parent: 123. Best Time to Buy and Sell Stock III

In #123, Given that we can do maxTrans = 2... Here we are allowed to do maxTrans = k. That's the diff only.

So just increase the limit of maxTrans from 2 => K.

Check the code(same code!!)

==============================> Approach and Time Complexity <============================


1) DP
Time: O(2^N) => O(N)
Space: O(N*K)

 */




class Solution {
public:


    int t[100001][2][100];

    int maxProfitSupport(int day, int buyToAllowed, int curTran, vector<int>& prices, int maxTran) {

        // Base case (change here)
        if (day == prices.size() || curTran >= maxTran)
            return 0;

        if (t[day][buyToAllowed][curTran] != -1)
            return t[day][buyToAllowed][curTran];

        int profit;
        if (buyToAllowed) {
            profit = max(-prices[day] + maxProfitSupport(day + 1, !buyToAllowed, curTran, prices, maxTran), 0 + maxProfitSupport(day + 1, buyToAllowed, curTran, prices, maxTran));
        }
        else {
            profit = max(prices[day] + maxProfitSupport(day + 1, !buyToAllowed, curTran + 1, prices, maxTran), 0 + maxProfitSupport(day + 1, buyToAllowed, curTran, prices, maxTran));
        }


        return t[day][buyToAllowed][curTran] = profit;
    }


    int maxProfit(int k, vector<int>& prices) {
        memset(t, -1, sizeof(t));
        int curTran = 0;
        int buyToAllowed = 1;
        return maxProfitSupport(0, buyToAllowed, curTran, prices, k);
    }
};






class Solution {
public:

    int maxProfit(int k, vector<int>& prices) {

        int m = prices.size();
        int maxTran = k;

        // (change here, increase the limit)
        vector<vector<vector<int>>> dp(m + 1, vector<vector<int>>(2, vector<int>(maxTran + 1, 0)));

        // Base case (All covered during initialization)
        // dp[m][j][k] = 0;
        // dp[m][j][k] = 0;

        // dp[i][j][maxTran] = 0;
        // dp[j][j][maxTran] = 0;

        for (int day = m - 1; day >= 0; day--) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < maxTran; k++) {
                    int profit = 0;
                    if (j == 1) {
                        profit = max(-prices[day] + dp[day + 1][!j][k], dp[day + 1][j][k]);
                    }
                    else {
                        profit = max(prices[day] + dp[day + 1][!j][k + 1], dp[day + 1][j][k]);
                    }
                    dp[day][j][k] = profit;
                }
            }
        }

        return dp[0][1][0]; // get idea from top-down, where we start at day=0, buyToAllowed=1, curTran = 0
    }
}