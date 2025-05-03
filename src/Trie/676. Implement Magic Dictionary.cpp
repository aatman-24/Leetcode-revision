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

Question : 676. Implement Magic Dictionary
Topic : Trie
Problems : https://leetcode.com/problems/implement-magic-dictionary/description/?envType=problem-list-v2&envId=trie


==============================> Explanation <=============================================

Stnadard question, with some trick....

we earlier see... in trie how we can accept the wildcard "." which match with any character
and still we can compare the rest of string.

This question is little tricker of that question... Here given that.... to match any word in
dict.... we must have one character mismatch (if two word match exactly then it is not matching)..

so that logic we have to encorporate....

Idea is that... at each s[i]... we try all characters "a" to "z"...to create mismatch...

Note: Keep in mind...if s[i] is not matching with node....only then time mismatch is happen...that's
wrong assumption... we need to check each of s[i] with mismatch condition... check the code...


==============================> Approach and Time Complexity <============================

1) Trie
Time: O(M*K)
Space: O(26^K)

*/


// Trie Node
struct Node {

	Node* links[26];

	bool endOfWord = false;

	Node* get(char ch) {
		return links[ch - 'a'];
	}

	void put(char ch, Node* node) {
		links[ch - 'a'] = node;
	}

	void markEndOfWord() {
		endOfWord = true;
	}

	bool contains(char ch) {
		return links[ch - 'a'] != NULL;
	}

	bool isEndOfWord() {
		return endOfWord;
	}
};



class MagicDictionary {
public:

	Node* root;

	MagicDictionary() {
		root = new Node();
	}

	void buildDict(vector<string> dictionary) {
		for (string word : dictionary) {
			insertWord(word);
		}

	}


	// heart of problem
	// we need atleast one mismatch, if entire string is matching then it is not matched.
	// so what we are gonna do is, for each s[i] we try to create mismatch if allowed(earlier not used)
	// and see if get the rest of word match or not.
	bool searchSupport(string s, int index, Node* node, bool allowedOnce) {

		if (node == NULL)
			return false;

		for (int i = index; i < s.size(); i++) {

			// if mismatch allowed
			if (allowedOnce) {

				// try all char from 'a' to 'z'
				for (char p = 'a'; p <= 'z'; p++) {

					// if s[i] == p, then s[i] is same, so we allowed one mismatch
					if (searchSupport(s, i + 1, node->get(p), s[i] == p)) {
						return true;
					}
				}

				// not able to find any word, after exploring all possible ways
				return false;
			}

			if (!node->contains(s[i]))
				return false;

			node = node->get(s[i]);
		}

		// we check.... atleast one mismatch and reached end of word
		if (node != NULL && !allowedOnce && node->isEndOfWord())
			return true;

		return false;
	}


	bool search(string searchWord) {
		return searchSupport(searchWord, 0, root, true);
	}



private:

	void insertWord(string word) {
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

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary* obj = new MagicDictionary();
 * obj->buildDict(dictionary);
 * bool param_2 = obj->search(searchWord);
 */
