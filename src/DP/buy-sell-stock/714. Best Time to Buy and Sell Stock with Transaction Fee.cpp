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

Question : 714. Best Time to Buy and Sell Stock with Transaction Fee
Topic : DP
Problems : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/description/
==============================> Explanation <=============================================

Pattern: Buy-Sell-Stocks
Parent: 122. Best Time to Buy and Sell Stock II

We derived recurrent relation in #122.. where we can buy and sell stocks any number of times.

Recurrence Relation:

    solve(day, buyToAllowed) =>

        buyToAllowed==1: max(-prices[day] + solve(day+1, !buyToAllowed), 0 + solve(day+1, buyToAllowed))
        buyToAllowed==0: max(prices[day] + solve(day+1, !buyToAllowed), 0 + solve(day+1, buyToAllowed))

This one indicate, we can't running two transaction same times, and transaction fee is zero, and we can do any no. of transactions.

Let's applied the transaction fee on this equation,

    Given that when we complete transaction (buy-sell), then for all transactions single transaction fee is applied. It means we can subtract that
    during buy/sell times... let's apply during sell... (because most of question have little change during sell times only... no specific reason)..


    solve(day, buyToAllowed) =>

        buyToAllowed==1: max(-prices[day] + solve(day+1, !buyToAllowed), 0 + solve(day+1, buyToAllowed))
        buyToAllowed==0: max(prices[day] - fee + solve(day+1, !buyToAllowed), 0 + solve(day+1, buyToAllowed))

Check the code!!


==============================> Approach and Time Complexity <============================

1) DP
Time: O(2^N) => O(N)
Space: O(N)

 */


// Top-down Approach
class Solution {
public:

    int t[50001][2];

    int maxProfitSupport(int day, int allowedToBuy, vector<int> &prices, int fee) {

        if (day == prices.size())
            return 0;

        if (t[day][allowedToBuy] != -1) {
            return t[day][allowedToBuy];
        }

        int profit = 0;
        if (allowedToBuy) {
            profit = max(-prices[day] + maxProfitSupport(day + 1, !allowedToBuy, prices, fee), 0 + maxProfitSupport(day + 1, allowedToBuy, prices, fee));
        }
        else {
            // fee applied during selling of stocks (we can put during buying as well... )
            profit = max(prices[day] - fee + maxProfitSupport(day + 1, !allowedToBuy, prices, fee), 0 + maxProfitSupport(day + 1, allowedToBuy, prices, fee));
        }

        return t[day][allowedToBuy] = profit;
    }



    int maxProfit(vector<int>& prices, int fee) {
        memset(t, -1, sizeof(t));
        return maxProfitSupport(0, 1, prices, fee);
    }
};


// Bottom-up Apporach
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {

        int m = prices.size();

        // dp table
        vector<vector<int>> dp(m + 1, vector<int> (2, 0));

        // base case (added during dp table initialization)
        // dp[0][j] = 0;

        for (int day = m - 1; day >= 0; day--) {
            dp[day][1] = max(-prices[day] + dp[day + 1][0], 0 + dp[day + 1][1]);
            dp[day][0] = max(prices[day] - fee + dp[day + 1][1], 0 + dp[day + 1][0]);
        }

        return dp[0][1];
    }
};

