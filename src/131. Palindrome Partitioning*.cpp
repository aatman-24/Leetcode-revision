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

Question : 131. Palindrome Partitioning*
Topic : Backtracking
Problems : https://leetcode.com/problems/palindrome-partitioning/description/
==============================> Explanation <=============================================


We can apply the bruteforce apporach with backtracking... It is very clear that we need to make the cut at every possible place(simliar to generate all subsets).

- We try to make partition at every index(BFS). If left side of part is palindrome
then we go to the depth(DFS) and check for the right side(remaining string) until we reached the end of the
string. If we reached end of string... we found palindrome set. Reason is that, we are not considering any substr which are not palindrome, in short we are jumping to
(i+1) index if we are able to find (startIndex,i) as palindrome.

And by doing that, if we reached EOS, It means we found set.

- BFS make partition from (index, endOfString) and DFS go to the depth if is possible.

- Make tree and visualzie it.

Time = O(2^N)(Try out every index partition)(Just same as subset problem) * O(N^2)(For Loop + _isPalindrome)
Space = O(N)(Path) + O(N)(Aux)



==============================> Approach and Time Complexity <============================

1) Backtracking
Time: O(N * 2^N)
Space: O(N) (stack space) + O(2^N) (to hold the result)

Formula => processing_time_for_each_node * (breadth^depth)
Space => (maximum_depth)(stack space)

It is similar to generate all subsets... either we are making cut at ith index(picking up ith element) if it is palindrome or not.
Each node have two subnodes when left part is palindrome.

Depth => N.
Breadth => 2
processing_time_for_each_node => O(N) (in worst case).

Time = O(N * 2^N)
Space = O(2^N) (to hold the result)


 */


// 131. Palindrome Partitioning
class Solution {
public:

	// store the result.
	vector<vector<string>> ans;

	// Will take O(len(s)) to check.
	bool isPalindrome(string s, int start, int end) {
		while (start <= end) {
			if (s[start] != s[end]) {
				return false;
			}
			start++; end--;
		}
		return true;
	}

	void helper(string s, int startIndex, vector<string> palindromeSubset) {

		// If reached here, it means we are able to parition the string "s" into palindrome subset.
		// Reason is that, we are moving to (i+1) index only if found palindrome substr from (startIndex, i)
		// Reaching here... indicate found set of palindrome substrings from (0, s.size())
		if (startIndex >= s.size()) {
			ans.push_back(palindromeSubset)
			return;
		}

		for (int i = startIndex; i < s.size(); i++) {

			//  check (startIndex, i) length substr is palindrome or not.
			if (isPalindrome(s, startIndex, i)) {

				// yes, get substr
				string substr = s.substr(startIndex, (i - startIndex + 1));

				// put in set
				palindromeSubset.push_back(substr);

				// find palindromeSubset for remaining (i+1, s.size()) string
				helper(s, i + 1, palindromeSubset);

				// bactrack
				palindromeSubset.pop_back();
			}
		}
	}


	vector<vector<string>> partition(string s) {
		vector<string> palindromeSubset;
		helper(s, 0, palindromeSubset);
		return ans;
	}
};