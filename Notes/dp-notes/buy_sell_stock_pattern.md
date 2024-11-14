### Dynamic programming, Pattern = Buy-sell-stock

----

### [121. Best Time to Buy and Sell Stock](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/)

```c
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
```

```c
// (DP Solution) 

/* Intuition:

Recurssion Relation:

    solve(day, allowToBuy)
        if allowToBuy:
            profit = max(-prices[i] + solve(day+1, false), 0 + solve(day+1, true))
        else:
            profit = max(prices[i] + solve(day+1, true), 0 + solve(day+1, false))

Modification of this recurrence relation, keeping mind that, we can't have  multilple transaction, 
        
    solve(day, allowToBuy)
        if allowToBuy:
            profit = max(-prices[i] + solve(day+1, false), 0 + solve(day+1, true))
        else:
            profit = max(prices[i], 0 + solve(day+1, false))


*/
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
```

### [122. Best Time to Buy and Sell Stock II](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/)

```c
// Top-down Approach
/* Intuition:

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

*/
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
```

### [123. Best Time to Buy and Sell Stock III](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/)

```c
// Top-down Appraoch
/* Intuition:
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

*/
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
```

### [188. Best Time to Buy and Sell Stock IV](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/)

```c
/* Intuition:
In #123, Given that we can do maxTrans = 2... Here we are allowed to do maxTrans = k. That's the diff only.

So just increase the limit of maxTrans from 2 => K.    
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
};
```

### [309. Best Time to Buy and Sell Stock with Cooldown](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/)

```c
// Top-down approach
/* Intuition:
Recurrence Relation:

    solve(day, buyToAllowed) =>

        buyToAllowed==1: max(-prices[day] + solve(day+1, !buyToAllowed), 0 + solve(day+1, buyToAllowed))
        buyToAllowed==0: max(prices[day] + solve(day+1, !buyToAllowed), 0 + solve(day+1, buyToAllowed))

This relations indicate that...we can buy and sell stocks any times... but we can't have two transactions running same(means buy stocks, sell those and again we can buy it).
But we can't do buy-buy-sell-sell such transactions. Hope you get it!

----

In this question, cooldown period = 1 day.... which means if you complete the transactions(buy-sell) then you need to wait for additional one day before you again buy.

It means.. if you sell it ith day... then you can again buy at (i+2)th day directly....

Cooldown period applys during the selling only.... So there is little change in equations....


Recurrence Relation:

    solve(day, buyToAllowed) =>

        buyToAllowed==1: max(-prices[day] + solve(day+1, !buyToAllowed), 0 + solve(day+1, buyToAllowed))
        buyToAllowed==0: max(prices[day] + solve(day+2*, !buyToAllowed), 0 + solve(day+1, buyToAllowed))

Just when we sell the stocks.. instead of jumping to next day (day+1) we move to (day+2).


*/
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
```

### 

### [714. Best Time to Buy and Sell Stock with Transaction Fee](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/)

```c
// Top-down Approach
/* Intuition:
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

*/
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
```
