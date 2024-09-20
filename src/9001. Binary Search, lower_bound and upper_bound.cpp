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

Question : 9001. Binary Search, lower_bound and upper_bound
Topic : Search
Problems :

==============================> Explanation <=============================================

Standard Binary Search Algorithm.

Added the lower_bound and upper_bound algorithm.

lower_bound of T, lower_bound = T or Just greater element than T
upper_bound of T, upper_bound = T or Just lesser element than T

During impl only one diffcutly is that, when target element is not found and you are at the last step..

Arr:
0   1
10  15

T: 15, Currently, L = 0, R = 1

mid = L + R / 2 = 0

arr[mid] < T(12), L = mid + 1, L = 1, R = 1

Last iteration,

L = 1, R = 1, M = 1,

T(12) < arr[1](15) => L = 1, R = 0, M =1

upper_bound(12) => 12 or just lesser element which is 10 => That's why we return R, arr[R] = 10.

lower_bound(12) => 12 or just greater element whish is 15 => That's why we return L, arr[L] = 15.

==============================> Approach and Time Complexity <============================

1) Binary Search
Time: O(N)
Space: O(N)

 */


// Iterative
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int low = 0, high = nums.size() - 1;
        while (low < high) {
            int mid = (low + high) >> 1;
            if (nums[mid] == target)
                return mid;
            else if (nums[mid] < target) {
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }
        return -1;
    }
};


// Recursively
class Solution {
public:

    int search(vector<int> &nums, int low, int high, int target) {
        if (low > high)
            return -1;

        int mid = (low + high) >> 1;

        if (nums[mid] == target)
            return mid;

        if (nums[mid] < target) {
            return search(nums, mid + 1, high, target);
        }

        return search(nums, low, mid - 1, target);
    }


    int search(vector<int>& nums, int target) {
        return search(nums, 0, nums.size() - 1, target);
    }
};

// lower_bound and upper_bound

class Solution {
public:

    int upper_bound(vector<int> &arr, int target) {
        int lf = 0, rh = arr.size() - 1;
        while (lf <= rh) {
            int mid = (lf + rh) >> 1;
            if (arr[mid] == target)
                return arr[mid];
            else if (arr[mid] < target)
                lf = mid + 1;
            else
                rh = mid - 1;
        }
        return arr[rh];             // 10 | 15, T = 14, lf=rh=15.... At the end: 10(rh) | 15(lf), return rh;
    }

    int lower_bound(vector<int> &arr, int target) {
        int lf = 0, rh = arr.size() - 1;
        while (lf <= rh) {
            int mid = (lf + rh) >> 1;
            if (arr[mid] == target)
                return arr[mid];
            else if (arr[mid] < target)
                lf = mid + 1;
            else
                rh = mid - 1;
        }
        return arr[lf];  // 10 | 15, T = 14, lf=rh=15.... At the end: 10(rh) | 15(lf), return lf.
    }
};
