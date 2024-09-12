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

Question : 496. Next Greater Element I
Topic : Stack, Mono-stack
Problems : https://leetcode.com/problems/next-greater-element-i/description/

==============================> Explanation <=============================================

1) Brute Force: For each nums1[i] element, I can locate that into nums2[i]. If it is at jth location, I can traverse the remaining array to find
next greater element for nums1[i].

2) Mono Decreasing stack:

- Idea is that,

Suppose there are

x1 x2 x3 x4 elements into the array.

and (x1 > x2 > x3) < x4.

So for each of the x1, x2 and x3, next greater element is x4.

We manage one mono decreasing stack, and anytime we get st.top() < nums[i]... It means nums[i] is just greater element for st.top().

So stack holds all the elements which doesn't have the next greater element at moment(that's why it is mono decreasing stack)

That's logic.


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
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {

        // mono decreasing
        stack<int> st;

        // key: nums2[i], value=next_greater_element
        unordered_map<int, int> mp;
        for (int num : nums2) {
            while (!st.empty() && st.top() < num) {
                mp[st.top()] = num;
                st.pop();
            }
            st.push(num);
        }

        // Getting next greater elements for the nums1 array.
        vector<int> nextGraterElements;
        for (int num : nums1) {
            nextGraterElements.push_back(mp.count(num) ? mp[num] : -1);
        }
        return nextGraterElements;
    }
};