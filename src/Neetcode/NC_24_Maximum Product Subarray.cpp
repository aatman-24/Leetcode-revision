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
================================================================================
                                Problem Description
================================================================================

Problem: NC_24_Maximum Product Subarray
Topic: 1D-DP
Link: https://neetcode.io/problems/maximum-product-subarray

================================================================================
                                Problem Summary
================================================================================

Need to find the maximum product of subarray inside the given array. Need to find subarray
not subsequence.

================================================================================
                                Intuition & Explanation
================================================================================

At first it looks difficult but it is not.

Brute Force: Generate all subarray and get the product of it.....O(N^3)(if we do separate product operation)... O(N^2)
dyanamic subarray product....

So we know, if every number in array is positive... then its multiplication of all numbers.

But for (-ve) number we need to think,

    if (nums[i] < 0) => if, maximum product we want this number then,

            minimum_product_till_i-1 * nums[i] => which result into the positive maximum number.

    if(nums[i] > 0) => if, maximum product we want with this number then,

            maximum_product_till_i-1 * nums[i] => which result into the positive number...

    Edge case: nums[i] == 0 => we set the maxi and mini = 1... because it break the subarray and we don't want to include this...

Also, we need to keep track of max_product and min_product at each index, because the next state is depend on that...

simliar to kadene algorithm...

See, it is continuous subarray problem, so we need to keep track of result at each index....

================================================================================
                          Approach & Time/Space Complexity
================================================================================

Approach: kadene
Time Complexity: O(N)
Space Complexity: O(1)
*/

class Solution {
public:
    int maxProduct(vector<int>& nums) {

        int n = nums.size();

        // based on the first number, we keep track of max_positive and min_negative
        int pos_prev = nums[0] <= 0 ? 1 : nums[0];
        int neg_prev = nums[0] <= 0 ? nums[0] : 1;
        int maxP =  nums[0];

        int pos, neg;

        for (int i = 1; i < n; i++) {

            if (nums[i] <= 0) {

                pos = nums[i] * neg_prev;
                neg = nums[i] * pos_prev;

                maxP = max(maxP, pos);

                // make sure positive don't drop below zero... if a[i] is less than zero... then neg can go below
                // zero but not positive....
                pos = max(pos, 1);
            }
            else if (nums[i] == 0) {
                maxP = max(maxP, 0);
                pos = neg = 1;
            }
            else {

                pos = nums[i] * pos_prev;
                neg = nums[i] * neg_prev;

                maxP = max(maxP, pos);
            }

            pos_prev = pos;
            neg_prev = neg;
        }

        return maxP;
    }
};




class Solution {
public:
    int maxProduct(vector<int> A) {

        int n = A.size();

        // store the result that is the max we have found so far
        int r = A[0];

        // imax/imin stores the max/min product of
        int imax = r;   // maximum till ith
        int imin = r;   // minimum till ith

        // subarray that ends with the current number A[i]
        for (int i = 1; i < n; i++) {

            // multiplied by a negative makes big number smaller, small number bigger
            // so we redefine the extremums by swapping them
            if (A[i] < 0)
                swap(imax, imin);

            // max/min product for the current number is either the current number itself
            // or the max/min by the previous number times the current one
            imax = max(A[i], imax * A[i]);
            imin = min(A[i], imin * A[i]);

            // the newly computed max value is a candidate for our global result
            r = max(r, imax);
        }
        return r;
    }
};
