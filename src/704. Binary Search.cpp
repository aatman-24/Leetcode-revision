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

Question : 704. Binary Search
Topic : Traversal
Problems : https://leetcode.com/problems/binary-search/description/

==============================> Explanation <=============================================

Standard Binary Search Algorithm.

==============================> Approach and Time Complexity <============================

1) Binary Search
Time: O(logn)
Space: O(1), O(logn)(recursive call)

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