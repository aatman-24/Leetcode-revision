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

Question : 435. Non-overlapping Intervals
Topic : Greedy = Interval-Scheduling
Problems : https://leetcode.com/problems/non-overlapping-intervals/description/
==============================> Explanation <=============================================

Parent problem: 56. Merge Intervals

Goal is to remove minimum number of intervals so that it becomes non-overlapping.

As we know in #435, Overlapping intervals => ending_time <= starting_time...

But here... given that... Overlapping intervals => ending_time < starting_time...

---

Now Idea is that... to remove minimum number of intervals => we need to keep over interval short from the starting....
so that we can retain maximum number of intervals.

If we keep our interval range long(abs(start-end) larger) then we need to remove maximum number of intervals (which is opposite).

It means that if two overlapping internvals are there (1, 3) (2, 5).... our ending time = min(3, 5) = 3.... not #5.... because
if next intervals is (4, 7)... we want to retain then...

Algorithm:
- sort the intervals based on minimum start and end time.
- keep track of non_overlapped interval.
- whenever we see overlapping that time...we keep current interval short by choosing minimum ending time...
so we can retain maximum number of intervals from given array.
- At then end return N - non_overlapped interval.

==============================> Approach and Time Complexity <============================



1) Greedy
Time: O(N)
Space: O(1)

 */


class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
        int curStart = intervals[0][0], curEnd = intervals[0][1];
        int non_overlapped = 1;
        for (int i = 1; i < intervals.size(); i++) {
            int xx = intervals[i][0];
            int yy = intervals[i][1];
            if (xx < curEnd) {
                // Instead of large range we are keeping short..so we can retain maximum number
                // of Intervals.
                curEnd = min(curEnd, yy);
            }
            else {
                non_overlapped++;
                curStart = xx;
                curEnd = yy;
            }
        }
        return intervals.size() - non_overlapped;
    }
};