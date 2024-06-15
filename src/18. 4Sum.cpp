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

Question : 18. 4Sum
Topic : Array, HashMap, Two Pointer, Sorting
Problems : https://leetcode.com/problems/4sum/

==============================> Explanation <=============================================


1) Brute Force: Mainly, we are checking arr[i] + arr[j] + arr[k] + arr[l] = target.

Simliar to Two Sum & Three Sum, We are going to use sorting + two pointer approach. To avoid duplicate, we can't start with same number for first element(same
as three sum). Also, we can't have same second element(which we started in that ith loop).

[-1 1 1 2 3], T = 5

[-1(i) 1(j) 1 2(k) 3(l)] -> {-1, 1, 2, 3}

[-1(i) 1 1(j) 2(k) 3(l)] -> We can't take this because for same ith loop, we have same jth element which duplicate(simliar to three sum first element).

So we have two diff elements logic, now we have to change one more for different quadruplet. Simliar to 3Sum, once we found quadruplet we can skip third/fourth
elements(see code).


2) Hashing approach
- A) In this case, storing the string is easy to use solution. create unique string(by first sorting it) and find out next time it is in map or not.
- B) As we do for Two Sum, We store the last index of each element so we can avoid duplicates. Here as well, To avoid duplicate in our quad need to change
atleast three elements using that map.


==============================> Approach and Time Complexity <============================

N = nums.size()

1) Brute Force
Time: O(N^3)
Space: O(1)

3) Hashing: O(N*3)
Space: O(N)

*/


class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {

        int n = nums.size();
        vector<vector<int>> ans;

        if (n <= 3) return ans;

        sort(nums.begin(), nums.end());

        for (int i = 0; i < n - 3; i++) {

            if (i > 0 && nums[i - 1] == nums[i])
                continue;

            for (int j = i + 1; j < n - 2; j++) {

                if (j > i + 1 && nums[j - 1] == nums[j])
                    continue;

                long long total = nums[i] + nums[j];


                int begin = j + 1, end = n - 1;

                while (begin < end) {

                    long long curSum = total + nums[begin] + nums[end];

                    if (curSum == target) {

                        vector<int> quadruplets = {nums[i], nums[j], nums[begin], nums[end]};
                        ans.push_back(quadruplets);

                        while (begin < end && nums[begin] == quadruplets[2]) begin++;

                    }
                    else if (curSum < target) {
                        begin++;
                    }
                    else {
                        end--;
                    }
                }

            }


        }

        return ans;

    }
};





class Solution {
public:

    // O(N^3) - O(N)
    vector<vector<int>> fourSum(vector<int>& nums, int target) {

        vector<vector<int>> ans;

        if (nums.size() < 4) {
            return ans;
        }
        map<string, string> mp;

        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size() - 3; i++) {
            for (int j = i + 1; j < nums.size() - 2; j++) {
                int total = nums[i] + nums[j];
                int lh = j + 1, rh = nums.size() - 1;
                while (lh < rh) {
                    int curr = total + nums[lh] + nums[rh];
                    if (curr == target) {
                        string tmp = to_string(nums[i]) + '_' + to_string(nums[j]) + '_' + to_string(nums[lh]) + '_' + to_string(nums[rh]);
                        if (mp.find(tmp) == mp.end()) {
                            ans.push_back({nums[i], nums[j], nums[lh], nums[rh]});
                            mp[tmp] = tmp;
                        }
                        // don't forget to reduce subarray length.
                        lh++; rh--;
                    }
                    else if (curr < target) {
                        lh++;
                    }
                    else {
                        rh--;
                    }
                }
            }
        }
        return ans;
    }
}


class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {

        int n = nums.size();
        vector<vector<int>> ans;

        if (n <= 3) return ans;

        sort(nums.begin(), nums.end());

        // Store the index of number.
        unordered_map<long long, int> mp;
        for (int i = 0; i < n; i++)
            mp[nums[i]] = i;


        for (int i = 0; i < n - 3; i++) {

            for (int j = i + 1; j < n - 2; j++) {

                long long total = nums[i] + nums[j];

                for (int k = j + 1; k < n - 1 ; k++) {

                    long long required = target * 1L - (total + nums[k]);

                    if (mp.count(required) && k < mp[required]) {

                        vector<int> quadruplets = {nums[i], nums[j], nums[k], (int)required};
                        ans.push_back(quadruplets);

                    }

                    // skip all nums[k]
                    k = mp[nums[k]];
                }

                // skip all nums[j]
                j = mp[nums[j]];
            }

            // skip all nums[i]
            i = mp[nums[i]];
        }

        return ans;

    }
};