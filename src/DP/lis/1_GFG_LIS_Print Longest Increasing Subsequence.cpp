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

Question : 1_GFG_LIS_Print Longest Increasing Subsequence
Topic : DP
Problems : https://www.geeksforgeeks.org/problems/printing-longest-increasing-subsequence
==============================> Explanation <=============================================

Pattern: LIS

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


==============================> Approach and Time Complexity <============================



1) DP
Time: O(N)
Space: O(N) => O(1)

 */


// Bottom-up Without Using DP
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


