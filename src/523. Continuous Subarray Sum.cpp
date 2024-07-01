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

Question : 523. Continuous Subarray Sum
Topic : PrefixSum
Problems : https://leetcode.com/problems/continuous-subarray-sum/description/?source=submission-noac

==============================> Explanation <=============================================

1) Brute Force:
- We can get all subarray with two for loops and then check if that subarray sum is divisible by k or not. Take: O(N^2)*O(N)(Peform sum), O(1) time.

2) Brute Force optimization with Prefix Sum array:
- Used same apporach, but using prefix sum array we can reduce O(N^3) -> O(N^2), space: O(N)

2) Prefix of Mod:

- During prefix sum, we got curSum % k = n, n got repeted two times for any i and j position that means sum[i+1, j] % k == 0.. that's why we again
got the same value.


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

above equation is valid when,

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

    bool checkSubarraySum(vector<int>& nums, int k) {

        unordered_map<int, int> mp;
        int prefixSum = 0;

        // prefiSum % k = 0 at -1 position. If we again get 0 as curSum % k, it means from (0, i) the sum is divisible by k.
        mp[0] = -1;

        for (int i = 0; i < nums.size(); i++) {

            prefixSum += nums[i];

            if (k != 0) prefixSum = prefixSum % k;

            if (mp.count(prefixSum)) {
                int prevPosition = mp[prefixSum];
                if (i - prevPosition > 1)
                    return true;
            }
            else {
                mp[prefixSum] = i;
            }
        }

        return false;
    }
};