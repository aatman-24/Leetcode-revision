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

Question : 81. Search in Rotated Sorted Array II
Topic : Binary Search
Problems : https://leetcode.com/problems/search-in-rotated-sorted-array-ii/description/

==============================> Explanation <=============================================

Parent: 33. Search in Rotated Sorted Array

But in this questions, we can have duplicates as well.

1 1 2 3 4 -> 1 2 3 4 1 -> K = 4 times rotated.

In this case, the #33 solution won't work, because duplicates, so that is edge case. So whenever arr[lh]==arr[rh],

1) We check, arr[lh] is target or not. If not then we shortern boundary by removing both elements => [2, 3, 4] again lookup for target.
2) Apart from that, it is same as #33 to search in rotated array.

==============================> Approach and Time Complexity <============================


1) Binary Search
Time: O(logN)
Space: O(logN)


 */


class Solution {
public:
	bool search(vector<int>& arr, int target) {

		int lh = 0, rh = arr.size() - 1;

		while (lh <= rh) {

			// edge case, if lh -> rh points to the same element, we can skip both by checking it is target or not.
			if (arr[lh] == arr[rh]) {
				if (arr[lh] == target)
					return true;
				lh++; rh--;
				continue;
			}

			int mid = (lh + rh) >> 1;

			if (arr[mid] == target)
				return true;

			if (arr[lh] <= arr[mid]) { // lh -> mid sorted

				// [arr[lh] <= target < arr[mid]]
				if (arr[lh] <= target && target < arr[mid]) {		// already checked arr[mid] == target, but we need to check arr[lh] <= target
					rh = mid - 1;
				}
				else {		// otherwise check on other side.
					lh = mid + 1;
				}

			}
			else {				// mid -> rh sorted

				// (arr[mid] < target <= arr[rh])		// sorted range
				if (arr[mid] < target && target <= arr[rh]) {
					lh = mid + 1;
				}
				else {		// otherwise check on other side
					rh = mid - 1;
				}

			}
		}
		return false;
	}
};



