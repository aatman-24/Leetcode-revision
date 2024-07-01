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

Question :  2006. Count Number of Pairs With Absolute Difference K
Topic : Hashing
Problems : https://leetcode.com/problems/count-number-of-pairs-with-absolute-difference-k/description/

==============================> Explanation <=============================================

Brute force: Using two for loops iterate over the array find pais which meet the given condition.

Hashing:  The intuition behind this solution is that,

|a - b| = k, a => b + k, a => b - k....

We have to find these two numbers (b + k) and (b - k).. and best way to do is to putting all number in HashMap so we can check that condition in O(1).

Also it given array have duplicate elements... so we are storing its frequency as well....

for example...

1 1 2 2 2

for first 1 => Total Three 2.... which can be solution.
for second 1 => Total Three 2.... which can be solution...

And last things is that, when the pointer comes to the first 2.... it also add the same pair again... (2, 1) and (2, 1).... which are already counted
so we have to remove that... means count/2... because each pair counted two times in our solutin..

NOTE: If we don't fill the map in advance, during iteration we keep track of frquency, we don't need to perform count/2. For example... when we lookup for "1" we don't see anything on map with "2". But when we do lookup for "2" that time we see "1". so we
consider that only. 

==============================> Approach and Time Complexity <============================

N = nums.size()


1) Brute Force
Time: O(N^2)
Space: O(1)

1) Hashing
Time: O(N)
Space: O(N)

*/


class Solution {
public:
    int countKDifference(vector<int>& nums, int k) {
        int count = 0;
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (abs(nums[i] - nums[j]) == k) {
                    count++;
                }
            }
        }
        return count;
    }
};


class Solution {
public:
    int countKDifference(vector<int>& nums, int k) {

        int count = 0, N = nums.size();

        unordered_map<int, int> countMap;

        for (int i = 0; i < N; i++) {
            countMap[nums[i]]++;
        }


        for (int i = 0; i < nums.size(); i++) {


            int firstNum = nums[i];

            // potential number we need to check in hashmap.
            int secondNum1 = firstNum + k;
            int secondNum2 = firstNum - k;

            if (countMap.count(secondNum1)) {
                count += countMap[secondNum1];
            }


            if (countMap.count(secondNum2)) {
                count += countMap[secondNum2];

            }

        }

        // Each pair counted two times so we have to divide it by 2.
        return count / 2;
    }
};


// Without count/2. 
class Solution {
public:
    int countKDifference(vector<int>& nums, int k) {
        
        int count = 0, N = nums.size();
        
        unordered_map<int,int> countMap;
    
        for(int i = 0; i < nums.size(); i++) { 


            int firstNum = nums[i];
            int secondNum1 = firstNum + k;
            int secondNum2 = firstNum - k;

            if(countMap.count(secondNum1)) {
                count += countMap[secondNum1];
            }


            if(countMap.count(secondNum2)) {
                count += countMap[secondNum2];

            }

            countMap[nums[i]]++;
        }


        return count;
    }
};
