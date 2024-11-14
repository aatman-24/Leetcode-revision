##### Dynamic programming, Pattern = Subset Sum Pattern

---

> In this pattern, We have given the elements in form of array and "target". We have to find subset of element such that, its sum is equal to "target". 
> In recursion/backtracking series, we already learned how to generate all subsets, by making two choice for each element "to take it" or "don't take it". 
> So we apply that rule by considering "target" constraint. 

### [7_CN_Subset Sum Equal To K](https://www.naukri.com/code360/problems/subset-sum-equal-to-k_1550954)

```c
// Top-down
/* Intuition:

    We use recursion apporach with memorization, by applying the constraint of target. 

    We don't generate the subsets here, we can keep track of subset-sum by using "curSum". 

    Chocie Diagram:

        For ith element => curSubsetSum + arr[i] <= target, (we can add arr[i] into subset)

                                But we have to chocie, 

                                    Take it,

                                    don't Take it

                            curSubsetSum + arr[i] > target, (Not feasible to add element).

                                    We can't take it. 


        Recurrsion Relation:

            solve(i, target) => 

                    (feasible)

                        arr[i] + solve(i - 1, target-arr[i]) || solve(i-1, target)

                    (not feasible)

                        solve(i-1, target)

*/
#include <bits/stdc++.h>

int t[1001][1001];

bool subsetSumToKHelper(vector<int> &arr, int index, int target) {

    // Base case
    if (target == 0)
        return true;

    // Incase we are out of element and still target > 0, indicate we failed to find subset.
    if (index < 0)
        return false;

    if (t[index][target] != -1)
        return t[index][target];

    bool foundSubset = false;

    // we take arr[index] into consideration, only when arr[index] <= target.
    // We have two choice either take it or not take it(remember the subset backtracking problem).
    if (target - arr[index] >= 0) {
        foundSubset = subsetSumToKHelper(arr, index - 1, target - arr[index]) || subsetSumToKHelper(arr, index - 1, target);
    }
    else {    // Incase we won't able to take, we move to next element.
        foundSubset = subsetSumToKHelper(arr, index - 1, target);
    }

    return t[index][target] = foundSubset;
}



bool subsetSumToK(int n, int k, vector<int> &arr) {
    memset(t, -1, sizeof(t));
    return subsetSumToKHelper(arr, n - 1, k);
}


// Bottom-Up
bool subsetSumToK(int n, int k, vector<int> &arr) {

    vector<vector<bool>> dp(n + 1, vector<bool>(k + 1, false));

    // base case.
    for (int i = 0; i <= n; i++)
        dp[i][0] = true;             // target == 0

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            if (j - arr[i - 1] >= 0) {     // following 0th based index in arr, i-1.
                dp[i][j] = dp[i - 1][j - arr[i - 1]] || dp[i - 1][j];
            }
            else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    return dp[n][k];
}

// BUS
bool subsetSumToK(int n, int k, vector<int> &arr) {

    vector<int> prev(k + 1, false), cur(k + 1, false);

    // base case, indicate...dp[0][0] = true
    pre[0] = true;

    for (int i = 1; i <= n; i++) {

        // dp[i][0] = true, indicate dp[i][0] = true, as target = 0.
        cur[0] = true;

        for (int j = 1; j <= k; j++) {
            if (j - arr[i - 1] >= 0) {
                cur[j] = prev[j - arr[i - 1]] || prev[j];
            }
            else {
                cur[j] = prev[j];
            }
        }

        swap(cur, prev);        // at the end, result will got stored in prev.
    }

    return prev[k];
}
```

### [8_CN_Partition Equal Subset Sum](https://www.naukri.com/code360/problems/partition-equal-subset-sum_892980)

```c
// TD
/* Intuition:

    We need to find whether we can divide the given array into two subset such that both subset hold equal sum.
    Indirectly indicate that, can we find the subset whose sum is arr(sum)/2. That case only possible to divide
    given array into two equal subset whose sum is equal.

    First we check, sum(arr) is even or odd, in case it odd we can't divide.

    If it is even, then we need to find SubsetSum(target = sum(arr)/2)(#7_CN_Subset Sum Equal To K)

*/
int t[101][10001];

#include <bits/stdc++.h>

// Return total sum of array.
int getArraySum(vector<int> &arr) {
    int sum = 0;
    for (int num : arr) {
        sum += num;
    }
    return sum;
}

bool findSubsetWithSumEqualK(vector<int> &arr, int index, int target) {

    // Base case
    if (target == 0)
        return true;

    // Edge case, out of range, no more element and target > 0.
    if (index < 0)
        return false;

    if (t[index][target] != -1)
        return t[index][target];

    bool foundSubset = false;
    if (target - arr[index] >= 0) {
        foundSubset = findSubsetWithSumEqualK(arr, index - 1, target - arr[index]) || findSubsetWithSumEqualK(arr, index - 1, target);
    }
    else {
        foundSubset = findSubsetWithSumEqualK(arr, index - 1, target);
    }

    return t[index][target] = foundSubset;
}

bool canPartition(vector<int> &arr, int n) {

    int sum = getArraySum(arr);
    bool isArraySumEven = sum % 2 == 0;
    if (!isArraySumEven)
        return false;
    memset(t, -1, sizeof(t));
    return findSubsetWithSumEqualK(arr, n - 1, sum / 2);
}


// Bottom-Up
bool canPartition(vector<int> &arr, int n) {

    int sum = getArraySum(arr);
    bool isArraySumEven = sum % 2 == 0;
    if (!isArraySumEven)
        return false;

    int target = sum / 2;

    // dp table
    vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));

    // base case
    for (int i = 0; i <= n; i++) {
        dp[i][0] = true;    // dp[i][target] = true, as target = 0.
    }


    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= target; j++) {
            if (j - arr[i - 1] >= 0) {        // following 0th based index in arr.
                dp[i][j] = dp[i - 1][j - arr[i - 1]] || dp[i - 1][j];
            }
            else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    return dp[n][target];
}


// BUS
bool canPartition(vector<int> &arr, int n) {

    int sum = getArraySum(arr);
    bool isArraySumEven = sum % 2 == 0;
    if (!isArraySumEven)
        return false;

    int target = sum / 2;

    // dp table
    vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));
    vector<bool> pre(target + 1, false), cur(target + 1, false);

    // base case
    pre[0] = true;         // indicate.. dp[i][0] = true....

    for (int i = 1; i <= n; i++) {
        cur[0] = true;        // indicate, dp[i][0] = true...
        for (int j = 1; j <= target; j++) {
            if (j - arr[i - 1] >= 0) {        // following 0th based index in arr.
                cur[j] = pre[j - arr[i - 1]] || pre[j];
            }
            else {
                cur[j] = pre[j];
            }
        }
        swap(pre, cur);        // at the end last result will be stored in pre.
    }

    return pre[target];
}
```

### [9_CN_Array partition with minimum difference*](https://www.naukri.com/code360/problems/partition-a-set-into-two-subsets-such-that-the-difference-of-subset-sums-is-minimum_842494)

> ```textile
> Intuition:
> 
> Need to find two subset => S1 & S2
> 
> Whose sum diff should be as minimum as possible.
> 
> Instead of finding both subset we can focus on finding one subset such that whose sum is in range
> of [0, sum(arr)/2]... Doing that we will automatically find other subset s2 from [sum(arr)/2... sum(arr)].. right ?
> 
> At the end, we need abs diff of sum of thoses subset as small as possible, which is possible through such division only. 
> 
> But how we can find all subset sum whose range is from [0, sum(arr)/2] ?
> 
> Remember, during Bottom-up approach, last row of dp table,
> 
>     dp[n-1][target] what it indicate,
> 
>         dp[n-1][5] => Indicate we can find subset whose target=5, from given array.
>         dp[n-1][12] => Indicate we can find subset whose target=12, from given array.
> 
> 
>     So, we use that last row to find our both subset diff....
> 
>         Total = 30, target=12(s1 sum), then s2_sum = 30-12 = 18, min{s1-s2} = 6....
> 
>     So we iterate over the last row and see if dp[n-1][j] == true, it means target=j possible with
>     one subset...so we calculate second subset and find min diff from that.
> ```

```c
#include <bits/stdc++.h>

int getArraySum(vector<int> &arr) {
    int sum = 0;
    for (int num : arr) {
        sum += num;
    }
    return sum;
}


int minSubsetSumDifference(vector<int>& arr, int n) {

    int sum = getArraySum(arr);

    int target = sum / 2;

    vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));

    // base case
    for (int i = 0; i <= n; i++)
        dp[i][0] = true;             // target = 0 =

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= target; j++) {
            if (j - arr[i - 1] >= 0) {
                dp[i][j] = dp[i - 1][j - arr[i - 1]] || dp[i - 1][j];
            }
            else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    // Acutal problem start from here, where we use the last row.
    int min_diff = INT_MAX;
    for (int j = 0; j <= target; j++) {            // s1_sum = 0 => target... because arr[i] also be 0... so start from 0.. s1 can be {0, 0} as well.
        if (dp[n][j] == true) {
            int s1_sum = j;
            int s2_sum = sum - j;
            min_diff = min(min_diff, abs(s1_sum - s2_sum));
        }
    }

    return min_diff;
}
```

#### [ 10_Count Subsets with Sum K](https://www.naukri.com/code360/problems/number-of-subsets_3952532)

```c
/* Intuition:

Instead of checking such subset is possible, here we need to count how many such subset is possible.

Instead of tracking (true/false) we keep track of count.

Other all things remain same, check the code!!

Edge case: target = 0, arr = {0}

    Two ways to reach target, either take it or don't take it.

        base case => return 2


    arr = {0, 0}, T = 0

    arr(1) => take_2nd_zero + don't_take_2nd_zero
           => arr(0) + arr(0)
           => 2 + 2
           => 4

    {0}, {0}, {}, {0, 0}


Two option we have to handle edge cases,

    1) Sort in asceding order & check arr[0] = 0 => 2, because if you take it or don't take it will reach target so two ways to reach target.

    2) Sort in desecing order,

        If you do that, you don't need to change algorithm, because all zero will be at last

        so take it or don't to take...also happen on that... which happend with-in algorithm and everything remain same.

        Ex: {1, 0, 0}

        index=2 => take it + not_take it, T=1
        index=1 => take it = not_take it, T =1
        index=0 => take it + not_take it, T =0 (which return 1)

        so all works in place, no code change required!!


        // Base case, target is zero. 
        // Two case: 
        // 1) Last element is '0', we return 2. (Take it , or don't take it) doesn't matter. 
        // 2) index < 0, out of elements, but reached target so, we return 1. 
            if (target == 0 && index <= 0) {
                if(index == 0 && arr[index] == 0)
                    return 2;
                return 1;
                }

*/
// Edge Case: Apporach-1. 
int t[1001][1001];

int subsetSumToKHelper(vector<int> &arr, int index, int target) {

    // Base case, target is zero, found subset.
    if (target == 0) {
        return 1;
    }

    // Incase we are out of element and still target > 0, indicate we failed to find subset.
    if (index < 0)
        return 0;

    if (t[index][target] != -1)
        return t[index][target];

    long countSubset = 0;

    // we take arr[index] into consideration, only when arr[index] <= target.
    // We have two choice either take it or not take it(remember the subset backtracking problem).
    if (target - arr[index] >= 0) {
        countSubset = (subsetSumToKHelper(arr, index - 1, target - arr[index]) % mod) + (subsetSumToKHelper(arr, index - 1, target) % mod);
    }
    else {  // Incase we won't able to take, we move to next element.
        countSubset = subsetSumToKHelper(arr, index - 1, target);
    }

    return t[index][target] = countSubset % mod;
}



int findWays(vector<int>& arr, int k)
{
    memset(t, -1, sizeof(t));

    sort(arr.begin(), arr.end(), greater<int>());   // Edge Case: arr= {0, 0, 1}

    return subsetSumToKHelper(arr, arr.size() - 1, k);
}




// Edge Case: #2 Approach. 
int t[1001][1001];

int subsetSumToKHelper(vector<int> &arr, int index, int target) {

    // Base case, target is zero. 
    // Two case: 
    // 1) Last element is '0', we return 2. (Take it , or don't take it) doesn't matter. 
    // 2) index < 0, out of elements, but reached target so, we return 1. 
    if (target == 0 && index <= 0) {
        if(index == 0 && arr[index] == 0)
            return 2;
        return 1;
    }

    // Incase we are out of element and still target > 0, indicate we failed to find subset.
    if (index < 0)
        return 0;

    if (t[index][target] != -1)
        return t[index][target];

    long countSubset = 0;

    // we take arr[index] into consideration, only when arr[index] <= target.
    // We have two choice either take it or not take it(remember the subset backtracking problem).
    if (target - arr[index] >= 0) {
        countSubset = (subsetSumToKHelper(arr, index - 1, target - arr[index]) % mod) + (subsetSumToKHelper(arr, index - 1, target) % mod);
    }
    else {    // Incase we won't able to take, we move to next element.
        countSubset = subsetSumToKHelper(arr, index - 1, target);
    }

    return t[index][target] = countSubset % mod;
}



int findWays(vector<int>& arr, int k)
{
    memset(t, -1, sizeof(t));

    sort(arr.begin(), arr.end());    // Sorting in asceding order:

    return subsetSumToKHelper(arr, arr.size() - 1, k);
}
```

### [11_CN_Partitions With Given Difference](https://www.naukri.com/code360/problems/partitions-with-given-difference_3751628)

```c
/* Intuition:

    Similar to count subset with target.... We need to count how many ways we can find such s1 & s2 pair, whose diff s1-s2 = d.

    Given that, diff between two subset is D, and total of it is sum(arr).

    S1 + S2 = T
    S1 - S2 = D... Given that S1 > S2... S1 and S2 indicate respective set sum.

    S1 = (T + D) / 2

    Again we converted above problem in single variable... with target = s1...

    #Edge case: If (T+D) is odd number, we can't divide arr then two subsets we will return 0.

    Else, We apply 10_Count Subsets with Sum K...

*/

#include <bits/stdc++.h>
#define mod 1000000007

int t[1001][1001];

int getArraySum(vector<int> &arr) {
    int sum = 0;
    for (int num : arr) {
        sum += num;
    }
    return sum;
}


int subsetSumToKHelper(vector<int> &arr, int index, int target) {

    // Base case, target is zero, found subset.
    if (target == 0) {
        return 1;
    }

    // Incase we are out of element and still target > 0, indicate we failed to find subset.
    if (index < 0)
        return 0;

    if (t[index][target] != -1)
        return t[index][target];

    long countSubset = 0;

    // we take arr[index] into consideration, only when arr[index] <= target.
    // We have two choice either take it or not take it(remember the subset backtracking problem).
    if (target - arr[index] >= 0) {
        countSubset = (subsetSumToKHelper(arr, index - 1, target - arr[index]) % mod) + (subsetSumToKHelper(arr, index - 1, target) % mod);
    }
    else {  // Incase we won't able to take, we move to next element.
        countSubset = subsetSumToKHelper(arr, index - 1, target);
    }

    return t[index][target] = countSubset % mod;
}


int countPartitions(int n, int d, vector<int> &arr) {

    int sum = getArraySum(arr);

    int target = (d + sum) >> 1;

    if ((d + sum) % 2 == 1) return 0;       // check descirption... (d+sum) odd we can't divide into two subsets. 

    memset(t, -1, sizeof(t));

    sort(arr.begin(), arr.end(), greater<int>());   // Edge Case: arr= {0, 0}

    return subsetSumToKHelper(arr, arr.size() - 1, target);
}
```

### [494. Target Sum](https://leetcode.com/problems/target-sum/)

11_CN_Partitions With Given Difference (Same Soution)

> Don't solve this problem, by assigning + and - signs(two choice) to each element and then apply recursion with memorization.
> It will work that way... Check the code... But,
> 
> This is same problem: Count S1 - S2 = D. Because when we assign sign to element that time, we are dividing them in two subset.
> 
> + sign => S1
> - sign => S2
> 
> So solve this problem using that. The same solution `11_CN_Partitions With Given Difference`



```cpp

// Don't use this solution.
class Solution {

    int OFFSET = 2e4;

public:

    int t[21][100000];

    int findTargetSumWaysSupport(int index, int target, vector<int>& nums) {

        // out of bound, index range (1, N)
        if (index == 0) {
            return target == 0;
        }

        if (t[index][target + OFFSET] != -1)
            return t[index][target + OFFSET];

        return t[index][target + OFFSET] = findTargetSumWaysSupport(index - 1, target - nums[index - 1], nums) + findTargetSumWaysSupport(index - 1, target + nums[index - 1], nums);
    }


    int findTargetSumWays(vector<int>& nums, int target) {

        memset(t, -1, sizeof(t));

        return findTargetSumWaysSupport(nums.size(), target, nums);
    }
};
```
