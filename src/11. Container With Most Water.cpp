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

Question :  11. Container With Most Water
Topic : Two Pointer
Problems : https://leetcode.com/problems/container-with-most-water/description/

==============================> Explanation <=============================================

Ultimately, In this question we have to find the largest reactangle(container) with most water.

1) Brute Force:

    To find largest reactangle = finding the largest area of reactangle = max area of subreactangle which is possible for given reactangle.

    What we are thinking of to try out each width(i, j) pairs... and see which sub-reactangle can have maximum area.

    width => (j - i)
    height => min(height[i], height[j]) ex: (3, 5) we can store water upto 3 level only, after it overflow.


2) Two Pointer:


Intiution behind this approach is that,


If height[i] < height[i+1] then for every k > i, maximum water can be hold by height[i] is => height[i].
If height[j] < height[j-1] then for every k < j, max water can be hold by height[k] is => height[k].

For example,

[4, 5, 8, 3, 2, 1]

i = 0, height[i] = 4
sub-reactangle => (4, 5) => max level of water can be store is => 4
sub-reactangle => (4, 8) => max level of water can be store is => 4

j = 5, height[j] = 1
sub-reactangle => (2, 1) => max level of water can be store is => 1
sub-reactangle => (3, 1) => max level of water can be store is => 1

So using this apporach we can start with max width which is possible and then eliminate the lowest height from either end, because at any moment lowest height
can hold water max water is upto that level only...

[4(L), 5, 8, 3, 2, 1(R)]

(L, R) = (4, 1) => min(4, 1) => 1.... It can never store more water then height 1. Not for just L = 4 but also for L = 5, 8, 3, 2, 1..... If we increase the L
then width got shortern so area could decrease so best area is possible is with L on 4.

NOTE: When we increase the L and R pointer, we ulitmately try to seek the bigger heights for (L, R) which can overpower the shrinked width.


==============================> Approach and Time Complexity <============================

N = nums.size()

1) Brute Force
Time: O(N^2)
Space: O(1)

2) Two Pointer
Time: O(N)
Space: O(1)

*/

// TLE
class Solution {
public:

    int maxArea(vector<int>& height) {

        int maximumArea = 0;
        int N = height.size();

        // For each of subreactangle
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                // find max-area.
                maximumArea = max(maximumArea, (j - i) * min(height[i], height[j]));
            }
        }

        return maximumArea;
    }
};


class Solution {
public:

    int maxArea(vector<int>& height) {

        int maximumArea = 0, N = height.size();
        int left = 0, right = N - 1;

        while (left < right) {

            // for(left, right), first find max area possible.
            maximumArea = max(maximumArea, (min(height[left], height[right]) * (right - left)));

            // Shrink the width by increasing one of the pointer.
            if (height[left] < height[right]) {
                left++;
            }
            else {
                right--;
            }

        }

        return maximumArea;

    }
};