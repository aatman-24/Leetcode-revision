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

Question : 227. Basic Calculator II
Topic : String, Stack
Problems : https://leetcode.com/problems/basic-calculator-ii/
==============================> Explanation <=============================================

Idea is that,

- We keep track of lastVisitedsign.

- If last sign is * || / then we direct perform the opreation and push the result into the stack.

- But if it is + or - then we add the element with this sign.

- So at last when we traverse the all the string we perform only addition opreation bcz all opreation
is already performed.

==============================> Approach and Time Complexity <============================

N = s.size()

2) Stack
Time: O(N)
Space: O(1) (We are using constant space, 3 bytes maximum)


*/

class Solution {
public:

    bool isSpace(char ch) {
        return ch == ' ';
    }

    bool isOpreator(char ch) {
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
            return true;
        return false;
    }

    bool isDigit(char ch) {
        if (ch >= '0' && ch <= '9')
            return true;
        return false;
    }

    int calculate(string s) {

        stack<ll> st;
        ll tmp = 0LL;
        char lastVisitedSign = '+';

        for (int i = 0; i < s.size(); i++) {

            if (isDigit(s[i])) {
                tmp = tmp * 10 + int(s[i] - '0');
            }

            if ((!isSpace(s[i])) && !isDigit(s[i]) || i == s.size() - 1) {

                if (lastVisitedSign == '+') {
                    st.push(tmp);
                }
                else if (lastVisitedSign == '-') {
                    st.push(-tmp);
                }
                else {

                    int num = st.top(); st.pop();
                    if (lastVisitedSign == '*') {
                        st.push(num * tmp);
                    }
                    else {
                        st.push(num / tmp);
                    }

                }
                lastVisitedSign = s[i];
                tmp = 0;
            }

        }

        ll ans = 0;
        while (!st.empty()) {
            ans += st.top(); st.pop();
        }

        return (int)ans;

    }
};