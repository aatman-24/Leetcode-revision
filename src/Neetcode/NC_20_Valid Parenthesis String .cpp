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
================================================================================
                                Problem Description
================================================================================

Problem: NC_20_Valid Parenthesis String
Topic: DP, Greedy
Link: https://neetcode.io/problems/valid-parenthesis-string

================================================================================
                                Problem Summary
================================================================================

We are given a string containing '(', ')' and '*'. We need to determine if the string
can be interpreted as a valid parenthesis expression. The '*' character can represent
either '(', ')' or an empty string.

================================================================================
                             Approaches & Intuition
================================================================================

1) Recursion:
- Idea: At each step, we keep a count of open parentheses.
- When we encounter '*', we try all three possibilities:
    - Treat it as '('
    - Treat it as ')'
    - Treat it as an empty string
- If any of the recursive paths return true, the string is valid.
- This recursive solution can be optimized using:
    - Top-Down Dynamic Programming (Memoization)
    - Bottom-Up Dynamic Programming (Tabulation)

--------------------------------------------------------------------------------

2) Greedy (Using Stacks):
- Use two stacks:
    - One to store the indices of '('
    - Another to store the indices of '*'
- When we encounter ')':
    - Try to match it with the top of the '(' stack
    - If no '(', then try to match with a '*' (acting as '(')
- After traversal:
    - Check remaining '(' and '*' in stacks
    - Ensure each unmatched '(' has a '*' after it to act as ')'
- This greedy approach works by flexibly assigning '*' as needed.

--------------------------------------------------------------------------------

3) Greedy (Using Counters):
- Maintain two counters:
    - `openMin`: Minimum possible open parentheses
    - `openMax`: Maximum possible open parentheses
- Traverse the string:
    - For '(': increment both `openMin` and `openMax`
    - For ')': decrement both (but don't allow `openMin` < 0)
    - For '*':
        - Treat as '(': increment `openMax`
        - Treat as ')': decrement `openMin`
        - Treat as empty: `openMin` stays the same
- If at any point `openMax` < 0, return false
- At the end, if `openMin` == 0, the string is valid


================================================================================
                          Approach & Time/Space Complexity
================================================================================

Approach: Recursion
Time Complexity: O(3^N), breadth=3, depth=N
Space Complexity: O(N) (stack space)


Approach: DP
Time Complexity: O(N^2)
Space Complexity: O(N^2) (memo table)


Approach: Space Optimization
Time Complexity: O(N^2)
Space Complexity: O(N)

Approach: Greedy
Time Complexity: O(N)
Space Complexity: O(N)

Approach: Greedy
Time Complexity: O(N)
Space Complexity: O(1)
*/

// Recursion
class Solution {
public:
    bool checkValidString(string s) {
        return dfs(0, 0, s);
    }

private:
    bool dfs(int i, int open, const string& s) {
        if (open < 0) return false;
        if (i == s.size()) return open == 0;

        if (s[i] == '(') {
            return dfs(i + 1, open + 1, s);
        } else if (s[i] == ')') {
            return dfs(i + 1, open - 1, s);
        } else {
            return dfs(i + 1, open, s) ||
                   dfs(i + 1, open + 1, s) ||
                   dfs(i + 1, open - 1, s);
        }
    }
};



class Solution {
public:
    bool checkValidString(string s) {
        stack<int> open, star;
        for (int i = 0; i < s.size(); i++) {
            char ch = s[i];
            if (ch == '(') {
                open.push(i);
            }
            else if (ch == '*') {
                star.push(i);
            }
            else {

                // both are empty => and we get ch = ")", Invalid
                if (open.empty() && star.empty()) return false;

                // greedy: if we have open bracket to match, then we match it ")" to it..
                if (!open.empty()) {
                    open.pop();
                }
                else {
                    star.pop();
                }
            }
        }

        // need to match remaining "("...
        while (!open.empty() && !star.empty()) {

            // "*(" "*(" those are invalid....
            if (open.top() > star.top()) {
                return false;
            }
            open.pop(); star.pop();
        }

        return open.empty();
    }
};


// Greedy Approach
// Idea is to have, openMax > 0, while considering greedy approach(whenever we have chance * -> "(")
// we make it.....
class Solution {
public:
    bool checkValidString(string s) {

        int openMin = 0, openMax = 0;

        for (int i = 0; i < s.size(); i++) {

            char ch = s[i];

            if (ch == '(') {
                openMax++;
                openMin++;
            }
            else if (ch == ')') {
                openMax--;
                openMin--;
            }
            else {
                openMax++;  // * -> (
                openMin--;  // * -> )
            }

            // it means total number of {*, )} >>>> numOf("(")
            if (openMax < 0)
                return false;

            // unecessary * -> has been convered into the ) => we ignore those
            if (openMin < 0)
                openMin = 0;

        }

        // all open needs to be close
        return openMin == 0;
    }
};
