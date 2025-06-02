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
================================================================================
                                Problem Description
================================================================================

Problem: NC_37_Best Time to Buy and Sell Stock
Topic: Two Pointer
Link: https://neetcode.io/problems/buy-and-sell-crypto

================================================================================
                                Problem Summary
================================================================================

You can do one transaction to buy a stock at any single and you need to sell it
to maximize the profit.

================================================================================
                                Intuition & Explanation
================================================================================

We already know the dynamic programming approach for this problem:

For any given day, if we want to sell the stock, we need the minimum price from
the range (0 to day-1).
The formula becomes:

    maxProfit = prices[day] - minBuyingPriceSoFar

Apart from that, we also have the classic DP state transition for buy/sell stock:

    if (buyAllowed) {
        max(-prices[day] + solve(day+1, false), solve(day+1, true))
    } else {
        max(prices[day] + solve(day+1, true), solve(day+1, false))
    }

However, in this problem, we are using the **Two Pointer (Sliding Window)** approach:

- `left` → points to the day with the current minimum price in the window
- `right` → acts as a runner pointer scanning forward

We update the maximum profit at each step based on:

    if (prices[left] < prices[right]) {
        // Profit is possible, track it
        maxProfit = max(maxProfit, prices[right] - prices[left])
        right++
    } else {
        // Current price is lower or equal, update left
        left = right
        right++
    }

Check the code for implementation details.

================================================================================
                          Approach & Time/Space Complexity
================================================================================

Approach: Two pointer (Sliding window)
Time Complexity: O(N)
Space Complexity: O(N)

*/


class Solution {
public:

    int maxProfit(vector<int>& prices) {

        int left = 0, right = 1;

        int profit = 0;

        while (right < prices.size()) {

            if (prices[left] < prices[right]) {

                profit = max(profit, prices[right] - prices[left]);

            }

            // prices[right] < prices[left]
            else {

                left = right;
            }

            right++;
        }


        return profit;
    }
};