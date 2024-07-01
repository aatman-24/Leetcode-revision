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

Question :  2395. Find Subarrays With Equal Sum
Topic : Hashing
Problems : https://leetcode.com/problems/find-subarrays-with-equal-sum/

==============================> Explanation <=============================================

Brtue force: Use two for loops, first one to get sum of arr[i-1]+arr[i] and then next for loop to find sum in remaining array.


Hashing:  The intuition behind this solution is to find two subarray(not subsequence) of length 2 with equal sum. While iterating I can
do sum of two subsequent elements then check same element found in map or not. If not, then I add current sum into map and check for next elements.
Whenever I am getting sum in map that time I found those two subarrays.


==============================> Approach and Time Complexity <============================

N = nums.size()

1) Hashing
Time: O(N)
Space: O(1)

*/


class Solution {
public:
    bool findSubarrays(vector<int>& nums) {

        unordered_map<int, int> mp;

        int N = nums.size();

        for (int i = 1; i < N; i++) {

            int curSum = nums[i - 1] + nums[i];

            if (mp.count(curSum)) {
                return true;
            }

            mp[curSum] = 1;

        }

        return false;
    }
};