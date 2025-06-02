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

Problem: NC_19_Partition Labels
Topic: Greedy
Link: https://neetcode.io/problems/partition-labels

================================================================================
                                Problem Summary
================================================================================

Given a string, partition it into as many parts as possible such that each letter
appears in at most one part. Return a list of integers representing the size of these parts.

================================================================================
                                Intuition & Explanation
================================================================================

The goal is to group all instances of the same character into one segment, ensuring
no character appears in more than one segment. To achieve this:

1. Record the last occurrence of each character.
2. Iterate through the string while maintaining a window from the current index to
   the farthest last occurrence of any character seen so far.
3. When the current index reaches the end of the window, we've found a valid partition.
   Start a new partition from the next character.

Example:
For string "abac",
- The last occurrence of 'a' is at index 2
- The last occurrence of 'b' is at index 1
We expand the window to include both until the farthest index (2), and then cut the partition.

================================================================================
                          Approach & Time/Space Complexity
================================================================================

Approach: Greedy
Time Complexity: O(N) – Single pass through the string
Space Complexity: O(1) – Fixed size map of 26 letters (constant space)
*/



class Solution {
public:
    vector<int> partitionLabels(string s) {
        int N = s.size();

        // we store the lastIndex of every character
        unordered_map<char, int> lastIndex;
        for (int i = 0; i < N; i++) {
            lastIndex[s[i]] = i;
        }

        vector<int> partition;

        int start = 0;

        while (start < N) {

            // [L........R]
            int L = start;
            int R = lastIndex[s[start]];

            // we know that, ch(s[start]) is starting from the "L" and ending at "R".
            // so in between any characters comes, whose ending is > R...then we expand the range.
            for (int i = L; i <= R; i++) {
                R = max(R, lastIndex[s[i]]);
            }

            int lengthOfPartition = R - L + 1;
            partition.push_back(lengthOfPartition);

            start = R + 1;
        }

        return partition;
    }
};
