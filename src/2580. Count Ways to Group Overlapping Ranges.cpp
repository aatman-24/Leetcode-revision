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

Question : 2580. Count Ways to Group Overlapping Ranges
Topic : Greedy = Interval-Scheduling
Problems : https://leetcode.com/problems/count-ways-to-group-overlapping-ranges/description/
==============================> Explanation <=============================================

Pattern: 56. Merge Intervals

In this question, it is asked to put given intervals in two group such that.. if there are
overlapping intervals it must go to single group.

Idea is that.... If we have one group(M number of intervals which are overlappep).. we have
basically two options to put that in either group1 or group2.

If there are M groups such then count = 2^M. (Two choice we have).....

So what we need to find is.... such overlapped group... which can easily we get with merge
interval concept...check the code...


==============================> Approach and Time Complexity <============================



1) Greedy
Time: O(N)
Space: O(1)

 */



class Solution {
public:

    int mod = 1000000007;

    int powerOfTwo(int n) {
        int ans = 1;
        for (int i = 1; i <= n; i++) {
            ans = (ans * 2) % mod;
        }
        return ans;
    }

    int countWays(vector<vector<int>>& ranges) {
        sort(ranges.begin(), ranges.end());
        int totalGrp = 1;
        int start = ranges[0][0], end = ranges[0][1];
        int i = 1;
        while (i < ranges.size()) {

            // consume all non-overlapping intervals as single group.
            while (i < ranges.size() && ranges[i][0] <= end) {

                // update the endPoint of group.
                end = max(end, ranges[i][1]);
                i++;
            }

            // reset the start & end... means new group...
            if (i < ranges.size()) {
                start = ranges[i][0];
                end = ranges[i][1];
                i++;
                totalGrp++;
            }
        }
        return powerOfTwo(totalGrp) % mod;
    }
};