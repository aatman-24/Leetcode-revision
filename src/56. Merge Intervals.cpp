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

Question : 56. Merge Intervals
Topic : Greedy = Interval-Scheduling
Problems : https://leetcode.com/problems/merge-intervals/
==============================> Explanation <=============================================

Standard Question on Merging Interval.

Basically, In question we have given intervals [(start, end)]... we need to merge all overapping intervals.

Overlapping Intervals are: [(x1, y1), (x2, y2)], if x2 <= y1... then it is overlapping intervals.

So first thought comes into mind is to sort the intervals. We can sort them by their starting time(x) and if that same
then we sort on ending time.

After, we iterate over the intervals.. and keep (cur_x, cur_y)....

for (x, y) from internvals:
    if(cur_y >= x):
        cur_y = max(cur_y, y)
    else:
        push(cur_x & cur_y) into results.
        cur_x & cur_y = (x, y)


==============================> Approach and Time Complexity <============================



1) Greedy
Time: O(N)
Space: O(1)

 */


class Solution {
public:

    int comparator(vector<int> &p1, vector<int> &p2) {
        if (p1[0] == p2[0]) {
            return p1[1] < p2[1];
        }
        return p1[0] < p2[0];
    }

    vector<vector<int>> merge(vector<vector<int>>& intervals) {

        vector<vector<int>> result;

        sort(intervals.begin(), intervals.end(), comparator);

        int cur_x = intervals[0], cur_y = intervals[1];

        for (int i = 1; i < intervals.size(); i++) {

            int xx = intervals[i][0];
            int yy = intervals[i][1];

            // start_time_i < previous_ending (overlapping)
            if (xx <= cur_y) {
                cur_y = max(cur_y, yy);     // just extend the current range (cur_x, cur_y)
            }
            else {
                result.push_back({cur_x, cur_y});   // push current one into result.

                // reset interval with new one.
                cur_x == xx;
                cur_y == yy;
            }

        }

        // whatever last interval range we have.. push it into the result.
        result.push_back({cur_x, cur_y});

        return result;

    }
};