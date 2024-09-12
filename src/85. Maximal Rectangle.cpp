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

Question : 85. Maximal Rectangle
Topic : Stack, Mono-stack
Problems : https://leetcode.com/problems/maximal-rectangle/description/

==============================> Explanation <=============================================

We know how to find the maximum reactangle if we given only heights[i]. Using T: O(N) and S: O(N).

We use the same apporach here as well,

At first, you don't find the way how to fit that into current problem.

But if we observe well enough, mat[0] + mat[1].. create height of reactangle. So for each row(0 -> N) we have the reactangles with changing the
heights, so finding max reactangle with M rows take O(N*M) time and space.

we have to keep track of heights, any time mat[i][j] = 0, then we dont' have access of previous heights. so we again start with zero.

1 0 1 0 0
1 0 1 1 1 *
1 1 1 1 1
1 0 0 1 0 *

See height[i] for each row.

#1: 1 0 1 0 0
#2: 2 0 2 1 1
#3: 3 1 3 2 1 -> Here we get that 2 * 2 reactangle => 4.
#4: 4 0 0 1 0

==============================> Approach and Time Complexity <============================

N = s.size()

2) Mono incresing stack
Time: O(N*M)
Space: O(N*M)


*/

class Solution {
public:

    int findMaxReactangle(vector<int> arr) {

        stack<int> st;
        int max_reactangle = 0;

        for (int i = 0; i <= arr.size(); i++) {

            while (!st.empty() && (i == arr.size() || arr[st.top()] > arr[i])) {

                int j = st.top(); st.pop();
                int left = st.empty() ? 0 : st.top() + 1;
                int width = (i - left);
                max_reactangle = max(max_reactangle, arr[j] * width);

            }

            st.push(i);
        }

        return max_reactangle;

    }



    int maximalRectangle(vector<vector<char>>& mat) {

        int maxReactangle = 0, N = mat.size(), M = mat[0].size();
        vector<int> prefix(M, 0);

        for (int i = 0; i < N; i++) {

            for (int j = 0; j < M; j++) {

                if (mat[i][j] == '0') {
                    prefix[j] = 0;
                }
                else {
                    prefix[j] += 1;
                }
            }

            maxReactangle = max(maxReactangle, findMaxReactangle(prefix));

        }

        return maxReactangle;
    }
};