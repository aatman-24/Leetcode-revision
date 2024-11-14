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

Question : MCM_5_Boolean Evaluation
Topic : DP-MCM
Problems : https://www.naukri.com/code360/problems/boolean-evaluation_1214650?utm_source=striver&utm_medium=website&utm_campaign=a_zcoursetuf&leftPanelTabValue=PROBLEM
==============================> Explanation <=============================================

It is very obvious that, we have to divide string into two parts, and find how many ways
left and right expression can return true and do aggregation. We can divide string at each
operator.

If operator is reside at kth location => count(i, k-1) + count(k+1, j)

count(i, j) return total count of ways expression can resolved to true.

What if experssion return false ? => We ignore that...right ? "NOOOOO"

See,

OR
T T => T
T F => T (see this one)
F T => T (see this one)
F F => F

One of experssion is returning false, still the overall experssion can be resolved to true.

Operator = OR

leftEx = T, rightEx = F

count = leftEx * rightEx

Same goes for AND & XOR. So we have to consider that as well......

So basically, third dimension comes into picture, let's call it "isTrue"..

count(i, j, isTrue=1) => return total number of ways experssion can be resolved to True
count(i, j, isTrue=0) => return total number of ways experssion can be resolved to False

So now we know how to resolve experssion as true/false, and how to count all the ways.

Let's see Base case,

i > j => return 0. (out of bound)
i == j, isTrue = 1, => return (int) exp[i] == 'T'; (if last charater is = T and isTrue = 1, then only we return 1, else 0)
i == j, isTrue = 0, => return (int) exp[j] == 'F'; (same as above, but vice versa).



==============================> Approach and Time Complexity <============================



1) DP
Time: O(2 * N^2)
Space: O(N^2)

 */





/* Intution

    It is very obvious that, we have to divide string into two parts, and find how many ways
    left and right expression can return true and do aggregation. We can divide string at each
    operator.

    If operator is reside at kth location => count(i, k-1) + count(k+1, j)

    count(i, j) return total count of ways expression can resolved to true.

    What if experssion return false ? => We ignore that...right ? NOOOOO

    See,

    OR
    T T => T
    T F => T (see this one)
    F T => T (see this one)
    F F => F

    One of experssion is returning false, still the overall experssion can be resolved to true.

    Same goes for AND & XOR. So we have to consider that as well......

    So basically, third dimension comes into picture, let's call it "isTrue"..

    count(i, j, isTrue=1) => return total number of ways experssion can be resolved to True
    count(i, j, isTrue=0) => return total number of ways experssion can be resolved to False

    So now we know how to resolve experssion as true/false, and how to count all the ways.

    Let's see Base case,

    i > j => return 0. (out of bound)
    i == j, isTrue = 1, => return (int) exp[i] == 'T'; (if last charater is = T and isTrue = 1, then only we return 1, else 0)
    i == j, isTrue = 0, => return (int) exp[j] == 'F'; (same as above, but vice versa).
*/
int getNumberOfWaysBasedOnOperator(char oper, int lt, int rt, int lf, int rf, int resolvedAsTrue) {

    /* OR
        T T => T
        T F => T
        F T => T
        F F => F
    */
    if (oper == '|') {
        if (resolvedAsTrue)
            return lt * rt + lt * rf + lf * rt;
        else
            return lf * rf;
    }


    /* AND
        T T => T
        T F => F
        F T => F
        F F => F
    */
    if (oper == '&') {
        if (resolvedAsTrue)
            return lt * rt;
        else
            return lt * rf + lf * rt + lf * rf;
    }

    /* XOR
        T T => F
        T F => T
        F T => T
        F F => F
    */

    if (oper == '^') {
        if (resolvedAsTrue)
            return lt * rf + lf * rt;
        else
            return lt * rt + lf * rf;
    }

}

int evaluateExp(string &exp, int i, int j, int isTrue) {

    // base case

    // out of bound
    if (i > j) return 0;

    if (i == j) {
        if (isTrue) return exp[i] == 'T';
        else return exp[i] == 'F';
    }

    int count = 0;

    // with increment of 2, k now only point to operator in experssion.
    // jth point to last oprand, so we stop k at last operator.
    for (int k = i + 1; k < j; k += 2) {

        int leftExpTrue = evaluateExp(exp, i, k - 1, 1);
        int rightExpTrue = evaluateExp(exp, k + 1, j, 1);
        int leftExpFalse = evaluateExp(exp, i, k - 1, 0);
        int rightExpFalse = evaluateExp(exp, k + 1, j, 0);

        count += getNumberOfWaysBasedOnOperator(exp[k], leftExpTrue, rightExpTrue, leftExpFalse, rightExpFalse, isTrue);
    }

    return count;
}

int evaluateExp(string &exp) {

    // Given isTrue = 1, because we want to resolve all exp as True.
    return evaluateExp(exp, 0, exp.size() - 1, 1);

}




/* Intution

    It is very obvious that, we have to divide string into two parts, and find how many ways
    left and right expression can return true and do aggregation. We can divide string at each
    operator.

    If operator is reside at kth location => count(i, k-1) + count(k+1, j)

    count(i, j) return total count of ways expression can resolved to true.

    What if experssion return false ? => We ignore that...right ? NOOOOO

    See,

    OR
    T T => T
    T F => T (see this one)
    F T => T (see this one)
    F F => F

    One of experssion is returning false, still the overall experssion can be resolved to true.

    Same goes for AND & XOR. So we have to consider that as well......

    So basically, third dimension comes into picture, let's call it "isTrue"..

    count(i, j, isTrue=1) => return total number of ways experssion can be resolved to True
    count(i, j, isTrue=0) => return total number of ways experssion can be resolved to False

    So now we know how to resolve experssion as true/false, and how to count all the ways.

    Let's see Base case,

    i > j => return 0. (out of bound)
    i == j, isTrue = 1, => return (int) exp[i] == 'T'; (if last charater is = T and isTrue = 1, then only we return 1, else 0)
    i == j, isTrue = 0, => return (int) exp[j] == 'F'; (same as above, but vice versa).
*/

// Memorization

int mod = 1000000007;

long long t[201][201][2];

long long getNumberOfWaysBasedOnOperator(char oper, long long lt, long long rt, long long lf, long long rf, int resolvedAsTrue) {

    /* OR
        T T => T
        T F => T
        F T => T
        F F => F
    */
    if (oper == '|') {
        if (resolvedAsTrue)
            return ((lt * rt) % mod + (lt * rf) % mod + (lf * rt) % mod) % mod;
        else
            return (lf * rf) % mod;
    }


    /* AND
        T T => T
        T F => F
        F T => F
        F F => F
    */
    if (oper == '&') {
        if (resolvedAsTrue)
            return (lt * rt) % mod;
        else
            return ((lt * rf) % mod + (lf * rt) % mod + (lf * rf) % mod) % mod;
    }

    /* XOR
        T T => F
        T F => T
        F T => T
        F F => F
    */

    if (oper == '^') {
        if (resolvedAsTrue)
            return ((lt * rf) % mod + (lf * rt) % mod) % mod;
        else
            return ((lt * rt) % mod + (lf * rf) % mod) % mod;
    }

}

long long evaluateExp(string &exp, int i, int j, int isTrue) {

    // base case
    // out of bound
    if (i > j) return 0;

    if (i == j) {
        if (isTrue) return exp[i] == 'T';
        else return exp[i] == 'F';
    }

    if (t[i][j][isTrue] != -1)
        return t[i][j][isTrue];

    long long count = 0;

    // with increment of 2, k now only point to operator in experssion.
    // jth point to last oprand, so we stop k at last operator.
    for (int k = i + 1; k < j; k += 2) {

        long long leftExpTrue = evaluateExp(exp, i, k - 1, 1);
        long long rightExpTrue = evaluateExp(exp, k + 1, j, 1);
        long long leftExpFalse = evaluateExp(exp, i, k - 1, 0);
        long long rightExpFalse = evaluateExp(exp, k + 1, j, 0);

        count = (count % mod) + (getNumberOfWaysBasedOnOperator(exp[k], leftExpTrue, rightExpTrue, leftExpFalse, rightExpFalse, isTrue) % mod) % mod;
    }

    return t[i][j][isTrue] = count % mod;
}

int evaluateExp(string &exp) {

    memset(t, -1, sizeof(t));

    // Given isTrue = 1, because we want to resolve all exp as True.
    return (int) evaluateExp(exp, 0, exp.size() - 1, 1);

}
