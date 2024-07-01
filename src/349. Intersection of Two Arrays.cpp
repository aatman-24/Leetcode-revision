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

Question : 349. Intersection of Two Arrays
Topic : Hashing
Problems : https://leetcode.com/problems/intersection-of-two-arrays/description/

==============================> Explanation <=============================================

1) Brute Force: Iterate over one array element by element, and check that element present in nums2 by iterating over elements.

2) Binary Search Lookup:
- Same as previous apporach, but instead of linear search we can sort the 2nd array and perform binary search to reduce time complexity.

3) Use Set to avoid duplicate and for hashing purpose.


==============================> Approach and Time Complexity <============================

N = nums1.size(), M = nums2.size()

1) Brute Force:
Time: O(N*M)
Space: O(1)

2) Binary Search:
Time: O(N*logM) + O(M*LogM)
Space: O(M)

3) Set:
Time: O(M), st.count() -> O(1), st.erase() -> O(1).
Space: O(N)

*/


class Solution {
public:


    int binary_search(vector<int> &nums, int target) {

        int low = 0, high = nums.size() - 1;

        while (low <= high) {

            int mid = (low + high) / 2;

            if (nums[mid] < target) {
                low++;
            }
            else if (nums[mid] == target) {
                return mid;
            }
            else {
                high--;
            }
        }

        return -1;
    }

    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {

        // Sort the second array.
        sort(nums2.begin(), nums2.end());

        unordered_set<int> intersect;

        for (int num : nums1) {

            if (binary_search(nums2, num) != -1) {
                intersect.insert(num);
            }
        }

        vector<int> ans;
        for (int num : intersect) {
            ans.push_back(num);
        }
        return ans;

    }
};






class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> st(nums1.begin(), nums1.end());
        vector<int> intersect;
        for (int num : nums2) {
            if (st.count(num)) {
                intersect.push_back(num);
                st.erase(num);
            }
        }
        return intersect;
    }
};
