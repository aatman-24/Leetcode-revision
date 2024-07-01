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

Question : 151. Reverse Words in a String
Topic : String, Pointer, Stack
Problems : https://leetcode.com/problems/reverse-words-in-a-string/

==============================> Explanation <=============================================


1) Brute Force:
- Use some of pointers to break the string and add it in the vector and again build the answer string from the end of vector.

2) Stack Solution:
- Got word reverse, can think of stack. Break the whole string in words..add it in the stack. use it to build answer string.

3) Two Pointer.
- Reverse a whole string
- Find the word in that, make that word reverse again. Fill the word from left side.
- At the end, remove all the space left on right side.



==============================> Approach and Time Complexity <============================

N = nums.size()

1) Brute Force
Time: O(N)
Space: O(N)

2) Stack
Time: O(N)
Space: O(N)

3) Two Pointer:
Time: O(N)
Space: O(1)

*/



class Solution {
public:

    string getWord(string s, int left, int right) {
        string ans = "";
        for (int i = left; i <= right; i++) ans += s[i];
        return ans;
    }

    string reverseWords(string s) {

        int startOfWord = 0;
        int runner = 0;
        int N = s.size();
        vector<string> words;

        while (runner < N) {

            // runner is pointing to character and startOfWord is pointing to space then point that to runner as startOfWord.
            if (s[runner] != ' ') {
                if (s[startOfWord] == ' ') startOfWord = runner;
            }
            else {

                // If runner got on empty space, and startOfWord is not empty space, found word:        A(startOfWord) B C _(runner)
                if (s[startOfWord] != ' ') {
                    words.push_back(getWord(s, startOfWord, runner - 1));
                }
                startOfWord = runner;       // reset startOfWord to get new word.
            }
            runner++;
        }

        // Edge case, if after last word no space then it got skipped. we need to handle this case.
        if (runner == N && s[startOfWord] != ' ') {
            words.push_back(getWord(s, startOfWord, runner - 1));
        }

        string ans = "";
        for (int i = 0; i < words.size(); i++) {
            if (i == words.size() - 1) {
                ans += words[i];
            }
            else {
                ans += words[i] + "";
            }
        }

        return ans;
    }
};


class Solution {
public:

    // O(N) + O(N) [Stack Solution]
    string reverseWords(string s) {

        stack<string> st;
        string tmp, ans;

        for (int i = 0; i <= s.size(); i++) {

            // Add last string whatever it into stack.
            if (i == s.size()) {
                if (tmp.size() > 0) st.push(tmp);
                break;
            }

            // if empty char encounter and tmp.size() > 0 menas some
            // word already made we push into the stack.
            if (s[i] == ' ') {
                if (tmp.size() > 0) st.push(tmp);
                tmp = "";
            }
            else {
                tmp += s[i];
            }
        }

        // make string from the stack.
        while (!st.empty()) {
            ans += st.top(); st.pop();
            if (!st.empty()) ans += ' ';
        }

        return ans;

    }
};



class Solution {
public:

    string reverseWords(string s) {

        // reverse the entire string.
        reverse(s.begin(), s.end());

        int pos = 0;
        int runner = 0;
        int N = s.size();

        while (runner < N) {

            if (s[runner] != ' ') {

                // Not first word. Add space.
                if (pos != 0)
                    s[pos++] = ' ';

                // Spot entire word & add it in sequence.
                int beginOfWord = runner;
                int j = runner;
                while (j < N && s[j] != ' ') s[pos++] = s[j++];

                // revese newly added word only. (j - beginOfWord) is size of newly added word
                reverse(s.begin() + pos - (j - beginOfWord), s.begin() + pos);
                runner = j;
            }
            else {
                runner++;
            }
        }

        // remove unecessary space at the end.
        s.erase(s.begin() + pos, s.end());

        return s;
    }
};