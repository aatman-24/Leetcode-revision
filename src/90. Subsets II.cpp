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

Question :  90. Subsets II
Topic : Backtracking
Problems : https://leetcode.com/problems/subsets-ii/

==============================> Explanation <=============================================

Parent Problem: 78 subsets

Simliar to parent problem, but here we won't allow duplicate subset, which we need to handle.

Idea is that, "we won't start newNode with same value at same level"

For example,

See the code to check how to manage non-duplicate set.

1 1 2 3

So when we backtrack for first 1.. that time we skip next 1..so we have set {1(first_one), 2, 3} and try to create all subsets.

So when we visit 1(second_one) that time also we have simliar set{1, 2, 3} which create duplicate set.... So to avoid that we skip 1(second_one) as new node(same level at 1_one in recursion tree).

Draw the recursion tree and you will get idea.

==============================> Approach and Time Complexity <============================

1) Recursion
Time: O(2^N)
Space: O(N) (stack space)

Formula => processing_time_for_each_node * (breadth^depth) => O(1) * O(2^N)
Space => O(N) (maximum_depth)(stack space)

Each time we are adding nums[i] or not adding(jump to next element, during backtracking)...

For time complexity draw the recursiont ree

 */


// 90. Subsets II: Generate all the subsets without any duplicate subset. (Backtracking)
class Solution {
public:

    vector<vector<int>> allSubsets;

    void helper(vector<int> &nums, int startFrom, vector<int> curSubset) {

        // Add the curSubset
        allSubsets.push_back(curSubset);

        for (int i = startFrom; i < nums.size(); i++) {

            // To handle the case for duplicate. (We don't create new node with that..because all subset is already visited, when we explore nums[i-1] skipping nums[i])
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