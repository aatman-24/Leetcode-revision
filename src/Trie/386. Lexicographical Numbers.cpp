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

Question : 386. Lexicographical Numbers
Topic :
Problems : https://leetcode.com/problems/lexicographical-numbers/description/?envType=problem-list-v2&envId=trie

==============================> Explanation <=============================================

Given that we have to generate the numbers in lexo order, we need to think in
direction of DFS... because with DFS we explore the depth first which is exactly what
we need.

Idea is clear, we can create Trie for each of the number, and then traverse trie in
inorder manner, where we apply DFS on Trie.... (check the code).

Other option we have is, we can directly apply the DFS to generate the numbers,
and if num > limit, then we stop going more into the depth.... which is quite easy
and intutitive. (check the code).

==============================> Approach and Time Complexity <============================

Given 1 <= n <= 5 * 10^4, K = 4.......

1) Trie
Time: O(10^K)
Space: O(10^K) (K  = length of number)

2) DFS
Time: O(N) (Visit the required node only)
Speace: O(K) (K  = length of number)

*/


struct Node {

	// node from (0 -> 9)
	Node* links[10];

	bool endOfWord = false;

	void put(char ch, Node* node) {
		links[ch - '0'] = node;
	}

	bool contains(char ch) {
		return links[ch - '0'] != NULL;
	}

	Node* get(char ch) {
		return links[ch - '0'];
	}

	void markAsEndOfWord() {
		endOfWord = true;
	}

	bool isEndOfWord() {
		return endOfWord;
	}

};



class Solution {

public:

	Node* root;

	Solution() {
		root = new Node();
	}

	void inorderTraversal(Node* node, string &curNum, vector<int> &lexOrder) {

		if (node == NULL)
			return;

		// found number, convert it into the integer
		if (node->isEndOfWord()) {
			lexOrder.push_back(convertToNumber(curNum));
		}

		// start looking for next number, by exploring its children...
		for (char ch = '0'; ch <= '9'; ch++) {

			if (node->contains(ch)) {

				curNum += ch;

				inorderTraversal(node->get(ch), curNum, lexOrder);

				// backtrack
				curNum.pop_back();
			}
		}
	}

	vector<int> lexicalOrder(int n) {

		// create a trie
		for (int i = 1; i <= n; i++) {
			insert(to_string(i));
		}

		vector<int> lexOrder;

		string curNum = "";

		inorderTraversal(root, curNum, lexOrder);

		return lexOrder;
	}


private:

	void insert(string word) {
		Node* node = root;
		for (char ch : word) {
			if (!node->contains(ch)) {
				node->put(ch, new Node());
			}
			node = node->get(ch);
		}
		node->markAsEndOfWord();
	}


	int convertToNumber(string num) {

		int result = 0, n = num.size();

		for (int i = 0; i < n; i++) {

			result += pow(10, (n - i - 1)) * int(num[i] - '0');
		}

		return result;
	}
};


// simple DFS
class Solution {

public:

	void dfs(int num, int limit, vector<int> &result) {

		if (num > limit) return;

		result.push_back(num);

		// from the second character, we can pick any character from (0, 9)
		for (int i = 0; i <= 9; i++) {

			int nextNum = num * 10 + i;

			// optimization, if "111" is not soultion then "112", "113".... any of this number
			// cannot be our answer, so we break the for loop instead of checking every nubmer.
			if (nextNum > limit) break;

			dfs(nextNum, limit, result);
		}
	}

	vector<int> lexicalOrder(int n) {

		vector<int> lexOrder;

		// number can be start from (1, 9) only, not from "0".
		for (int curNum = 1; curNum <= 9; curNum++) {

			dfs(curNum, n, lexOrder);

		}

		return lexOrder;
	}

};