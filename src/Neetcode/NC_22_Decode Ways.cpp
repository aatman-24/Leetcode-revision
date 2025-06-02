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

Problem: NC_22_Decode Ways
Topic: DP
Link: https://neetcode.io/problems/decode-ways

================================================================================
                                Problem Summary
================================================================================

We need to find total number of ways we can decode the given string...

================================================================================
                                Intuition & Explanation
================================================================================

Idea is that..... we know we can only match either 1-len or 2-len string during the
decoding so we try only those....

If Given S = "123" => "1" | "23"(need to check this part)
                   => "12" | "3"(need to check this part)

If anytime we reach end of string it means we have found the valid decoding because
each of previous string pair have related mapping into the decoding_map....

Recurrence Relation:

    solve(s, index) => for, len = 1 => 2,

                        if s.substr(index, index+len) is valid, (found in map)

                            count += solve(s, index+len)


NOTE: space optimization is possible, but here I didn't add...

================================================================================
                          Approach & Time/Space Complexity
================================================================================

Approach: Recursion
Time Complexity: O(2^N)
Space Complexity: O(N)


Approach: Top Down DP
Time Complexity: O(N)
Space Complexity: O(N)


Approach: Bottom up
Time Complexity: O(N)
Space Complexity: O(N)

Approach: Bottom up (space optinization)
Time Complexity: O(N)
Space Complexity: O(1)


*/

class Solution {
public:

    unordered_map<string, int> mp;

    int helper(string s, int i) {

        // out of bound
        if (i >= s.size()) return 1;

        int count = 0;

        for (int len = 1; len <= 2; len++) {

            if (i + len <= s.size()) {

                string t = s.substr(i, len);

                if (mp.count(t)) {

                    count += helper(s, i + len);

                }

            }

        }

        return count;
    }

    int numDecodings(string s) {

        for (int i = 1; i <= 26; i++) {
            mp[to_string(i)] = i;
        }


        return helper(s, 0);
    }
};


// Top-down

class Solution {
public:

    int t[101];

    unordered_map<string, int> mp;

    int helper(string s, int i) {

        // out of bound
        if (i >= s.size()) return 1;

        if (t[i] != -1)
            return t[i];

        int count = 0;

        for (int len = 1; len <= 2; len++) {

            if (i + len <= s.size()) {

                string t = s.substr(i, len);

                if (mp.count(t)) {

                    count += helper(s, i + len);

                }

            }

        }

        return t[i] = count;
    }

    int numDecodings(string s) {

        for (int i = 1; i <= 26; i++) {
            mp[to_string(i)] = i;
        }

        memset(t, -1, sizeof(t));


        return helper(s, 0);
    }
};


// Bottom up

class Solution {
public:

    unordered_map<string, int> mp;

    int numDecodings(string s) {

        for (int i = 1; i <= 26; i++) {
            mp[to_string(i)] = i;
        }

        int N = s.size();

        vector<int> dp(N + 1, 0);

        // base case dp[N] = 1;
        dp[N] = 1;

        for (int i = N - 1; i >= 0; i--) {


            // same copied and pasted from top-down
            int count = 0;

            for (int len = 1; len <= 2; len++) {

                if (i + len <= s.size()) {

                    string t = s.substr(i, len);

                    if (mp.count(t)) {

                        count += dp[i + len];       // NOTE: Space optimization, we know dp[i] depend on dp[i+1] or dp[i+2] only....

                    }

                }
            }

            dp[i] = count;
        }

        return dp[0];
    }
};
