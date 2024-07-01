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

Question : 303. Range Sum Query - Immutable
Topic : PrefixSum
Problems : https://leetcode.com/problems/range-sum-query-immutable/description/

==============================> Explanation <=============================================

1) Brute Force:
- For each (i, j) I can compute the subarray sum and return it. But We have to do it for each of the query.

2) Optimize by pre-compute:

arr = [a, (L)b, c, (R)d, e]

if we use the prefix sum here,

prefix = [a,  a+b, a+b+c, a+b+c+d, a+b+c+d+e]

answer is = sum(L, R) => (a+b+c+d)(R) - (a)(L-1) => b+c+d

In short, ans(L, R) = prefix[R] - prefix[L-1]

==============================> Approach and Time Complexity <============================

N = s.size()

1) Brute Force
Time: O(N) for each query
Space: O(N)

2) prefixsum
Time: O(1) for each query
Space: O(N)


*/



class NumArray {
public:

    vector<int> prefix;

    NumArray(vector<int>& nums) {
        int N = nums.size();
        prefix.assign(N, 0);
        prefix[0] = nums[0];
        for (int i = 1; i < N; i++) {
            prefix[i] = prefix[i - 1] + nums[i];
        }
    }

    int sumRange(int left, int right) {
        int sum = prefix[right];
        if (left - 1 >= 0) sum -= prefix[left - 1];
        return sum;
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */