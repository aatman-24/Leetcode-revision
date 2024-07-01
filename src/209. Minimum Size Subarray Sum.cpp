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

Question : 209. Minimum Size Subarray Sum
Topic : Sliding Window
Problems : https://leetcode.com/problems/minimum-size-subarray-sum/description/
==============================> Explanation <=============================================

Sliding Window Technique:
- In Question given that, minimum length of subarray and every interger is positive.. so we can think of one window which have sum >= target.. once
its have more than target we shrink that window and when its have less we add more element. I tried out on pen and paper and it works!
Check the code!!

PrefixSum + Binary Search:
- In the follow up they asked the O(NlogN) solution, so in the mind first thing came up is sorting...but it doesn't work by sorting original array... and it is tricky to come
up with that solution.

Idea is that, if we use prefix-sum of array, we can get sorted array and use that array to find the length of sub-array(second boundary of window) using binary search..

How ?

When we use the sorted array, we can use binary search to find the next target element = prefix[i] + target. (in our new target also prefix[i] is already added so it compensate that part)

    2 3 1 2 4 3
  0 2 5 6 8 12 15

    target => 7

     i = 3, prefix[i+1] = 8, by adding 7 we can get 15 which is last element of prefix-array so (4, 3) as our solution.


Check the code!!

==============================> Approach and Time Complexity <============================

N = s.size()

1) Sliding Window
Time: O(N)
Space: O(1)

2) Prefix Sum + Binary Search



*/


class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {

        int N = nums.size();
        int begin = 0;
        int min_subarray_size = INT_MAX;
        int curSum = 0;

        for (int end = 0; end < N; end++) {

            // Add new element
            curSum += nums[end];

            // Validate the window.
            while (curSum >= target) {
                min_subarray_size = min(min_subarray_size, end - begin + 1);
                curSum -= nums[begin++];
            }
        }

        return min_subarray_size == INT_MAX ? 0 : min_subarray_size;

    }
};



class Solution {
public:

    int binary_search(int low, int high, int target, vector<int> nums) {

        while (low <= high) {

            int mid = (low + high) >> 1;

            if (nums[mid] < target) {
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }

        return low;
    }


    int minSubArrayLen(int target, vector<int>& nums) {

        int N = nums.size();
        int min_subarray_size = INT_MAX;
        vector<int> prefix(N + 1, 0);

        // prefix sum
        for (int i = 1; i <= N; i++)
            prefix[i] = prefix[i - 1] + nums[i - 1];

        for (int begin = 0; begin < N; begin++) {

            // low => begin + 1; because in prefix array nums[begin] is added in next index(begin+1).
            // end => N, because prefix array is N+1 length.
            // target => prefix[begin](till ith element sum) +target, so this new target in prefix array also have first part, which got componsate and we get acutal target.
            int end = binary_search(begin + 1, N, prefix[begin] + target, prefix);

            // not found. No need to check further element because arry is sorted, if we don't get prefix[begin]+target, then no need to such greater number than it.
            if (end == N + 1) break;

            // compute the window size. here end already have that (+1) factor so no need to add that.
            min_subarray_size = min(min_subarray_size, end - begin);
        }

        return min_subarray_size == INT_MAX ? 0 : min_subarray_size;

    }
};