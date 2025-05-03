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

Question : 421. Maximum XOR of Two Numbers in an Array
Topic : Trie, Bitset
Problems : https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/description/?envType=problem-list-v2&envId=trie

==============================> Explanation <=============================================

Not easy to pick it up, but you need to remember this bitset+Trie pattern as well.

So given that you have to find maximum XOR of two numbers, nums[i] and nums[j] such that nums[i] ^ nums[j] is maximum

Brute force: Iterate over two for loops, and keep track of maximum XOR. you can get this in O(N^2).

Core Idea:
To maximize the XOR between two numbers, we want their bits to differ as much as possible, especially at the higher (leftmost) bits.

Strategy:
Insert all numbers into a Trie (based on their binary representation).

For each number, try to find the number in the Trie that gives the maximum XOR with it.

At each bit position:

If the current bit is 1, we look for 0 in the Trie (and vice versa) to get a 1 in XOR.

If the opposite bit exists in the Trie, we move in that direction and set this bit in the result.

If not, we follow the path with the same bit and move on.

Bit Importance:
We start checking from the most significant bit (leftmost) to the least significant bit (rightmost).

This ensures that we prioritize setting higher weighted bits first.

Note on Bitset Indexing:
In bitset, bt[0] refers to the least significant bit (LSB).

For example:

std::bitset<6>(5) gives 000101, where:

bt[0] = 1 (LSB)

bt[5] = 0 (MSB)








==============================> Approach and Time Complexity <============================

1) Trie
Time: O(NLogN)
Space: O(N)

*/

struct Node {

	Node* links[2];

	void put(int i, Node* node) {
		links[i] = node;
	}

	bool contains(int i) {
		return links[i] != NULL;
	}

	Node* get(int i) {
		return links[i];
	}

};


class Solution {

public:

	Node* root;

	Solution() {
		root = new Node();
	}

	int findMaximumXOR(vector<int>& nums) {

		// insert every number into the trie
		for (int num : nums) {
			insertIntoTrie(num);
		}

		int maxi = INT_MIN;

		// get relevant maximum for each number and choose maximum among them.
		for (int num : nums) {
			maxi = max(maxi, getRelevantXORMaximum(num));
		}

		return maxi;
	}


private:

	// heart of the solution
	int getRelevantXORMaximum(int num) {

		int maxi = 0;

		bitset<32> bt(num);

		Node* node = root;

		for (int i = 31; i >= 0; i--) {

			// if node contains opposite bit, then we are going to pick it up, becasue 1^0 = 1, 0^1 = 1
			if (node->contains(!bt[i])) {

				node = node->get(!bt[i]);

				maxi = maxi | (1 << i); // set the ith bit in answer.

			}

			// otherwise we choose same element (1^1 = 0) || (0^0 = 0) so we dont set that bit as well.
			else {

				node = node->get(bt[i]);
			}
		}

		return maxi;
	}

	// convert into the bitset and then add it into the trie...
	void insertIntoTrie(int num) {

		bitset<32> bt(num);

		Node* node = root;

		for (int i = 31; i >= 0; i--) {

			if (!node->contains(bt[i])) {
				node->put(bt[i], new Node());
			}

			node = node->get(bt[i]);
		}
	}

};