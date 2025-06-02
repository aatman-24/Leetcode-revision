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

Question : NC_15_Jump Game II
Topic : Trie
Problems : https://neetcode.io/problems/jump-game-ii

==============================> Explanation <=============================================

DP: It's direct, we use the top down approach, we try all approach and use the intermidatory
result if required......

Greedy: We use the BFS here to explore all the nodes(index). We maintain leftBoundary and rightBoundary....
in between nodes can be visited to get the maximumJump, and each time we take maximumJump only.

whenever we take jump we reassing this boundary,

leftBoundary = rightBoundary + 1 (bcz from [l,r] we can reach, so next we want to reach from r + 1)
rightBoundary = furthest points we get last time

==============================> Approach and Time Complexity <============================

1) Trie
Time: O(M*K)
Space: O(26^K)

*/



// Top-down

class Solution {
public:

	int MAX = 1e6;

	int t[1001];

	int support(vector<int> &nums, int index) {

		if (index >= nums.size() - 1) return 0;

		if (t[index] != -1) return t[index];

		int minJump = MAX;

		for (int jump = 1; jump <= nums[index]; jump++) {

			minJump = min(minJump, support(nums, index + jump) + 1);
		}

		return t[index] = minJump;
	}


	int jump(vector<int>& nums) {
		memset(t, -1, sizeof(t));
		return support(nums, 0);
	}
};


// BFS, with using two pointer

class Solution {
public:
	int jump(vector<int>& nums) {

		int res = 0, l = 0, r = 0;

		while (r < nums.size() - 1) {

			// calcualte the farthest point from (l, r)
			int farthest = 0;
			for (int i = l; i <= r; i++) {
				farthest = max(farthest, i + nums[i]);
			}

			// update the pointer
			// already we can reach (l, r) with "res" jump, so next we want to start from r+1.
			l = r + 1;

			// farthest points we can reach from previous range (l, r)
			r = farthest;

			// added jump
			res++;
		}
		return res;
	}
};