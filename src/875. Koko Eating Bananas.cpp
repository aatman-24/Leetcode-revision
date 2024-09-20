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

Question : 875. Koko Eating Bananas
Topic : Binary Search
Problems : https://leetcode.com/problems/koko-eating-bananas/description/

==============================> Explanation <=============================================

Pattern: 367. Valid Perfect Square

It won't be easy to figure out pattern here, but this is also one pattern.
=> In this pattern, we need to find some minimum/maximum value K(pivot) such that some condition will met. From question you can get idea,
if any number A < K, that "A" violate/meet condition then for values lesser than "A" also its violate/meet. And opposite side A > K its do opposite.

Here, we need to find the minimum eating speed K per hour such that condition(koko can eat all the bananas from piles). And we know that,
If answer for K is 10,
	then speed in this range [1,2...9] < K won't be able meet conditions.
	and speed in this range [10, 11, 12... INT_MAX] >= K will meet conditions. but we need minimum which is K.

We have left = 1(minimum speed possible) and right = max(piles), because with max_value we have answer length(piles) which is gurantee.

So we check for each mid(k) whether it is feasible or not and keep track of minimum K.

how hoursRequired calculated with O(N) time ?
Given that, if pile has banana more than K, it will eat only K bananas.
			if pile has banana less than K, it will eat only remaining bananas.
// [10, 4], K = 3... To finish first pile(10) => 3 + 3 + 3 + 1 => 4 hours, 4 => 3 + 1 => 2 hours.
Which is nothing but ceil(N/K). So we can calculate required hours by taking ceil(num/K) and do the aggreation of that.


==============================> Approach and Time Complexity <============================


1) Binary Search
Time: O(logN)
Space: O(logN)


 */


class Solution {
public:

	// return max pile from piles.
	int maxPile(vector<int> &piles) {
		int max_pile = INT_MIN;
		for (int num : piles) {
			max_pile = max(max_pile, num);
		}
		return max_pile;
	}

	// check whether is it feasible with "k" speed to finish all the piles within "h" hours.
	bool isFeasible(vector<int>& piles, int h, int k) {
		long hoursRequired = 0;
		for (int num : piles) {
			hoursRequired += ceil(num * 1.0 / k);
		}
		return hoursRequired <= h;
	}


	int minEatingSpeed(vector<int>& piles, int h) {
		long lh = 1, rh = maxPile(piles);
		long minK = 1;		// keep track of minimum speed we got till now.
		while (lh <= rh) {
			long mid = (lh + rh) >> 1;
			if (isFeasible(piles, h, mid)) {
				rh = mid - 1;
				minK = mid;		// feasible keep track of minK. Here we don't need do minK=min(minK, mid).. because each iteration we move to shorter range only.
			}
			else {
				lh = mid + 1;
			}
		}
		return minK;
	}
};