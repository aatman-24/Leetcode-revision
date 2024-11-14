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

Question : 78. Subsets
Topic : Backtracking
Problems : https://leetcode.com/problems/subsets/description/
==============================> Explanation <=============================================

Parent: 6000 Subsets Sums

Approach: Recursion-Backtracking
It's simliar to parent problem, there we are tracking subsetSum here we need to track subset itself(using array),
core logic remain same.


Apporach: Iterative
    In which we start with {} set. And each ttime we see new element we add it in all previous set by coping them...

==============================> Approach and Time Complexity <============================

1) Backtracking
Time: O(2^N)
Space: O(N) (stack space)

Formula => processing_time_for_each_node * (breadth^depth) => O(1) * O(2^N)
Space => O(N) (maximum_depth)(stack space)

Time complexity is derived from the recursion trace.. at each point we are adding the element and removing it.

 */



// 78: Generate all the subsets (Recursive)
class Solution {
public:

    // store all the subsets.
    vector<vector<int>> allSubsets;

    void subsetsHelper(vector<int>& nums, int index, vector<int> curSubset) {

        // Base condition
        if (index == nums.size()) {
            allSubsets.push_back(curSubset);
            return;
        }

        // Don't take it
        subsetsHelper(nums, index + 1, curSubset);

        // Take it
        curSubset.push_back(nums[index]);
        subsetsHelper(nums, index + 1, curSubset);
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> curSubset;
        subsetsHelper(nums, 0, curSubset);
        return allSubsets;
    }
};



// 78: 2nd Approach: Generate all the subsets (Backtracking) (Right approach)
class Solution {
public:

    // store all the subsets.
    vector<vector<int>> allSubsets;

    void subsetsHelper(vector<int>& nums, int startFrom, vector<int> curSubset) {

        // Add curSubset as one of the set.
        allSubsets.push_back(curSubset);

        for (int i = startFrom; i < nums.size(); i++) {
            curSubset.push_back(nums[i]);           // add curr element
            subsetsHelper(nums, i + 1, curSubset);  // Create all subset with curr element nums[index] in the set.
            curSubset.pop_back();                   // remove nums[i] (backtrack).. and form all subsets without it.
        }
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> curr;
        subsetsHelper(nums, 0, curr);
        return allSubsets;
    }
};
