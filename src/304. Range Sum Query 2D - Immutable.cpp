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

Question : 304. Range Sum Query 2D - Immutable
Topic : PrefixSum
Problems : https://leetcode.com/problems/range-sum-query-2d-immutable/description/

==============================> Explanation <=============================================

1) Brute Force:
- For each (r1, c1) to (r2, c2), use two for loops and calcualte the sum. Each Query will take O(N*M) time. IF K query, Time: O(NMK), O(1)

2) Pre-computation:
- We can perform prefix sum on entire matrix from left -> right first, up -> down second. Doing that,
- s[i, j] contains sum from (0, 0) to (i, j).

Given that we need to find sum of (r1, c1) to (r2, c2):

s[r2, c2] contains the sum from s[0,0]->s[r2,c2].

We need to subtract addition element which got added. If you create matrix and try to visualize it, you can get idea.

sum(r1, c1) to sum(r2, c2) = prefix(r2, c2) - prefix(r1-1, c2) - prefix(r2, c1-1) + prefix(r1-1, c1-1)

You see we have added prefix(r1-1, c1-1) because, due to two substraction elements from (0,0) -> (r1-1, c1-1) got subtracted two times,
so we need to add it again.


==============================> Approach and Time Complexity <============================

N = s.size()

1) Brute Force
Time: O(N*M*K), For k Query. 
Space: O(1)

2) prefixProduct && suffixProduct
Time: O(N*M), Query: O(1)
Space: O(N*M)

*/



class NumMatrix {
public:

    vector<vector<int>> prefix;

    NumMatrix(vector<vector<int>>& matrix) {
        prefix = matrix;
        int M = matrix.size(), N = matrix[0].size();

        for (int i = 0; i < M; i++) {
            for (int j = 1; j < N; j++) {
                prefix[i][j] += prefix[i][j - 1];
            }
        }

        for (int j = 0; j < N; j++) {
            for (int i = 1; i < M; i++) {
                prefix[i][j] += prefix[i - 1][j];
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {

        int total = prefix[row2][col2];

        if (row1 - 1 >= 0) {
            total -= prefix[row1 - 1][col2];
        }

        if (col1 - 1 >= 0) {
            total -= prefix[row2][col1 - 1];
        }

        if (row1 - 1 >= 0 && col1 - 1 >= 0) {
            total += prefix[row1 - 1][col1 - 1];
        }

        return total;
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */
