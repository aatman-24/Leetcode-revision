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

Question :  27. Remove Element
Topic : Two Pointer
Problems : https://leetcode.com/problems/remove-element/description/

==============================> Explanation <=============================================

Two Pointer:  The intuition behind this solution is to iterate through the array and keep track of two pointers: index and j.
The index pointer represents the position where the next non-target element should be placed,
while the i pointer iterates through the array elements. By overwriting the target elements with non-target elements,
the solution effectively removes all occurrences of the target value from the array

==============================> Approach and Time Complexity <============================

N = nums.size()

1) Two Pointer
Time: O(N)
Space: O(1)

*/


class Solution {
public:
    int removeElement(vector<int>& nums, int val) {

        int index = 0, j = 0, N = nums.size();

        while (j < N) {

            // check if current nums[j] is non-target, if yes then place it at index position.
            if (nums[j] != val) {
                nums[index++] = nums[j];
            }

            j++;
        }

        return index;
    }
};