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

Question : 392. Is Subsequence
Topic : Two Pointer
Problems : https://leetcode.com/problems/is-subsequence/description/

==============================> Explanation <=============================================


Two Pointer:
- given that, s1 < s2(in length).
We can simply interate over the s2 and whenever we see match we increase the counter of s1. At the end if entire s1 got visited (counter == s1.size())
then we found Subsequence s1 into s2, otherwise not.

==============================> Approach and Time Complexity <============================

N = nums1.size(), M = nums2.size(), N > M.
1) Two Pointer
Time: O(N)
Space: O(1)


*/


class Solution {
public:
    bool isSubsequence(string s, string t) {
        int i = 0, M = s.size();
        for (int j = 0; j < t.size(); j++) {
            if (t[j] == s[i]) {
                i++;
            }
        }
        return i == M;
    }
};