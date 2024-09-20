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

Question :  4. Median of Two Sorted Arrays
Topic : Binary Search
Problems : https://leetcode.com/problems/median-of-two-sorted-arrays/

==============================> Explanation <=============================================

- Very nice Problem on BS.

Apporach 1) We can merge both sorted into the single array and take the median of it.
 O(N) + O(N) (Merge Two Sorted Array using Extra array) [merge sort + merge method]

Apporach 2) O(N) + O(1) (Same but without Extra array use the Counter to count element is
            already  merged.)
    For odd numbers  we need to pick = n/2
    for even numbers we need to pick = n/2 - 1, n/2 both and do the average

Appoorach 3) O(min(logN,logM)) (binary Search)

Idea is that,

nums1: 1 5
nums2: 2 3 4

Even: 1 2 3 | 4 5 6
Odd: 1 2 3 | 4 5

To get median half of elements on left side of cut, half on right side. (exception for total odd numbers). For odd we try to make the cut N+1 | N.

We need to focus on left side only and figure out how many coming from nums1 and nums2.

Total element = 10, left side = 5.

nums1 => 1, nums2 => 4
nums1 => 2, nums2 => 3
nums1 => 3, nums2 => 1
..
..

After cut we got this.

num1: 1 2 | 3 4
num2:  5 6 | 7 8

Then 2 < 3 and 6 < 7. It is obvious.

But we need to check on entire left < entire right.

	1 2 5 6 | 3 4 7 8.... 6 < 3 (not right cutting)

left1 < right1 & left2 < right2 (That we know due to cutting)
We need to check,
left1 < right2 & left2 < righ1..... to make it valid.

Yes, we can do this in linear way as well, but then we get this in O(N+M) time. Doesn't make any difference.

How Binary Search ?

nums1 = 1 5 7 9

we know that, nums1 = 1 5 7 is right answer.

for ex:
now if make cut on => 1 | 5 7 9 		(It is not valid). then... | 1 5 7 9 (also never become valid) so we skip entire left range. and move to right side.

So we basically use the binary search on one the array and based on that define left1, left2, right1, right2.

1) left1 > right2
=> it means that, cut1 is more on right side.. we should decrease that to make left1 < right2.

2) left2 > right1
=> it means that right1 is very low, we need to increase right1 to make sure left2 < right1.

And also we make sure that on whichever array we apply binary search is always smaller compare to others.

How to handle even and odd case ?

In the odd case, we know we make parition n+1|n.... so we choose max(left1, left2).

For the even case, we choose (max(left1, left2) + min(right1, right2)) / 2


==============================> Approach and Time Complexity <============================

1) Binary Search
Time: O(logN)
Space: O(logN)

 */


// OLD CODE, BEST ONE.
class Solution {
public:

	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {

		// Try to make first as smaller array.
		if (nums1.size() > nums2.size()) return findMedianSortedArrays(nums2, nums1);

		int n1 = nums1.size(), n2 = nums2.size(), low = 0, high = n1;

		// Binary Search on first array.
		while (low <= high) {

			// cut1 -> picking the cut1(0, cut1) elements from nums1.
			// cut2 -> picking the cut2(0, cut2) elements from nums2. (total/2 - cut1)
			int cut1 = (low + high) >> 1;

			// For odd elements we try to make partition n+1 | n so that is reason +1 is added.
			int cut2 = (n1 + n2 + 1) / 2 - cut1;

			// find out left side and right side of split.
			int left1 = cut1 == 0 ? INT_MIN : nums1[cut1 - 1];
			int left2 = cut2 == 0 ? INT_MIN : nums2[cut2 - 1];

			int right1 = cut1 == n1 ? INT_MAX : nums1[cut1];
			int right2 = cut2 == n2 ? INT_MAX : nums2[cut2];

			// valid condition
			if (left1 <= right2 && left2 <= right1) {
				if ((n1 + n2) % 2 == 0) {
					return ((max(left1, left2) + min(right1, right2)) / 2.0);
				}
				else {
					// for odd length, we adjust our answer so that it is from the left part.
					return max(left1, left2);
				}

			}
			// left needs to shrink. Because left contain larger element.
			else if (left1 > right2) {
				high = cut1 - 1;
			}
			// right contains larger element so right needs to be shrink. Left increase.
			// left2 > right1 (that means right1 needs to increase (left2 needs to decrease).
			else {
				low = cut1 + 1;
			}

		}

		return 0.0;
	}
};