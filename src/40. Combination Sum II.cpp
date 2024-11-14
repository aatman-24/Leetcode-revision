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

Question : 40. Combination Sum II
Topic : Backtracking
Problems : https://leetcode.com/problems/combination-sum-ii/description/

==============================> Explanation <=============================================

Parent Problem: 39. Combination Sum

Additional logic is that, we can't choose same number multiple time. => after choosing ith index, jump to (i+1)th index.

Don't allow to have duplicate combiantion(set),
    We don't create fresh node at same level of duplicated value.

==============================> Approach and Time Complexity <============================

1) Backtracking
Time: O(2^N)
Space: O(N) (stack space) + O(2^N)(To store result)

Formula => processing_time_for_each_node * (breadth^depth) => O(1) * O(2^N)
Space => O(N) (maximum_depth)(stack space)

Again same, either we are adding element or not adding. Two choice... 2 recursive call.
Max depth possible is = 20 < N.....
Given that, 2 <= nums[i] <= 40 and target <= 40... so depth => 40 - 2(20(times)) = 20(in worst case)

 */



class Solution {
public:

    // store the answer.
    vector<vector<int>> ans;

    void helper(vector<int> &nums, int startIndex, int curSum, int target, vector<int> curSet) {

        // base condition
        if (curSum == target) {
            ans.push_back(curSet);
            return;
        }

        // base condition
        if (curSum > target)
            return;

        // iterative over the all elements from (startIndex, N)
        for (int i = startIndex; i < nums.size(); i++) {

            // How to avoid duplicate set when nums have duplicate number.
            // We don't start with fresh node at level-1 if duplicated.
            // What I mean ?
            // arr = [1, 2, 2, 4, 5]....first_2 visit we alread made set with [first_2, 2(skip), 4, 5]
            // then we skip for [2_second, 4, 5]... at same level first_2 in recursion tree.
            if (abs(i - startIndex) > 0 && nums[i] == nums[i - 1]) continue;

            curSum += nums[i];
            curSet.push_back(nums[i]);

            // check here.. we can choose the same element again nums[i] (NOTE: we can't chose previous nums[i-1], nums[i-2] elements, otherwise we get duplicate set issue (1, 2, 3) => (3, 2, 1))
            helper(nums, i + 1, curSum, target, curSet);

            // backtrack.
            curSum -= nums[i];
            curSet.pop_back();
        }
    }

    vector<vector<int>> combinationSum2(vector<int>& nums, int target) {
        vector<int> curSet;
        sort(nums.begin(), nums.end());
        helper(nums, 0, 0, target, curSet);
        return ans;
    }
};




