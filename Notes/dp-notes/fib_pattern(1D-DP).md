### Dynamic programming, Pattern = Fib (Fibbonacci Pattern), (1D-DP)

---

> In this pattern, the outcome of dp[n] is depend on previous states. And processing time of each
> node is O(1).

#### [509. Fibonacci Number](https://leetcode.com/problems/fibonacci-number/)(Standard Problem)

```c
// FIB = 1, 1, 2, 3, 5, 8....
// Recursion
int fib(int n) {
    if (n <= 2) {
        return 1;
    }
    return fib(n - 1) + fib(n - 2);
}
// Time: 2^N, space: N


// Top-Down
int fib(int n, int memo[]) {

    if (n <= 2) {
        memo[n] = 1;
        return 1;
    }

    if (memo[n] != -1)
        return memo[n];

    return memo[n] = fib(n - 1) + fib(n - 2);
}

int fib(n) {
    int memo[n + 1] = { -1};
    return fib(n, memo);
}

// Bottom-Up
int fib(int n) {

    // declare dp table.
    int dp[n + 1] = {0};

    // base case
    dp[1] = dp[2] = 1;


    for (int i = 3; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    // return dp[n] which hold the result for fib(n).
    return dp[n];
}

// BUS
// As we can see, dp[i] only need two previous state. We can use two variable instead of having entire array.
int fib(int n) {

    // To handle the base case.
    if (n <= 2)
        return true;

    int prev_1 = 1;     // dp[i-1]
    int prev_2 = 1;     // dp[i-2]

    for (int i = 3; i <= n; i++) {
        int curr = prev_1 + prev_2;
        prev_2 = prev_1;
        prev_1 = curr;      // At the end we store result prev_1.
    }

    return prev_1;
}
```

[70. Climbing Stairs](https://leetcode.com/problems/climbing-stairs/) [O(2^N)(Recursion) => O(N)(DP), O(N) => O(1)]

```c
// TD [0th step => Nth step]
/* Intution:
    Recurrence Relation (0th_stair => Nth_stair)
    F(N) => F(N+1) + F(N+2) (To reach, Nth step from 0th step, we can take N+1 step or N+2 step upward)
    Base case, M > N  => 0, M = N => 1
*/
class Solution {

public:

    int memo[100];

    int helper(int at, int N) {

        // Went above Nth stair, not acceptable we return 0. (How many way to reach at Nth step, when you are N+1 step ? => 0)
        if (at > N)
            return 0;

        // How many way to reach at Nth step, when you are Nth step ? => 1.
        if (at == N)
            return 1;

        if (memo[at] != -1)
            return memo[at];

        // climbStairs(n) = climbStairs(n+1) + climbStairs(n+2)
        // To reach Nth step we can either jump from (n-1)th step To Nth step or from (n-2)th step to N. (Yeah It looks counter intutitive in descriptive manner).
        return memo[at] = helper(at + 1, N) + helper(at + 2, N);
    }

    int climbStairs(int n) {
        memset(memo, -1, 100);
        return helper(0, n);
    }
};


// BU [0th step => Nth step]
class Solution {

public:

    int climbStairs(int n) {

        // Create dp table.
        int dp[100] = {0};

        // Base condition
        dp[N] = 1;

        for (int j = N - 1; j >= 0; j--)
            dp[j] = dp[j + 1] + dp[j + 2];

        return dp[0];
    }
};


// TD-Space: We can use two states instead of entire array. (I didn't coded here!!)
```

#### [1_CN_Frog Jump](https://www.naukri.com/code360/problems/frog-jump_3621012?source=youtube&campaign=striver_dp_videos&utm_source=youtube&utm_medium=affiliate&utm_campaign=striver_dp_videos&leftPanelTabValue=PROBLEM)

```c
// TD Approach

/* Intuition:

Recurrence Relation:
    F(i) = min(F(i-1) + abs(h[i]-h[i-1]), F(i-2) + abs(h[i]-h[i-2]))

Explanation: If we are going from Nth => to 1st Stair, Then we can move to (i-1)th stair or (i-2)th stair from ith stair + (direct cost) energy lost due to that jump. 

Energy Lost = difference between stair's height. 

*/

int memo[100001];

int frogJump(vector<int> &heights, int index) {

    if (index == 1)
        return 0;        // base case, standing at 1st and staring from 1st, no energy required.

    if (memo[index] != -1)
        return memo[index];

    // Why if-else condition instead of equation use direct ?
    // Reason is that, if we do that way... f(index < 1) that time we return INT_MAX... and that is added with some cost
    // which don't fit in INT range... so we never call f(index<1) that's reason we wrote the code this way.


    int minCost = INT_MAX;

    if (index - 1 > 0) {
        minCost = min(minCost, frogJump(heights, index - 1) + abs(heights[index - 1] - heights[index - 2]));    // offset heights index by -1. 
    }

    if (index - 2 > 0) {
        minCost = min(minCost, frogJump(heights, index - 2) + abs(heights[index - 1] - heights[index - 3]));
    }

    return memo[index] = minCost;
}


int frogJump(int n, vector<int> &heights) {

    memset(memo, -1, sizeof(memo));

    return frogJump(heights, n);
}

// BU Approach
int frogJump(int n, vector<int> &heights) {

    vector<int> dp(n + 1, -1);

    // BASE CASE
    dp[1] = 0;

    for (int i = 2; i <= n; i++) {

        dp[i] = INT_MAX;        // MINCOST

        if (i - 1 > 0) {
            dp[i] = min(dp[i], dp[i - 1] + abs(heights[i - 1] - heights[i - 2]));
        }

        if (i - 2 > 0) {
            dp[i] = min(dp[i], dp[i - 2] + abs(heights[i - 1] - heights[i - 3]));
        }

    }

    return dp[n];
}


// BU-SPACE
int frogJump(int n, vector<int> &heights) {

    if (n == 1)
        return 0;

    // Two state to hold the result.
    int prev_1 = 0;             // f(i-1) state
    int prev_2 = INT_MAX;        // f(i-2) state

    for (int i = 2; i <= n; i++) {

        int curr = INT_MAX;        // MINCOST

        if (i - 1 > 0) {
            curr = min(curr, prev_1 + abs(heights[i - 1] - heights[i - 2]));
        }

        if (i - 2 > 0) {
            curr = min(curr, prev_2 + abs(heights[i - 1] - heights[i - 3]));
        }

        // SWAP THE results for next state
        prev_2 = prev_1;
        prev_1 = curr;            // at the end we are storing our result here
    }

    return prev_1;
}
```

#### [2_Frog_2](https://atcoder.jp/contests/dp/tasks/dp_b)

```c
// TD

/* Intuition:

Here frog can jump to any next K stone instead of 1 & 2. So we need to find the minimum cost among all the possibilites at given index.

Recurrance Relation:

    For j = 1 -> K,
        f(i) = min_cost(f(i-1) + abs(h[i] - h[i-1-j]))

*/

int memo[100001];

int frogJump(vector<int> &heights, int index, int k) {          // index=N.

    if (index == 1)
        return 0;       // base case, standing at 1st and reaching to 1st stone, no energy required.

    if (memo[index] != -1)
        return memo[index];

    int minCost = INT_MAX;
    for (int j = 1; j <= k; j++) {
        if ((index - j) > 0) {
            minCost = min(minCost, frogJump(heights, index - j, k) + abs(heights[index - 1] - heights[index - 1 - j]));
        }
    }

    return memo[index] = minCost;

}

// BU
int frogJump(vector<int> &heights, int N, int k) {

    // Base Case
    if (N == 1)
        return 0;

    vector<int> dp(N + 1, -1);

    // base case.
    dp[1] = 0;

    for (int i = 2; i <= N; i++) {
        int minCost = INT_MAX;
        for (int j = 1; j <= k; j++) {      // can jump upto k stone.
            if ((i - j) > 0) {
                minCost = min(minCost, dp[i - j] + abs(heights[i - 1] - heights[i - 1 - j]));
            }
        }
        dp[i] = minCost;
    }

    return dp[N];
}


// BU-Space: We need to know the last K state only. Space:O(K)
// We need to override the kth state every time.. what I mean is that... state=1, k=3 then when we reach at
// state=4..then we store that result at dp[(state-k)=(4-3)=1]..got it ?
int frogJump2(vector<int> &heights, int N, int k) {

    // Base Case
    if (N == 1)
        return 0;

    vector<int> dp(k + 1, -1);

    // offset to adjust dp table index. As we are using the % operator for overriding we need to store result starting from 0th index for easiness.
    // but do this step later.. first write code and then offet the dp table index only.
    // you know why we need to use % K...right.
    int OFFSET = 1;

    // base case.
    dp[1 - OFFSET] = 0;

    for (int i = 2; i <= N; i++) {
        int minCost = INT_MAX;
        for (int j = 1; j <= k; j++) {      // can jump upto k stone.
            if ((i - j) > 0) {
                minCost = min(minCost, dp[(i - j - OFFSET) % k] + abs(heights[i - 1] - heights[i - 1 - j]));
            }
        }
        dp[(i - OFFSET) % k] = minCost;
    }

    return dp[(N - OFFSET) % k];
}
```

#### [4_CN_Maximum sum of non-adjacent elements](https://www.naukri.com/code360/problems/maximum-sum-of-non-adjacent-elements_843261?source=youtube&campaign=striver_dp_videos&leftPanelTabValue=PROBLEM)

```c
// TD (From 0 -> N)
/* Intuition:

What choice diagram looks like ?

F(i) => Return the maximum sum possible with given constraint in question from [arr[i] -> arr[N]).
For that we have two choice,
    Pick up current element, or not to pick up current elemment
        If we pick up ith element, then we can't pick up next element, can pick up (i+2)th element:
            cost = arr[i] + F(i+2)[Which give best result from [arr[i+2] => N]]
        not pick up:
            cost = F(i+1)[Which give best result from [arr[i+1] => N]]

So we got our recurrence relation which looks like this,

    F(i) = max(arr[i] + F(i+2), F(i+1))

    And each F(i) have atleast arr[i] as maxCost in case, (i+2) and (i+1) is not valid.
*/


int memo[100001];

int helper(vector<int> &nums, int index) {

    // Base case: Only one element left, you have to take it. 
    if (index == nums.size() - 1)
        return nums[index];

    if (memo[index] != -1)
        return memo[index];

    // Assigned direct cost, because for array [1, 2] when we take 0th element, we can't jump to index=2... 
    // So to consider the cost of 0th index, we pre-assign the cost. 
    int maxCost = nums[index];

    // Take current "index", then jump to "index+2"
    if ((index + 2) < nums.size()) {
        maxCost = max(maxCost, helper(nums, index + 2) + nums[index]);
    }

    // Not to take current "index", then we can take cost from "index+1".
    if ((index + 1) < nums.size()) {
        maxCost = max(maxCost, helper(nums, index + 1));
    }

    return memo[index] = maxCost;
}


int maximumNonAdjacentSum(vector<int> &nums) {
    memset(memo, -1, sizeof(memo));
    return helper(nums, 0);
}


// BU
int maximumNonAdjacentSum(vector<int> &nums) {

    int N = nums.size();

    // base case
    if (N == 1)
        return nums[0];

    vector<int> dp(N, -1);
    dp[N - 1] = nums[N - 1]; // base case

    for (int i = N - 1; i >= 0; i--) {

        // Atleast ith number have cost nums[i]. (bare minimum)
        int maxCost = nums[i];

        // Taking current "ith" num.
        if (i + 2 < N) {
            maxCost = max(maxCost, dp[i + 2] + nums[i]);
        }

        // Not taking the current "ith" num, and choosing the previous number best result.
        if (i + 1 < N) {
            maxCost = max(maxCost, dp[i + 1]);
        }

        dp[i] = maxCost;
    }

    // At the end, final result stored in dp[0].
    return dp[0];
}






// TD TD (From N -> 0)

int memo[100001];

int helper(vector<int> &nums, int index) {

    // base case
    if (index == 0)
        return nums[index];

    if (memo[index] != -1)
        return memo[index];

    int maxCost = nums[index];

    // Taking "index" element, then jump to (index-2)th element.
    if ((index - 2) >= 0) {
        maxCost = max(maxCost, helper(nums, index - 2) + nums[index]);
    }
    if ((index - 1) >= 0) {
        maxCost = max(maxCost, helper(nums, index - 1));
    }

    return memo[index] = maxCost;
}


int maximumNonAdjacentSum(vector<int> &nums) {
    memset(memo, -1, sizeof(memo));
    return helper(nums, nums.size() - 1);
}


// BU
int maximumNonAdjacentSum(vector<int> &nums) {
    int N = nums.size();

    // base case
    if (N == 1)
        return nums[0];

    vector<int> dp(N + 1, -1);
    dp[0] = nums[0]; // base case

    for (int i = 1; i < N; i++) {

        // atleast ith number have cost nums[i]. (bare minimum)
        int maxCost = nums[i];

        // Taking current ith num.
        if (i - 2 >= 0) {
            maxCost = max(maxCost, dp[i - 2] + nums[i]);
        }

        // Not taking the current ith num, and choosing the previous number best result.
        if (i - 1 >= 0) {
            maxCost = max(maxCost, dp[i - 1]);
        }

        dp[i] = maxCost;
    }

    return dp[N - 1];
}
```





### [198 House Robber](https://leetcode.com/problems/house-robber/description/)

```c
// TD
/*
Parent: 4_CN_Maximum sum of non-adjacent elements

It is same problem. Given that, we have to check each possbilities of robbing house with constraint(not to rob two adjancent house).
So at each index, we have two options,
	1) to rob ith house, and jump to (i+2)th house
	2) to not rob ith house and jump to next house.
And we choose the best, decision such that it maximize the cost.
*/

class Solution {
public:

	int memo[10001];

	int robHelper(vector<int>&costs, int i) {

		// Base case, In case we reach at last home, then rob that house. Doing that we are maximizing cost, instead of not robbing.
		if (i == costs.size() - 1)
			return costs[i];

		// Base case, Out of bound, mark end of houses. Returning minimum cost because goal is to maximize the cost.
		if (i == costs.size())
			return 0;

		if (memo[i] != -1)
			return memo[i];

		// Two Choice We have, Either rob ith house(where we are at) and jump to i+2 house.
		// Or we can skip the current house and jump to next i+1 house.
		return memo[i] = max(costs[i] + robHelper(costs, i + 2), robHelper(costs, i + 1))
	}

	int rob(vector<int>& nums) {
		memset(memo, -1, sizeof(memo));
		int at = 0;
		return robHelper(nums, at);
	}
};

// BU
class Solution {
public:
	int rob(vector<int>& nums) {
		int N = nums.size();
		vector<int> dp(N + 1, 0);
		dp[N - 1] = nums[N - 1];
		for (int i = N - 2; i >= 0; i--) {
			// Keep track of maxCost
			int maxCost = max(dp[i + 1], dp[i + 2] + nums[i]);
			dp[i] = maxCost;
		}
		return dp[0];
	}
};


// BUS
class Solution {
public:
	int rob(vector<int>& nums) {
		int N = nums.size();
		int prev_1 = dp[N - 1]; // (i+1)th state
		int prev_2 = 0;		// (i+2)th state, assign lower value, we are finding maximum cost

		for (int i = N - 2; i >= 0; i--) {

			// Keep track of maxCost
			int maxCost = 0;

			// Two choice
			if (i + 1 < N) {
				maxCost = max(maxCost, prev_1);
			}
			if (i + 2 < N) {
				maxCost = max(maxCost, prev_2 + nums[i]);
			}

			// Swap the state with curr as prev_1.
			prev_2 = prev_1;
			prev_1 = maxCost;
		}
		return prev_1;
	}
};



// -----------------------------


// BU (0 -> N)
class Solution {
public:
	// Trying to do in reverse from Top-down, 0 -> N
	int rob(vector<int>& nums) {
		int N = nums.size();
		vector<int> dp(N + 1, 0);
		dp[0] = nums[0];
		for (int i = 1; i < N; i++) {

			// Keep track of maxCost
			int maxCost = 0;

			// Two choice
			if (i - 1 >= 0) {
				maxCost = max(maxCost, dp[i - 1]);
			}
			if (i - 2 >= 0) {
				maxCost = max(maxCost, dp[i - 2] + nums[i]);
			}

			dp[i] = maxCost;
		}
		return dp[N - 1];
	}
};
```



#### [213 House Robber II](https://leetcode.com/problems/house-robber-ii/description/)



```c
/*
Parent Problem: 198. House Robber

Given that, we have to check each possbilities of robbing house with constraint(not to rob two adjancent house).
So at each index, we have two options,
	1) to rob ith house, and jump to (i+2)th house
	2) to not rob ith house and jump to next house.
And we choose the best, decision such that it maximize the cost.

With special constraint that, first and last house is connected so we can either rob one of them house if required.

Two subproblem is occured, we perform same algorithm two times...

1) (0 -> N-2) (Last one not included)
2) (1 -> N-1) (First one included)

And take maximum of them.

Reason is that there are total three case for (first and last)

	Not Rob first, Not Rob last
	Not Rob First, Rob last
	Rob First, Not Rob last

Which is covered into two subproblems. 1) Don't Rob last (Rob or not rob first)
                                       2) Don't Rob first (Rob or not rob last)

*/
// TD

class Solution {
public:

	int memo[10001];

	int robHelper(vector<int>&costs, int i) {

		// Base case, In case we reach at last house, then loot everything from that house.
		// Doing that we are returning maximum cost.
		if (i == costs.size() - 1)
			return costs[i];

		// Not valid case(out of bound), so we are returning minimum cost because we are finding maximum cost.
		if (i >= costs.size())
			return 0;

		if (memo[i] != -1)
			return memo[i];

		// Two Choice We have, Either loot ith house(where we are at) and jump to i+2 house.
		// Or we can skip the current house and jump to next i+1 house.
		return memo[i] = max(costs[i] + robHelper(costs, i + 2), robHelper(costs, i + 1));
	}

	int rob(vector<int>& nums) {
		// Base case: In case one house, rob that one.
		// This one is required because when we skip the first or last that time we will return {} array if size of nums is 1.
		// So special attention required for this case.
		if (nums.size() == 1)
			return nums[0];

		memset(memo, -1, sizeof(memo));
		int at = 0;
		vector<int> takingFirst(nums.begin(), nums.end() - 1);
		int maxByTakingFirstHouse = robHelper(takingFirst, at);

		memset(memo, -1, sizeof(memo));
		at = 0;
		vector<int> takingLast(nums.begin() + 1, nums.end());
		int maxByTakingLastHouse = robHelper(takingLast, at);

		return max(maxByTakingFirstHouse, maxByTakingLastHouse);
	}
};



// BU - 2 Phase
class Solution {
public:
	int robLinearManner(vector<int>& nums) {
		int N = nums.size();
		vector<int> dp(N + 1, 0);
		dp[N - 1] = nums[N - 1];
		for (int i = N - 2; i >= 0; i--) {
			// Keep track of maxCost
			int maxCost = max(dp[i + 1], dp[i + 2] + nums[i]);
			dp[i] = maxCost;
		}
		return dp[0];
	}

	int rob(vector<int>& nums) {

		if (nums.size() == 1)
			return nums[0];

		vector<int> takingFirst(nums.begin(), nums.end() - 1);
		vector<int> takingLast(nums.begin() + 1, nums.end());

		return max(robLinearManner(takingFirst), robLinearManner(takingLast));
	}
};


// BU - 1 Phase
class Solution {
public:
	int rob(vector<int>& nums) {

		int N = nums.size();

		if (nums.size() == 1)
			return nums[0];

		vector<int> dpTakingFirst(N + 1, 0);
		dpTakingFirst[N - 2] = nums[N - 2];	// Not taking Last.

		vector<int> dpTakingLast(N + 1, 0);
		dpTakingLast[N - 1] = nums[N - 1]; // Taking Last.
		int offSet = 1;

		for (int i = N - 3; i >= 0; i--) {

			// Consider Range from (N-2 => 1), We need to add offset for each index.
			dpTakingLast[i + offSet] = max(dpTakingLast[i + 1 + offSet], dpTakingLast[i + 2 + offSet] + nums[i + offSet]);

			// Consider Range from (N-3 => 1)
			dpTakingFirst[i] = max(dpTakingFirst[i + 1], dpTakingFirst[i + 2] + nums[i]);
		}

		return max(dpTakingFirst[0], dpTakingLast[1]);
	}
};


```
