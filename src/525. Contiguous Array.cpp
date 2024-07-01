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

Question : 525. Contiguous Array
Topic : PrefixSum
Problems : https://leetcode.com/problems/contiguous-array/description/

==============================> Explanation <=============================================

1) Brute Force:
- We can get all subarray with two for loops and then check it have same nubmer of 1 and 0. Take: O(N^2), O(1)

2) Prefix + Hashing:
- Idea is that, we need to keep track of curSum.

We subtract -1, when it is 0, Add 1, when it is 1. 

AnyTime curSum got repeated, it means that we added something and subtracted same thing, that's why we again at same place. It is possible because we only have two state.

NOTE: If it is more than three state, then it won't possible to use this apporach.

Reason: 1 2 -3 => First two element addition, and single element subtraction againt make curSum = 0. Tha's why It won't possible to use this apporahc.

But here with two state(0, 1)

Whatever we add, we have to subtract same number of opposite element to again come to same state. We can use this apporach to get solution.

Edge case:

mp[0] = -1, because curSum = 0, that time we are at -1 position.

Check the code!!


==============================> Approach and Time Complexity <============================

N = s.size()

1) Brute Force
Time: O(N^2)
Space: O(1)

2) prefixSum
Time: O(N)
Space: O(N)

*/



class Solution {
public:
    int findMaxLength(vector<int>& nums) {

        int curSum = 0, max_length = INT_MIN;
        unordered_map<int, int> mp;
        mp[0] = -1; // Initial position of count=0, is at -1.

        for (int i = 0; i < nums.size(); i++) {

            // Encounter 0 add -1, 1 add 1.
            if (nums[i] == 0) {
                curSum--;
            }
            else {
                curSum++;
            }

            // If we already have "curSum" in map, then we found the subarray with index, when previous curSum got added. (index, i) have equal 1 and 0.
            if (mp.count(curSum)) {
                max_length = max(max_length, i - mp[curSum]);
            } else {
                // Else, add first position of curSum.
                mp[curSum] = i;
            }
        }

        return max_length == INT_MIN ? 0 : max_length;;
    }
};
