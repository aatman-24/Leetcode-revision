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

Question : 72. Edit Distance
Topic : DP
Problems : https://leetcode.com/problems/edit-distance/description/
==============================> Explanation <=============================================

Pattern: LCS

Famous Question: Edit Distance

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


Check the code...

We can also do space optimization..


==============================> Approach and Time Complexity <============================



1) DP
Time: O(3^(M+N)) -> O(M*N)
Space: O(M*N) => O(M+N) (stack space)

Breadth => 3 calls => 3
Depth => (m + n)  (why? We can start with (m, n) => (m, 1) => (1, 1) => (0, 0) such case possible)

What I mean is that... s1 = "ABC", s2 = "DEF"... we can go like s1 = "ABC" to s2 = ""... and then s1 = "", s2 = "".

 */



// Top-down Approach
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