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

Question : 122. Best Time to Buy and Sell Stock II
Topic : DP
Problems : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/description/
==============================> Explanation <=============================================

Pattern: Buy-Sell-Stocks

Not easy to understand (Try to understand the pattern).

- Given that, any ith day... you can buy/sell stock. And once you sell the stock at jth day.. you can again buy it.

Which indicate that, if you buy at 1st day... then you can sell it 2nd/3rd/4th... any day....
Same way, if you buy at 2nd day....then you can sell it any day...

Thing is.. how you determine the previous days state(0, i-1).... and based on that decide to buy/sell at current ith day.

For that, we need one more variable (allowToBuy) which indicate whether we can buy at give day or not...

(day, allowToBuy) become our signature.


**How do you calculate the profit ?**
profit = -buyAmount + sellAmount
So if we are buying first then we deduce the prices[i] and when we sell it we add prices[i].. and diff will be profit.

**How to create buy-sell and again buy-sell chain to maximize the profit can we create ?**

Initially, we are allowed to buy at 0th day...

    Understand, one thing we need to try all possible ways to get optimium solution. What I mean is that buy at every ith day and sell at every jth day. i < j.

    To do that, if allowToBuy=true means we are allowed to buy at ith day... but to try all combination we "can buy" and "not do buy".

    Same, allowToBuy=false means we are allowed to sell at jth day...but to try all combination for selling side we "can sell" or "not to sell".

    Check the below Recurssion relations.

    How chaining is working ?

        profit chain => -prices[i] + prices[j].... (that's how profit of paricular(i-j) is added into profitChain)


Recurssion Relation:

    solve(day, allowToBuy)
        if allowToBuy:
            profit = max(-prices[i] + solve(day+1, false), 0 + solve(day+1, true))
        else:
            profit = max(prices[i] + solve(day+1, true), 0 + solve(day+1, false))

Base condition:

    if(day == n) return 0. (out of bound, doesn't matter whethere we are holding buying stock or not)

==============================> Approach and Time Complexity <============================



1) DP
Time: O(N)
Space: O(N) => O(1)

 */

// Top-down Approach
class Solution {
public:

    int t[100000][2];

    int maxProfitSupport(int day, int buyToAllow, vector<int>& prices) {

        // base condition
        if (day == prices.size())
            return 0;

        if (t[day][buyToAllow] != -1)
            return t[day][buyToAllow];

        int profit = 0;
        if (buyToAllow) {
            profit = max(-prices[day] + maxProfitSupport(day + 1, 0, prices),
                         0 + maxProfitSupport(day + 1, 1, prices ));
        }
        else {
            profit = max(prices[day] + maxProfitSupport(day + 1, 1, prices),
                         0 + maxProfitSupport(day + 1, 0, prices ));
        }

        return t[day][buyToAllow] = profit;
    }

    int maxProfit(vector<int>& prices) {

        memset(t, -1, sizeof(t));

        return maxProfitSupport(0, 1, prices);
    }
};

// Bottom-up Approach
class Solution {
public:

    int maxProfit(vector<int>& prices) {

        int m = prices.size();
        vector<vector<int>> dp(m + 1, vector<int>(2, 0));

        // base condition
        dp[m][0] = 0;
        dp[m][1] = 0;

        for (int day = m - 1; day >= 0; day--) {
            dp[day][1] = max(-prices[day] + dp[day + 1][0], 0 + dp[day + 1][1]);
            dp[day][0] = max(prices[day] + dp[day + 1][1], 0 + dp[day + 1][0]);
        }

        return dp[0][1];    // Starting at first day, buyToAllow=true... so we consider that only as our answer.
    }
};
