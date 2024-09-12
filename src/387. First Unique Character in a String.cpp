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

Question : 387. First Unique Character in a String
Topic : Hashing
Problems : https://leetcode.com/problems/first-unique-character-in-a-string/description/

==============================> Explanation <=============================================

Idea is that,

count the frequency of each character in first pass.

second pass check from left which character have freq==1.

==============================> Approach and Time Complexity <============================

N = s.size()

2) Stack
Time: O(1) each operation take o(1).
Space: O(N)

*/


class Solution {
public:
    int firstUniqChar(string s) {

        // keep track of frquency.
        int arr[26] = {0};

        // calculate frquency of each character in first pass.
        for (auto ch : s) {
            arr[ch - 'a']++;
        }

        // check freq==1, again in second pass starting from begin
        for (int i = 0; i < s.size(); i++) {
            if (arr[s[i] - 'a'] == 1)
                return i;
        }

        return -1;
    }
};