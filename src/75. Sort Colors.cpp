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

Question :  75. Sort Colors
Topic : Two Pointer
Problems : https://leetcode.com/problems/sort-colors/

==============================> Explanation <=============================================

1) Brute Force: Simply we can count each of 0, 1 and 2. And manipulate array to have those in sequence in order.

2) Two Pointer: Instead of pre-calculation we can use some pointer to do in-place sorting...

left -> 0, mid -> 1, right -> 2, pointer points to corrosponding value.

We know left & right location, but don't know about mid location which is unknown.

We can think of placing 0 and 2 at corner and tight the range each time. Check the code...

arr[mid] = 0 -> swap with left pointer, left++(tight range).. mid++(move to next element)
arr[mid] = 2 -> swap with right pointer, right--(tight range).. don't need to do mid++(because we are iterating element from left side, so next we again check same swapped element)
arr[mid] = 1 -> mid++ (move to next element)

any time current left points to location where we can put the next 0 element, same for 2...


==============================> Approach and Time Complexity <============================

N = nums.size()

1) Brute Force
Time: O(N)
Space: O(1)

2) Two Pointer
Time: O(N)
Space: O(1)

*/



class Solution {
public:
    void sortColors(vector<int>& nums) {

        int zeroCount = 0, oneCount = 0, twoCount = 0;
        for (int num : nums) {
            if (num == 0) zeroCount++;
            else if (num == 1) oneCount++;
            else twoCount++;
        }

        int index = -1;
        while (zeroCount > 0) {
            nums[++index] = 0;
            zeroCount--;
        }

        while (oneCount > 0) {
            nums[++index] = 1;
            oneCount--;
        }

        while (twoCount > 0) {
            nums[++index] = 2;
            twoCount--;
        }
    }
};


class Solution {
public:

    void swap(vector<int> &arr, int a, int b) {
        int temp = arr[a];
        arr[a] = arr[b];
        arr[b] = temp;
    }

    void sortColors(vector<int>& nums) {

        int left = 0, mid = 0, right = nums.size() - 1;
        while (mid <= right) {

            if (nums[mid] == 0) {
                swap(nums, left, mid);
                left++;  mid++;
            }
            else if (nums[mid] == 1) {
                mid++;
            }
            else {
                swap(nums, right, mid);
                right--;
            }
        }

    }
};