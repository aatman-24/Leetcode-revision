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

Question : NC_12_Minimum Interval to Include Each Query
Topic : Interval, PQ, Sliding Window
Problems : https://neetcode.io/problems/minimum-interval-including-query


==============================> Explanation <=============================================

Brute Force(O(N*M)): So brute force is very easy, we can iterate over all the points, and for each points
we find all intervals in which current points fall, and then pick up the shortest range one out of that.
Check the code!!

Priority Queue(O(N*logN) + O(M*logM): Here, we optimize the above approach, instead of checking all the intervals
we check the intervals which are relevant, for that we need to use sorting with priority queue.

So idea is that, if we sort the intervals based on their starting time, and also sort the query... we can keep track
of intervals which are close and relevant... because if point is = 10... then there is not reason to check in (100, 120) intervals
which is very far from the point...

Next thing is that, we use the sliding window technique here using the priority queue,

so we know that, for any particular point we can have multiple intervals where our point can fall.... so idea
is that we keep track of those, inside the priority queue and we sort them accoriding to their size in priority
queue so pq.top() can give u the answer(minLenght) directly...

Priority queue, sliding window:

Expand: for each point, we check if given interval_start_time < point...we add that interval

Shrink: for each point, we check if given interval_end_time < point... we remove that

After that we check if !pq.empty(), then pq.top() is our answer....

Check the code...

==============================> Approach and Time Complexity <============================

1) Brute Force
Time: O(N*M)
Space: O(N)

2) Sliding Window
Time: O(NlogN+MlogM)
Space: O(N+M)

*/



// Brute force
class Solution {
public:

	int getRange(vector<int>& a) {
		return abs(a[0] - a[1]) + 1;
	}

	bool isPointWithinInterval(vector<int> &internval, int point) {
		if ( point < internval[0]  || point > internval[1]) {
			return false;
		}
		return true;
	}

	// O(N)
	int getShortestIntervalLength(vector<vector<int>>& intervals, int point) {

		int minDistance = INT_MAX;

		for (auto it : intervals) {

			if (isPointWithinInterval(it, point)) {
				minDistance = min(minDistance, getRange(it));
			}
		}

		return minDistance == INT_MAX ? -1 : minDistance;
	}

	vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {

		vector<int> queryResult;


		// O(M)
		for (int point : queries) {

			// O(M) * O(N) => O(M*N)
			int ans = getShortestIntervalLength(intervals, point);

			queryResult.push_back(ans);
		}

		return queryResult;

	}
};


// Priority Queue
class Solution {
public:

	int getRange(vector<int>& a) {
		return abs(a[1] - a[0]) + 1;
	}

	bool isPointWithinInterval(vector<int> &internval, int point) {
		if ( point < internval[0]  || point > internval[1]) {
			return false;
		}
		return true;
	}


	vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {

		int N = intervals.size(), M = queries.size();

		// sort the intervals, based on starting time
		sort(intervals.begin(), intervals.end());

		// {point, index}
		vector<pair<int, int>> points;
		for (int i = 0; i < queries.size(); i++) {
			points.push_back({queries[i], i});
		}

		// sort the queries (need to transform this)
		sort(points.begin(), points.end());

		// track the intervals
		int i = 0;

		// minHeap, with special property if two intervals have same length then one which end first needs to be on top.
		auto cmp = [](const pair<int, int> &a, const pair<int, int> &b) {
			return a.first > b.first || (a.first == b.first && a.second > b.second);
		};

		// minHeap: one point can be part of multiple intervals, so this heap return the shortest length interval.
		priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);

		// store the result inside this
		vector<int> queryResult(M, -1);

		// O(M)
		for (auto point : points) {

			// add all eligible interval for current points into the pq
			while (i < N && intervals[i][0] <= point.first) {
				int lengthOfInterval = getRange(intervals[i]);
				pq.push({lengthOfInterval, intervals[i][1]});
				i++;
			}

			// remove the outdated intervals from the pq.
			while (!pq.empty() && pq.top().second < point.first) {
				pq.pop();
			}


			// pick up the best one, and push it into the result.
			if (!pq.empty()) {
				int minLength = pq.top().first;
				queryResult[point.second] = minLength;
			}
		}

		return queryResult;

	}
};
