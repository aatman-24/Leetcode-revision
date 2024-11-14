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

Question : 1048. Longest String Chain
Topic : DP-LIS
Problems : https://leetcode.com/problems/longest-string-chain/description/
==============================> Explanation <=============================================

Pattern: LIS

Given words of different length we need to make longest chain by connecting
predecessor of words. Predecessor is word, which has 1 character less/missing from next string, but
order of characters should be maintained.

Basically, they ask to create longest chain by following this predecessor logic, which is
very similar to LIS logic.

LIS => nums[j] < nums[i] && (1 + lis[j] < lis[i])
Here => isPrdecessor(nums[j], nums[i]) && (1 + lis[j] < lis[i])

Basically, we try to extend all chain which was ended at "jth" index, by joining "ith" index.

#1: Standard LIS
Bottom-up is quite easy, applied directly that one. Just check the isPredecessor() logic.
Apart from that it is same as LIS. We have sorted the given words in terms of length, because
we want predecessor(less length) words are visited first.
Time: O(N^2) * O(16)(for comparsion of two string)


#2: Tricking LIS
Instead of directly joining the two string with Predecessor logic. One thing we can do is,
We can sort the given words in terms of length.

Order of visiting words be like: 1_length_word |2_len_word |3_len_word

And we also know that.... 1_len_word can be predecessor of 2_len_word only...

So we can apply that logic.

There is word = ac

There is next word of length 3 = bac => b + ac(above word)

"ac" is predecessor of "bac".

So, what we do is, we elimiate the one of single character from string "s".
And check whatever string left is already visited or not, if "yes" then that
string is predecessor of this "s". We don't know which character we need to drop
so we drop one by one and check by doing that.... we can get predecessor by O(16),
instead of O(N).

Also maintain one map which is LIS. Which tell which last added string and its length of chain.

Time => O(N*16)

Check the code!!

==============================> Approach and Time Complexity <============================



1) DP
Time: O(N^2*16) => O(16*N)
Space: O(N)

 */

// Direct Applying LIS Time: (N^2*L)
/* Intution:
	Bottom-up is quite easy, applied directly that one. Just check the isPredecessor() logic.
	Apart from that it is same as LIS. We have sorted the given words in terms of length, because
	we want predecessor(less length) words are visited first.
	Time: O(N^2) * O(16)(for comparsion of two string)
*/
class Solution {
public:

	static bool compartor(string a, string b) {
		return a.size() < b.size():
		}

		// Check if string "b" can be predecssor of string "a".
		// Logic is that: If both string length is differ by 1...
		// Will compare each character one by one, allow one mismatch, if second mismatch encounter return false.
		bool isPredecessor(string a, string b) {

		// check size first, must be differ by "1".
		if (a.size() - b.size() != 1) return false;

		// check relative position.
		int i = 0, j = 0;

		bool allowoneMismatch = true;

		while (i < a.size()) {

			if (a[i] == b[j]) {
				i++; j++;
			}
			else if (allowoneMismatch) {
				i++;
				allowoneMismatch = false;
			}
			else {
				return false;
			}
		}

		return true;
	}

	int longestStrChain(vector<string>& words) {

		int N = words.size();

		vector<int> lis(N, 1);

		sort(words.begin(), words.end(), compartor);

		int maxChain = 1;

		for (int i = 1; i < N; i++) {

			for (int j = i - 1; j >= 0; j--) {

				if (isPredecessor(words[i], words[j]) && (1 + lis[j] > lis[i])) {
					lis[i] = 1 + lis[j];
				}

				maxChain = max(maxChain, lis[i]);
			}
		}

		return maxChain;
	}
};


// Applying LIS in different way, so we can reduce that mathching alogrithm.
/* Intution:
   Idea is that, (L-1) length words will be visited first, compare to L length words.
   So when we visit the L length words, we can make it (L-1) by drooping one of its characer,
   and then we can find in alreday visited (L-1) words, to find it predecessory, If we get it
   then we extend that chain by updating LIS_map.
*/
class Solution {
public:

	static bool compartor(string a, string b) {
		return a.size() < b.size();
	}

	int longestStrChain(vector<string>& words) {

		int N = words.size();

		unordered_map<string, int> dp;

		sort(words.begin(), words.end(), compartor);

		int maxChain = 1;

		for (string w : words) {

			// Each word can create atleast 1 size of chain. (base case)
			dp[w] = 1;

			for (int i = 0; i < w.length(); i++) {

				// break the word, by removing "ith" character, so we can check in map
				// if such predecessor is already visited or not, if yes, then we can extend it more.
				string pre = w.substr(0, i) + w.substr(i + 1);

				// found predecessor, extend it.
				if (dp.count(pre)) {
					dp[w] = max(dp[w], dp[pre] + 1);
				}

			}

			maxChain = max(maxChain, dp[w]);
		}

		return maxChain;
	}
};
