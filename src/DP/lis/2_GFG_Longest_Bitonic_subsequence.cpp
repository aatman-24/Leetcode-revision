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

Question : 2_GFG_Longest_Bitonic_subsequence
Topic : DP-LIS
Problems : https://www.geeksforgeeks.org/problems/longest-bitonic-subsequence0824/1

==============================> Explanation <=============================================

Pattern = LIS

Bitonic Subseq => {Strictly_Increasing, Center, Strictly_Decreasing}

We have to find such longest subseq, that's what ask is.

Idea is that,

	We will find both increasing and decreasing subseq separately, and will merge the length so
	we have bitonic subseq...will take maximum of that.

	And one more thing is that, we have to find strictly decreasing sub from behind(N-1 -> 0)..
	Then only we add it as suffix.

Edge case: Given that both prefix + suffix should be present to consider it as bitonic. So we can't initialize the
dp array with "1" because we are using it to validate, both prefix and suffix present or not. So what we do, we initialize with "0" for both dp arrays, and during computation we will add +1(for nums[i]).

Check the code!!

==============================> Approach and Time Complexity <============================



1) DP
Time: P(2*N^2)
Space: O(N)

 */


/* Intution:

	We need subseq which is increasing and decreasing from center point. And center point can be any of nums[i].

	For increasing subsequence we can use LIS Algorithm.

	For decreasing subsequence as well, we can use LIS(LDS) algorithm, but twist is that. We have to find LDS from behind.

	Because,

	First_part_increassing + nums[i] + Second_Part_Decreasing

	LIS: 1 3 5 7
	LDS: 7 2 1

	Also given that, both part should be present to consider it as Bitonic. So we don't consider nums[i] length
	when we compute nums[i]...that's why I initialized with "0"... and Later during computation we will add that.

	Check the code!!

*/


class Solution {
public:
	int LongestBitonicSequence(int N, vector<int> &nums) {

		// Initialize with "0", not considering length of number itself.
		vector<int> lis(N, 0), lds(N, 0);

		// Find LIS
		for (int i = 1; i < N; i++) {
			for (int j = i - 1; j >= 0; j--) {
				if ((nums[j] < nums[i]) && (1 + lis[j] > lis[i])) {
					lis[i] = 1 + lis[j];
				}
			}
		}

		// Find LDS
		for (int i = N - 2; i >= 0; i--) {
			for (int j = i + 1; j < N; j++) {
				if ((nums[j] < nums[i]) && (1 + lds[j] > lds[i])) {
					lds[i] = 1 + lds[j];
				}
			}
		}

		// get MaxBitonicSub Length
		int maxBitonicSub = 0;
		for (int i = 0; i < N; i++) {
			if (lis[i] > 0 && lds[i] > 0) {
				maxBitonicSub = max(maxBitonicSub, lis[i] + lds[i] + 1);	// +1 (nums[i], should be present atleast one time)
			}
		}

		return maxBitonicSub;
	}
};
