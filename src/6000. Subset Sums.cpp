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

Question : 6000. Subset Sums
Topic : Recursion
Problems : https://www.geeksforgeeks.org/problems/subset-sums2234/1
==============================> Explanation <=============================================

Subset-Sum-I

This is recursion solution:.
At each index, we have two options 1) Take it 2) Not to take it, given index number to form subset.

Backtracking solution:
Check the code!!

Both in recursion and backtrack solution, recursion tree are different. In recursion.. we are adding/not-adding
new number in previous level output. And in backtracking... we are adding something and removing it to go to next
element...It is not working the level wise but it is more about trying all the arrangments.

==============================> Approach and Time Complexity <============================

1) Recursion
Time: O(2^N)
Space: O(N) (stack space)

Formula => processing_time_for_each_node * (breadth^depth) => O(1) * O(2^N)
Space => O(N) (maximum_depth)(stack space)

 */


// Recursion solution
class Solution {
public:

    // to hold the result.
    vector<int> ans;

    void subsetSums(vector<int> arr, int curSum, int index) {

        // Base conditions, reach at the end of the arr. So whatever element we selected(added in curSum) is one of the combination to form subset.
        if (index == arr.size()) {
            ans.push_back(curSum);
            return;
        }

        subsetSums(arr, curSum + arr[index], index + 1);    // take it
        subsetSums(arr, curSum, index + 1);                 // don't take it.
    }

    vector<int> subsetSums(vector<int> arr, int n) {
        subsetSums(arr, 0, 0);
        return ans;
    }
};


// Backtracking solution.
class Solution {
public:

    // to hold the result.
    vector<int> ans;

    void subsetSums(vector<int> arr, int curSum, int startFrom) {

        ans.push_back(curSum);

        for (int i = startFrom; i < arr.size(); i++) {
            curSum += arr[i];
            subsetSums(arr, curSum, i + 1);
            curSum -= arr[i];       // backtracking...
        }
    }

    vector<int> subsetSums(vector<int> arr, int n) {
        subsetSums(arr, 0, 0);
        return ans;
    }
};



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



// 78: 2nd Approach: Generate all the subsets (Backtracking)
class Solution {
public:

    // store all the subsets.
    vector<vector<int>> allSubsets;

    void subsetsHelper(vector<int>& nums, int startFrom, vector<int> curSubset) {

        // Add curSubset as one of the set.
        allSubsets.push_back(curSubset);

        for (int i = startFrom; i < nums.size(); i++) {
            curSubset.push_back(nums[i]);           // add curr element
            subsetsHelper(nums, i + 1, curSubset);  // Create all subset with curr element nums[index]
            curSubset.pop_back();                   // remove (backtrack).. and form all subsets without it.
        }
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> curr;
        subsetsHelper(nums, 0, curr);
        return allSubsets;
    }
};







// 90. Subsets II: Generate all the subsets without any duplicate subset. (Backtracking)
class Solution {
public:

    vector<vector<int>> allSubsets;

    void helper(vector<int> &nums, int startFrom, vector<int> curSubset) {

        // Add the curSubset
        allSubsets.push_back(curSubset);

        for (int i = startFrom; i < nums.size(); i++) {

            // To handle the case for duplicate. (We don't new node with that..because all subset is already visited, when we explore nums[i-1] skipping nums[i])
            if (abs(i - startFrom) > 0 && nums[i] == nums[i - 1]) continue;

            curSubset.push_back(nums[i]);

            helper(nums, i + 1, curSubset);

            curSubset.pop_back(); // backtrack

        }

    }

    vector<vector<int>> subsetsWithDup(vector<int>& nums) {

        // sorting is required, to handle the case for duplicate set.
        sort(nums.begin(), nums.end());

        vector<int> curSubset;

        helper(nums, 0, curSubset);

        return allSubsets;
    }
};