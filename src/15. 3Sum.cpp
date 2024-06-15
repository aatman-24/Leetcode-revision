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

Question : 15. 3Sum
Topic : Two pointer.
Problems : https://leetcode.com/problems/3sum/

==============================> Explanation <=============================================


1) Brute Force: Mainly, we are checking arr[i] + arr[j] + arr[k] = 0.

What about to duplicate logic, we can't have same triplet {-2, 0, 2} again ?

lOGIC: First we need to sort the array, so that we can use two pointer apporach by fixing the one element either from left side or right side(one by one).
(Here we used first element(minimum number)).

-4(first) [-1 -1 0 1 2]

So we fix the smallest number(ith index num) and try to find two more numbers in right side subarray such that smallest + arr[j] + arr[k] = target(0). (i < j < k)

We need to modify this standard apporach to avoid duplicate.

To avoid duplicate => It means can't pick up same two elements which is current triplet.

1) We can't start with same minimum(ith) number in triplet, why ?
A: If we found any triplet {minimum(ith_index), arr[j], arr[k]}, then we can't have any different triplet with same minimum number(duplicate). So we move to next
number

-4 -1 -1 0 1 2
triplet: arr[1](-1) arr[3](0) arr[4](1)
triplet: arr[2](-1) arr[3](0) arr[4](1) (duplicate)

2) We can't have the same second number/last number during search, why ?
- Avoiding duplicate triplet, we have to change atleast two numbers(we already changed first(madatory) number). So either we have to skip same nums[j] or nums[k],
when we found the triplet.


2) Hashing approach
- Similar to TWO SUM, we can store one of the number in map and during search opeartion we can check (target-nums[i]-nums[j]) is in map or not.

Duplicate logic: Again, We have to avoid duplicate logic.

Here, Instead of first(min), we search for max number(to optimize search, by avoiding first element lookup chain if it is less than 0)

We store the last index of number in map, so once we found any triplet we can skip the all same elements for jth and kth index. We also need to check i < j < k.


==============================> Approach and Time Complexity <============================

N = nums.size()

1) Brute Force
Time: O(NLogN) + O(N^2)
Space: O(1)

2) Hashing: .
Time: O(NLogN) + O(N^2)
Space: O(N)


*/


// 1. Brute Force

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {

        int n = nums.size();

        vector<vector<int>> ans;

        // return empty answer in case of elements are less than 3.
        if (n <= 2) return ans;

        // sort the array
        sort(nums.begin(), nums.end());

        for (int i = 0; i < n - 2; i++) {

            // Duplicate Logic: Can't start with same first number again.
            if (i > 0 && nums[i - 1] == nums[i])
                continue;

            int begin = i + 1, end = n - 1;

            while (begin < end) {

                int total = nums[i] + nums[begin] + nums[end];

                if (total == 0) {

                    vector<int> tripets = {nums[i], nums[begin], nums[end]};

                    ans.push_back(tripets);

                    // Can't have second/third number in triplet, once it found.
                    while (begin < end && nums[begin] == tripets[1]) begin++;

                    // This is for optimization, without skipping same nums[end] also we can avoid duplication.
                    while (begin < end && nums[end] == tripets[2]) end--;
                }
                else if (total < 0) {
                    begin++;
                }
                else {
                    end--;
                }

            }

        }

        return ans;
    }
};


class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {

        int n = nums.size();

        vector<vector<int>> ans;

        // return empty answer in case of elements are less than 3.
        if (n <= 2) return ans;

        // sort the array
        sort(nums.begin(), nums.end());

        // Target is 0, so after sorting if first element > 0, then sum != 0.
        if (nums[0] > 0) return ans;

        // Logic for duplicate: We create one map, which basically store last index of element. Ex: {1, 2, 1} = map{{1(element), 2(index)}}
        unordered_map<int, int> mp;
        for (int i = 0; i < nums.size(); i++)
            mp[nums[i]] = i;

        // N3 = T - N1 - N2, Where... N1 < N2 < N3
        // N3 = 0 - N1 - N2
        // N3 = - (N1 + N2)

        // Pick up the pair
        for (int i = 0; i < n - 2; i++) {

            // Avoid such number. It don't give the triplet for target 0.
            // N3 = - (N1 + N2) => If N1 < 0, N3 = - (N2 + -N1) => - (N2 - N1) => N3 < N2... violate our condition (N1 < N2 < N3)
            if (nums[i] > 0)
                continue;

            for (int j = i + 1; j < n - 1; j++) {

                int required = 0 - nums[i] - nums[j];

                // Check If required is in the map and Index should be i < j < required.
                // To avoid the duplication we always add the last required element's .
                if (mp.count(required) && j < mp[required]) {

                    ans.push_back(nums[i], nums[j], required);

                    // Skipping same number, nums[j].
                    j = mp[nums[j]];
                }

                // Skipping same number, nums[i].
                i = mp[nums[i]];

            }


        }
        return ans;
    }
};



