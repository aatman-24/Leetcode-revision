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

Question : NC_10_Meeting_Rooms
Topic : Interval Scheduling
Problems : https://neetcode.io/problems/meeting-schedule

==============================> Explanation <=============================================

Just need to check there is overlapping or not between intervals.

==============================> Approach and Time Complexity <============================

1) Greedy_Intervals
Time: O(N*logN)
Space: O(1)

*/

/**
 * Definition of Interval:
 * class Interval {
 * public:
 *     int start, end;
 *     Interval(int start, int end) {
 *         this->start = start;
 *         this->end = end;
 *     }
 * }
 */

/**
 * Definition of Interval:
 * class Interval {
 * public:
 *     int start, end;
 *     Interval(int start, int end) {
 *         this->start = start;
 *         this->end = end;
 *     }
 * }
 */

class Solution {
public:

    static bool compare(Interval &a, Interval& b) {
        if (a.start == b.start) return a.end > b.end;
        return a.start < b.start;
    }

    bool canAttendMeetings(vector<Interval>& intervals) {

        if (intervals.size() == 0) return true;

        sort(intervals.begin(), intervals.end(), compare);

        int curStart = intervals[0].start, curEnd = intervals[0].end;

        for (int i = 1; i < intervals.size(); i++) {

            int xx = intervals[i].start;
            int yy = intervals[i].end;

            // overlapped
            if (xx < curEnd) {
                return false;
            }

            // keept track of latest interval
            curStart = xx;
            curEnd = yy;
        }

        return true;
    }
};


// differnt way to write compare function

class Solution {
public:

    bool canAttendMeetings(vector<Interval>& intervals) {

        if (intervals.size() == 0) return true;

        auto compare = [](Interval & a, Interval & b) {
            if (a.start == b.start) return a.end > b.end;
            return a.start < b.start;
        };

        sort(intervals.begin(), intervals.end(), compare);

        int curStart = intervals[0].start, curEnd = intervals[0].end;

        for (int i = 1; i < intervals.size(); i++) {

            int xx = intervals[i].start;
            int yy = intervals[i].end;

            // overlapped
            if (xx < curEnd) {
                return false;
            }

            // keept track of latest interval
            curStart = xx;
            curEnd = yy;
        }

        return true;
    }
};


class Solution {
public:

    bool canAttendMeetings(vector<Interval>& intervals) {

        if (intervals.size() == 0) return true;

        auto compare =

        sort(intervals.begin(), intervals.end(), [](Interval & a, Interval & b) {
            if (a.start == b.start) return a.end > b.end;
            return a.start < b.start;
        });

        int curStart = intervals[0].start, curEnd = intervals[0].end;

        for (int i = 1; i < intervals.size(); i++) {

            int xx = intervals[i].start;
            int yy = intervals[i].end;

            // overlapped
            if (xx < curEnd) {
                return false;
            }

            // keept track of latest interval
            curStart = xx;
            curEnd = yy;
        }

        return true;
    }
};
