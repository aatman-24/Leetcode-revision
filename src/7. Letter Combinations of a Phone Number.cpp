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
d
/*
==============================> Description <=============================================

Question :  17. Letter Combinations of a Phone Number
Topic : Backtracking
Problems : https://leetcode.com/problems/letter-combinations-of-a-phone-number/

==============================> Explanation <=============================================
1) Backtracking. 39. Combination Sum
- In DFS we can go upto the size of given number "123". And BFS we go upto the char which is mapped to the
each digit.

- 2) Iterative. We already covered this type of solution. You also can use the
size variable to determine how many elements needs to update.

-3) Use Extra space Queue. Pop from the first and modified it and add again.


==============================> Apporach and Time Complexity <=============================================
1) Backtraking:
Time: O(Depth^Branch) = O(N^M) -> N = number size(DFS size), M = 3(BFS Size)
Space: O(N^M)(Aux)

All take same Complexity.
*/


class Solution {
public:

    map<char, string> mp;

    // Add ith digit character from [0, j] into ans.
    void formString(string digits, string current, int i, vector<string> &ans) {

        // when digit is finished. add the current into the answer.
        if (i == digits.size()) {
            ans.push_back(current);
            return;
        }

        string letters = mp[digits[i]];


        // BFS go the size of letters. For the current digit after all digits combination is added to into answer.
        for (int j = 0; j < letters.size(); j++) {
            current.push_back(letters[j]);

            // go to the next digit in DFS.
            formString(digits, current, i + 1, ans);

            current.pop_back();
        }
    }



    vector<string> letterCombinations(string digits) {

        if (digits.size() < 1) return {};

        mp['2'] = "abc";
        mp['3'] = "def";
        mp['4'] = "ghi";
        mp['5'] = "jkl";
        mp['6'] = "mno";
        mp['7'] = "pqrs";
        mp['8'] = "tuv";
        mp['9'] = "wxyz";



        vector<string> ans;
        string current = "";

        // backtracking
        formString(digits, current, 0, ans);

        return ans;

    }
};



class Solution {
public:
    const vector<string> pad = {
        "", "", "abc", "def", "ghi", "jkl",
        "mno", "pqrs", "tuv", "wxyz"
    };

    // Iterative.
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};
        vector<string> result;
        result.push_back("");

        for (auto digit : digits) {
            vector<string> tmp;

            // Add all the char to current answer one by one.
            for (auto candidate : pad[digit - '0']) {

                // single current s has added all the candidate. candidate[a, b, c] -> da, db , dc
                for (auto s : result) {
                    tmp.push_back(s + candidate);
                }
            }
            result.swap(tmp);
        }
        return result;
    }
};