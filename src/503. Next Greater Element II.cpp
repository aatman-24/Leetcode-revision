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

Question : 503. Next Greater Element II
Topic : Stack, Mono-stack
Problems : https://leetcode.com/problems/next-greater-element-ii/description/

==============================> Explanation <=============================================

Parent: 496. Next Greater Element I, This question is extension of the #496.

So here, array is circular, for the last element nums[N-1] next element is nums[0]. So we need to incorporate that logic.

It means for nums[N-1] greater element can be from {nums[0]...nums[N-2]}.


1) Brute Force: For each nums[i] element, I can traverse the remaining array to find
next greater element for nums[i]. And for nums[N-1] I need to traverse nums[0] to nums[N-2] to get greater element.

2) Mono Decreasing stack:

- Idea is that,

Suppose there are

x1 x2 x3 x4 elements into the array.

and (x1 > x2 > x3) < x4.

So for each of the x1, x2 and x3, next greater element is x4.

We manage one mono decreasing stack, and anytime we get st.top() < nums[i]... It means nums[i] is just greater element for st.top().

So stack holds all the elements which doesn't have the next greater element at moment(that's why it is mono decreasing stack)

That's logic.

Extension: Here we need to handle the special case for num[N-1]. Either I can traverse entire array to get greater element for num[N-1] or I can use
the same approach. We can push (0, N-2) elements into the nums again and use the same approach. During the answer we can only return greater element for
original array. Check the code..

2) So rathar than doing physically(adding elements into nums) we can perform using virtually using % opearator.
There N elements, need to traverse same element two times -> 2N, except the last one -> 2N-1.
Whenever we get element from array use the % N. Check the code!!


==============================> Approach and Time Complexity <============================

N = s.size()

1) Brute Force
Time: O(N^2)
Space: O(1)

2) Mono incresing stack
Time: O(N)
Space: O(N)


*/


class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int N = nums.size();
        for (int i = 0; i < N - 1; i++) {
            nums.push_back(nums[i]);
        }

        vector<int> ans(N, -1);
        stack<int> st;

        for (int i = 0; i < nums.size(); i++) {
            while (!st.empty() && nums[st.top()] < nums[i]) {
                if (st.top() < N)
                    ans[st.top()] = nums[i];
                st.pop();
            }
            st.push(i);
        }

        return ans;

    }
};


class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int N = nums.size();

        vector<int> ans(N, -1);

        stack<int> st;

        for (int i = 0; i < 2 * N - 1; i++) {
            while (!st.empty() && nums[st.top() % N] < nums[i % N]) {   // here we used % N
                if (st.top() < N)
                    ans[st.top()] = nums[i % N];                         // here we used % N
                st.pop();
            }
            st.push(i);
        }

        return ans;

    }
};