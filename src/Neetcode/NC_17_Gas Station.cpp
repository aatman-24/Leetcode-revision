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

Question : NC_17_Gas Station
Topic    : Greedy
Link     : https://neetcode.io/problems/gas-station

==============================> Explanation <=============================================

Goal: Find a starting station to complete a full cycle with sufficient fuel at every point.

**Brute Force:**
Try starting at each station. If fuel ever drops below 0 during the cycle, that start is invalid.

**Brute Force Optimization:**
Use a diff[] = gas[i] - cost[i]. If diff[i] < 0, skip station i as a possible start.

**Two Pointer Approach:**
Use one pointer from the end and one from the start.
- If `gas[end] - cost[end] < 0`, move the end pointer backward to gain more fuel.
- If fuel ≥ 0, move the start pointer forward.
Continue until pointers meet. If total fuel is ≥ 0, a valid start exists.

**Greedy (Kadane-like):**
- First, check if total gas ≥ total cost. If not, return -1.
- Traverse array, accumulating fuel.
  - If fuel drops below 0, reset and set new start point to `i + 1`.
  - Continue until the end; the last recorded start point is the answer.

==============================> Approach and Time Complexity <============================

1) Brute Force         -> Time: O(N^2), Space: O(1)
2) Two Pointer         -> Time: O(N),   Space: O(1)
3) Greedy (Kadane-like)-> Time: O(N),   Space: O(1)

*/

// Brute Force
class Solution {
public:
	int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {

		int N = gas.size();

		for (int startFrom = 0; startFrom < N; startFrom++) {

			int fuel = gas[startFrom] - cost[startFrom];

			// not possible to reach to the next station
			if (fuel < 0) {
				continue;
			}

			int runner = (startFrom + 1) % N;

			while (runner != startFrom) {

				fuel += gas[runner] - cost[runner];

				if (fuel < 0)
					break;

				runner = (runner + 1) % N;
			}

			// able to complete the cycle
			if (runner == startFrom)
				return startFrom;
		}

		return -1;
	}
};


// Two pointer
class Solution {
public:
	int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {

		int N = gas.size();
		int startFrom = N - 1;
		int ending = 0;

		// goal is to reach startFrom to ending, while having fuel > 0.
		int fuel = gas[N - 1] - cost[N - 1];

		while (ending < startFrom) {

			// negative fuel, then we move to backward see if some fuel saved, which we can use
			if (fuel < 0) {
				startFrom--;
				fuel += gas[startFrom] - cost[startFrom];	// startFrom=N-1, fuel is processed so we first move to backward point then processed it.
			}

			// positive fuel, then we move foward
			else {
				fuel += gas[ending] - cost[ending]; // see ending = 0, fuel is not processed so we first processed and later we move ot the next
				ending++;
			}
		}

		return fuel >= 0 ? startFrom : -1;
	}
};

// Greedy
class Solution {
public:
	int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {

		// total_gas > total_cost, if not return -1
		if (accumulate(gas.begin(), gas.end(), 0) <
		        accumulate(cost.begin(), cost.end(), 0)) {
			return -1;
		}

		// keep track of totalGas
		int total = 0;
		int startFrom = 0;

		for (int i = 0; i < gas.size(); i++) {

			total += (gas[i] - cost[i]);

			// it indicate, none of the index from [0, i] can be starting point, so we
			// just moving our startFrom to the next index.....

			// see, there must be way because we have total_gas > total_cost.... so we
			// just need to check which index can keep total_gas positive till we reach
			// end of the array.
			if (total < 0) {
				total = 0;
				startFrom = i + 1;
			}
		}

		return startFrom;
	}
};