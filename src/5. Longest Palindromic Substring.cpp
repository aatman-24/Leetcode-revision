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

Question : 5. Longest Palindromic Substring
Topic : DP, both side traversal
Problems : https://leetcode.com/problems/longest-palindromic-substring/

==============================> Explanation <=============================================

- Intuition behind this solution is that,
We need to check for each of character(considering as mid) whether it is center of any palindrome. And keep track of maximum palindrome.

Odd length: aba
Even Length: abba -> When center has two length, with same characters.


2) DP: Pending




==============================> Approach and Time Complexity <============================

N = nums.size()

1) Two Pointer
Time: O(N^2): For each of mid, we can visit entire string maximum to check for palindrome.
Space: O(1)

2) DP:
Time:
Space: O(N)


*/



class Solution {
public:

    void extendUntilPalindrome(string s, int &left, int &right) {
        int N = s.size();
        while (left >= 0 && right < N && s[left] == s[right]) {
            left--; right++;
        }
        // unwind last failed check.
        left++, right--;
    }

    string getSubString(string s, int lft, int rht) {
        string ans = "";
        for (int i = lft; i <= rht; i++) ans += s[i];
        return ans;
    }

    string longestPalindrome(string s) {

        int N = s.size();

        if (N <= 1)
            return s;

        string longest = "";

        for (int mid = 0; mid < s.size(); mid++) {

            // odd length
            int lft = mid, rht = mid;
            extendUntilPalindrome(s, lft, rht);

            if (abs(rht - lft + 1) > longest.size()) {
                longest = getSubString(s, lft, rht);
            }

            // even length
            if ((mid + 1) < N && s[mid] == s[mid + 1]) {

                lft = mid, rht = mid + 1;
                extendUntilPalindrome(s, lft, rht);

                if (abs(rht - lft + 1) > longest.size()) {
                    longest = getSubString(s, lft, rht);
                }
            }
        }

        return longest;
    }
};