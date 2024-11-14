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

Question : 300. Longest Increasing Subsequence
Topic : DP
Problems : https://leetcode.com/problems/longest-increasing-subsequence/description/
==============================> Explanation <=============================================

Pattern: LIS


To find LIS in given array,

Brute Force: Generate all the subsequence of given array(find all subsets) & check which one follow LIS property and longest.

Remember this point, whenever we have to generate all possible ways, we have two choice for each element... (take it | don't take it).

And when some condition is given and need to generate all possible ways such that, that condition got satisified then,

    if(condition==true)
        two_chocies:    take it | don't take it
    else:
        don't take it.

We are planning to do same thing, here... LIS property is that nums[prev_index] < nums[i]... (then we can add nums[i] in current LIS) else not.

Check the recursive code!!

Let's jump to Top-down Approach,

    Two para which are changing.... (i, prev_index)

    prev_index = -1... so we need to shift it by +1.. so we can create memo table...

    prev_index + offset... indexing will be this way...

Bottom-up:

    On bottom up, to manage the prev_index==-1, we are shifting the entire jth column to (j+1)th column for dp table. Due to that,
    whenever we using jth index in dp table(dp[i][j]) that time we need to offset it by +1. (dp[i][j] -> dp[i][j+offset]).

    And one more point is that... we have pairs in this format (i, prev_index(<i))... so second for loop start at (i-1).

    Check the code!!

Bottom-up with space optimization:

    We can reduce one dimesion by using prev and curr, 1D dp table.

Bottom-up without using DP:

    We can get LIS_Length using 2 for loops in O(N^2) time, which is equivalent to DP-Bottom-up.

    Idea is that,

        each lis[i] = 1... (each ith element have LIS of length 1)

        One loop goes from (i = 0 -> 1)

            inside loop (we check from 0 -> j)

                nums[j] < nums[i]... it means (seq which was added at nums[j] can be extend by nums[i]) so that way...we choose longest seq for dp[i]....

        Check the code!!

Printing LIS:

    To print LIS,#Bottom-up without using DP this approach is very easy... we just need to keep track of prev element using other array. (check the code)

Binary Search LIS:

    Idea comes from the, #Bottom-up without using DP...

    Where we use the two for loops, to get LIS length...

    We can replace inner one using binary_search.

    For that, understand the concept, form here: https://takeuforward.org/data-structure/longest-increasing-subsequence-binary-search-dp-43/

    - We keep track of increasing order array. Where we either update oen of element if (cur_num < last_element) or add cur_num as back of array.

    - Idea is that, We try to get the LIS at each element as tail of it.

        First of all => LIS = 1, Each element can be consider as LIS of itself.

        Then we check,

            nums[i] <= last_element_of_increasing_order,

                It means nums[i]... can replace some greater number from the increasing order (It is not increasing the length)

                This time, we LIS remain same because we are justing replacing (just greater than "nums[i]" with nums[i](most optimal choice)) (3, 4), nums[i] == 1...we replace "3" not 4.

                Externally, we are creating a new lis_order... but due to ask is "length_of_lis"... we can do within single array.

            nums[i] > last_element_of_increasing_order,

                Add nums[i] in increasing order...

        At the end, increasing order array's size is maxLis.

==============================> Approach and Time Complexity <============================



1) DP
Time: O(N^2)
Space: O(N^2) => O(1)

2) Binary Search
Time: O(NlogN)
Space: O(N)

 */


// Recursive solution
class Solution {
public:

    int LIS(int i, int prev_index, vector<int> &nums) {

        if (i >= nums.size())
            return 0;

        int lengthOfLIS;

        // you can take nums[i] in LIS, so you have two choice to take it or don't take it.
        if (prev_index == -1 || nums[prev_index] < nums[i]) {

            // // take it
            // 1 + LIS(i+1, i, nums);

            // // don't take it
            // LIS(i+1, prev_index, nums);

            lengthOfLIS = max(1 + LIS(i + 1, i, nums), LIS(i + 1, prev_index, nums));
        }
        else {
            lengthOfLIS = LIS(i + 1, prev_index, nums);
        }

        return lengthOfLIS;
    }


    int lengthOfLIS(vector<int>& nums) {

        return LIS(0, -1, nums);
    }
};


// Top-down
// 1 <= nums.length <= 2500
class Solution {
public:

    int t[2502][2502];

    int OFFSET = 1;

    int LIS(int i, int prev_index, vector<int> &nums) {

        if (i >= nums.size())
            return 0;

        if (t[i][prev_index + OFFSET] != -1)
            return t[i][prev_index + OFFSET];

        int lengthOfLIS;

        // you can take nums[i] in LIS, so you have two choice to take it or don't take it.
        if (prev_index == -1 || nums[prev_index] < nums[i]) {

            // // take it
            // 1 + LIS(i+1, i, nums);

            // // don't take it
            // LIS(i+1, prev_index, nums);

            lengthOfLIS = max(1 + LIS(i + 1, i, nums), LIS(i + 1, prev_index, nums));
        }
        else {
            lengthOfLIS = LIS(i + 1, prev_index, nums);
        }

        return t[i][prev_index + OFFSET] = lengthOfLIS;
    }


    int lengthOfLIS(vector<int>& nums) {
        memset(t, -1, sizeof(t));
        return LIS(0, -1, nums);
    }
};


// Bottom-up
// 1 <= nums.length <= 2500
class Solution {
public:

    int OFFSET = 1;

    int lengthOfLIS(vector<int>& nums) {
        int m = nums.size();
        vector<vector<int>> dp(m + 1, vector<int>(m + 1, 0));

        // base case (covered during initialization)
        // dp[m][j] = 0;

        for (int i = m - 1; i >= 0; i--) {

            for (int prev_index = i - 1; prev_index >= -1; prev_index--) {

                int lengthOfLIS;

                // you can take nums[i] in LIS, so you have two choice to take it or don't take it.
                if (prev_index == -1 || nums[prev_index] < nums[i]) {

                    // // take it
                    // 1 + LIS(i+1, i, nums);

                    // // don't take it
                    // LIS(i+1, prev_index, nums);

                    lengthOfLIS = max(1 + dp[i + 1][i + OFFSET], dp[i + 1][prev_index + OFFSET]);
                }
                else {
                    lengthOfLIS = dp[i + 1][prev_index + OFFSET];
                }

                dp[i][prev_index + OFFSET] = lengthOfLIS;

            }
        }

        return dp[0][-1 + OFFSET];
    }
};

// Bottom-up Space Optimization
class Solution {
public:

    int OFFSET = 1;

    int lengthOfLIS(vector<int>& nums) {
        int m = nums.size();

        vector<int> prev(m + 1, 0), cur(m + 1, 0);
        // base case dp[m][j] = 0, covered.

        for (int i = m - 1; i >= 0; i--) {

            for (int prev_index = i - 1; prev_index >= -1; prev_index--) {

                int lengthOfLIS;

                // you can take nums[i] in LIS, so you have two choice to take it or don't take it.
                if (prev_index == -1 || nums[prev_index] < nums[i]) {

                    // // take it
                    // 1 + LIS(i+1, i, nums);

                    // // don't take it
                    // LIS(i+1, prev_index, nums);

                    lengthOfLIS = max(1 + prev[i + OFFSET], prev[prev_index + OFFSET]);
                }
                else {
                    lengthOfLIS = prev[prev_index + OFFSET];
                }

                cur[prev_index + OFFSET] = lengthOfLIS;
            }

            swap(prev, cur);
        }

        return prev[-1 + OFFSET];
    }
};


// Bottom-up Withou Using DP
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int m = nums.size();
        vector<int> lis(m, 1);
        int maxLis = 1; // keep track of maxLis Length
        for (int i = 1; i < m; i++) {
            for (int j = i - 1; j >= 0; j--) {
                if (nums[j] < nums[i] && (1 + lis[j]) > lis[i]) {
                    lis[i] = 1 + lis[j];
                }
            }
            maxLis = max(maxLis, lis[i]);   // update after computing lis[i], we are considering ith element as end of lis so taking its length.
        }
        return maxLis;
    }
};

// Bottom-up Without Using DP (Printing LIS)
class Solution {
public:
    vector<int> longestIncreasingSubsequence(int m, vector<int>& nums) {
        vector<int> lis(m, 1), prev(m, 0);
        int maxLis = 1; // keep track of maxLis Length
        for (int i = 0; i < m; i++) {
            prev[i] = i;    // setting prev element as itself.
            for (int j = 0; j < i; j++) {       // for lexo order we need to check from (0 , j) else (j --> i) is also fine.
                if (nums[j] < nums[i] && (1 + lis[j]) > lis[i]) {
                    lis[i] = 1 + lis[j];
                    prev[i] = j;        // indicate... ith element previous element is at jth index.
                }
            }
            maxLis = max(maxLis, lis[i]);   // update after computing lis[i], we are considering ith element as end of lis so taking its length.
        }

        // find the index, which have maxLis so we can start from that.
        int index = 0;
        while (lis[index] != maxLis) {
            index++;
        }

        vector<int> lisOrder;

        // Until we don't reach to last element keep doing that..
        while (prev[index] != index) {
            lisOrder.push_back(nums[index]);
            index = prev[index];
        }

        // Add last prev[index] == index... element (because that is last number which is also part of LIS)
        lisOrder.push_back(nums[index]);

        reverse(lisOrder.begin(), lisOrder.end());

        return lisOrder;
    }
};

// LIS using the Binary Search, O(NlogN)
class Solution {


    // Return index of element which is equal to "target" or just greater than "target".
    int lower_bound(vector<int>& arr, int num) {

        int low = 0, high = arr.size() - 1;

        while (low <= high) {

            int mid = (low + high) >> 1;

            if (arr[mid] == num) {
                return mid;
            } else if (num < arr[mid]) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        return low;
    }

public:
    int lengthOfLIS(vector<int>& nums) {

        int m = nums.size();

        // Keep track of increasing order.
        vector<int> incOrder;

        incOrder.push_back(nums[0]); // base case, add first element... as we know atleast LIS=1 is possible with any single number

        for (int i = 1; i < m; i++) {

            // if nums[i] <= last_element of incOrder.. it means it can swap one of greater number than it.
            if (nums[i] <= incOrder.back()) {
                int replaceAt = lower_bound(incOrder, nums[i]);
                incOrder[replaceAt] = nums[i];
            } else {        // nums[i] > last_elememt.... then nums[i] extend the lis by ending at nums[i]
                incOrder.push_back(nums[i]);
            }
        }
        return incOrder.size(); // size of incOrder will be length of LIS. Note: lncOrder is not LIS order it is just increasing order.
    }
};