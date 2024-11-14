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

Question : 673. Number of Longest Increasing Subsequence
Topic : DP-LIS
Problems : https://leetcode.com/problems/number-of-longest-increasing-subsequence/description/

==============================> Explanation <=============================================

Pattern: LIS

This is LIS Pattern that we know, but in this question ask is, return number of LIS.

So we just not need to track maxLIS but its count as well.

Simple idea is that,

    1 3 5 4 7
    LIS ending at 3 => 1 3
    LIS ending at 5 => 1 3 5
    LIS ending at 4 => 1 3 4
    LIS ending at 7 => 1 3 5 7 | 1 3 4 7

    If we notice, LIS ending at 7.... is considering all the LIS of length 3.

    LIS => 3 + 1 => 4
    LIS_Count => 1 + 1 => 2

    So there is slight change standard LIS,

        The way we are calculating LIS will remain same, only change is there...

        1 + lis[j] == lis[i] => indicate that... lis[i] is already updated with this length,
        but there are subsequence which are ending at jth also can have same length lis[i].

        So we need to consider its count.

        For example:

            LIS ending at 7 = 1 3 4 7

            But it can also extend the "LIS ending at 5 => 1 3 5"

            So we only update the count of maxLIS.

    So it is obvious that, we need 2D array dp[N][2]... to keep track of LIS and LISCount.


    // Got bigger length LIS
    dp[i][0] = 1 + dp[j][0]
    dp[i][1] = dp[j][1] (can extend all subseq which are ending at dp[j])

    // Got same length LIS
    dp[i][1] += dp[j][1] (only update count)


==============================> Approach and Time Complexity <============================

1) DP
Time: O(N^2)
Space: O(2*N)

 */


/* Intution:

This is LIS Pattern that we know, but in this question ask is, return number of LIS.

So we just not need to track maxLIS but its count as well.

Simple idea is that,

    1 3 5 4 7
    LIS ending at 3 => 1 3
    LIS ending at 5 => 1 3 5
    LIS ending at 4 => 1 3 4
    LIS ending at 7 => 1 3 5 7 | 1 3 4 7

    If we notice, LIS ending at 7.... is considering all the LIS of length 3.

    LIS => 3 + 1 => 4
    LIS_Count => 1 + 1 => 2

    So there is slight change standard LIS,

        The way we are calculating LIS will remain same, only change is there...

        1 + lis[j] == lis[i] => indicate that... lis[i] is already updated with this length,
        but there are subsequence which are ending at jth also can have same length lis[i].

        So we need to consider its count.

        For example:

            LIS ending at 7 = 1 3 4 7

            But it can also extend the "LIS ending at 5 => 1 3 5"

            So we only update the count of maxLIS.

    So it is obvious that, we need 2D array dp[N][2]... to keep track of LIS and LISCount.


    // Got bigger length LIS
    dp[i][0] = 1 + dp[j][0]
    dp[i][1] = dp[j][1] (can extend all subseq which are ending at dp[j])

    // Got same length LIS
    dp[i][1] += dp[j][1] (only update count)

*/
class Solution {
public:

    int findNumberOfLIS(vector<int>& nums) {

        int N = nums.size();

        // dp table store, dp[0][0] => maxLIS, dp[0][1] => maxLISCount
        // First Index[0], it store the length of longest LIS
        // Second Index[1], it store the number of longest LIS
        vector<vector<int>> dp(N, vector<int>(2, 1));

        int maxLIS = 1;

        for (int i = 1; i < N; i++) {

            for (int j = i - 1; j >= 0; j--) {

                if (nums[j] < nums[i] && (1 + dp[j][0] >= dp[i][0])) {

                    // Found Bigger LIS
                    if (1 + dp[j][0] > dp[i][0]) {
                        dp[i][0] = 1 + dp[j][0];    // Update LIS Length
                        dp[i][1] = dp[j][1];        // Same number of LIS, ended at jth index we can extend it
                    }

                    // Got other LIS whose length is also same as lis[i]
                    // So we can increase the count of LIS, which are ending at jth index
                    // and can be extended of same length.
                    else {
                        dp[i][1] += dp[j][1];
                    }
                }
            }

            maxLIS = max(maxLIS, dp[i][0]);
        }

        // Count all LIS which have largest LIS
        int count = 0;
        for (int i = 0; i < N; i++) {
            // Consider all chain, which have maxLIS.
            if (dp[i][0] == maxLIS) {
                count += dp[i][1];
            }
        }
        return count;
    }
};



