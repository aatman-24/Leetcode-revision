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

Question : 121. Best Time to Buy and Sell Stock
Topic : DP
Problems : https://leetcode.com/problems/best-time-to-buy-and-sell-stock/description/
==============================> Explanation <=============================================

Pattern: Buy-Sell-Stocks

Parent: 122. Best Time to Buy and Sell Stock II

To get maximum profit we tend to buy at minimum price and sell at highest price.

So we apply brute force,

    for any day=i... we try to get minimum price from (0, i-1) and sell it at current day=i, and keep track of maximum profit.

And each recursion call return minimum buying price to previous recursion call(i+1 day).

Check the code... you will get idea..

==============================> Approach and Time Complexity <============================

1) DP
Time: O(N)
Space: O(N) => O(1)

 */


// Top-down Approach
class Solution {
public:

    // Keep track of maximum Profit.
    int maximumProfit = 0;

    int getMinBuyingPriceForDay(int day, vector<int> &prices) {

        // Base case: At 0th day... we can't sell anything so maximumProfit = 0.
        if (day == 0)
            return prices[0];

        int minBuying = getMinBuyingPriceForDay(day - 1, prices);
        if (prices[day] - minBuying > maximumProfit) {
            maximumProfit = prices[day] - minBuying;
        }

        // return minimum buying price for next day (day+1)
        return min(prices[day], minBuying);
    }

    int maxProfit(vector<int>& prices) {
        getMinBuyingPriceForDay(prices.size() - 1, prices);
        return maximumProfit;
    }
};

// Bottom-up
class Solution {
public:

    int maxProfit(vector<int>& prices) {

        // Keep track of maximum Profit.
        int maximumProfit = 0;

        int m = prices.size();

        // Base case
        int minBuying = prices[0];

        for (int day = 1; day < m; day++) {

            if (prices[day] - minBuying > maximumProfit) {
                maximumProfit = prices[day] - minBuying;
            }

            minBuying = min(prices[day], minBuying);
        }

        return maximumProfit;
    }
};



// These are dp solution.... which needs to be used compare to previous one....

class Solution {
public:

    int t[100001][2];

    int maxProfitHelper(int day, int buyToAllow, vector<int> &prices) {

        if (day == prices.size())
            return 0;

        if (t[day][buyToAllow] != -1)
            return t[day][buyToAllow];

        if (buyToAllow) {       // indicate, we can buy and sell later.
            return t[day][buyToAllow] = max(-prices[day] + maxProfitHelper(day + 1, 0, prices), 0 + maxProfitHelper(day + 1, 1, prices));
        }
        else {      // we can only sell later with good price... no buy chain(buy-sell-stock-2 diff)
            return t[day][buyToAllow] = max(prices[day], maxProfitHelper(day + 1, 0, prices));
        }

    }

    int maxProfit(vector<int>& prices) {

        memset(t, -1, sizeof(t));

        return maxProfitHelper(0, 1, prices);
    }
};



// Top-down Approach
class Solution {
public:

    int maxProfit(vector<int>& prices) {

        int m = prices.size();

        vector<vector<int>> dp(m + 1, vector<int>(2, 0));

        // Base case
        dp[m][0] = 0;
        dp[m][1] = 0;

        for (int day = m - 1; day >= 0; day--) {
            dp[day][1] = max(-prices[day] + dp[day + 1][0], 0 + dp[day + 1][1]);
            dp[day][0] = max(prices[day], dp[day + 1][0]);
        }

        return dp[0][0];
    }
};