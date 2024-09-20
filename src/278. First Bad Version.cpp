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

Question : 278. First Bad Version
Topic : Binary Search
Problems : https://leetcode.com/problems/first-bad-version/description/

==============================> Explanation <=============================================

In the question, it is clearly given that "all the versions after a bad version are also bad". And we need to find the first bad version.
version looks liks this way: [good, good, good, bad, bad, bad, bad, bad]
We need to find first bad version.

We can simply apply binary search,
	If we get mid as good version will check from (mid+1, right)
	If we get the mid as bad version will check from (left, mid-1), mid consider as lastBadVersion.

==============================> Approach and Time Complexity <============================

1) Binary Search
Time: O(logN)
Space: O(logN)

 */


// The API isBadVersion is defined for you.
// bool isBadVersion(int version);


class Solution {
public:
	int firstBadVersion(int n) {
		long lf = 1, rh = n;
		long lastBadVersion = 1;
		while (lf <= rh) {
			long mid = (lf + rh) >> 1;
			if (isBadVersion(mid)) {
				rh = mid - 1;
				lastBadVersion = mid;		// mid is bad version, so before reduce the range we store it as lastBadVersion
			}
			else {
				lf = mid + 1;
			}
		}
		return lastBadVersion;
	}
};