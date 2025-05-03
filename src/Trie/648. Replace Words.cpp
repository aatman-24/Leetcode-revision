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

Question : 648. Replace Words
Topic : Trie
Problems : https://leetcode.com/problems/replace-words/?envType=problem-list-v2


==============================> Explanation <=============================================

It is strightforward, given the dictionary of prefix, we can create the trie out of it.

And after that we can break the sentance, with spliter = " "..... so we have word...

then we try to find the smallest prefix of that word into the trie, in trie when we get
the match and node->isEndOfWord()....we build up that prefix(we need to build it up by using
curString)..... and that's our result.....

=> time: O(N*K) => total words * matching word, here we don't need to match for each of dict word, as it is
already populate into the trie..

(I don't code it, because it is same as other )



If we don't got any match then we use the exact word as it is.

Brute-Force: We can directly compare the word with each of dictionary word, and if there is
match we consider it, but still we continue to explore to get the smallest prefix result..
we can even sort the dict in terms of word length as well. => O(N*M*K) => N total words, M = dict size, K = avg word size

==============================> Approach and Time Complexity <============================

1) Trie
Time: O(M*K)
Space: O(26^K)

*/



class Solution {
public:

    bool isMatched(string word, string root) {
        for (int i = 0, j = 0; i < root.size(); i++, j++) {
            if (word[i] != root[j])
                return false;
        }
        return true;
    }


    string replaceWords(vector<string>& dictionary, string sentence) {

        vector<string> ds;
        string word;
        stringstream ss(sentence);
        while (getline(ss, word, ' ')) {
            ds.push_back(word);
            // cout << word << endl;
        }


        for (auto root : dictionary) {   // O(M)
            for (int i = 0; i < ds.size(); i++) { // O(N)
                if (root.size() < ds[i].size() && isMatched(ds[i], root)) { // O(K)
                    ds[i] = root;
                }
            }
        }

        string ans = ds[0];
        for (int i = 1; i < ds.size() ; i++) {
            ans += ' ' + ds[i];
        }

        return ans;
    }
};