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

Question : 1248. Count Number of Nice Subarrays
Topic : prefix-sum, hashing, sliding-window
Problems : https://leetcode.com/problems/count-number-of-nice-subarrays/description/

==============================> Explanation <=============================================

1) Brute Force:
- We can get all subarray with two for loops and then check if that subarray have odd numbers in it, we can use prefix sum which keep track of total number of odd number found till ith location,
doing that we can reduce time complexity by O(N).

2) PrefixSum + Hashing:
- Intuition is that, we can store how many odd number encounter at a moment and next time we visit we can check if (oddNumbersTillNow-T) is already present
into map. If yes we can add those counts.
It works in same fashing, subarray sum, subarray sum divide by k.... all are same.

3) Sliding Window:
- Idea is same, given that need to count number of subarray which have k odd numbers.
We can peform this = atMostoddNumber(K) - atMostoddNumber(k-1), so we get exactly Kth odd numbers subarray count.
Again facing the same issue, because checking odd number is peforming % 2 == 0, so we have 0 in subarray.

BTW, if we perform % 2 for each elemnt of array we get the #930. Binary Subarrays With Sum.

Check this!!
930. Binary Subarrays With Sum

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

    int atMostK(vector<int>& nums, int k)  {
        int begin = 0, end = 0, count = 0, ans = 0;
        while (end < nums.size()) {
            count += (nums[end++] % 2 == 1);
            while (count > k) {
                count -= (nums[begin++] % 2 == 1);
            }
            ans += (end - begin);
        }
        return ans;
    }

    int numberOfSubarrays(vector<int>& nums, int k) {
        return atMostK(nums, k) - atMostK(nums, k - 1);
    }
};


class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {

        // key: number of odd Coutner till ith location, value: how many time it got repeated.
        unordered_map<int, int> mp;
        int prefixCountOfOddNumbers = 0, totalSubArray = 0;
        mp[0] = 1;  // 0 odd numbers, got repeated 1 time. (Not selecting any number is also a choice)
        for (int i = 0; i < nums.size(); i++) {
            prefixCountOfOddNumbers += (nums[i] % 2) == 1;
            if (mp.count(prefixCountOfOddNumbers - k)) {
                totalSubArray += mp[prefixCountOfOddNumbers - k];
            }
            mp[prefixCountOfOddNumbers]++;
        }
        return totalSubArray;
    }
};