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

Question : NC_5_Task Scheduler
Topic : Heap, PQ
Problems : https://neetcode.io/problems/task-scheduling

==============================> Explanation <=============================================

Approach-1: Simulation
So, we can count the freq of elements and push that into the pq. so
we can get the most frequenet element in O(logN)=O(log26). We basically,
try to schedule one element at time, if we have more than one elements..
then we put the remainign elements into the waitQueue with activeTime(currTime+cycleTime).
- Each time we see, if some elements are active then we again push into the pq, to
scheudle them.

Approach-2: Greedy Scheudling
- In this approach, we have noticed pattern..to get the least interval...
we need to schedule the maxFreq element first...so we first schedule it.
During that time we have soo much idleSpace in between.. which we count...
and try to fill up in greddy manner.

Case-1:

A = 3
B = 2

A _ _ _ A _ _ _ A => IdleSpace = 6

B_freq <= (max_freq-1) => we can place it in idleSpace so we need to subtract those space.


Case-2:

A = 3
B = 3

A _ _ _ A _ _ _ A B => IdleSpace = 6

B_freq > (max_freq-1) => we can place only (maxFreq-1) elements of 'B' in idleSpace so we need to subtract those only.


Total space = idleSpace + each_elements


Approach-3: Use math based on #2.

So here...we noticed that... to schedule the maxFreq element with n interval....

We need total space = (maxFreq-1) * (n + 1)

We set the reamining element at the end....because.....

We have to add those all maxFreq element(A=3, B=3)...at the end direclty without space...

so we just count maxCount..... for that...

Edge case: elements.size() = 100 and n = 2..... in such case we don't need any extra space(idle)..
we can shuffle elements such way that...we can make sure intervalCycle....
so answer will be elemetns.size() only.....


==============================> Approach and Time Complexity <============================

1) PQ
Time: O(NLogN)
Space: O(N)

*/


// simulation (O(N))
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {

        vector<int> count(26, 0);
        for (char ch : tasks) {
            count[ch - 'A']++;
        }

        priority_queue<int> pq;
        for (int num : count) {
            if (num > 0) {
                pq.push(num);
            }
        }

        // {remaining_freq, timer} => so when we scheudle first 'A' at time=0, and cycleTime = 3..then we place other remaining 'A' into
        // waitQueue by calculating the next time when they again become active(eg: until timer = currentTimer + cycleTime)
        queue<pair<int, int>> waitQueue;

        int timer = 0;
        while (!pq.empty() || !waitQueue.empty()) {

            timer++;

            // just set the timer with first element of remaining elements, which we
            // put into the wait status.
            if (pq.empty()) {
                timer = waitQueue.front().second;
            }
            else {
                int maxFreq = pq.top(); pq.pop();
                // put remaining element into the queue
                if (maxFreq - 1 > 0) {
                    waitQueue.push({maxFreq - 1, timer + n});
                }
            }


            // can schedule the element, from the waitQueue.
            if (!waitQueue.empty() && waitQueue.front().second == timer) {
                auto it = waitQueue.front(); waitQueue.pop();
                pq.push(it.first);
            }
        }

        return timer;
    }
};


// greedy, scheduler, O(N)
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {

        vector<int> count(26, 0);

        for (char ch : tasks) {
            count[ch - 'A']++;
        }

        sort(count.begin(), count.end());

        int maxFreq = count[25];

        // A = 3, B = 2, N = 2
        // A _ _ A _ _ A  => Total 4 idle spaces, with 2 major gap
        int idleSpace = (maxFreq - 1) * n;

        for (int j = 24; j >= 0; j--) {

            // how much other elements can use that idleSpace we need to count that and subtract that.

            // maxFreq-1(major gap) > count[j]: number of element is less than major gap, so used idleSpace=freqOfThatElement
            // maxFreq-1(major gap) < count[j]: number of element greater than major gap, so only able to used idleSpace=major gap.
            int otherElementCanUse = min(maxFreq - 1, count[j]);

            idleSpace -= otherElementCanUse;
        }

        // total_element + idleSpace
        return tasks.size() + max(0, idleSpace);

    }
};


// Math O(N)

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {

        vector<int> count(26, 0);

        for (char ch : tasks) {
            count[ch - 'A']++;
        }

        int maxFreq = *max_element(count.begin(), count.end());

        // required total space for scheduling (maxFreq-1) elements.
        int space = (maxFreq - 1) * (n + 1);

        // why maxCount, because if 2-elements which have same amount of
        // frequency which is maximum....
        // A _ _ A _ _  (scheuled maxFreq-1) element with space.
        // A B _ A B _ A(.) B(.)
        // As you can see we have to add +2 for last set which is decide
        // through the freq.
        int maxCount = 0;
        for (int num : count) {
            if (num == maxFreq) {
                maxCount++;
            }
        }

        int time = idleSpace + maxCount;


        // if we have lots of elements... but n is very less compare to those size..
        // we can shuffle elements somehow, and leastSpace is tasks.size().
        return max((int)tasks.size(), timer);
    }
};
