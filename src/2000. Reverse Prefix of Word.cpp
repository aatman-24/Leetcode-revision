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

Question : 2000. Reverse Prefix of Word
Topic : Two Pointer
Problems : https://leetcode.com/problems/reverse-prefix-of-word/description/

==============================> Explanation <=============================================

Idea is that, find the index of targetCh... which is j, then reverse the string (i, j) in place..

==============================> Approach and Time Complexity <============================

1) Two Pointer
Time: O(N)
Space: O(N)

*/



class Solution {
public:


    string reversePrefix(string word, char targetCh) {

        // Find the targetCh, into the word. spotIndex is the location of targetCh in word.
        int spotIndex = 0;
        for (char ch : word) {
            if (targetCh == ch) {
                break;
            }
            spotIndex++;
        }

        // edge case
        // spotIndex == 0, targetCh is first character.
        // spotIndex == word.size(), targetch not found.
        if (spotIndex <= 0 || spotIndex == word.size())
            return word;

        // final string = s[j...i] + s[j+1...n]
        int i = 0, j = spotIndex;
        while (i < j) {
            swap(word[i++], word[j--]);
        }

        return word;
    }
};