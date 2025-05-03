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

Question: 215. Kth Largest Element in an Array
Topic : PQ, sorting, Partition method
Problems : https://leetcode.com/problems/kth-largest-element-in-an-array/

==============================> Explanation <=============================================
1) Add Element into the pq. Deal with K element only.

2) Inplace sorting deal with N elements.

3) Parition method same used in Quiksort.

==============================> Apporach and Time Complexity <=============================================
N = length of array.
M = maximum string length. M = 100.

1) Inplace Sorting:
Time: O(N*logN)    -> Sort with respect to all the elements.
Space: O(1)

2) Heap:
Time: O(N*logK)   -> Sort on only on K most promising elements.
Space: O(K)

3) Parition Method:
Time: Avg,Best:O(N), Worst:O(N^2)
Space: O(1)

*/


class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {

        priority_queue<int, vector<int>, greater<int>> pq;
        for (int num : nums) {
            pq.push(num);
            if (pq.size() > k) {
                pq.pop();
            }
        }

        return pq.top();
    }
};


// rathar than finding Kth largest element. Finding (N-K) smallest element.
class Solution {
public:

    int findKthLargest(vector<int>& nums, int k) {

        int start = 0, end = nums.size() - 1, index = nums.size() - k;

        while (start <= end) {
            int pivot = partition(nums, start, end);
            if (pivot == index)
                return nums[pivot];
            else if (pivot < index) {
                start = pivot + 1;
            }
            else {
                end = pivot - 1;
            }
        }

        return nums[start];
    }


    // smallest equal pivot lagest
    int partition(vector<int> &nums, int start, int end) {
        int pivot = start;
        while (start <= end) {
            while (start <= end && nums[start] <= nums[pivot]) start++;
            while (start <= end && nums[end] > nums[pivot]) end--;
            if (start > end)
                break;
            swap(nums[start], nums[end]);
        }

        // the nums[end] hold the number which is the last smallest or equal number then
        // nums[pivot].
        swap(nums[end], nums[pivot]);
        return end;
    }
};


class Solution {
public:

    int findKthLargest(vector<int>& nums, int index) {

        int start = 0, end = nums.size() - 1;

        while (start <= end) {
            int pivot = partition(nums, start, end);
            if (pivot == index - 1)
                return nums[pivot];
            else if (pivot < index - 1) {
                start = pivot + 1;
            }
            else {
                end = pivot - 1;
            }
        }

        return nums[start];
    }

    // greatest equal pivot smallest
    int partition(vector<int> &nums, int start, int end) {
        int pivot = start;
        while (start <= end) {
            while (start <= end && nums[start] >= nums[pivot]) start++;
            while (start <= end && nums[end] < nums[pivot]) end--;
            if (start > end)
                break;
            swap(nums[start], nums[end]);
        }

        // the nums[end] hold the number which is the last greatest number then
        // nums[pivot].
        swap(nums[end], nums[pivot]);
        return end;
    }
};