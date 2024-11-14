### Dynamic programming, Pattern = 0-1 Knapsack(Infinite Source)

---



> Problem Statment:
> 
> In this pattern, you have given some choices to make such that, your 
> combination gives the max/min optimum cost.
> 
> But constraint is, each item can be selected infinite number of times and 
> each time either you take item fully or not at all.
> 
> And selecting any item cost you some amount, and you have 
> knapsack which have some limit which you can't exceed.
> 
> 
> 
> Solution:
> 
>     At any moment, you have left with W capacity, and at ith item,
>     
>     W - wt[i] >= 0 => Feasible to take ith element, because we have capacity,
>     
>         But We have Two Choice: Take it OR don't take it. 
>     
>     W - wt[i] < 0 => Not feasible to take => don't take it. 
> 
> Recurrence Relation:
> 
>     solve(i, W) => max(solve(i+1, value+val[i], W-wt[i]), solve(i+1, value, W)) (feasible to take wt[i])
>     solve(i, W) => solve(i+1, value, W) (Not feasible to take wt[i])
> 
> Base case:
> 
>     W == 0 => value = 0 (No weight, no item you can take)
>     i < 0 => value = 0 (no element you can pick up, out of bound) 
>     (Problem, considered 1 based index, so i == 0 become out of bound)



> Sub-patterns:
> 
> 
> 
> Pattern=1, Limited Supply, Finding maximum Value
> Pattern=2, Unlimited Supply, Finding maximum value.
> 
> Pattern=3, Limited supply, Finding minimum elements required (less asked)
> 
> Pattern=4, Unlimited supply, Finding minimum elements required (imp)
> 
> Pattern=5, Limited Supply, Finding number of ways to reach capacity (less asked)
> Pattern=6, Unlimited supply, Finding number of ways to reach capacity (imp)





### [12_CN_0_1_Knapsack_Standard, #Pattern=1](https://www.naukri.com/code360/problems/0-1-knapsack_920542)



```c
// Top-Down Apporach.
// For easiness, we are treating i=0 as out of bound. 
// So managed index that way for weight[] and values[] (with -1 offset) 

#include <bits/stdc++.h>

int t[101][1001];

int knapsackSupport(int i, vector<int> wt, vector<int> values, int W) {

	// Base case
	// Out of bound, For easiness we are treating index from (1, N).
	// Finding maximum value, so returned smallest positive value.
	if (i == 0) {
		return 0;
	}

	// Base case: No weight we can add any more, so we are returning value = 0.
	if (W == 0) {
		return 0;
	}

	if (t[i][W] != -1)
		return t[i][W];

	// If we are able to take ith item
	// We have two choice to try, take it or don't take it.
	int maxValue = 0;
	if (W - wt[i - 1] >= 0) {
		maxValue = max(knapsackSupport(i - 1, wt, values, W - wt[i - 1]) + values[i - 1], knapsackSupport(i - 1, wt, values, W));
	}

	// If we can't take ith item due to Weight constraint, we don't take it.
	else {
		maxValue = knapsackSupport(i - 1, wt, values, W);
	}

	return t[i][W] = maxValue;
}


int knapsack(vector<int> wt, vector<int> values, int n, int maxWeight) {

	// fill the memo table with -1.
	memset(t, -1, sizeof(t));

	return knapsackSupport(wt.size(), wt, values, maxWeight);
}


// Bottom-Up Approach
int knapsack(vector<int> wt, vector<int> values, int n, int W) {

	vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

	// Base case (Covered, dp table is initialize with 0 value)
	// dp[0][j] = 0.    // (out of element)
	// dp[i][0] = 0;    // (W == 0)

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= W; j++) {
			int maxValue = 0;
			if (j - wt[i - 1] >= 0) {
				maxValue = max(dp[i - 1][j - wt[i - 1]] + values[i - 1], dp[i - 1][j]);
			}
			else {
				maxValue = dp[i - 1][j];
			}
			dp[i][j] = maxValue;
		}
	}

	return dp[n][W];
}


// Bottom-Up Approach With Space Optimization
int knapsack(vector<int> wt, vector<int> values, int n, int W) {

	vector<int> prev(W + 1, 0), cur(W + 1, 0);
	// Base case (Covered, dp table is initialize with 0 value)
	// cur[0][j] = 0.

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= W; j++) {
			int maxValue = 0;
			if (j - wt[i - 1] >= 0) {
				maxValue = max(prev[j - wt[i - 1]] + values[i - 1], prev[j]);
			}
			else {
				maxValue = prev[j];
			}
			cur[j] = maxValue;
		}
		swap(cur, prev);
	}

	return prev[W];
}
```



### [13_CN_Minimum Elements](https://www.naukri.com/code360/problems/minimum-elements_3843091) | [322. Coin Change ](https://leetcode.com/problems/coin-change/) #Pattern-4

> Intuition:
> 
>     Recurrence Relation:
>     
>         solve(i, T) => min(1 + solve(i, T-nums[i]), solve(i-1, T)) (if T - nums[i] >= 0) (feasible, you have two choice to take ith element, or don't take ith element)
>                     => solve(i-1, T) (not feasible, don't take ith element)
>     
>                     We have unlimited supply, so after taking ith element, we can again take ith element. 
>     
>     Base case:
>     
>         // Last element left, T >= 0
>         if(index == 0)
>             return T/nums[0], if T % nums[0] == 0.. (using x times nums[0], can make to target ? )
>     
>         In short, if last element is left then we need to take that again and again to make T = zero(T % nums[i]), if not possible then we
>         return sum large value(MAX).

```c
// Top-Down Approach
// 1 <= N <= 15
// 1 <= T <= 10000
#include <bits/stdc++.h>
int t[16][10001];
int MAX = 1e6;

int minimumElementsHelper(int i, vector<int> &nums, int T) {

    // Edge case, last element left and still T > 0.
    if (i == 0) {
        if (T % nums[0] == 0)
            return T / nums[0];
        return MAX;
    }

    if (t[i][T] != -1) return t[i][T];

    // Keep track of minimum elements.
    int minimumElements = INT_MAX;

    // Take it or don't take it.
    if (T - nums[i] >= 0) {
        minimumElements = min(1 + minimumElementsHelper(i, nums, T - nums[i]), minimumElementsHelper(i - 1, nums, T));
    }
    else {
        minimumElements = minimumElementsHelper(i - 1, nums, T);
    }

    return t[i][T] = minimumElements;
}

int minimumElements(vector<int> &num, int T) {

    memset(t, -1, sizeof(t));

    sort(num.begin(), num.end());

    int minimumElements =  minimumElementsHelper(num.size() - 1, num, T);

    return min_elements < MAX ? min_elements : -1;
}


// Bottom-Up Approach

#include <bits/stdc++.h>
int MAX = 1e9;

int minimumElements(vector<int> &nums, int target) {

    // Total elements
    int N = nums.size();

    vector<vector<int>> dp(N, vector<int>(target + 1, 0));

    // BASE CASE: Last element left && T > 0.
    for (int j = 0; j <= target; j++) {
        if (j % nums[0] == 0) {
            dp[0][j] = j % nums[0];
        }
        else {
            dp[0][j] = MAX;
        }
    }

    for (int i = 1; i < N; i++) {
        for (int j = 0; j <= target; j++) {
            int minimumElements = MAX;
            if (j - nums[i] >= 0) {            // TAKE IT OR DON'T TAKE IT
                minimumElements = min(1 + dp[i][j - nums[i]], dp[i - 1][j]);
            }
            else {
                minimumElements = dp[i - 1][j];
            }
            dp[i][j] = minimumElements;
        }
    }

    int ans = dp[N - 1][target];
    if (ans >= MAX)
        return -1;
    return ans;
}
```

### [518. Coin Change II, Pattern#6](https://leetcode.com/problems/coin-change-ii/)

```cpp

/* Intuition:

Given Infinite source, you can pick up same element multiple times. Here, ask is "number of ways", so 
we count ways. 

Base case:
T == 0 (1 way to pick up elements, by picking up no elements)

Recurrence Relation:

	solve(i, T) => solve(i, T-coins[i]) + solve(i-1, T)

                => (not fesiable) solve(i-1, T)


*/

// Top-down Approach
class Solution {
public:

    int t[500][5001];

    int changeSupport(int index, vector<int> &coins, int T) {

        // If you reach T = 0, it means there is one way to select amount = 0 (by selecting nothing)
        if (T == 0)
            return 1;

        // Out of bound.
        if (index <= 0)
            return 0;

        if (t[index][T] != -1) return t[index][T];

        int count = 0;

        if (T - coins[index - 1] >= 0) {
            count = changeSupport(index, coins, T - coins[index - 1]) + changeSupport(index - 1, coins, T);
        }
        else {
            count = changeSupport(index - 1, coins, T);
        }

        return t[index][T] = count;
    }


    int change(int amount, vector<int>& coins) {

        memset(t, -1, sizeof(t));

        return changeSupport(coins.size(), coins, amount);
    }
};


// Bottom-Up Approach
class Solution {
public:

    int change(int amount, vector<int>& coins) {

        int n = coins.size();

        vector<vector<int>> dp(n + 1, vector<int> (amount + 1, 0));

        // 1) base case
        for (int i = 1; i <= n; i++) {
            dp[i][0] = 1;             // T == 0, index <= 0 so we started with i = 1, instead of 0.
        }

        // 2) base case: index <= 0 => index = 0...
        // we covered this case during initialization, making entire dp table fill up with zero.

        for (int i = 1; i <= n; i++) {
            for (int T = 1; T <= amount; T++) {
                if (T - coins[i - 1] >= 0) {
                    dp[i][T] = dp[i][T - coins[i - 1]] +  dp[i - 1][T];
                }
                else {
                    dp[i][T] = dp[i - 1][T];
                }
            }
        }

        return dp[n][amount];
    }
};


// Bottom-up Space optimization
class Solution {
public:

    int change(int amount, vector<int>& coins) {

        int n = coins.size();

        vector<vector<int>> dp(n + 1, vector<int> (amount + 1, 0));

        // dp table converted into single array. Currently, prev => 0th row... cur is pointing to (prev+1) row.
        vector<int> prev(amount + 1, 0), cur(amount + 1, 0);

        // 1) base case
        prev[0] = 1;             //  dp[i][0] = 1 => dp[0][0] = 1 because prev currently pointing to 0th row only.

        // 2) base case: index <= 0 => index = 0...
        // we covered this case during initialization. prev = {1, 0, 0, 0...}

        for (int i = 1; i <= n; i++) {
            cur[0] = 1; // base case: dp[i][0] = 1 => cur[0] = 1.
            for (int T = 1; T <= amount; T++) {
                if (T - coins[i - 1] >= 0) {
                    cur[T] = cur[T - coins[i - 1]] +  prev[T];
                }
                else {
                    cur[T] = prev[T];
                }
            }
            swap(prev, cur);
        }

        return prev[amount];
    }
};
```



### [14_GFG_Rod Cutting, Pattern#2](https://www.geeksforgeeks.org/problems/rod-cutting0840/1)

```cpp
/*
Intuition:

	Given that values[i] and Length of Rod, we have to select diff length of Rod such that we can maximize the value. We can
	pick up same length rod multiple times as well.

	Only things which is not given is wt[], which we can create by our own with given length.

	wt[i] => ith length rod value.

	Recurrence Relation:

		solve(i, T) => max(solve(i, T-i) + values[i], solve(i, T))

	Base case:
		
		T == 0, NO ROD => value = 0
		i < 0, (out of bound) No element => value = 0 | -MAX	

*/


// Top-Down Approach
class Solution {
public:

    int t[1001][1001];

    int MAX = 1e6;

    int cutRodHelper(int index, int price[], int T) {

        // No Rod left, maximum value possible is 0.
        if (T == 0)
            return 0;

        // Out of Bound, index <= 0, it menas we have some T > 0 and doesn't have anything to pick up,
        // and we maximize the value so returned smallest value.
        if (index <= 0)
            return -MAX;

        if (t[index][T] != -1) return t[index][T];

        int maxValue = 0;

        // index=weight, so we check weather we can take (index) length rod or not. (same as pick up item based on weight)
        if (T - index >= 0) {
            maxValue = max(cutRodHelper(index, price, T - index) + price[index - 1], cutRodHelper(index - 1, price, T));
        }
        else {
            maxValue = cutRodHelper(index - 1, price, T);
        }

        return t[index][T] = maxValue;
    }


    int cutRod(int price[], int n) {

        memset(t, -1, sizeof(t));

        return cutRodHelper(n, price, n);
    }
};

// Bottom-up Approach
class Solution {
public:

    int MAX = 1e6;

    int cutRod(int price[], int n) {

        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        // base case - 1
        // already covered (T = 0)

        // base case - 2
        for (int j = 0; j <= n; j++)
            dp[0][j] = -MAX;

        for (int i = 1; i <= n; i++) {
            for (int T = 1; T <= n; T++) {
                if (T - i >= 0) {
                    dp[i][T] = max(dp[i][T - i] + price[i - 1], dp[i - 1][T]);
                }
                else {
                    dp[i][T] = dp[i - 1][T];
                }
            }
        }

        return dp[n][n];
    }
};


// Space Optimization
class Solution {
public:

    int MAX = 1e6;

    int cutRod(int price[], int n) {

        // prev, curr
        vector<int> prev(n + 1, -MAX), cur(n + 1, 0);


        // prev points to index = 0, right now.

        for (int i = 1; i <= n; i++) {
            cur[0] = 0;  // base case    T == 0
            for (int T = 1; T <= n; T++) {
                if (T - i >= 0) {
                    cur[T] = max(cur[T - i] + price[i - 1], prev[T]);
                }
                else {
                    cur[T] = prev[T];
                }
            }
            swap(prev, cur);
        }

        return prev[n];
    }
};
```
