#### Dynamic programming, Pattern = LCS

---

#### [1143. Longest Common Subsequence](https://leetcode.com/problems/longest-common-subsequence/)

```c

/* Intuition:
Standard Problem.

solve(i, j) => s1[i] == s2[j] => (match) => 1 + solve(i-1, j-1) (if match then we move to next character in both string)
            => s1[i] != s2[j] => (unmatch) => max(solve(i-1, j), solve(i, j-1)) (if not match then we try both combination)

            combination_1:  abcde => cdfg ====> solve(abcde, cdf)
            combination_2:  solve(abcd, cdf)

Means, we remove last unmatched character from both string one by one and try to match other string. (Which is brute force).

Base case: i == 0 || j == 0, one of the string is visited entirely, and no string left for comparision we return 0(lcs).

*/


// Recursion
class Solution {
public:

    int longestCommonSubsequenceHelper(int i, int j, string s1, string s2) {

        // If one the string is empty, we don't get common subsequence so return it 0.
        if (i == 0 || j == 0)
            return 0;

        if (s1[i - 1] == s2[j - 1]) {
            return 1 + longestCommonSubsequenceHelper(i - 1, j - 1, s1, s2);
        }
        else {
            return max(longestCommonSubsequenceHelper(i - 1, j, s1, s2), longestCommonSubsequenceHelper(i, j - 1, s1, s2));
        }
    }


    int longestCommonSubsequence(string s1, string s2) {
        return longestCommonSubsequenceHelper(s1.size(), s2.size(), s1, s2);
    }
};

// Top-Down

class Solution {
public:

    int t[1001][1001];

    int longestCommonSubsequenceHelper(int i, int j, string s1, string s2) {

        // If one the string is empty, we don't get common subsequence so return it 0.
        if (i == 0 || j == 0)
            return 0;

        if (t[i][j] != -1)
            return t[i][j];

        int longest = 0;

        if (s1[i - 1] == s2[j - 1]) {
            longest = 1 + longestCommonSubsequenceHelper(i - 1, j - 1, s1, s2);
        }
        else {
            longest = max(longestCommonSubsequenceHelper(i - 1, j, s1, s2), longestCommonSubsequenceHelper(i, j - 1, s1, s2));
        }

        return t[i][j] = longest;
    }


    int longestCommonSubsequence(string s1, string s2) {
        memset(t, -1, sizeof(t));
        return longestCommonSubsequenceHelper(s1.size(), s2.size(), s1, s2);
    }
};


// Bottom-up

class Solution {
public:
    int longestCommonSubsequence(string s1, string s2) {
        int m = s1.size(), n = s2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        // base case, (i == 0, j == 0) covered during initialization dp[i][0] = 0, dp[0][j] = 0.
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
        return dp[m][n];
    }
};


// Space Optimization
class Solution {
public:
    int longestCommonSubsequence(string s1, string s2) {
        int m = s1.size(), n = s2.size();
        vector<int> pre(n + 1, 0), cur(n + 1, 0);
        // base case, (i == 0, j == 0) pre = {0, 0, 0....} and curr = {0, 0, 0..} which covered. .
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    cur[j] = 1 + pre[j - 1];
                }
                else {
                    cur[j] = max(pre[j], cur[j - 1]);
                }
            }
            swap(pre, cur);
        }
        return pre[n];
    }
};
```

## 

## Longest Common Subsequence(print LCS)

```c
/* Intuition:
To print LCS,

We basically perform the backtracking, we start at right most corner (m, n). And do the backtracking of original alogrithm.

1) s1[i] == s2[j] => add s1[i] into LCS, move to (i-1, j-1).

2) s1[i] != s2[j],

    max(dp[i-1][j], dp[i][j-1]) => whichever comp return maximum value...there we move either (i-1,j) | (i, j-1)... in case both are maximum then...
..we can move to anyone... but such case indicate multiple same length LCS present...

*/
class Solution {

public:

    string printLCS(int i, int j, vector<vector<int>> dp, string s, string t) {

        // first create, longest_common_subseq length temp string.
        string str = "";
        int len = dp[i][j];
        for (int i = 1; i <= len; i++) {
            str += "$";
        }
        int index = len - 1;

        // Perform backtracking..
        while (i > 0 && j > 0) {

            if (s[i - 1] == t[j - 1]) { // both character match, add it in LCS
                str[index] = s[i - 1];
                index--;
                i--;
                j--;
            }
            else if (dp[i - 1][j] > dp[i][j - 1]) { // Otherwise pick up the maximum(where we came from)
                i--;
            }
            else {
                j--;
            }
        }

        return str;
    }

    string all_longest_common_subsequences(string s, string t) {
        int m = s1.size(), n = t.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s[i - 1] == t[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                }
                else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        int longestSubLen = dp[m][n];

        return printLCS(i, j, dp, s, t);
    }
};
```

### [21_GFG_Longest Common Substring](https://www.geeksforgeeks.org/problems/longest-common-substring1452/1)

```c

/* Intuition:
    

Longest Common Substring,

When we are finding the LCS(subsequence) that time seq is not required to be in consecutive manner, but for the
LCS(substring) we need in consecutive manner.

So there is change only.

Previously, when the s1[i] != s2[j], that time we return the max length from either call (i-1, j) || (i, j-1)... But
here such mismatch break the substring...so we need to return zero. (check the code)

Also, due to that.... we need to keep track of maxLen... because we are getting hte maximum length substring at subproblem not at global level.

*/

// Top-down Approach
class Solution {
public:

    int t[1001][1001];

    // keep track of longest common substring.
    int longestCommSubstr = 0;

    int longestCommonSubstrHelper(int i, int j, string s1, string s2) {

        if(i == 0 || j == 0)
            return 0;

        if(t[i][j] != -1)
            return t[i][j];

        int countOfLen = 0;

        if(s1[i-1] == s2[j-1]) {
            countOfLen = 1 + longestCommonSubstrHelper(i-1, j-1, s1, s2);       // Here only, we get the maxLen due to consecutive match. 
            if(longestCommSubstr < countOfLen) {
                longestCommSubstr = countOfLen;
            }
        } else {                                        // mismatch break the lcs... so we return 0. 
            longestCommonSubstrHelper(i-1, j, s1, s2);
            longestCommonSubstrHelper(i, j-1, s1, s2);
            countOfLen = 0;
        }

        return t[i][j] = countOfLen;
    }

    int longestCommonSubstr(string s1, string s2) {

        memset(t, -1, sizeof(t));

        longestCommonSubstrHelper(s1.size(), s2.size(), s1, s2);

        return longestCommSubstr;
    }
};



// Bottom-up Approach
class Solution {
public:

    int longestCommonSubstr(string s1, string s2) {

        int m = s1.size(), n = s2.size();
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));

        int maxCommonSubstr = 0;

        for(int i = 1; i <= m; i++) {
            for(int j = 1; j <= n; j++) {
                if(s1[i-1] == s2[j-1]) {
                    dp[i][j] = 1 + dp[i-1][j-1];
                    maxCommonSubstr = max(maxCommonSubstr, dp[i][j]);
                }
            }
        }

        return maxCommonSubstr;
    }
};
```

### [516. Longest Palindromic Subsequence](https://leetcode.com/problems/longest-palindromic-subsequence/)

```c
/* Intuition:

Intuition behind this apporach is that,

To find the LPS(Longest Palindrome Subseq), we have to reverse(S) and find LCS(S, reverse(S)).

Because, When we reverse the String=S, that time seq which is part of Palindrome remain same in terms of order.

And later, when we find the LCS between them, we get entire palindrome subseq as result.

Ex:

1) a c b d a  => a d b c a
as you can see, when we reverse the string the palindrome seq(aba) which remain as it is. That's concept we used
to derive the palindrome seq.

*/

class Solution {
public:


    int longestCommonSubseq(string s1, string s2) {

        int m = s1.size(), n = s2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        // base case
        // dp[i][0] = 0, dp[0][j] = 0 (already covered).

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

        return dp[m][n];
    }

    // Short Note: Longest Palindrome Subseq = LCS(s, rev(s))

    int longestPalindromeSubseq(string s) {

        // Base case, len(s) <= 1 for such string, longest palindrome of string is itself.
        if (s.size() <= 1)
            return s.size();


        string s2 = s;
        reverse(s2.begin(), s2.end());

        return longestCommonSubseq(s, s2);
    }
};
```

### [583. Delete Operation for Two Strings](https://leetcode.com/problems/delete-operation-for-two-strings/)

```c
/* Intuition:

We need to convert the S1 => S2, by doing one of operation (deletion-A, deletion-B(Insertion-A)). Each operation cost 1 unit.

First you need to identify problem is from LCS-Subset problems.

How ? 1) Given Two String 2) Asking minimum cost(optimization) 3) To get minimum cost you need to try all possible combination.

And if you notice carefully, you are not doing anything on LCS of them.

Let's jump to solution,

    S1 = HEAP
    S2 = PEA
    LCS = EA

    So what we do is, convert S1 => LCS, HEAP => EA (Required 2 Deletion from S1 (H, P))
                      convert S2 => LCS, PEA => EA  (Required 1 Deletion from S2 (P)) (Which is, Insertion in S1).

    We convert S1 => LCS and then LCS => S2... which result into S1 => S2.

    For pratical purpose, we convert s1 => lcs && s2 => lcs which is similar to above one.

    Opereation cost
        =  len(S1) - len(LCS) (Deletion from S1)
        +  len(S2) - len(LCS) (Deletion From S2 | Insertion in S1)

*/
class Solution {
public:

    int longestCommonSubseq(string s1, string s2) {

        int m = s1.size(), n = s2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        // base case
        // dp[i][0] = 0, dp[0][j] = 0 (already covered).

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

        return dp[m][n];
    }


    int minDistance(string word1, string word2) {

        /* Opereation cost 
        =  len(S1) - len(LCS) (Deletion from S1)  
        +  len(S2) - len(LCS) (Deletion From S2 | Insertion in S1) */  


        int longestCommonSubseqLen = longestCommonSubseq(word1, word2);

        return word1.size() - longestCommonSubseqLen + word2.size() - longestCommonSubseqLen;
    }
};
```

### [1312. Minimum Insertion Steps to Make a String Palindrome](https://leetcode.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/)

```c
/* Intuition:

Given that, For string=s, you need to find minimum insertion/deletion steps to make it palindrome.

Hard to Identify Pattern, but you have to (no choice).

Remember, When Palindrome question is given you must derive LCS between (s, reverse(s)).

First,

1) Learn how to find the LPS(Longest Palindrome Subsequence) for given String s.

        LPS(S) = LCS(S, reverse(S))

2) How to convert String s1 => s2, by doing deletion/insertion.

If you know #2, then you get the idea is...

    To convert string s1 => palindromic(s1).... you need to add/delete some of characters from s1.

    And how many characters(steps) you need to perform is derived through LCS.

        = len(S1) - LCS (deletion) + len(S2) - LCS(Insertion)

But here only S1 is given and whatever we do in S1 is also reflect in S2, so if we do one of operation DeletionFromS1 OR DeletionFromS2 is okay.

Ultimatly, no # of insertion/deletion required is = len(S) - len(LPS)

*/
class Solution {
public:

    int longestCommSubseq(string s1, string s2) {

        int m = s1.size(), n = s2.size();

        vector<vector<int>> dp(m+1, vector<int>(n+1));

        for(int i = 1; i <= m; i++) {
            for(int j = 1; j <= n; j++) {
                if(s1[i-1] == s2[j-1]) {
                    dp[i][j] = 1 + dp[i-1][j-1];
                }
                else {
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        return dp[m][n];
    }




    int minInsertions(string s) {

        // Convert S1 => S2, Cost = (len(S1) - len(LCS)) + (len(S2) - len(LCS)) (But Here, s2 == rev(s1), both are same)
        // Convert S1 => S2, Cost = (len(S1) - len(LCS))
        // How to get LCS of S1 = LPS(S1) = LCS(S1, reverse(S1))
        string s2 = s;
        reverse(s2.begin(), s2.end());
        int lcsLen = longestCommSubseq(s, s2);
        return s.size() - lcsLen;
    }
};
```

### [115. Distinct Subsequences](https://leetcode.com/problems/distinct-subsequences/)

```c

/* Intuition:

Given two strings s and t(target), we have to find all unique subsequence from "s" which match to "t".

So this problem is not exactly LCS Pattern, but we can take the idea from it,

We do comparsion, same way we do in LCS.

    s[i] == t[j] (matched) => That time we have two choice (consider as match) OR (Unmatched, Expecting simliar character forward)
    s[i] != t[j] => Unmatched

When we consider match that time we jump to (i-1, j-1) and for unmatch(i-1, j)... (j will be same... we are not finding LCS).

Base case,

    T = ""(j==0)... that time any sub-seq of S will match. So return 1. (count)
    S = ""(i==0,j!=0)...it means still T have some character left, but we reach End of String for "s". So we return 0 (don't able to find entire T in S)

Check the code!!

*/



// Top-down
class Solution {
public:

    int memo[1001][1001];

    int numDistinctHelper(int i, int j, string s, string t) {

        // End of target String.
        if (j == 0)
            return 1;

        // Don't able to match string "s" entirely with target string "t"
        if (i == 0)
            return 0;

        cout << i << " " << j << endl;

        if (memo[i][j] != -1) {
            return memo[i][j];
        }

        int count = 0;
        if (s[i - 1] == t[j - 1]) {
            // two choice, match and don't match
            count = numDistinctHelper(i - 1, j - 1, s, t) + numDistinctHelper(i - 1, j, s, t);
        }
        else {
            count = numDistinctHelper(i - 1, j, s, t);
        }


        return memo[i][j] = count ;
    }


    int numDistinct(string s, string t) {

        memset(memo, -1, sizeof(memo));

        return numDistinctHelper(s.size(), t.size(), s, t);
    }
};



// Bottom-up
class Solution {
public:

    int numDistinct(string s, string t) {

        int m = s.size(), n = t.size();
        vector<vector<unsigned int>> dp(m + 1, vector<unsigned int>(n + 1, 0));

        // base case
        for (int i = 0; i <= m; i++)
            dp[i][0] = 1;

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s[i - 1] == t[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j]; // (match + don't match)
                }
                else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }

        return dp[m][n];
    }
};
```

### [1092. Shortest Common Supersequence](https://leetcode.com/problems/shortest-common-supersequence/)

```c
/* Intuition:

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

*/
class Solution {
public:
    string shortestCommonSupersequence(string s1, string s2) {

      /*

    Shortest-sup-seq-Length = A + B - LCA(A, B)

    Print Shortest Supersequence,

        s[i] == t[j] => print s[i] single time only (elimiate duplicatancy in sup-seq)
        s[i] != t[j] => jump to max-side and add that character before jumping
        i > 0 && j == 0 => print all remaining ith characters until it 0.

      */

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
```

### [72. Edit Distance](https://leetcode.com/problems/edit-distance/)

```c
// Top-down Approach
/* Intuition:

Given that, you can use (add, update, delete) operations to convert S1 => S2.

Here each operation cost "1" unit (but in some questions that cost might be different).

Add Operation: adding s2[j] => into s1.. indirectly deleting s2[j] (j = j - 1)

    Ex: ABC, DEF => C != F => ABCF, DEF => ABC, DE (indirectly)

Update Operation: updating s1[i] = s2[j], indirectly (i = i-1, j = j - 1)

    Ex: ABC, DEF => C != F => ABF, DEF => AB, DE (indirectly)

Delete Operation: deleting s1[i].. deleting s1[j] (i = i -1)

    Ex: ABC, DEF => C != F => AB, DEF

And if we have match, s1[i] == s2[j] (then we jump to i-1, j-1 with no cost).

solve(i, j) =>
        if match:
            return solve(i-1, j-1)
        else:
            return min(insertCost+solve(i, j-1), updateCost+solve(i-1, j-1) + deleteCost(i-1, j))

Base case,

    i == 0 && j > 0, indicate convert "" into "ABC" => insertions which cost = len(s2)

    i > 0 && j == 0, indicate convert "ABC" into "" => deletion which sot = len(s1)


*/

class Solution {
public:

    int t[501][501];

    int minDistanceHelper(int i, int j, string s1, string s2) {
        if (i == 0) return j;
        if (j == 0) return i;
        if (t[i][j] != -1) return t[i][j];
        int minCost = INT_MAX;
        if (s1[i - 1] == s2[j - 1]) {                                       // match, no cost
            minCost = minDistanceHelper(i - 1, j - 1, s1, s2);
        }
        else {
            int insertCost = 1 + minDistanceHelper(i, j - 1, s1, s2);       // sometime given insert, update and delete cost.
            int updateCost = 1 + minDistanceHelper(i - 1, j - 1, s1, s2);
            int deleteCost = 1 + minDistanceHelper(i - 1, j, s1, s2);
            minCost = min(insertCost, min(updateCost, deleteCost));
        }
        return t[i][j] = minCost;
    }


    int minDistance(string word1, string word2) {
        memset(t, -1, sizeof(t));
        return minDistanceHelper(word1.size(), word2.size(), word1, word2);
    }
};


// Bottom-Approach
class Solution {
public:

    int minDistance(string s1, string s2) {

        int m = s1.size(), n = s2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        // base case
        for (int j = 0; j <= n; j++) {
            dp[0][j] = j;
        }

        for (int i = 0; i <= m; i++) {
            dp[i][0] = i;
        }

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else {
                    // sometime each operation have diff cost...so change according to it.
                    int insertCost = 1 + dp[i][j - 1];
                    int updateCost = 1 + dp[i - 1][j - 1];
                    int deleteCost = 1 + dp[i - 1][j];
                    dp[i][j] = min(insertCost, min(updateCost, deleteCost));
                }
            }
        }

        return dp[m][n];
    }
};
```

### [44. Wildcard Matching*](https://leetcode.com/problems/wildcard-matching/)

```c

/* Intuition:

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
```
