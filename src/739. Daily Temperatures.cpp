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

Question : 739. Daily Temperatures
Topic : Stack, Mono-stack
Problems : https://leetcode.com/problems/daily-temperatures/description/

==============================> Explanation <=============================================

Parent: 496. Next Greater Element I,

1) Brute Force: For each temperatures[i] element, I can traverse the remaining array to find
next greater element for nums[i]. And if it is found at jth index, then after (j - i)th day we got warmer temperature.

2) Mono Decreasing stack:

- Idea is that,

Suppose there are

x1 x2 x3 x4 elements into the array.

and (x1 > x2 > x3) < x4.

So for each of the x1, x2 and x3, next greater element is x4.

We manage one mono decreasing stack, and anytime we get st.top() < nums[i]... It means nums[i] is just greater element for st.top().

So stack holds all the elements which doesn't have the next greater element at moment(that's why it is mono decreasing stack)

That's logic.

----

- We use above apporach here, next greater element is next warmer day. And when we get that day we need to just calculate the logic of day difference.
Which I did, check the code!!


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
    vector<int> dailyTemperatures(vector<int>& temperatures) {

        // mono-decreasing stack.
        stack<int> st;

        // answer array
        vector<int> waitDays(temperatures.size(), 0);

        for (int i = 0; i < temperatures.size(); i++) {

            // To calcualte the day's difference we are putting the index into the stack.
            while (!st.empty() && temperatures[st.top()] < temperatures[i]) {       // got warmer day(temperatures[i]) for st.top()'s day.
                waitDays[st.top()] = (i - st.top());
                st.pop();
            }

            st.push(i);
        }

        return waitDays;

    }
};