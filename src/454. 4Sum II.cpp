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

Question :  454. 4Sum II
Topic : Two Pointer, Hashing
Problems : https://leetcode.com/problems/4sum-ii/description/

==============================> Explanation <=============================================

Brute Force: Use 4 For loops and see if sum is zero or not and increase the count++.

Hashing(Two Sum): Here, we first find the all possible sums of first array(i, j) and put under one map<sum,count>. And We can calculate the
sum for last two array by picking(i,j) and check for the -sum into the map. If we found, it means (i, j, k, l) is there whose sum is zero(target).

- We can modify this approach, by rathar than storing all possible sum for first two array, we can do the same for last two arrays. Later, iterate over the
map, and can find opposite sum in second map.

Example of: Totalcount = count1 * count2 (all combination give zero sum)

count1: -1 3, 3 -1
count2: 1 3, 3 1

totalCount = 4, whose sum is zero.


==============================> Approach and Time Complexity <============================

N = nums.size()

1) Brute Force
Time: O(N^4)
Space: O(1)

3) Hashing + Two Pointer: O(N^2)
Space: O(N^2) (Max diff sum possible)

*/

class Solution {
public:
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {

        int n = nums1.size();
        int totalSumCount = 0;

        map<int, int> firstSum, secondSum;

        // Finding the pair of sum for both arrays, putting under the map<sum, count> way.
        for (int i = 0; i < n; i++) {

            for (int j = 0; j < n; j++) {

                int sum1 = nums1[i] + nums2[j];
                firstSum[sum1] = firstSum[sum1] + 1;

                int sum2 = nums3[i] + nums4[j]
                           secondSum[sum2] = secondSum[sum2] + 1;

            }

        }

        for (auto it : firstSum) {

            int requiredSum = -it.first, curSumCount = it.second;

            if (secondSum.count(requiredSum)) {

                totalSumCount += ((curSumCount) * secondSum[requiredSum]); // totalCount = count1 * count2. You can select those subarrays by any combination.

            }

        }

        return totalSumCount;

    }
};



