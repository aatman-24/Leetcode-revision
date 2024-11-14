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

Question : 22. Generate Parentheses
Topic : Backtracking
Problems : https://leetcode.com/problems/generate-parentheses/description/
==============================> Explanation <=============================================

Pattern: Recursion

Idea is very simple, keep track of open and close parenthesis count,

At any moment, we have to choice to add "(" or add ")"(if, open > close)

so we make sure we have open >= close.

So we try both choice.

==============================> Approach and Time Complexity <============================

1) Recursion
Time: O(2^(2N))
Space: O(2N)

Depth => 2*N
Breadth => 2

 */


class Solution {
public:

    vector<string> parenthesisStore;

    void helper(int n, int open, int close, string curString) {

        if (curString.size() == 2 * n) {
            parenthesisStore.push_back(curString);
            return;
        }

        // If we can add open bracket...then we will add it. otherwise not.
        if (open < n) {
            helper(n, open + 1, close, curString + "(");
        }

        // this condition make sure, we have open brackert >= close bracket
        if (close < open) {
            helper(n, open, close + 1, curString + ")");
        }
    }



    vector<string> generateParenthesis(int n) {
        helper(n, 0, 0, "");
        return parenthesisStore;
    }
};


class Solution {
public:

    vector<string> parenthesisStore;

    void helper(int n, int open, int close, string curString) {

        if (open == n && close == n) {
            parenthesisStore.push_back(curString);
            return;
        }

        if (open > n || close > n)
            return;

        // this condition make sure, we have open brackert >= close bracket
        if (open == close) {
            string addOpenParenthesis = curString + "(";
            helper(n, open + 1, close, addOpenParenthesis);
        }
        else {
            // two option to add "(" or ")", if open > close....
            string addOpenParenthesis = curString + "(";
            string addCloseParenthesis = curString + ")";

            helper(n, open + 1, close, addOpenParenthesis);
            helper(n, open, close + 1, addCloseParenthesis);
        }
    }

    vector<string> generateParenthesis(int n) {
        string curString = "";
        helper(n, 0, 0, curString);
        return parenthesisStore;
    }
};