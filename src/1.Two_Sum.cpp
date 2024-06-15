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

Question : 1. Two Sum
Topic : Two Pointer, Hashing
Problems : https://leetcode.com/problems/two-sum/

==============================> Explanation <=============================================


1) Brute Force: For each i index, try to find jth index using two for loops such that a[i] + a[j] = target

2) Sorting + Linear Time: Instead of checking for each pair, we can minimize that range using sorting.

- Sort Array
- left_corner -> i(min num of array), right_corner->j(max num of array)
- arr[i] + arr[j] => sum, sum < target => i++ (increase min num of range), sum > target => j-- (decrease max num of range), sum == target => (i, j) (also check any duplicate logic if required)

Also Here,
Need to return the index{i, j}. So I need to store index before sorting the array. So used extra spcae of
O(N) to store the index, next sort array(num, index_of_num) and use two pointer approach.

3) Hashing: Stored visited element in map, and check the target-cur element is already visited or not.

==============================> Approach and Time Complexity <============================

N = nums.size()

1) Brute Force
Time: O(N^2)
Space: O(1)

2) 2. Sorting + Two pointer:
Time: O(N) + O(N*logN) + O(N) = O(N*logN)
Space: O(N)

3) Hashing: Store visited element in map, and check the target-cur element is already visited or not.
Time: O(N) [mp.find() return the answer in O(1)]
Space: O(N)

*/

// 1. Brute Force
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        for (int i = 0; i < nums.length(); i++) {
            for (int j = i + 1; j < nums.length(); j++) {
                if (nums[i] + nums[j] == target) {
                    return {i, j};
                }
            }
        }
    }
};

// 2. Sorting + Two pointer:
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {

        // Create the vector which use the {nums[i], index}. Used nums[i] at first position so no need to write sort function.
        vector<pair<int, int>> numWithIndexs;
        for (int i = 0; i < nums.size(); i++) {
            numWithIndexs.push_back({nums[i], i});
        }

        // Sort() method takes an array and sort it based on first element(in case of pair)
        sort(numWithIndexs.begin(), numWithIndexs.end());

        int i = 0, j = numWithIndexs.size() - 1;

        while (i < j) {
            int curSum = numWithIndexs[i].first + numWithIndexs[j].first == target;
            if (curSum == target) {
                return {numWithIndexs[i].second, numWithIndexs[j].second};
            }
            else if (curSum < target) {
                i++;
            }
            else {
                j--;
            }
        }

        return { -1, -1};
    }
};


// 3: Hashing
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> mp;
        for (int i = 0; i < nums.size(); i++) {
            if (mp.count(target - nums[i]) != 0) {
                return {i, mp[target - nums[i]]};
            }
            mp[nums[i]] =  i;
        }
        return { -1, -1};
    }
};





