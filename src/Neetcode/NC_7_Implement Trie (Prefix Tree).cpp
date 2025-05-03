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

Question : NC_7_Implement Trie (Prefix Tree)
Topic : Trie
Problems : https://neetcode.io/problems/implement-prefix-tree

==============================> Explanation <=============================================

Trie is data structure which is mainly used to match prefix or some overlapped words in
efficient manner, basically at each node have 26 children, which is map by
next character of word. Go through the code, easy to understand!

==============================> Approach and Time Complexity <============================

1) PQ
Time: O(NLogN)
Space: O(N)

*/

struct Node {

    Node* links[26];

    bool flag = false;  // indicate the end of word

    bool containsKey(char ch) {
        return links[ch - 'a'] != NULL;
    }

    Node* get(char ch) {
        return links[ch - 'a'];
    }

    void put(char ch, Node* node) {
        links[ch - 'a'] = node;
    }

    void setEndOfWord() {
        flag = true;
    }

    bool isEndOfWord() {
        return flag;
    }
};


class PrefixTree {

public:

    Node* root;

    PrefixTree() {
        root = new Node();
    }

    void insert(string word) {
        Node* node = root;
        for (char ch : word) {
            // if not found "ch", insert it
            if (!node->containsKey(ch)) {
                node->put(ch, new Node());
            }
            node = node->get(ch);
        }
        node->setEndOfWord();
    }



    bool search(string word) {
        Node* node = root;
        for (char ch : word) {
            // "ch" not found, break of word, return false
            if (!node->containsKey(ch)) {
                return false;
            }
            node = node->get(ch);
        }

        // if entire word matched, then EOW must be true.
        return node->isEndOfWord();
    }



    bool startsWith(string prefix) {
        Node* node = root;
        for (char ch : prefix) {
            if (!node->containsKey(ch)) {
                return false;
            }
            node = node->get(ch);
        }
        return true;
    }
};
