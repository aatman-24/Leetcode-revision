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

Question : 309. Best Time to Buy and Sell Stock with Cooldown
Topic : DP
Problems : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/description/
==============================> Explanation <=============================================

Pattern: Buy-Sell-Stocks
Parent: 122. Best Time to Buy and Sell Stock II

We derived recurrent relation in #122.. where we can buy and sell stocks any number of times.

Recurrence Relation:

    solve(day, buyToAllowed) =>

        buyToAllowed==1: max(-prices[day] + solve(day+1, !buyToAllowed), 0 + solve(day+1, buyToAllowed))
        buyToAllowed==0: max(prices[day] + solve(day+1, !buyToAllowed), 0 + solve(day+1, buyToAllowed))

This relations indicate that...we can buy and sell stocks any times... but we can't have two transactions running same(means buy stocks, sell those and again we can buy it).
But we can't do buy-buy-sell-sell such transactions. Hope you get it!

Also in this recurrent relation, we can bought stocks next day if we sold on current day.

In this question, cooldown period = 1 day.... which means if you complete the transactions(buy-sell) then you need to wait for additional one day before you again buy.

It means.. if you sell it ith day... then you can again buy at (i+2)th day directly....

Cooldown period applys during the selling only.... So there is little change in equations....


Recurrence Relation:

    solve(day, buyToAllowed) =>

        buyToAllowed==1: max(-prices[day] + solve(day+1, !buyToAllowed), 0 + solve(day+1, buyToAllowed))
        buyToAllowed==0: max(prices[day] + solve(day+2*, !buyToAllowed), 0 + solve(day+1, buyToAllowed))

Just when we sell the stocks.. instead of jumping to next day (day+1) we move to (day+2).

Other all things remain same...

Check the code!!...

==============================> Approach and Time Complexity <============================
1) DP
Time: O(2^N) => O(N)
Space: O(N)


 */

// Top-down approach

class Solution {
public:

    int t[5001][2];

    int maxProfitHelper(int day, int allowedToBuy, vector<int>& prices) {

        // base condition change... day > prices.size() as well so need to think about that as well.
        if (day >= prices.size())
            return 0;

        if (t[day][allowedToBuy] != -1)
            return t[day][allowedToBuy];

        int profit = 0;

        if (allowedToBuy) {
            profit = max(-prices[day] + maxProfitHelper(day + 1, !allowedToBuy, prices), 0 + maxProfitHelper(day + 1, allowedToBuy, prices));
        }
        else {
            // once we sell, we can't buy at day+1... due to cooldown period, so we can buy on (day+2) directly.
            profit = max(prices[day] + maxProfitHelper(day + 2, !allowedToBuy, prices), 0 + maxProfitHelper(day + 1, allowedToBuy, prices));
        }

        return t[day][allowedToBuy] = profit;
    }


    int maxProfit(vector<int>& prices) {

        memset(t, -1, sizeof(t));

        return maxProfitHelper(0, 1, prices);
    }
};

// Bottom-up Approach (Just converted top-down in bottom-up)


class Solution {
public:

    int maxProfit(vector<int>& prices) {

        int m = prices.size();

        // dp table.
        vector<vector<int>> dp(m + 2, vector<int>(2, 0));   // day=(m-1) => dp[day+2] => dp[m-1+2] => dp[m+1] considering that we have added one more row in dp table.

        // base condition.. (Already convered during initialization)
        // dp[m][j] = 0;
        // dp[m+1][j] = 0;

        for (int day = m - 1; day >= 0; day--) {
            dp[day][1] = max(-prices[day] + dp[day + 1][0], 0 + dp[day + 1][1]);
            dp[day][0] = max(prices[day] + dp[day + 2][1], 0 + dp[day + 1][0]);
        }

        return dp[0][1];
    }
};