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

Question : 140. Word Break II
Topic : Trie
Problems : https://leetcode.com/problems/word-break-ii/description/?envType=problem-list-v2&envId=trie

==============================> Explanation <=============================================

Given the wordDict and stuff to match strings... need to think about Trie.

As usual, create trie out of wordDict to we can match multiple words at a same time....

Here Idea is simple,

	We compare both string_index and trie_node, if we get match we move to the next index and node.

	If we don't get match we stop there, because required matching is not forming...

	In case, we reach end of word in trie....

		1) we can extract that word, and again start to find new word in trie from the start...

		2) or we can ignore it and try to get another longer word in trie path..

Check the code!



==============================> Approach and Time Complexity <============================

1) Trie
K = avg length of String
Time: O(2^M), M size of given string.... 2 is breadth two call happeing....
Space: O(16^K)

*/


struct Node {

	Node* links[26];
	bool endOfWord = false;

	Node* get(char ch) {
		return links[ch - 'a'];
	}

	void put(char ch, Node* node) {
		links[ch - 'a'] = node;
	}

	bool contains(char ch) {
		return links[ch - 'a'] != NULL;
	}

	void markEndOfWord() {
		endOfWord = true;
	}

	bool isEndofWord() {
		return endOfWord;
	}
};


class Solution {

public:

	string SPACE = " ";

	Node* root;

	vector<string> answer;

	Solution() {
		root = new Node();
	}

	void matchWord(string s, int index, Node* node, string cur, vector<string> &sen) {

		if (index == s.size() || node == NULL) {
			return;
		}

		if (!node->contains(s[index]))
			return;

		char ch = s[index];
		cur += ch;
		Node* nextNode = node->get(ch);

		if (nextNode->isEndofWord()) {
			sen.push_back(cur);

			// reached end of word
			if (index + 1 == s.size()) {
				string sentance = constructSentance(sen);
				answer.push_back(sentance);
			}
			else {
				matchWord(s, index + 1, root, "", sen);
			}

			// backtracking
			sen.pop_back();
		}

		matchWord(s, index + 1, nextNode, cur, sen);

		// backtracking
		cur.pop_back();
	}


	vector<string> wordBreak(string s, vector<string>& wordDict) {

		// insert into the trie
		for (string word : wordDict) {
			insert(word);
		}


		Node* node = root;
		string cur = "";
		vector<string> sen;

		matchWord(s, 0, node, cur, sen);

		return answer;
	}

private:

	string constructSentance(vector<string> words) {
		string res = "";
		for (string word : words) {
			res += word + SPACE;
		}
		// removed last extra space.
		res.pop_back();
		return res;
	}

	void insert(string word) {
		Node* node = root;
		for (char ch : word) {
			if (!node->contains(ch)) {
				node->put(ch, new Node());
			}
			node = node->get(ch);
		}
		node->markEndOfWord();
	}
};


// Same Approach Writting in other style

struct Node {

	Node* links[26];
	bool endOfWord = false;

	void put(char ch, Node* node) {
		links[ch - 'a'] = node;
	}

	Node* get(char ch) {
		return links[ch - 'a'];
	}

	bool contains(char ch) {
		return links[ch - 'a'] != NULL;
	}

	void setEndOfWord() {
		endOfWord = true;
	}

	bool isEndOfWord() {
		return endOfWord;
	}
};


class Solution {

public:

	Solution() {
		root = new Node();
	}

	void findWord(string s, vector<string> &words, vector<vector<string>> &sentance) {

		Node* node = root;
		int i;

		for (i = 0; i < s.size(); i++) {

			// found word
			if (node->isEndOfWord()) {

				// s.substr(0, i) => extract the matched word.
				words.push_back(s.substr(0, i));

				findWord(s.substr(i), words, sentance);

				// backtrack
				words.pop_back();
			}

			if (!node->contains(s[i])) {
				break;
			}

			node = node->get(s[i]);
		}

		// running for lop, one more time.... to check last remaining string...
		if (node->isEndOfWord() && i == s.size()) {
			words.push_back(s);
			sentance.push_back(words);
			words.pop_back();
		}
	}



	vector<string> wordBreak(string s, vector<string>& wordDict) {

		for (string word : wordDict) {
			insert(word);
		}

		// store separate word
		vector<string> words;

		// store list of words
		vector<vector<string>> sentances;

		findWord(s, words, sentances);


		vector<string> ans;

		for (auto sentance : sentances) {

			string sentanceWithSpace;

			for (int i = 0; i < sentance.size(); i++) {

				sentanceWithSpace += sentance[i];

				if (i != sentance.size() - 1) {

					sentanceWithSpace += ' ';
				}
			}

			ans.push_back(sentanceWithSpace);
		}

		return ans;
	}

private:

	Node* root;

	void insert(string word) {
		Node* node = root;
		for (char ch : word) {
			if (!node->contains(ch)) {
				node->put(ch, new Node());
			}
			node = node->get(ch);
		}
		node->setEndOfWord();
	}
};