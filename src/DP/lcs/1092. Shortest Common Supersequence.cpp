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

Question : 1092. Shortest Common Supersequence
Topic : DP
Problems : https://leetcode.com/problems/shortest-common-supersequence/description/
==============================> Explanation <=============================================

Pattern: LCS

What is shortest common supersequence ?

1) What is supersequence ?
    Supersequence of String A and B is sequence which contain both seq A & B. In short, you can pick A and B from
    supersequence while maintaining an internal order of string.

2) Then shortest supersequence, is shortest seq among all supersequence.

For example:

Given s1 = "brute" and s2 = "groot".

Supersequences can be => brutegroot, bgruteoot

You can derive s1 ans s2 from superseq... while s1 ans s2 follow its internal order when you pick up from sup seq.

Now let's jump to question....

    Here we need to find shortest sup seq of string A & B.

    One thing is very clear, in the worst case sup seq = A + B (But not sure whether is shortest or not, we need to find shortest one)

    Ex: BRUTE GROOT => BRUTEGROOT

    To get the shortest we need to eliminate repeated characters from sup seq....

    Indirectly, What I mean is that we can find the LCS(A, B) and take the LCS only one time.. and can remove the duplicate characters from sup-seq.

    Length of shortest common superseq => A + B - LCS(A, B)(Deleting duplicate characters while maintaining orders)

**How to derive the "SCS" String ?

=> Well, we know how we derive the LCS of A & B using dp table. Simliar concept we will be using here.

Case-1: s[i] == t[i] (character matched)
    => we take s[i] char only one time... and move to (i-1, j-1).

Case-2: s[i] != t[i]...

    1) then we check max(dp[i-1][j], dp[i][j-1]) and then jump to max. so for example...

        dp[i-1][j] is maximum then... we jump to (i-1, j)...

        That time we add s1[i] in our answer because we cut down the "s1[i]" char from "s" string when we jump to (i-1, j). And
        here we are finding sup-seq so we need to add all distinct characters...

Case-3(Edge Case):

    i > 0 && j == 0 (or vice versa).. it means that we reached end of string in one of string and other string still remain...
    We need to all the remain characters (again same reason we are finding sup-seq) ... because we add all distinct characters.

    During.. LCS("", S) => ""
             SSC("", S) => S

Check the code!!

In short,

    Shortest-sup-seq-Length = A + B - LCA(A, B)

    Print Shortest Supersequence,

        s[i] == t[j] => print s[i] single time only (elimiate duplicatancy in sup-seq)
        s[i] != t[j] => jump to max-side and add that character before jumping
        i > 0 && j == 0 => print all remaining ith characters until it 0.

==============================> Approach and Time Complexity <============================



1) DP
Time: O(2^(M+N)) -> O(M*N)
Space: O(M*N) => O(N) (stack space)
 */



class Solution {
public:
    string shortestCommonSupersequence(string s1, string s2) {


        // 1. Find LCS

        int m = s1.size(), n = s2.size();

        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                }
                else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        // print length of shortestCommonSupersequence => s1.size() + s2.size() - dp[m][n];


        // 2. Construct the shortestCommonSupersequence.

        string scs = "";

        int i = m, j = n;

        while (i > 0 && j > 0) {

            // match, add character in our answer one time (that's how we elimiate duplicate)
            if (s1[i - 1] == s2[j - 1]) {
                scs += s1[i - 1];
                i--; j--;
            }
            else if (dp[i - 1][j] > dp[i][j - 1]) {     // moving (i, j) => (i-1, j)...add s1[i] in scs.
                scs += s1[i - 1];
                i--;        // jump to (i-1, j)
            }
            else {                                      // moving (i, j) => (i, j-1)...add s1[j] in scs.
                scs += s2[j - 1];
                j--;
            }
        }

        // Add remaining characters
        while (i > 0) {
            scs += s1[i - 1];
            i--;        // jump to (i-1, j)
        }

        while (j > 0) {
            scs += s2[j - 1];
            j--;
        }


        // reverse scs....
        reverse(scs.begin(), scs.end());

        return scs;
    }
};