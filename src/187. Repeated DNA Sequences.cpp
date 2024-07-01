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

Question : 187. Repeated DNA Sequences
Topic : Sliding Window
Problems : https://leetcode.com/problems/repeated-dna-sequences/description/
==============================> Explanation <=============================================

Sliding Window Technique:
- We iteratate over the string with the window size of 10, that means each time we drop first character and add at the end. And use hashtable
to know the count of that string. Time => O(N*10) => O(N)
Space => O(10*N).

Optimization:
- Can we avoid 10 length string as key to opitimize the space ? Then how we can identify the repeated substring ?

Idea is that, Here we given only 4 diff characters. A, C, G, T -> So we can use bit manipulation to construct one int value which can work as key. How ?

A -> 0 = 00
C -> 1 = 01
G -> 2 = 10
T -> 3 = 11

10 length substring we get: AACCGGTTAA => 0000 0101 1010 1111 0000 => some interger value. Int have 32 bits, we only need 20 bits of them so it is possible.

We use that unique_key as key. Other logic will be the same...

Check the  code!!

==============================> Approach and Time Complexity <============================

N = s.size()

1) Sliding Window
Time: O(N)
Space: O(N)

*/


class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {

        int N = s.size();
        if (N < 10) {
            return {};
        }

        unordered_map<string, int> mp;
        vector<string> repeated;

        for (int i = 0; i <= N - 10; i++) {

            string tmp = s.substr(i, 10);

            mp[tmp]++;
        }

        for (auto it : mp) {
            if (it.second > 1) {
                repeated.push_back(it.first);
            }
        }

        return repeated;
    }
};


class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {

        int N = s.size();
        if (N < 10) {
            return {};
        }

        unordered_map<string, int> mp;
        vector<string> repeated;

        for (int i = 0; i <= N - 10; i++) {

            string tmp = s.substr(i, 10);

            // Optimization. Only we add into repeated when it is added for second time, if it more than second time we don't add it again.
            if (mp.count(tmp) && mp[tmp] == 1) {
                repeated.push_back(tmp);
            }

            mp[tmp]++;
        }

        return repeated;
    }
};



class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {

        int N = s.size();
        if (N < 10) {
            return {};
        }

        int character_map[26];
        character_map['A' - 'A'] = 0;
        character_map['C' - 'A'] = 1;
        character_map['G' - 'A'] = 2;
        character_map['T' - 'A'] = 3;

        unordered_map<int, int> mp;
        vector<string> repeated;

        for (int i = 0; i <= N - 10; i++) {

            string tmp = s.substr(i, 10);

            int unique_key = 0;
            for (auto ch : tmp) {
                unique_key = unique_key << 2;               // Shift 2 bit on left side.
                unique_key = unique_key | character_map[ch - 'A'];  // Add 2 bit based on character at the end.
            }

            if (mp.count(unique_key) && mp[unique_key] == 1) {
                repeated.push_back(tmp);
            }

            mp[unique_key]++;

        }

        return repeated;
    }
};