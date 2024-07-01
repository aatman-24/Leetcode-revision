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

Question : 219. Contains Duplicate II
Topic : Sliding Window
Problems : https://leetcode.com/problems/contains-duplicate-ii/description/
==============================> Explanation <=============================================

Sliding Window Technique:
- Given that, abs(i-j) <= k, it means we have to manage the window of size k, and check in that any element is duplicate.
- We can use the map/set to mark element as visited and unvisited.
Check the code!!

==============================> Approach and Time Complexity <============================

N = s.size()

1) Sliding Window
Time: O(N)
Space: O(N)

*/



class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {

        int N = nums.size();
        int begin = 0;
        unordered_map<int, int> mp;

        for (int i = 0; i < N; i++) {

            // manage the window.
            while ((i - begin) > k) {
                mp[nums[begin++]]--;
            }

            // check duplicate
            if (mp.count(nums[i]) && mp[nums[i]] > 0)
                return true;

            // add nums[i] in window.
            mp[nums[i]]++;

        }

        return false;
    }
};