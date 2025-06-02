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

Question : NC_11_Meeting Rooms II
Topic : Interval Scheduling
Problems : https://neetcode.io/problems/meeting-schedule-ii


==============================> Explanation <=============================================

This is interesting(new pattern) problem, we need to find the minimum number of days required to schedule all meetings without any conflicts.

It means that, we need to figure out at any particular time "how many maximum overlapping meeting possible", and we need to schedule those seperate days.

Concept is that,

meetings: [1, 5], [2, 6], [3, 7], [5, 9]

As we can see if first meeting is started with startTime = 1... then meeting: [2, 6] and [3, 7] are overlapping
because startTime for them which are (2, 3) < endTime(5).... But for the last meeting.... it is not overlapping
with first meeting... because first is ending at 5 and last one is starting at 5.....

So idea is that, we have to keep track of ending time of all parallel running meeting....and we need to compare
it with next meeting starting time...

	if endTime <= startTime..... it means meeting was over... then we drop that meeting...

	if endTime > startTime..... it means new meeting will be helding in parallel......


Approach-1: Use the minHeap to keep track of endTime of meeting.. First we sort the meeting by its
starting time..

Basically before starting any meeting we make
sure we remove all outdated meeting from queue....

so at any moment, pq hold all the meeting which are running in parallel..

and our answer is maximum pq.size().... because those are running in parallel...


Approch-2: Instead of using minHeap.... we can seperate out the starting and endtime in two separate array,
and then use the two pointers to achieve the same behaviour check the code...
statTime[i] < endTime[j] => it means new meeting needs to be start in parallel.
statTime[i] >= endTime[j] => it means old meeting needs to be remove.

NOTE: This question also can be twist by asking how many minimum parallel rooms required instead of minimum days.


==============================> Approach and Time Complexity <============================

1) Interval Scheduling
Time: O(M*K)
Space: O(26^K)

*/


// 1) minHeap

class Solution {
public:
	int minMeetingRooms(vector<Interval>& intervals) {

		if (intervals.size() == 0) return 0;

		// sort intervals according to their start time
		sort(intervals.begin(), intervals.end(), [](auto & a, auto & b) {
			return a.start < b.start;
		});

		priority_queue<int, vector<int>, greater<int>> pq;

		// keep track of max parallel meeting size
		int maxParllelMeeting = 0;

		// iterate over all the meetings...
		for (auto meeting : intervals) {

			// any outdated meeting in queue
			while (!pq.empty() && pq.top() <= meeting.start) {

				// remove all outdated meeting from queue.
				pq.pop();
			}

			// push only the ending time.
			pq.push(meeting.end);

			maxParllelMeeting = max(maxParllelMeeting, (int)pq.size());
		}

		// these are all the meeting which are running in parallel
		return maxParllelMeeting;
	}
};




//

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
	int minMeetingRooms(vector<Interval>& intervals) {

		if (intervals.size() == 0) return 0;

		vector<int> startTime;
		vector<int> endTime;

		for (auto it : intervals) {
			startTime.push_back(it.start);
			endTime.push_back(it.end);
		}

		// sort both starting and ending time..
		sort(startTime.begin(), startTime.end());
		sort(endTime.begin(), endTime.end());

		int N = intervals.size();

		// keep track of max parallel meeting size
		int maxParllelMeeting = 0;

		// two pointer
		int i = 0, j = 0;

		// keep track of current parallel meetings...
		int currParallelMeeting = 0;

		// iterate over all the meetings...
		while (i < N && j < N) {

			// adding new meeting...
			if (startTime[i] < endTime[j]) {
				i++;
				currParallelMeeting++;
			}

			// removing outdated meeting.... (see startTime[i] == endTime[j]...then also remove)
			else {
				j++;
				currParallelMeeting--;
			}

			maxParllelMeeting = max(maxParllelMeeting, currParallelMeeting);
		}

		// these are all the meeting which are running in parallel
		return maxParllelMeeting;
	}
};
