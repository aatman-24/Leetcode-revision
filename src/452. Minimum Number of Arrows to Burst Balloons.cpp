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

Question : 452. Minimum Number of Arrows to Burst Balloons
Topic : Greedy = Merge-Interval
Problems : https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/description/
==============================> Explanation <=============================================

Parent Problem:  56. Merge Intervals

In this problem, we have given intervals in this format... points[i] = [xstart, xend] which placement of ballon in x-axis on XY Plane.
But where exactly ballon is placed on Y axis is not given it can be random. And we have to shoot the arrow from specific point (x, 0)
in y-axis.... all the ballons which came in between... will be burst.

Let's make it simple: intervals = (1, 6), (2, 8), (3, 7)... so If I shot from x = 3...then all these bullon burst. So we need to find
minimum number of arrow to burst all...

--

Idea is that.... somehow we need to find "overlapping range" such that... if I shot one arrow from that range...all ballons got burst..
who share that range.... It's pretty similar to overlapping interval....

ex: (1, 6) & (2, 8) => overlapping range = (2, 6).. so if I shot from x = 2, 3, 4, 5, 6... both these ballon are going to burst...

    How ? => range_x = max(x1, x2), range_y = min(y1, y2) => overlapping range = [range_x, range_y]

Now we check the next interval... if that one also share some range with newly created overlapping range we also mix that one....

so for all intervals... who have construct overlapping range... needs only 1 arrow.

Check the code!!

==============================> Approach and Time Complexity <============================

1) Greedy
Time: O(N)
Space: O(1)

 */


class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        sort(points.begin(), points.end());
        int curStart = points[0][0], curEnd = points[0][1];
        int arrow = 1;
        for (int i = 1; i < points.size(); i++) {
            int starting = points[i][0];
            int ending = points[i][1];
            // overlapping
            if (starting <= curEnd) {

                // redefine boundary
                curStart = max(curStart, starting);
                curEnd = min(curEnd, ending);
            }

            // non-overlapping
            else {
                arrow++;        // need another arrow

                // reset the range
                curStart = starting;
                curEnd = ending;
            }
        }
        return arrow;
    }
};