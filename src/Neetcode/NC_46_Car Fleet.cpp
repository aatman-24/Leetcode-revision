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
================================================================================
                                Problem Description
================================================================================

Problem: NC_46_Car Fleet
Topic: Mono Stack
Link: https://neetcode.io/problems/car-fleet

================================================================================
                                Problem Summary
================================================================================

You are given the target location `target`, and two arrays `position[]` and `speed[]`, where:
- `position[i]` is the starting position of the i-th car.
- `speed[i]` is the speed of the i-th car.

All cars move toward the target in the same lane. A car **cannot overtake** another car ahead of it, but it can catch up and form a **fleet**, traveling at the same speed as the slower car ahead.

Return the number of **car fleets** that will arrive at the destination.


================================================================================
                                Intuition & Explanation
================================================================================

### Key Observations:
- If a car behind reaches a slower car ahead **before the target**, it merges and forms a **fleet**.
- Once merged, the fleet moves at the speed of the **slowest** car

First we need to find out, how many in hours it takes to reach any car to target => (target - position) / speed

Once we get that... and sort the cars based on its position... one thing is very clear...

If any car is taking more time then previous cars it become blocker and create fleet....

Ex: x1 > x2 > x3 < x4

X1 is taking 3 hrs, x2 is taking 2 hrs, x3 is taking 1 hrs But x4 is taking 5 hours... then all (x1, x2, x3) also take 5 hours...

So it very clear, we need to use the mono decreasing stack to eliminate such (x1, x2, x3) cars when we see higher value.


### Step-by-Step Approach:

1. **Calculate Time to Reach Target**:
   For each car:
   `time = (target - position) / speed`

2. **Sort Cars by Position Descending**:
   - Start from the closest car to the target and process backward.
   - Why? Because the car closest to the destination can't be blocked by any other car.

3. **Use a Monotonic Stack (Decreasing Time)**:
   - Iterate over the times.
   - If the current car takes **more time** than the last fleet in the stack, it forms a **new fleet**.
   - Otherwise, it merges with the fleet ahead.



See below example...


Let's look at some examples first.

Ex:
Target: 12
Pos:  [10,8,0,5,3]
Speed:[ 2,4,1,1,3]
First we sort the cars by there position.

Ex:
Target: 12
Pos:  [0,3,5,8,10]
Speed:[1,3,1,4, 2]
Then we calculate the time it need to reach target

Ex:
Target: 12
Pos:  [0, 3, 5, 8,10]
Speed:[1, 3, 1, 4, 2]
Time: [12,3, 7, 1, 1]

How to calculate the time?
Easy, (target-pos)/speed

Alright, I think the previous procedure is sort of intuitive if we want to observe the pattern of the problem.

Now let's observe the pattern of time.

For car 0, it is really slow, it takes 12s to reach target. Thus it is itself a fleet.
For car 3, it is fast, but it will be blocked by car 5.
For car 8, it is fast, but it will be blocked by car 10.
When does the fleet occur?

When one car is blocked by the next car.
Car 0, 5, 10 are the ones who block the previous.
And it is actually a monotonic decreasing stack! Why?

From the perspective of numbers:
Let's pick up 0, 5, 10 and there time needed: [12,7,1]
12,7,1 is monotonic decreasing
From the perspective of reasoning:
If a car is slower then previous, all the previous faster car will bump into this car and become a fleet.

Ex:
Time [1,2,3,5] ==> [5]
5 is too slow, that 1,2,3 bump into 5

Time [1,2,3,5,3,4] ==> [5,4]
5 is too slow, and 4 is slow too.
123 bump into 5, 3 bump into 4.
4 is still faster than 5. Thus they won't bump together.

Time [1,2,3,5,3,4,8] ==> [8]
8 is really too slow all the previous bump into it.
Finally, the answer will be the size of the stack.


================================================================================
                          Approach & Time/Space Complexity
================================================================================

Approach: Mono stack
Time Complexity: O(NLogN) + O(N)
Space Complexity: O(N)

*/



class Solution {
public:

    int carFleet(int target, vector<int>& position, vector<int>& speed) {

        int N = position.size();

        vector<vector<double>> cars;

        for (int i = 0; i < N; i++) {

            // how much time cars[i] take to reach the target considering the starting_point and its speed.
            double totalTimeTake = (target - position[i]) * 1.0 / speed[i];

            cars.push_back({1.0 * position[i], totalTimeTake});
        }

        sort(cars.begin(), cars.end());

        // mono decreasing stack: x1 > x2 > x3 < x4 => (cars x1, x2 and x3 take less time but x4 takes more..so all will be blocked by x4 and become fleet)
        stack<double> st;

        int totalFleet = 0;

        for (int i = 0; i < N; i++) {

            double timeRequired = cars[i][1];

            // If cars[i] required more time than previous cars, then it become blocker and create a fleet for all cars...
            while (!st.empty() && (st.top() < timeRequired)) {
                st.pop();
            }

            st.push(cars[i][1]);
        }

        // At the end whatever cars left, is fleet size... (13, 11, 10) => (decreasing order of time it takes to reach target)
        return st.size();
    }
};

// Without using the stack
class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        int n = position.size();
        vector<pair<int, int>> pair;
        for (int i = 0; i < n; i++) {
            pair.push_back({position[i], speed[i]});
        }
        sort(pair.rbegin(), pair.rend());


        // keep track of prevTime and currentTime
        int fleets = 1;
        double prevTime = (double)(target - pair[0].first) / pair[0].second;

        for (int i = 1; i < n; i++) {

            double currTime = (double)(target - pair[i].first) / pair[i].second;

            // if current cars[i] require more time, then it is blocker for rest of cars
            if (currTime > prevTime) {
                fleets++;
                prevTime = currTime;
            }
        }

        return fleets;
    }
};