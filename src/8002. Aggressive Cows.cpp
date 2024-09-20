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

Question : 8002. Aggressive Cows
Topic : BS
Problems : https://takeuforward.org/data-structure/aggressive-cows-detailed-solution/

==============================> Explanation <=============================================

Variation: Min-Max, Max-Min

Here we are finding the minimum distance between two cows, we we allocated cows to each stall. But we want maximum of such distance with all possiblites.

Again It is BST. Because If we can assign the cows to stalls while keeping atleast "a" distance then we are also able to do with "a-1" distance, so no need to look for those scenarino.

Same goes for larger side, if we are not able to assing all cows with "l" distnace, then there is no chance we can keep min distnace "l+1" and assing cows to stalls.

Think about search-space area,

lh = 1, MIN_DIST possible between two stall is 1.
rh = stalls[N-1] - stalls[0], distance between first and last stall.

Now our answer, reside in this range only.

So what we can do is, we try to assign cows to stall while keeping atleast "dist"(mid) between them.

    1) If we are able to do it, then that could be our answer, but as given in question we are looking maximum of such answer so will keep finding better answer.
    2) If we are not able to do it, then we need to decrease the distance crietria so we can assing more cows to stalls.


How we will verify whether with given "dist" we are able to do it or not ?

- For that, we choose greedy apporach. We place the cows such that dist between two consecutive cows must be >= dist. And we count how many
cows got allocated to stall.

allocated_cow < given_cow... (less cow allocated, to increase it we need to decrease distnace betweent them)
    rh = mid - 1
allocated_cow >=  given_cow  (we got one of the answer, but we are still looking for maximum distnace so we keep seaching better answer)
    ans = max(ans, mid)
    lh = mid + 1


==============================> Approach and Time Complexity <============================


1) Binary Search
Time: O(rh*logN)
Space: O(1)


 */


bool canWeArrageCows(vector<int> & stalls, int dist, int k) {

    int totalCowAllocated = 1;
    int lastStallDist = stalls[0];

    for (int curStallDist : stalls) {

        // keep track of distance between them, if it is more than dist, then we allocate new cow to that stall.
        if (abs(lastStallDist, curStallDist) >= dist) {
            totalCowAllocated++;
            lastStallDist = curStallDist;
        }

        // Just for optimization purpose, nothing to do with logic.
        if (totalCowAllocated >= k)
            return true;
    }

    // If more cow allocated, no problem we are still looking for better answer by increasing distance between them.
    return totalCowAllocated >= k;
}


int aggressiveCows(vector<int> &stalls, int k) {

    int N = stalls.size();

    // sorting stalls location, to make the minimum distance between stalls. Sorting doesn't have any connection with allocation of cows.
    sort(stalls.begin(), stalls.end());

    // minimum distance between stall which can be possible.
    int lh = 1;

    // maximum distance betweent to stall possible is
    int rh = stalls[N - 1] - stalls[0] + 1;

    // keep track of maximum of minimum distance.
    int maximumDistBetweenTwoCows = 1;

    while (lh < rh) {

        // Indicate, how much distance we need to keep atleast between two cows.
        int dist = (lh + rh) >> 1;

        // if we keep atleast "dist" distnace between two cows we are able to assign kth cows to stalls.
        // but we want this dist to maximum so we are still looking for better "dist" value.
        if (canWeArrageCows(stalls, dist, k)) {
            maximumDistBetweenTwoCows = max(maximumDistBetweenTwoCows, dist);
            lf = dist + 1;
        }
        // not able to assing kth cows to stalls, it means our "dist" is more than it should. so decrease it.
        else {
            rh = dist - 1;
        }

    }

    return maximumDistBetweenTwoCows;
}