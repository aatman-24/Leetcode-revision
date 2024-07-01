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

Question : 974. Subarray Sums Divisible by K
Topic : PrefixSum
Problems : https://leetcode.com/problems/subarray-sums-divisible-by-k/description/

==============================> Explanation <=============================================

1) Brute Force:
- We can get all subarray with two for loops and then check if that subarray sum is divisible by k or not. Take: O(N^2)*O(N)(Peform sum), O(1) time.

2) Brute Force optimization with Prefix Sum array:
- Used same apporach, but using prefix sum array we can reduce O(N^3) -> O(N^2), space: O(N)

2) Prefix of Mod: (Proof from #523. Continuous Subarray Sum)

- During prefix sum, we got curSum % k = n, n got repeted two times for any i and j position that means sum[i+1, j] % k == 0.. that's why we again
got the same value.

- We used same apporach. We know that for any i, curSum[i] % k return same value which we previously seen it means, [previousPosition, i] subarray is divisible by k.

Here, we need to find the count of such subarrays so we used map to keep track of how many subarray we can have for that mod.

For example.. curSum[j] mod K = n, and already map contains {n, 2}. [subarray1, subarray2] means, already two subarrays we encounterd which is divisible by k.

And now we have one more position at j, which also return n.

So, total new subarray got created are = {subarray1, n}, {subarray2, n}... so two additional subarray got created. And also we increase the counter of that "n" into map.

Because, next time if we again get n, for m element,

mp[n] = 3
{subarray1, n}, {subarray2, n}, {n}

so new subarrays got created will be

{subarray1, n, m}, {subarray2, n, m}, {n, m}

That's reason we are using that memory to calculate total number of subarrays.

NOTE:

if a > 0, a % k = m.
if a < 0, a % k != m but (a + n*k) % k = m. where, (a + n * k) > 0..... means that for negative number we need to add k for n times until that expresion become greater than zero.



Mathematical Proof:

- sum[i] % k = n1, sum[j] % k = n2  //   Here, sum[i] means sum of subarray from (0, i).

Given that, n1 == n2,
            sum[i] % k == sum[j] % k ----- (1)

now, suppose the difference between i and j is d, i <= j
- d = j - i.
- j = d + i ----- (2)

putting eq-2 value into eq-1..

sum[i] % k   = sum[d + i] % k
 sum[i] % k  = (sum[d] % k + sum[i] % k) % k

given that all elements are >= 0, above equation is valid when,

sum[d] % k == 0         // Where sum[d] is sum from (i+1, j).

It means that sum[d] is divisible by 0.

Conclusion:


Hence, proved that if arr contains all elements a(i) >= 0, any two ranges (0, i) and (0, j) gives equal sum of module for any k, then range (i+1, j) sum is divisible by k.
In other words,
    If we are getting sum % k = n, and these n is repeated two times and first time if it's position is I and current position is j the sum(i+1, j) % k == 0, that's why n is again
    got repeated..that sum(i+1, j) is divisible by k.

Check the code!!


==============================> Approach and Time Complexity <============================

N = s.size()

1) Brute Force
Time: O(N^2)
Space: O(1)

2) PrefixSum mod K
Time: O(N)
Space: O(1)

*/



class Solution {
public:
    int subarraysDivByK(vector<int>& nums, int k) {

        // store mp[sum%k] = frequency, sum%k=n.. how many time n got repeated.
        unordered_map<int, int> mp;

        int prefixSum = 0, totalSubarray = 0;

        // Base Case: preFixSum got repeated 1 time. Next time prefixSum % k == 0, it means from (0, i) we got the sum which is divisible by k.
        mp[prefixSum] = 1;

        for (int i = 0; i < nums.size(); i++) {

            prefixSum += nums[i];

            // take mod K
            // For negative num, we have to make positive by adding k. Then and only we can take mod.
            // For ex: -1 % 5 = -1 (which is wrong) correct answer is 4. (-1 + 5) % 5 = 4(correct way)
            while (prefixSum < 0) {
                prefixSum = (prefixSum + k) % k;
            }

            prefixSum = (prefixSum + k) % k;

            if (mp.count(prefixSum)) {
                totalSubarray += mp[prefixSum];         // Addition of nums[i], make contribution to each of previous subarray. So total same number of subarray got generated which is divisible by k.
            }

            mp[prefixSum]++;
        }

        return totalSubarray;

    }
};