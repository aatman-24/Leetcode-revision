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

Question : 33. Search in Rotated Sorted Array
Topic : Binary Search
Problems : https://leetcode.com/problems/search-in-rotated-sorted-array/description/

==============================> Explanation <=============================================

Variation of the standard binary algorithm,

Three case possible only due to clockwise rotation:

1) (L << M << R)
2) (L >> M << R)
3) (L << M >> R)


#1: no matter what where T reside it will be spotted easily.
#2: we know that M << R... so we just check that M << T << R... if yes then check on (M+1, R) else (L, M-1)
#3: we know that L << M... so we just check that L << T << M... if yes then check on (L, M-1) else (M+1, R).


Basically, we are using the sorted subarray information as benefit to decide which range to explore next.


==============================> Approach and Time Complexity <============================

1) Binary Search
Time: O(logN)
Space: O(1)

 */

class Solution {
public:
	int search(vector<int>& nums, int target) {

		int left = 0, right = nums.size() - 1;

		while (left <= right) {

			int mid = (left + right) >> 1;

			if (target == nums[mid])
				return mid;


			// left side sorted.
			if (nums[left] <= nums[mid]) {

				// if target is in sorted range, explore that only
				if (nums[left] <= target && target < nums[mid]) {
					right = mid - 1;
				}
				else {
					left = mid + 1;
				}
			}
			// right side sorted
			else {

				// if target is in sorted range, explore that only
				if (nums[mid] < target && target <= nums[right]) {
					left = mid + 1;
				}
				else {
					right = mid - 1;
				}
			}
		}

		return -1;
	}
};