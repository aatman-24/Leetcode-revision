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

Question : 150. Evaluate Reverse Polish Notation
Topic : Stack, Mono-stack
Problems : https://leetcode.com/problems/evaluate-reverse-polish-notation/description/

==============================> Explanation <=============================================

Let's deep dive into infix, prefix and postfix.

infix exp; (a + b)
prefix exp: +ab
postfix exp: ab+

1) How to convert the Infix expression into the postfix experssion ?
- postfix = "", stack<ch> st;
- add any operand directly into the postfix.
- for "(" -> direclty into the st.
- for ")" -> remove all operators from st and add into the postfix.
- for any operator(+, -, *, /),
    while(prece(st.top()) > prece(cur_operator)) {
        // we add st.top() operator into the postfix.
    }
- at the end, we remove all operators from stack(whichever remain) and add into postfix at the end.

2) How to convert the Infix experssion into the prefix expression ?
- Reverse the infix expression.
- Replace every ( with ) and vice versa.
- Get the postfix expression of the modified expression.
- Reverse the postfix expression to get the prefix expression.

3) How to evaluate the the Postfix experssion ?
- From left to right,
    - add operands into the stack.
    - if operator found, perform operation between top two of stack, add result back into stack.
- At the end, whatever is left in stack is result of experssion.


4) How to evaluate the the prefix experssion ?
- From right to left,
    - add operands into the stack.
    - if operator found, perform operation between top two of stack, add result back into stack.
- At the end, whatever is left in stack is result of experssion.

==============================> Approach and Time Complexity <============================

N = s.size()

1) Brute Force
Time: O(N^2)
Space: O(1)

2) Mono incresing stack
Time: O(N)
Space: O(N)


*/

// postfix evaluation.
class Solution {
public:

    int convertToNumber(string s) {

        if (s.size() == 0)
            return 0;

        char ch = s[0];
        bool isNegative = (ch == '-');
        int curNum = 0;

        for (int i = 0; i < s.size(); i++) {

            // skip the negtaive sign
            if (s[i] == '-') {
                continue;
            }

            curNum = curNum * 10 + int(s[i] - '0');
        }

        return isNegative ? -curNum : curNum;
    }


    int evalRPN(vector<string>& tokens) {

        stack<int> st;
        int num3;

        for (string token : tokens) {

            if (token == "+" || token == "-" || token == "*" || token == "/") {

                int num2 = st.top(); st.pop();
                int num1 = st.top(); st.pop();

                if (token == "+") {
                    num3 = num1 + num2;
                } else if (token == "-") {
                    num3 = num1 - num2;
                } else if (token == "*") {
                    num3 = num1 * num2;
                } else if (token == "/") {
                    num3 = num1 / num2;
                }

                st.push(num3);
            }
            else {
                st.push(convertToNumber(token));
            }


        }

        return st.top();
    }
};


// infix to postfix expression

int getPrecidition(char ch) {
    if (ch == '^')
        return 3;
    if (ch == '*' || ch == '/')
        return 2;
    if (ch == '+' || ch == '-')
        return 1;
    return 0;
}

bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}


string convertInfixToPostfix(string infix) {

    stack<char> operators;
    string postfix = "";

    for (char ch : infix) {

        // add operand directly.
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
            postfix += ch;
        }

        // add open parenthesis directly.
        else if ( ch == '(') {
            operators.push(ch);
        }

        // for close parenthesis, we need open. In between them add it into postfix.
        else if ( ch == ')') {
            while (!operators.empty() && operators.top() != '(' ) {
                postfix += operators.top();
                operators.pop();
            }
            operators.pop(); // remove close'(' at the end.
        }

        // operator
        else {

            // isOperator for st.top(), because we are adding open and close parenthesis as well.
            // We need to check if less Precidition operator we are adding in stack before that we need to remove high prec operator and add into postfix.
            // for example: a * b + c => ab*c+, because * and / has high prec. Before adding + into stack, we need to remove *.
            while (!operators.empty() && isOperator(operators.top()) && getPrecidition(operators.top()) > getPrecidition(ch)) {
                postfix += operators.top();
                operators.pop();
            }


            operators.push(ch);
        }
    }

    // remaining operator needs to be added directly into postfix.
    while (!operators.empty()) {
        postfix += operators.top();
        operators.pop();
    }

    return postfix;
}


// infix to prefix expression
string convertInfixToPrefix(string infix) {

    // change the "(" -> ")", ")" -> "("
    string tmp = "";
    for (char ch : infix) {
        if (ch == '(') {
            tmp += ')';
        }
        else if (ch == ')') {
            tmp += '(';
        }
        else {
            tmp += ch;
        }
    }

    // reverse the infix experssion.
    reverse(tmp.begin(), tmp.end());

    // find postfix of experssion
    string prefix_reverse = convertInfixToPostfix(tmp);

    // reverse the postifx experssion to get prefix
    reverse(prefix_reverse.begin(), prefix_reverse.end());

    return prefix_reverse;
}


int main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("inputf.in", "r", stdin);
    freopen("outputf.in", "w", stdout);
#endif


    cout << convertInfixToPostfix("(a-b/c)*(a/k-l)") << endl;
    cout << convertInfixToPrefix("(a-b/c)*(a/k-l)") << endl;

    return 0;
}