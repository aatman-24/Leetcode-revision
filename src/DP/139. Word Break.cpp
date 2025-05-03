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

Question : 139. Word Break
Topic : 1D-DP, Trie
Problems : https://leetcode.com/problems/word-break/description/?envType=problem-list-v2&envId=trie

==============================> Explanation <=============================================

Given that string "s" and couple of other words in dict.... we need to check whether we can break
given string "s" into such way that.... all substring are part of that dictonary....
OR in other word... using the dict words we can segment the given string "s". we are allowed to use
same dict word anytimes...

Idea is that....

we can put cut in given string "s" at any index "j", and then we can check substring s[i...j] is one of word,
and if it is then we need to solve the subproblem s[j+1...N]...

OR we can do reverse as well... but let's stick to one direction only here....

So it is dp questions.... because we put the cut at any index...and result is dependent on the subproblem...

Go through the code.. and you understand...


Optimization(imp) with trie, But not best than what we have written:

- So In the code we have used unordered_set to store the words... which basically check word is there in O(1) time..

So if we are not allowed to use unordered_set or unordered_map then we might use the array... so we need to check given s[i:j] for
each of dictword.... if total N word and avg length of word is M => O(N*M) time will be taken to just compare s[i:J].....

Insted if we create the trie..... using that dict..... then we check if s[i:j] is inside the dict in O(M) time... only...

So we optimized O(N*M) => O(M) (which is great).

==============================> Approach and Time Complexity <============================

1) DP
Time: O(2^N) -> O(N^2)
Space: O(N)

*/



// backtracking - brute force [directon (0 -> N)]       // depth => N, size of "s", breadth => 2 (making cut or not)
class Solution {
public:

    bool wordBreak(int startWith, string &s, unordered_set<string> &st) {

        // base case... reached the end of string....
        if (j == s.size())
            return true;

        for (int j = startWith; j < s.size(); j++) {

            int len = j - startWith + 1;
            string word = s.substr(startWith, len);

            if (st.count(word)) {
                if (wordBreak(j + 1, s, st)) {
                    return true;
                }
            }
        }

        return false;
    }

    bool wordBreak(string s, vector<string>& wordDict) {

        // remove duplicat word + O(logN) search time....
        unordered_set<string> st;
        for (string word : wordDict) {
            st.insert(word);
        }

        return wordBreak(0, s, st);
    }
};

// memorization     [directon (0 -> N)]         // O(N^2)
class Solution {
public:

    int t[1001];

    bool wordBreak(int i, string &s, unordered_set<string> &st) {

        // base case... reached the end of string....
        if (i == s.size())
            return true;

        if (t[i] != -1)
            return t[i];

        for (int j = i; j < s.size(); j++) {

            int len = j - i + 1;
            string word = s.substr(i, len);

            if (st.count(word)) {
                if (wordBreak(j + 1, s, st)) {
                    return t[j + 1] = 1;
                }
            }
        }

        return t[i] = 0;
    }

    bool wordBreak(string s, vector<string>& wordDict) {

        memset(t, -1, sizeof(t));

        // remove duplicat word + O(logN) search time....
        unordered_set<string> st;
        for (string word : wordDict) {
            st.insert(word);
        }


        // t[i] => indicate s[i....s.size()] can be segmented or not.

        return wordBreak(0, s, st);
    }
};


// bottom-up
// In simple word, to check S[i...N] can be segmented or not... we need to check
// 1) s[i...j](word is inside dict) + dp[j...N](is segmented).... then we can mark dp[i] = 1(=> s[i...N] is also segmented.)
class Solution {
public:

    bool wordBreak(string s, vector<string>& wordDict) {

        // remove duplicat word + O(logN) search time....
        unordered_set<string> st;
        for (string word : wordDict) {
            st.insert(word);
        }

        vector<int> dp(s.size() + 1, 0);


        // base case
        dp[s.size()] = 1;


        for (int i = s.size() - 1; i >= 0; i--) {

            for (int j = i; j < s.size(); j++) {

                int len = j - i + 1;

                string word = s.substr(i, len);

                if (st.count(word)) {

                    // S[j+1, N] => can be segmented......
                    if (dp[j + 1]) {

                        dp[i] = 1;

                        break;
                    }
                }
            }
        }

        return dp[0];
    }
};


// Reverse manner
// In simple word, to check S[i...N] can be segmented or not... we need to check
// 1) dp[0...j](is segmented) + s[j...i](word is inside dict).... then we can mark dp[i] = 1(=> s[0...i] is also segmented.)
class Solution {
public:

    bool wordBreak(string s, vector<string>& wordDict) {

        // remove duplicat word + O(logN) search time....
        unordered_set<string> st;
        for (string word : wordDict) {
            st.insert(word);
        }

        vector<int> dp(s.size() + 1, 0);


        // base case
        dp[0] = 1;


        for (int i = 1; i <= s.size(); i++) {

            for (int j = i - 1; j >= 0; j--) {

                int len = i - j;

                string word = s.substr(j, len);

                if (st.count(word)) {

                    // S[0, j] => can be segmented......
                    if (dp[j]) {

                        dp[i] = 1;

                        break;
                    }
                }
            }
        }

        return dp[s.size()];
    }
};

