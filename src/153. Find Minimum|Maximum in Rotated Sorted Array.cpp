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

Question : 153. Find Minimum|Maximum in Rotated Sorted Array
Topic : Binary Search
Problems : https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/description/

==============================> Explanation <=============================================

Given that array is sorted but rotated at K factor, still we can apply the binary search to find lowest element.

Three case possible only:
#1: 1 2 3 4 5 -> lowest element is 1
#2: 5 1 2 3 4
#3: 3 4 5 1 2

#approach-1:
we first check,
	arr[l] < arr[m] (L...M) is sorted in right order.
		1a. arr[m] < arr[r]... (L<<M<<R) everything is sorted. We need to check on (L<<M-1) range only.
			r = mid - 1
		2a. arr[m] > arr[r]... (L<<M>>R) left side is sorted... something wrong in (M, R) so we check there.
			l = mid
	arr[l] >= arr[m]
		1b. arr[m] < arr[r]...(L>>M<<R) right side is sorted...someting wrong in (L, M) so we check there.
			r = mid;
		2b. arr[m] > arr[r]...(L>>M>>R) we can have lowest in (M, R) only.
			l = mid+1;

To be honest, #2b is not possible, array is rotated in clockwise only. And #1a we can simply return the arr[l] as lowest elements.
That's approach-2.

#approach-2:

	#1a.(L<<M<<R) array sorted, return arr[l] as lowest element.
	else
		(L>>R)
		#2a.(L<<M>>R) left side array sorted, look into (M+1, R) only.  // 3 4 5 1 2
		#2b.(L>>M<<R) right side array sorted, look into (L, M]. 		// [5 1 2 3 4], [2 1]


For both approach,

Base Case | Edge case(two elements):

#1 Approach

1) 1 2

L = 1, M = 1, R = 2
- That case, R => mid, R = 2

2) 2 1

L = 2, M = 2, R = 1
- That case, L = mid + 1, L = 1, R = 1

Both case, Right hold the minimum value.

#2 Approach

1) 1 2 (we return 1 as minimum)

1) 2 1
L = 2, M = 2, R = 1
L = mid + 1, L = 1, R = 1, So L and R both hold minimum value.


Rememeber the second approach.



==============================> Approach and Time Complexity <============================

1) Binary Search
Time: O(N)
Space: O(N)

 */


class Solution {
public:
	int findMin(vector<int>& arr) {

		int l = 0, r = arr.size() - 1;

		while (l <= r) {

			int mid = (l + r) >> 1;

			if (arr[l] < arr[mid]) {

				if (arr[mid] < arr[r]) { 		// (L<<M<<R)
					r = mid - 1;
				}
				else {
					l = mid;					// (L<<M>>R)
				}
			}
			else {

				if (arr[mid] < arr[r]) {			// (L>>M<<R)
					r = mid;
				}
				else {
					l = mid + 1;				// (L>>M>>R) (not possible due to clockwise rotation)
				}


			}

		}

		return arr[r];
	}
};




class Solution {
public:
	int findMin(vector<int>& nums) {

		int left = 0, right = nums.size() - 1;

		while (left < right) {

			// sorted array, return lowest.
			if (nums[left] < nums[right])
				return nums[left];

			int mid = (left + right) >> 1;

			if (nums[left] <= nums[mid]) {			// (L<<M>>R) 3 4 5 1 2 	-> check on 1, 2. (m+1, R) we are sure that arr[m] can't be minimum.
				left = mid + 1;
			}
			else {
				right = mid;						// (L>>M<<R) 5 1 2 3 4 check on 5,1, 4 5 1 2 3  -> check on 4, 1, (l, m)
			}
		}

		return nums[right]; // nums[left];
	}
};


// finding maximum in sorted array.
class Solution {
public:
	int findMin(vector<int>& nums) {

		int left = 0, right = nums.size() - 1;

		while (left < right) {

			// sorted array, return maximum.
			if (nums[left] < nums[right])			// (L<<R)
				return nums[right];

			int mid = (left + right) >> 1;

			if (nums[left] < nums[mid]) {			// (L>>R) && (L<<M>>R) 3 4 5 1 2 	-> check on 1, 2. (m+1, R) we are sure that arr[m] can't be minimum.
				left = mid;
			}
			else {
				right = mid - 1;						// (L>>R) && (L>>M<<R) 5 1 2 3 4 check on 5,1, 4 5 1 2 3  -> check on 4, 1, (l, m)
			}
		}


		// edge case: 1 2... we return 2 directly.
		// edge case: 2 1.... L=0, M=0, R=1.... nums[0]<nums[0](false)=> R = 0-1=-1... return arr[L](2)
		return nums[left];
	}
};