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

Question :  NC_8_Design Add and Search Word Data Structure
Topic : Trie
Problems : https://neetcode.io/problems/design-word-search-data-structure

==============================> Explanation <=============================================

Standard Trie question, with little trick.

So during the matching if we get the '.' that time... we try to match "." with all childrens(a-z) one by one, which have set...
(it means we just skip that node.... and try to resume matching from the next character)

Ex: Trie => A->B->C->D.... word = "AB.D" => when we reach B that time we see all the path from B... which is here B -> C....
it means "C" is matched with wildcard "."... so skip that node... and resume the matching from next character which is "D".

But we need to check for all children of that node, because we don't know which children mathching is right.


==============================> Approach and Time Complexity <============================

1) Trie
Time: Search: O(26N), Insert: O(N)
Space: O(N^26)

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

    bool isEndofWord() {
        return endOfWord;
    }
};





class WordDictionary {
public:

    Node* root;

    WordDictionary() {
        root = new Node();
    }

    void addWord(string word) {
        Node* node = root;
        for (char ch : word) {
            if (!node->contains(ch)) {
                node->put(ch, new Node());
            }
            node = node->get(ch);
        }
        node->markEndOfWord();
    }

    bool search(string word) {
        return searchHelper(word, root);
    }

    bool searchHelper(string word, Node* node) {

        for (int i = 0; i < word.size(); i++) {

            char ch = word[i];

            // If wildcard.... we match with all children which are from "a" -> "z"..
            if (ch == '.') {
                for (char ch = 'a'; ch <= 'z'; ch++) {

                    // if node has specific child... it means "." with that children...
                    // so we check for rest of word by skipping that node and if rest of word match then we return true.
                    if (node->contains(ch) && searchHelper(word.substr(i + 1), node->get(ch))) {
                        return true;
                    }
                }

                // if "." does not meet the above condition then we should return false.
                return false;
            }
            if (!node->contains(ch))
                return  false;
            node = node->get(ch);
        }

        // at the end we need to check last is marked as end of word or not, to avoid mathching word with prefix.
        return node->isEndofWord();
    }



};
