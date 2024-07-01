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

Question :  167. Two Sum II - Input Array Is Sorted
Topic : Two Pointer
Problems : https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/description/

==============================> Explanation <=============================================

Given this statement at the end of the problems:
- The tests are generated such that there is exactly one solution. You may not use the same element twice.
- Your solution must use only constant extra space.

Two Pointer: It is same as Two Sum Problem. In Two Sum array is not sorted here it is sorted so we can skip that step. Other all things remain
same to find the two most promising candidate out of given range (begin, end).

Hashing : We can't use it because we only allow to use constant space O(1).

==============================> Approach and Time Complexity <============================

N = nums.size()

1) Two Pointer
Time: O(N)
Space: O(1)

*/


class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {

        int N = numbers.size();
        int begin = 0, end = N - 1;

        while (begin < end) {

            int curSum = numbers[begin] + numbers[end];

            if (curSum == target) {
                return {begin + 1, end + 1}; // given in problem to offset with 1 to position.
            }
            else if (curSum < target) {
                begin++;
            }
            else {
                end--;
            }

        }

        return { -1, -1};
    }
};