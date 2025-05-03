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

Question : 57. Insert Interval
Topic : Greedy = Interval-Scheduling
Problems : https://leetcode.com/problems/insert-interval/description/
==============================> Explanation <=============================================

Parent Problem: 56 Merge Interval

Need to merge one given newInterval into given intervals. We can merge the intervals if they
are overlapped.

Idea is that,
- first we add all the non-overlapping intervals whose "interval.ending" < starting_time_of_new_interval (I would call it preintervals..)
- then we merge all overlapping intervals with newInterval.
- later we add all the non-overlapping intervals whose "interval.starting" > ending_time_of_new_interval

For the middle part, we dynamically keep track of our interval (low, high) range... so we can merge overlapping intervals into one interval only.

Check the code!!

==============================> Approach and Time Complexity <============================



1) Greedy
Time: O(N)
Space: O(1)

 */


class Solution {
public:

    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> result;
        int idx = 0, N = intervals.size();
        int start = newInterval[0], end = newInterval[1];

        // add all the intervals first, whose ending < starting_of_new_interval
        while (idx < N && intervals[idx][1] < start) {
            result.push_back(intervals[idx++]);
        }

        // merge all the intervals, whose starting < ending_of_new_interval
        while (idx < N && intervals[idx][0] <= end) {
            start = min(start, intervals[idx][0]);
            end = max(end, intervals[idx][1]);
            idx++;
        }
        result.push_back({start, end});

        // add all the intervals(rest), whose starting > ending_of_new_interval
        while (idx < N) {
            result.push_back(intervals[idx++]);
        }

        return result;
    }
};
