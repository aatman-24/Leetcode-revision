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

Question: 88. Merge Sorted Array
Topic : Sorting
Problems : https://leetcode.com/problems/merge-sorted-array/

==============================> Explanation <=============================================

- Logic is that start filling the nums1 array from the back so we can use the given free space at the
end of the nums1 array.

- Compare both array element whichever is greater is filled into the array(nums1) from the back.

- If you try to fill the array(nums1) from the start then too many swaps required to arrange the space and
order of the elements.

Both apporach are same.

==============================> Approach and Time Complexity <============================

N = nums.size(), M = nums.size()

1) Sorted Array
Time: O(M + N)
Space: O(1)


*/


class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {

        int i = m - 1, j = n - 1, k = m + n - 1;

        while (k >= 0) {

            if (i >= 0 & j >= 0) {
                if (nums1[i] >= nums2[j]) {
                    nums1[k--] = nums1[i--];
                } else {
                    nums1[k--] = nums2[j--];
                }
            } else if (j >= 0) {
                nums1[k--] = nums2[j--];
            } else {
                nums1[k--] = nums1[i--];
            }
        }
    }
};



class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {

        int i = m - 1, j = n - 1, k = m + n - 1;

        while (i >= 0 && j >= 0) {

            if (nums1[i] <= nums2[j]) {
                nums1[k--] = nums2[j--];
            }
            else {
                nums1[k--] = nums1[i--];
            }
        }


        // Remaining elements of nums1 array.
        while (i >= 0) {
            nums1[k--] = nums1[i--];
        }


        // Remaining elements of nums2 array.
        while (j >= 0) {
            nums1[k--] = nums2[j--];
        }

    }
};




