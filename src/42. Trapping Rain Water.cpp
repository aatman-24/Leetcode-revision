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

Question :  42. Trapping Rain Water
Topic : Prefix, Two Pointer, Stack
Problems : https://leetcode.com/problems/trapping-rain-water/description/

==============================> Explanation <=============================================

What is diff between this question and 11. Container With Most Water ?
- In that qustion, there is distance of 1 between two heigths. But in this question, it is not. There we have to find largest container(reactangle)
but here we need to find the total area, not maximum.


1) Brute Force:
- Water can be store on any height(arr[i]) is => MIN(left_side_height_support, right_side_height_support) - (current_height).
- So for each heights[i], we find that area and sum it up as total water.

2) Prefix + Suffix Calcuation:

- Instead of finding the left or right side height support for each of height during that time, we can precalcualte it and use that.
Again equation is same,

    prefix[i] = max(prefix[i-1], cur[i]), where prefix[i-1] holds the maximum height support till [0, i-1] (left, side)
    suffix[i] = max(suffix[i+1], cur[i]), where suffix[i-1] holds the maximum height support till [i+1, N] (right side)

    area(i) = MIN(left_side_height_support, right_side_height_support) - (current_height)
            = min(prefix[i] - suffix[i]) - arr[i]

    What could be the value of prefix[0] and suffix[N-1] is first and last element respectively. Because those are extreme boundary so prefix[-1] can be consider
    as minimum and suffix[N] also simliar way.

    prefix[0] => holds the maximum height support till [0, 0]... it means height[0].. right ? Yes.


3) Two Pointer Appraoch:
- I thought two pointer can't be applied here compared to  11. Container With Most Water, But I'm wrong.

Intuition is that, instead of pre-calculating the left_side_height_support & right_side_height_support, we can do it dynamically. We can use
two pointer to hold those value.

There is left and right pointer. We advance one of the point which have less height(so opposite one become right side extreme point). We keep track
of left_side_height_support and right_side_height_support and calculate area check code.



4) Monotonic Decreasing Stack:

Intuition behind this approach is that,

When we push element out of stack,
    popped_element = st.pop()
    st.top() become left_side_height_support for popped_element
    height[i] become right_side_height_support for popped_element

based on that we calculate total water.

Edge case: When we pop element out of stack(popped_element) that time if no element left in the stack, it means no left_side_height_support. Which we need
to handle.

This apporach work because we keep adding left_side_height_support in stack until we find the right_side_height_support.


==============================> Approach and Time Complexity <============================

N = nums.size()

1) Brute Force
Time: O(N^2)
Space: O(1)

2) Prefix + Suffix Calcuation
Time: O(N)
Space: O(N)

3) Two Pointer
Time: O(N)
Space: O(1)

3) Monotonic Decreasing Stack
Time: O(N)
Space: O(1)

*/



class Solution {
public:
    int trap(vector<int>& height) {

        int totalWater = 0, N = height.size();

        for (int i = 0; i < N; i++) {

            // Finding Left Side and Right side Height Support for current height.
            int leftSideHeightSupport = height[i], rightSideHeightSupport = height[i];
            for (int j = 0; j < i; j++) leftSideHeightSupport = max(leftSideHeightSupport, height[j]);
            for (int k = i + 1; k < N; k++) rightSideHeightSupport = max(rightSideHeightSupport, height[k]);

            totalWater += min(leftSideHeightSupport, rightSideHeightSupport) - height[i];

        }

        return totalWater;
    }
};



class Solution {
public:
    int trap(vector<int>& height) {

        int totalWater = 0, N = height.size();

        // Pre-calculate the maximum left side support.
        int prefix[N];
        prefix[0] = height[0];
        for (int i = 1; i < N; i++) {
            prefix[i] = max(prefix[i - 1], height[i]);
        }

        // Pre-calculate the maximum right side support.
        int suffix[N];
        suffix[N - 1] = height[N - 1];
        for (int i = N - 2; i >= 0; i--) {
            suffix[i] = max(suffix[i + 1], height[i]);
        }

        // Calcualte total water.
        for (int i = 0; i < N; i++) {
            totalWater += min(prefix[i], suffix[i]) - height[i];
        }

        return totalWater;
    }
};


class Solution {
public:
    int trap(vector<int>& height) {

        int totalWater = 0, N = height.size();
        int left = 0, right = N - 1;
        int left_side_height_support = INT_MIN, right_side_height_support = INT_MIN;

        while (left < right) {

            if (height[left] <= height[right]) {

                if (left_side_height_support > height[left]) {
                    totalWater += left_side_height_support - height[left];
                }

                left_side_height_support = max(left_side_height_support, height[left]);
                left++;

            } else {

                if (right_side_height_support > height[right]) {
                    totalWater += right_side_height_support - height[right];
                }

                right_side_height_support = max(right_side_height_support, height[right]);
                right--;
            }

        }

        return totalWater;
    }
};


class Solution {
public:
    int trap(vector<int>& height) {

        int totalWater = 0, N = height.size();
        stack<int> st;
        for (int i = 0; i < N; i++) {

            // height[st.top()] < height[i](right_side_height_support)
            while (!st.empty() && height[st.top()] < height[i]) {

                int poppedElementIndex = st.top(); st.pop();

                if (st.empty()) {
                    break;
                }

                // height[st.top()] (left_side_height_support)
                int height_of_i = min(height[st.top()], height[i]) - height[poppedElementIndex];
                int width_of_i = (i - st.top() - 1);
                totalWater += (height_of_i * width_of_i);
            }

            st.push(i);
        }

        return totalWater;
    }
};



