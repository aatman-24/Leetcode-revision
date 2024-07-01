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

Question : 930. Binary Subarrays With Sum
Topic : PrefixSum, SlidingWindow
Problems : https://leetcode.com/problems/binary-subarrays-with-sum/description/

==============================> Explanation <=============================================

1) Brute Force:
- We can get all subarray with two for loops and then check if that subarray sum is equal to target.

2) Prefix Sum with Hashmap:
- Intuition behind this apporach is that,

If we have prefixSum and target, then we can find the remainingSum into map by storing it.

target = prefixSum + remainingSum(We store in hashmap, so we can check for it in O(1)), we already know this.

It works for positive and negative numbers!!


3) Sliding Window:

We can't use the sliding window directly, reason is that it works when element in arr is > 0. But here we have 0 as well, so it won't work.
For ex:

arr = [0 0 0 1 1 0], T = 1. NumOfSubArray =
window: 0 0 0 1, curSum = 1 *
window: 0 0 0 1 1, curSum = 2 > T..so we decrease the window
window: 0 0 1 1 curSum = 2 > T..so we decrease the window
window: 0 1 1, curSum = 2 > T..so we decrease the window
window: 1 1 curSum = 2 > T..so we decrease the window
window: 1 curSum = 1 == T..so we count it and increase the window *
window: 1 0 curSum = 1 == T..so we count it and increase the window *

Found only 3 window which have T = 1, missed too many like 0 0 1, 0 1, due to we shrink the window due to addition of rare element '1'.

That's why a[i] <= 0, sliding window won't work. So we have to modify such that we can use it!!


Intuition Behind this algorithm is, we first count the subarray which sum is at most K and after that we
count subarray which sum is at most (K - 1) and subtract it from the previous which result into the subarray
which sum is K.

subarray sum with K = subarray with sum at Most K - subarray with sum at Most K-1.
subarray with sum 2 = subarray with sum at most 2(sum=2, sum=1, sum=0) - subarray with sum at most 1(sum=1, sum=0)
                    = subarray with sum 2


Index: 0 1 2 3 4 5 6
Array: 0 0 0 1 1 0 0

K=2  : 1 2 3 4 5(') 6 7

5 -> [0, 0, 0, 1, 1], [0, 0, 1, 1], [0, 1, 1], [1, 1], [1] (sum at most 2 -> (0, 1, 2))

K=1  : 1 2 3 4 1(') 2 3

1 -> [1] (last one in above). (sum at most 1 -> (1, 0))

res  : 0 0 0 0 4(') 4 4

Ans=4 -> [0, 0, 0, 1, 1], [0, 0, 1, 1], [0, 1, 1], [1, 1] (sum exactly -> 2)

Check the code!!

==============================> Approach and Time Complexity <============================

N = s.size()

1) Brute Force
Time: O(N^2)
Space: O(1)

2) PrefixSum + Hashing
Time: O(N)
Space: O(K)

3) Sliding Window
Time: O(N)
Space: O(1)


*/



class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {

        unordered_map<int, int> mp;
        int prefixSum = 0, ans = 0;

        // key=prefix-sum. value=frequency of that prefix sum.
        // When we start that time our prefixSum is 0, so we have to encounter that as 1 frequency.
        // see why on description...
        mp[prefixSum] = 1;

        for (int i = 0; i < nums.size(); i++) {

            prefixSum += nums[i];

            // Check if, prefixSum-goal is already encountered previously. Yes, then how many times ?
            if (mp.count(prefixSum - goal)) {
                ans += mp[prefixSum - goal];
            }

            // save current prefixSum for next elements.
            mp[prefixSum]++;
        }

        return ans;
    }
};


// Sliding Window
class Solution {
public:

    // Return the num of subarray whose sum is [0, T].
    int sumAtMostT(vector<int>& nums, int T) {

        if (T < 0) return 0;

        int begin = 0, end = 0, N = nums.size();
        int cnt = 0, curSum = 0;

        while (end < N) {

            curSum += nums[end++];

            while (curSum > T) {
                curSum -= nums[begin];
                begin++;
            }

            cnt += (end - begin);
        }

        return cnt;
    }

    int numSubarraysWithSum(vector<int>& nums, int goal) {
        return sumAtMostT(nums, goal) - sumAtMostT(nums, goal - 1);
    }
};