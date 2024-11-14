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

Question : 44. Wildcard Matching*
Topic : DP
Problems : https://leetcode.com/problems/wildcard-matching/description/
==============================> Explanation <=============================================

Pattern: LCS

- Given that one string "s" and pattern "p"(with two wildcards ?, *)...we have to check string "s" match with pattern completely or not.

It is matching algorithm, where we match s[i] and p[j]...anytime they don't match we return false.

But this become intersting with wildcards entry (?, *)..

1) wildcard: "?"
p[j] = "?" which match to one character. That time we simply match it with current ith char from string "s".
As result, we jump to (i-1, j-1).

2) wildcard: "*"
p[j] = "*" which match with zero(empty string) or any number of characters from string "s".
To handle this case,

s = "ABC", p = "A*"

So we are not sure how many characters we should match with "*"... so we apply brute force there... * can match
[0...len(s)] we try all possible ways and any time it return true we are good.

We can apply the for loop and do recursion call based on that(the way we did in backtracking).. but wait we have
good approach.

Instead of using for loops we can do one thing.

    "ABC" | "A*" => AB|A* || ABC | A

    What we are trying to do is, * can match with empty character of "s" so (j-1) OR
                                 * can match with one character of "s" so (i-1) + still pattern contain "*"

    Because, we don't know how many characters * should match...so we don't remove it...

    In next recurison call...

        AB|A* => A|A* || AB| A

        See, A|A* (indicate two character BC, matched with *), AB|A (indicate * matched with one character)

        In short keeping * in string... we are basically applying the brute force only but better way.

    match(i, j) = match(i-1, j)(* is still there) || match(i, j-1) (* matched with empty character)

Remember: How we find all the permutation/subsets by considering two choice (take it or don't take it)...same thing
we applied here...


3) s[i] != p[j] => we return false;
4) s[i] == p[j] = return match(i-1, j-1).

Now let's see... base conditions.

1) Base condition: i <= 0 && j <= 0 (Got complete match, return true)
2) Base condition: j <= 0 && i > 0 (pat = "a*bc", s = "") Indicate pattern contain more characters .... so we return false.
3) Base condition: i <= 0 && j > 0, indicate s = "", but pattern = "AB"...
        1) If pattern = "***"... then it can match with s = "", only then we return true.
        For any other case, len(pattern) > 0... it is partial match so we return false.

Check the code... you will get idea.

Bottom-up and space optimization is conversion of top-down.

==============================> Approach and Time Complexity <============================



1) DP
Time: O(2^(M+N)) -> O(M*N)
Space: O(M*N) => O(N) (stack space)

 */




// Top-down Approach
class Solution {
public:

    int memo[2001][2001];

    bool allStars(string pattern, int j) {
        for (int k = 0; k < j; k++) {
            if (pattern[k] != '*')
                return false;
        }
        return true;
    }

    bool isMatchSupport(int i, int j, string s, string p) {

        // both string "s" and pattern "p" is empty.
        if (i <= 0 && j <= 0)
            return true;

        // s = "", and pattern = "***"
        if (i <= 0 && j > 0) {
            return allStars(p, j);
        }

        // pattern = "", and s = "abc"
        if (j <= 0 && i > 0)
            return false;


        if (memo[i][j] != -1)
            return memo[i][j];

        bool matched = false;

        // First check wildcards
        if (p[j - 1] == '?' || s[i - 1] == p[j - 1]) {
            matched = isMatchSupport(i - 1, j - 1, s, p);
        }
        else if (p[j - 1] == '*') {
            matched = isMatchSupport(i, j - 1, s, p) || isMatchSupport(i - 1, j, s, p); // (i, j-1)(* matched with empty string) || (i-1, j) (* matched with one character and still present)
        }
        else if (s[i - 1] != p[j - 1]) {
            matched = false;
        }
        return memo[i][j] = matched;
    }


    bool isMatch(string s, string p) {

        memset(memo, -1, sizeof(memo));

        return isMatchSupport(s.size(), p.size(), s, p);
    }
};


// Bottom-up Approach

class Solution {
public:

    bool allStars(string pattern, int j) {
        for (int k = 0; k < j; k++) {
            if (pattern[k] != '*')
                return false;
        }
        return true;
    }

    bool isMatch(string s, string p) {

        int m = s.size(), n = p.size();
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));

        // 1. Base condition
        dp[0][0] = true;

        // 2. Base condition, Indicate... str = "", len(p) > 1... then all characters in p should be *...
        for (int j = 1; j <= n; j++) {
            dp[0][j] = allStars(p, j);
        }
        // 3. Base condition
        for (int i = 1; i <= m; i++)
            dp[i][0] = false;

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                bool matched = false;
                if (p[j - 1] == '?' || s[i - 1] == p[j - 1]) {
                    matched = dp[i - 1][j - 1];
                }
                else if (p[j - 1] == '*') {
                    matched = dp[i][j - 1] || dp[i - 1][j];
                }
                else if (s[i - 1] != p[j - 1]) {
                    matched = false;
                }
                dp[i][j] = matched;
            }
        }
        return dp[m][n];
    }
};



// Bottom-up Approach - Space Optimization

class Solution {
public:

    bool allStars(string pattern, int j) {
        for (int k = 0; k < j; k++) {
            if (pattern[k] != '*')
                return false;
        }
        return true;
    }

    bool isMatch(string s, string p) {

        int m = s.size(), n = p.size();
        vector<bool> prev(n + 1, false), cur(n + 1, false);

        // 1. Base condition
        prev[0] = true;            // dp[0][0] = true;

        // 2. Base condition
        for (int j = 1; j <= n; j++) {
            prev[j] = allStars(p, j);   //  dp[0][j] = allStars(p, j);
        }

        // // 3. Base condition
        // for(int i = 1; i <= m; i++)
        //     dp[i][0] = false;

        for (int i = 1; i <= m; i++) {
            cur[0] = false;         // Base condition-3
            for (int j = 1; j <= n; j++) {
                bool matched = false;
                if (p[j - 1] == '?' || s[i - 1] == p[j - 1]) {
                    matched = prev[j - 1];
                }
                else if (p[j - 1] == '*') {
                    matched = cur[j - 1] || prev[j];
                }
                else if (s[i - 1] != p[j - 1]) {
                    matched = false;
                }
                cur[j] = matched;
            }
            swap(prev, cur);
        }
        return prev[n];
    }
};