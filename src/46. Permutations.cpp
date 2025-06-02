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
================================================================================
                                Problem Description
================================================================================

Problem: 46. Permutations
Topic: Backtracking
Link: https://leetcode.com/problems/permutations/description/

================================================================================
                                Problem Summary
================================================================================

Given the array, you need to generate all the permutations of that.


================================================================================
                                Intuition & Explanation
================================================================================

Idea is that, we can start the permutation with any of the number, and after the
first number as well, we can get any number as second... it short we have to try
all possible number at each of the index, so we use the backtracking (simliar to)
subsets.

Check the code

================================================================================
                          Approach & Time/Space Complexity
================================================================================

Approach: Backtracking
Time Complexity: O(N^N) depth = N, breadth = N
Space Complexity: O(N)
*/




class Solution {
public:

    vector<vector<int>> permutations;

    void helper(vector<int> &nums, vector<int> curPermutation, vector<int> &visited) {

        // get entire array
        if (nums.size() == curPermutation.size()) {
            permutations.push_back(curPermutation);
            return;
        }

        // we try all numbers
        for (int i = 0; i < nums.size(); i++) {

            // if number is not part of curPermutation, then we can take it
            if (!visited[i]) {

                // take this number
                curPermutation.push_back(nums[i]);
                visited[i] = 1;

                helper(nums, curPermutation, visited);

                // remove this number
                curPermutation.pop_back();
                visited[i] = 0;
            }
        }

    }

    vector<vector<int>> permute(vector<int>& nums) {

        // keep track of curPermuation
        vector<int> curPermutation;
        vector<int> visited(nums.size(), 0);

        helper(nums, curPermutation, visited);

        return permutations;

    }
};
