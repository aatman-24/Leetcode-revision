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

Question : 1106. Parsing A Boolean Expression
Topic : Stack
Problems : https://leetcode.com/problems/parsing-a-boolean-expression/
==============================> Explanation <=============================================

Pattern: Stack Expersssion

Initially, I though it is DP Question because I am solving from that set currently,

But it is stack question, where we need to resolve given experssion.

Already solved such problem with arithemtic expression, here they replaced with logical expression.

Intuition will remain same,

    We maintain one stack... add everything "(", operators, oprands.... except (")")

    When we see, ")"...we resolve the experssion until we dont' find "(".

    as we starting.... experssion solving from end of experssion within "()"...we need operator along with that...(which we got first here...)

    That's why we use the second stack to maintain those... and once "()" subexperssion resolved we remove that as well.

==============================> Approach and Time Complexity <============================



1) Stack
Time: O(N)
Space: O(N)

 */


class Solution {
public:


    /* Intuition:

    We maintain one stack... add everything "(", operators, oprands.... except (")")

    When we see, ")"...we resolve the experssion until we dont' find "(".

    as we starting.... experssion solving from end of experssion within "()"...we need operator along with that...(which we got first here...)

    That's why we use the second stack to maintain those... and once "()" subexperssion resolved we remove that as well.

    */

    bool parseBoolExpr(string exp) {

        // maintian oprands
        stack<char> expStack;

        // maintani operator
        stack<char> opSign;

        for (int k = 0; k < exp.size(); k++) {

            // ignore
            if (exp[k] == ',') continue;

            else if (exp[k] == '!' || exp[k] == '&' || exp[k] == '|') {
                opSign.push(exp[k]);
            }

            else if (exp[k] == '(' || exp[k] == 't' || exp[k] == 'f') {
                expStack.push(exp[k]);
            }

            // resolve "(...)" when we see ")"
            else if (exp[k] == ')') {

                bool ansExp = expStack.top() == 't' ? true : false;
                expStack.pop();

                if (opSign.top() == '!') {
                    ansExp = !ansExp;
                }

                while (expStack.top() != '(') {

                    bool nextExp = expStack.top() == 't' ? true : false;

                    if (opSign.top() == '|') {
                        ansExp = ansExp || nextExp;
                    }

                    else if (opSign.top() == '&') {
                        ansExp = ansExp && nextExp;
                    }

                    expStack.pop();
                }

                expStack.pop(); opSign.pop();

                // again push result into the stack.
                expStack.push(ansExp == true ? 't' : 'f');

            }

        }

        return expStack.top() == 't' ? true : false;
    }
};
