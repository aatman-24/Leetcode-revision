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

Question : NC_9_Word Search II
Topic : Trie
Problems : https://neetcode.io/problems/search-for-word-ii

==============================> Explanation <=============================================

Brute force: This is very straight forwad, we pick up one word each time, and try to match
that in the given matrix with starting at every position (i, j), and then we use the dfs() do that,
if we reach the end of word, it means we found entire word.

Trie:
First you need to understand how Trie fit inside this problem...

We create trie out of given words, yes it is reverse but it make sense.... see!

we actually start every (i, j) and match that character with currNode of trie... if its match...
then next char of trie should match neighbors of (i, j)... which we are checking through dfs....
and if we reach the node which indicatig end of word then we found entire word....(check the code)..

Tries is helping us to match multiple words at the same time.... which is comes under optimization...

ex:

batball
batman

trie: b -> a -> t -> b -> a -> l -> l
                  -> m -> a -> n

when we reach at node(t) that time (i, j) is matching with "t".... okay...

now we need to check if its(i, j) neighbors if match
nextNode "b" or "m".... it means we are checking multiple words at same time...


==============================> Approach and Time Complexity <============================


1) Brute Forece
M => total words...
K => avg word length
board size => N^2
Time: O(M) * O((N^2)*K)(breadth^depth)
Space: O(N^2)

2) Trie
M => Total Words
K => Avg word length
board size => N^2

Time: O(N^2*K) => At each (i, j)... you can have maximum depth O(K)
Space: O(26^K)

*/


// Brute Force: TLE
class Solution {
public:

    int dx[4] = { -1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    bool dfs(vector<vector<char>>& board, int x, int y, string word, int idx, vector<vector<int>> &visited) {

        // current character is matching with (x, y) or not....
        if (board[x][y] != word[idx])
            return false;

        // mathcing && reached end of word, return true.
        if (idx == word.size())
            return true;

        // mark visited
        visited[x][y] = 1;

        for (int k = 0; k < 4; k++) {

            int xx = x + dx[k];
            int yy = y + dy[k];

            if (xx < 0 || yy < 0 || xx >= board.size() || yy >= board[0].size() || visited[xx][yy])
                continue;

            if (dfs(board, xx, yy, word, idx + 1, visited))
                return true;

        }

        // unmark, backtracking
        visited[x][y] = 0;

        return false;
    }



    bool isAvailableOnBoard(vector<vector<char>>& board, string word) {

        int m = board.size(), n = board[0].size();

        vector<vector<int>> visited(m, vector<int>(n, 0));

        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {

                // start to match word with (i, j)
                if (dfs(board, i, j, word, 0, visited)) {
                    return true;
                }
            }
        }

        return false;
    }



    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {

        vector<string> matchedWords;

        for (string word : words) {
            if (isAvailableOnBoard(board, word)) {
                matchedWords.push_back(word);
            }
        }

        return matchedWords;
    }
};



// Approach: Trie

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

    void markEndOfWord() {
        endOfWord = true;
    }

    bool isEndOfWord() {
        return endOfWord;
    }

};



class Solution {

public:

    Node* root;

    int dx[4] = { -1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    Solution() {
        root = new Node();
    }


    void dfs(vector<vector<char>>& board, int x, int y, Node* node, string currWord, unordered_set<string> &result) {

        // don't able to reach end of word, so no chance we can match any word.
        if (node == NULL)
            return;

        if (!node->contains(board[x][y]))
            return;

        char ch = board[x][y];

        currWord += ch;

        board[x][y] = 'V'; // marked as visited

        Node* nextNode = node->get(ch);

        if (nextNode->isEndOfWord()) {
            result.insert(currWord);
        }

        for (int k = 0; k < 4; k++) {

            int xx = x + dx[k];
            int yy = y + dy[k];

            if (xx < 0 || yy < 0 || xx >= board.size() || yy >= board[0].size() || board[xx][yy] == 'V')
                continue;

            dfs(board, xx, yy, nextNode, currWord, result);
        }


        // backtrack
        board[x][y] = ch;

    }


    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {

        // 1. insert every words into the trie.
        for (string word : words) {
            insertIntoTrie(word);
        }


        // 2. Start with each (i, j) and check if any of word is matching, when its first character
        // match (i, j) position and reached end of word through trie.

        // store the answer inside this.
        unordered_set<string> result;

        string currWord = "";

        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                dfs(board, i, j, root, currWord, result);
            }
        }


        return vector<string>(result.begin(), result.end());
    }


private:

    void insertIntoTrie(string word) {

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