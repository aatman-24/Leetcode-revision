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

Question : NC_3_Kth Largest Element in an Array
Topic : PQ, Heap
Problems : https://neetcode.io/problems/kth-largest-element-in-an-array

==============================> Explanation <=============================================

1) First approach is to use priority queue.....if need to find largest element then use the
minHeap with fixed size of K.... and if it is smallest element then use the maxHeap with
fixed size of K.... and pop out element from queue when have more element than K... st.top()
is your answer. This takes: O(K) space for heap, O(NlogK) time....

2) Use parition method of Quick Sort.... In this we basically randomly try to find the point(location)
such that all elements on left are smallers and all elements on right are greater....

==============================> Approach and Time Complexity <============================

1) Two Pointer
Time: O(N)
Space: O(N)

*/


class Solution {
public:

    // return position(or point) from there all elements on left are smaller and on right are greater.
    int partition(vector<int> &nums, int left, int right) {
        int pivot = left;
        int low = left + 1;
        int high = right;
        while (low <= high) {
            while (low <= high && nums[low] <= nums[pivot]) low++;
            while (low <= high && nums[pivot] <= nums[high]) high--;
            if (!(low <= high)) break;
            swap(nums[low], nums[high]);
        }
        swap(nums[pivot], nums[high]);
        // (because once high < low.... high hold last smallest elements than pivot which we swipe)
        return high;
    }



    int findKthLargest(vector<int>& nums, int k) {

        int kThSmallest = nums.size() - k;

        int left = 0, right = nums.size() - 1;

        while (left <= right) {

            int pos = partition(nums, left, right);

            if (pos == kThSmallest)
                return nums[pos];

            // got position, smaller try to find bigger one but in reduced array.
            if (pos < kThSmallest) {
                left = pos + 1;
            }
            else {
                right = post - 1;
            }

        }

        return -1;
    }

};
