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

Question : 84. Largest Rectangle in Histogram
Topic : Stack, Mono-stack
Problems : https://leetcode.com/problems/largest-rectangle-in-histogram/description/

==============================> Explanation <=============================================

1) Brute Force:
Idea is that, To find a max reactangle = (width * height), we need height and width maximum, we can't increase height but we can consider max width.
Given for each H[i], we try to find maximum width.
For that, we need to find left_boundary and right_boundary. Boundary is element which is first element which is just less than H[i].
And we can keep track of max_area.

2) Precomputation (mono increasing stack):
- Instead of counting the left_bounadary and right_boundary, we can pre-calculate it.
But how to do it ? (Given that, "Boundary is element which is first element which is just less than H[i]" (simliar to next greater, next lesser element))
- We can use the mono stack. Which one increasing or decreasing ?
- We are finding the first element which is just less than H[i], it means st.top() >= H[i](we remove these st.top()). Means we need increasing stack.
- Any time st.top() < H[i], then st.top() is left_boundary. If there is nothing on stack, then left boundary is 0.
- Same we do for the right_boundary.
Check the code!!

3) (Mono increasing stack)
- We can calcualte the left_boundary and right_boundary at runtime.

How ?
- Suppose, we are maintaining increasing stack (2, 3, 4).... so all elements [0, i-1] is less than ith element. It means (i-1)th element in stack is left_boundary.
- And if, current nums[i] which is st.top() > nums[i], then nums[i](right boundary for st.top())
- In short, st: [a b c d(st.top())].. then for C is left_boundary for D and nums[i] is right_boundary.
- [a b c d], nums[i] = e, d got popped out.
- [a b c], nums[i]=e, b < c < e... then for cth height, we b is left_boundary and e is right boundary. And width is (e - b).
Check the code.

Understading of that special case:
4 8 9 7
st = [4, 8, 9]
now, nums[i] = 7, It is right_boundary for 8 and 9 so they got popped out.
pop = 9, left_boundary = 8, right_boundary = 7... so width = 1 #(i-left), here we consider left=2 is after 1th position(only valid constraint).
pop = 8, left_boundary = 4 right_boundary = 7... so width = 2 #(i-left)
(distance from pop_element and nums[i] indicate that atleast pop_element height reactangle can be made with those missing height between those, due to incrasing stack)


==============================> Approach and Time Complexity <============================

N = s.size()

1) Brute Force
Time: O(N^2)
Space: O(1)

2) Mono incresing stack
Time: O(N)
Space: O(N)


*/

// O(N^2) => Give N = 10^5 => It gives TLE.
class Solution {
public:
    int largestRectangleArea(vector<int>& arr) {

        int largest = 0, N = arr.size();

        for (int i = 0; i < arr.size(); i++) {

            // find left boundary and right boundary. Once we get first element less than H[i](cur_height), it means it have height less than H[i].
            // It means we are finding first lesser element than H[i] on both side.
            int left = i, right = i;
            while (left >= 0 && arr[left] >= arr[i] ) {
                left--;
            }

            while (right < N && arr[right] >= arr[i] ) {
                right++;
            }

            int width = (i - left) + (right - i) - 1;    // (i - left) width on left side, (right - i) width on right side, two times width of ith is counted, so we need to subtract that one.
            int height = arr[i];

            largest = max(largest, height * width);
        }

        return largest;
    }
};


class Solution {
public:
    int largestRectangleArea(vector<int>& arr) {

        int largest = 0, N = arr.size();

        stack<int> st;          // increasing stack, because we want to put boundary(i) in left_boundary[i] when st.top() < H[i];
        vector<int> left_boundary(N, 0);
        for (int i = 0; i < arr.size(); i++) {

            while (!st.empty() && arr[st.top()] >= H[i]) {          // st.top() >= H[i], then we can have react reactangle st.top() height as well, we want to get left_bounary which violate constraint for H[i] to be reactangle height.
                st.pop();
            }

            if (st.empty()) {
                left_boundary[i] = 0;
            }
            else {
                left_boundary[i] = st.top() + 1;
            }

            st.push(i);
        }


        while (!st.empty()) st.pop();

        vector<int> right_boundary(N, 0);
        for (int i = N - 1; i >= 0; i--) {

            while (!st.empty() && arr[st.top()] >= H[i]) {          // st.top() >= H[i], then we can have reactangle with st.top() height as well, we want to get right_boundary which violate constraint for H[i] to be reactangle height.
                st.pop();
            }

            if (st.empty()) {
                right_boundary[i] = N - 1;
            }
            else {
                right_boundary[i] = st.top() - 1;
            }

            st.push(i);
        }


        for (int i = 0; i < N; i++) {
            int height = arr[i];
            int width = (i - left_boundary[i]) + (right_boundary[i] - i) + 1;
            // why +1 here, and when -1 in above apporach ?
            // In above approach we are putting boundary which violate the constraint for H[i], And here we are putting(st.top()+1, st.top()-1) right boundary. If it's
            // violate for ith position then we put (i+1, i-1) last fulfill constriant.
            // Two times H[i] got deducted, so we need to add width of H[i].
            largest = max(largest, height * width);

        }

        return largest;
    }
};


class Solution {
public:
    int largestRectangleArea(vector<int>& arr) {

        int largest = 0, N = arr.size();
        stack<int> st;

        for (int i = 0; i <= arr.size(); i++) {

            // Curr H[i] is right boundary for any element on the stack before its because H[i] < arr[st.top()]
            // Those elements are in stack, are waiting for the right_boundary(element lesser than its), those already have left_boundary due to increasing order of stack.
            while (!st.empty() && (i == N || arr[st.top()] >= arr[i])) {

                int j = st.top(); st.pop(); // For jth element, H[i] is right boundary.
                int left = st.empty() ? 0 : st.top() + 1;   // left boundary, stack is in increasing order, // 3 4 5... so element just before arr[i] is left boundary.
                int width = (i - left);
                largest = max(largest, width * arr[j]);
            }

            st.push(i);
        }

        return largest;
    }
};