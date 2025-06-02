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

Question : NC_18_Merge Triplets to Form Target Triplet
Topic    : Greedy / Observation
Link     : https://neetcode.io/problems/merge-triplets-to-form-target-triplet

==============================> Explanation <=============================================

The main idea is to **filter out invalid triplets** first.

1. **Observation**:
   When merging triplets, for each coordinate (x, y, z), we always take the maximum among triplets.
   So, if any triplet has a coordinate **greater than** the corresponding target coordinate,
   it can potentially ruin the merge result and should be skipped.

2. **Filtering**:
   Keep only triplets where all coordinates `≤` target triplet coordinates.

3. **Merging**:
   From the remaining valid triplets, take the maximum of x, y, and z separately.
   If the merged triplet equals the target triplet, return true.
   Else, return false.

==============================> Time and Space Complexity <===============================

Time  : O(N)
Space : O(1)

*/

// Proper Greedy Solution

class Solution {
public:
    bool mergeTriplets(vector<vector<int>>& triplets, vector<int>& target) {

        unordered_set<int> visitedCoordinates;

        for (vector<int> triplet : triplets) {

            // If any coordinate (x, y, z) in a triplet is greater than the corresponding target (a, b, c),
            // the triplet cannot be used — because merging only works with values ≤ target coordinates.
            if (triplet[0] > target[0] || triplet[1] > target[1] || triplet[2] > target[2])
                continue;

            for (int i = 0; i < triplet.size(); i++) {

                // which coordinate is mathching with target, that we put inside the set.
                // now you get, we used the set because it is possible same corordinate we get here
                if (triplet[i] == target[i]) {
                    visitedCoordinates.insert(i);
                }

            }

        }

        // set contain all threee coordinates (x, y, z) it means we found complete triplet
        return visitedCoordinates.size() == 3;
    }
};
