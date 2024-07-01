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

Question :  26. Remove Duplicates from Sorted Array
Difficulty: Easy
Topic : Two Pointer
Problems : https://leetcode.com/problems/remove-duplicates-from-sorted-array/description/

==============================> Explanation <=============================================

Two Pointer: As It is written that I need to remove duplicate in-place in question I got idea that I need to use two pointer approach.

First I thought I can move all the duplicate at the end of the array by swapping with current element, but it doesn't work because those last
element who got replaced, hard to diffcult those.

After I thought instead of moving duplicate at the last, can I move next distinct element on left side sequence... I tried on paper and it got work.

1 2 3 4 4 5

I can move next j = 5 after 3 I mean......

Simply, I am using two pointer first (i)... left side of ith have all distinct elements... and j is lookup pointer which task is to find next
distinct element check on code directly..

when I found next distinct element, I move that element to (i+1)th position..


Hashing(Two Sum): I can use other map to add all distinct element and then remove all of them in line and add it into the array from start. But
it is clearly given that I need to use do in-place so I can't use it.


==============================> Approach and Time Complexity <============================

N = nums.size()

1) Two Pointer
Time: O(N)
Space: O(1)

3) Hashing :
Time: O(N)
Space: O(N)

*/


class Solution {
public:
    int removeDuplicates(vector<int>& nums) {

        int i = 0, j = i + 1, N = nums.size();

        while (j < N) {

            // found next diff element move it to (i+1) position.
            if (nums[i] != nums[j]) {
                nums[++i] = nums[j];
            }

            j++;

        }

        return i + 1;
    }
};

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {

        map<int, int> mp;
        for (int i = 0; i < nums.size(); i++) {
            mp[nums[i]] = i;
        }


        int i = 0;
        for (auto it : mp) {
            // load the array with sorted number(without duplicates ones)
            nums[i++] = it.first;
        }

        return i;
    }
};