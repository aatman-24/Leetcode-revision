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

Question : 74. Search a 2D Matrix
Topic : Binary Search
Problems : https://leetcode.com/problems/search-a-2d-matrix/description/

==============================> Explanation <=============================================

Given matrix is sorted, so first thought comes to mind should be binary search.

1 	3 	5 	7
10 	11 	16 	20
23 	30 	34 	60

target is = 16, then we can get it second row only, 10 < 16 < 23.
target is = 6, then we can get it in first row only, 1 < 6 < 10.

So it is strightforward that we first need to find in which row our target can be found, which is done
by finding upper_bound of target in first column.

1 10 23

T = 16 upper_bound = 10
T = 6   upper_bound = 1

upper_bound of T = T || lesser element than T

so either we get Target or row in which the target can be found.

so we need to lookup into that row only. And that row is sorted so we can use the binary search to find the element in that specific row.

Time: O(lookup_in_first_column) + O(lookup_in_row) = O(log(N)) + O(log(M)) => O(log(MN))



#2: Convert the matrix into single array and the perform binary search.

It is only possible due to given that...

	last_element_in_row < first_element_in_next_row + each_row_is_sorted.

How to convert into single array ?

For that,

let's see...

1) How to convert the matrix into array

M = NO_OF_ROW
N = NO_OF_COL

mat[x][y] => arr[x*M + y]


2) How to conver the array into matrix


M = NO_OF_COL
N = NO_OF_ROW

arr[i] => mat[i/M][i%M]


Check the code

==============================> Approach and Time Complexity <============================

1) Binary Search
Time: O(N)
Space: O(N)


2) Binary Search As Whole Array
Time: O(N*M)
Space: O(N*M)

 */

class Solution {
public:
	int upper_bound(vector<vector<int>>& mat, int target) {
		int left = 0, right = mat.size() - 1;

		while (left <= right) {

			int mid = (left + right) >> 1;

			if (mat[mid][0] == target) {
				return mid;
			} else if (mat[mid][0] < target) {
				left = mid + 1;
			} else {
				right = mid - 1;
			}
		}

		return right;
	}

	bool binarySearch(vector<int>& arr, int target) {
		int lf = 0, rh = arr.size() - 1;
		while (lf <= rh) {
			int mid = (lf + rh) >> 1;
			if (arr[mid] == target)
				return true;
			else if (arr[mid] < target)
				lf = mid + 1;
			else
				rh = mid - 1;
		}
		return false;
	}

	bool searchMatrix(vector<vector<int>>& matrix, int target) {

		int row = upper_bound(matrix, target);

		if (row == -1)
			return false;

		if (matrix[row][0] == target) {
			return true;
		}

		return binarySearch(matrix[row], target);
	}
};



class Solution {
public:
	bool searchMatrix(vector<vector<int>>& mat, int target) {
		int M = mat[0].size(), N = mat.size();
		int left = 0, right = M * N - 1;
		while (left <= right) {
			int mid = (left + right) >> 1;
			if (mat[mid / M][mid % M] == target) {
				return true;
			} else if (mat[mid / M][mid % M] < target) {
				left = mid + 1;
			} else {
				right = mid - 1;
			}
		}
		return false;
	}
};