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

Question :  16. 3Sum Closest
Topic : Sorting, Two Pointer
Problems : https://leetcode.com/problems/3sum-closest/

==============================> Explanation <=============================================

Simliar to 3Sum.

1) Brute Force: Used three pointer and keep track of minDiff to check which triplet have closestSum to Target.

Fundamental of Sorting + Two pointer approach:
=> We are finding the best candidate a & b from range [i, j] whose sum is nearest to target. Two pointer gives us
those nearest(most optimal) candidates for given Target T. By reducing the time complexity of O(N^2) => O(NlogN) + O(N).

2) Sorting + Two Pointer:

How it is releated to this 3Sum approach ?

- Here given that we have to find triplet whose sum is closest to the target. Which is kind of Fundamental to sorting + Two pointer approach.. right ?
Next thing I consider is,

-4 -3 -1 2 3 5

First three elements sum = -9 (-4 -3 -1)
Middle three element Sum = -4 (-1 2 3)
Target is = 5

- So we have better chance of min_diff with second triplets right ? compare to first one. So it gets idea of using two pointer after sorting and
select the triplet based upon (curSum < target) or (curSum > target).

- And we also get clear idea by thinking that.

    curSum(too much left) < curSum(close to target)(1) < target < curSum(close to target)(2) < curSum(too much right)

As you can see answer must be one of these(1 or 2) which is close to curSum(triplet). We are just using two pointers to come close to target and checking
both 1 & 2.

So each iteration, we find triplet whose first element is fix nums[i], then we find best candidates a & b from [j, k] range and check whether its give
cloests sum or not.


==============================> Approach and Time Complexity <============================

N = nums.size()

1) Brute Force
Time: O(N^3)
Space: O(1)

3) Sorting + Two Pointer: O(NlogN) + O(N^2)
Space: O(1)

*/


class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {

        int CUR_MIN = INT_MAX;
        int closestSum = INT_MAX;
        int n = nums.size();

        for (int i = 0; i < n - 2; i++) {
            for (int j = i + 1; j < n - 1; j++) {
                for (int k = j + 1; k < n; k++) {
                    int curSum = nums[i] + nums[j] + nums[k];
                    if (abs(target - curSum) < CUR_MIN) {
                        CUR_MIN = abs(target - curSum);
                        closestSum = curSum;
                    }
                }
            }
        }

        return closestSum;
    }
};


class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {

        int CUR_MIN = INT_MAX;
        int closestSum = INT_MAX;
        int n = nums.size();

        // sort the nums array.
        sort(nums.begin(), nums.end());

        for (int i = 0; i < n - 2; i++) {

            int begin = i + 1, end = n - 1;

            while (begin < end) {

                int curSum = nums[i] + nums[begin] + nums[end];

                if (abs(target - curSum) < CUR_MIN) {
                    CUR_MIN = abs(target - curSum);
                    closestSum = curSum;
                }

                if (curSum < target) {
                    begin++;
                }
                else if (curSum == target) { // Same target so difference is zero. No need to check further.
                    return curSum;
                }
                else {
                    end--;
                }
            }

        }

        return closestSum;
    }
};