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

Question : 123. Best Time to Buy and Sell Stock III
Topic : DP
Problems : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/description/

==============================> Explanation <=============================================

Pattern: Buy-Sell-Stocks

122. Best Time to Buy and Sell Stock II

Given that, We can do upto two maximum transaction, and try to get maximum profit. It means that,

    we can do (buy-sell) -> (buy-sell)... maximum 2 times only.

We derived this recurrence relation for this pattern in #122,

    solve(day, buyToAllowed) =>

        buyToAllowed==1: max(-prices[day] + solve(day+1, !buyToAllowed), 0 + solve(day+1, buyToAllowed))
        buyToAllowed==0: max(prices[day] + solve(day+1, !buyToAllowed), 0 + solve(day+1, buyToAllowed))

This recurrent relation allowed us to perform unlimited transactions, but now we want to restrict that upto 2(maxTran).

It means, that we need to keep track of transaction we are currently on. Whenever we exceed the limit we return profit as 0(base case).

For that, let's introduce new variable to signature which keep track "no_of_transaction" we are at.

New Recurreance Relation:

    solve(day, buyToAllowed, curTran) =>

        buyToAllowed==1: max(-prices[day] + solve(day+1, !buyToAllowed, curTran), 0 + solve(day+1, buyToAllowed, curTran))
        buyToAllowed==0: max(prices[day] + solve(day+1, !buyToAllowed, curTran+1), 0 + solve(day+1, buyToAllowed, curTran))

When curTran is overed and new Transaction Start ?

    When first (buy-sell) pair got completed, it means when we sell the stock that time only we move to new transaction...

        selling_stock = prices[day] + solve(day+1, !buyToAllowed, curTran+1)

And we need to add one base case,

    curTran >= maxTran => return 0 (it means, doesn't allow to buy-sell more stocks).

Check the code!!

Bottom-up approach, we simply converted top-down into BU.

==============================> Approach and Time Complexity <============================

1) DP
Time: O(2^N) => O(N)
Space: O(N)

 */



// Top-down Appraoch
class Solution {
public:


    int t[100001][2][2];

    int maxProfitSupport(int day, int buyToAllowed, int curTran, vector<int>& prices) {

        // Base case
        if (day == prices.size() || curTran >= 2)
            return 0;

        if (t[day][buyToAllowed][curTran] != -1)
            return t[day][buyToAllowed][curTran];

        int profit;
        if (buyToAllowed) {
            profit = max(-prices[day] + maxProfitSupport(day + 1, !buyToAllowed, curTran, prices), 0 + maxProfitSupport(day + 1, buyToAllowed, curTran, prices));
        }
        else {
            profit = max(prices[day] + maxProfitSupport(day + 1, !buyToAllowed, curTran + 1, prices), 0 + maxProfitSupport(day + 1, buyToAllowed, curTran, prices));
        }


        return t[day][buyToAllowed][curTran] = profit;
    }


    int maxProfit(vector<int>& prices) {
        memset(t, -1, sizeof(t));
        int curTran = 0;
        int buyToAllowed = 1;
        return maxProfitSupport(0, buyToAllowed, curTran, prices);
    }
};


// Bottom-Up Appraoch
class Solution {
public:

    int maxProfit(vector<int>& prices) {

        int m = prices.size();

        vector<vector<vector<int>>> dp(m + 1, vector<vector<int>>(2, vector<int>(3, 0)));

        // Base case (All covered during initialization)
        // dp[m][j][k] = 0;
        // dp[m][j][k] = 0;

        // dp[i][j][2] = 0;
        // dp[j][j][2] = 0;


        for (int day = m - 1; day >= 0; day--) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
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
};