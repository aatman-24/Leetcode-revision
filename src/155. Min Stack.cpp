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

Problem: NC_44_Longest Substring Without Repeating Characters
Topic: Hashing
https://neetcode.io/problems/count-connected-components

================================================================================
                                Problem Summary
================================================================================

{generate based on above link}


================================================================================
                                Intuition & Explanation
================================================================================





================================================================================
                          Approach & Time/Space Complexity
================================================================================

Approach: Hashing
Time Complexity: O(N+E)
Space Complexity: O(N+E)

*/



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

Question: 155. Min Stack
Topic : Design Question, Stack
Problems : https://leetcode.com/problems/min-stack/

==============================> Explanation <=============================================
Design Question:

Solution is Based on Cracking the Coding Interview.

1) Brute Force:
- Using single variable keep track of minValue. But when the minValue element is popped that time
we have to visit all the stack and again find the next minValue. Which is costly and not O(1).

Valid Solution:

- We can keep track of minValue at every step so every time we call minValue() we can directly
return top of stack minValue.

1) Create a minStack using Node Structure.

2) Use Two stack.

3) Using One Stack:

Idea is that, instead of pushing the element into the stack, we push the diff between element and current minimum value, and also
update the minValue. It is strange but yes, that's how we store it, and when we pop the element that time we make sure we update the minValue
 if we are poping current minimum of stack. Check the code...


In a normal stack, you lose track of the minimum when elements are popped. To solve this, many solutions use two stacks: one for values and one for tracking the minimum at each level.

But what if you could avoid the second stack and still know when the minimum changes?

Here’s the key idea:

Instead of pushing the actual number, push the difference between the number and the current minimum.

Now, think about what this difference tells you:

If the difference is positive, the number is greater than or equal to the current minimum.

If the difference is negative, the number is the new minimum — it dropped lower than any before.

This difference becomes a signal:

"Hey, this value introduced a new minimum" (negative difference),

or "This value didn’t affect the minimum" (positive difference).

When you pop and see a negative difference, it means the value that was popped had changed the min. So, you can use the difference to recover the previous min — as if you're undoing that change.

For the top:

If the difference is negative, the actual top is the current min.

If it’s positive, just add the difference back to min to get the real value.

You're not storing all minimums. You're storing how each value changed the minimum (or didn't). This "change-tracking" approach makes it possible to always reconstruct the current or previous min from just one value and one variable.

==============================> Apporach and Time Complexity <=============================================

1) Top-Down Pattern = Cadane
Time: O(N)
Space: O(1)

*/


class Node {

public:

    int minValue, value;
    Node* next;

    Node(int val, int minVal, Node* nxt) {
        value = val;
        minValue = minVal;
        next = nxt;
    }
};


// Design Question, Create Node in which we keep track of MinValue at every Step.
class MinStack {

public:

    Node* top_;

    MinStack() {
        top_ = nullptr;
    }

    void push(int val) {
        int curMin = getMin();
        Node* nwNode = new Node(val, min(val, curMin), top_);
        top_ = nwNode;
    }

    void pop() {
        if (top_ != nullptr)
            top_ = top_->next;
    }

    int top() {
        if (top_ == nullptr)
            return INT_MAX;
        return top_->value;
    }

    int getMin() {
        if (top_ == nullptr)
            return INT_MAX;
        return top_->minValue;
    }
};





// Using Two STL stack to keep track of element and minValue.
class MinStack {

public:

    stack<int> st;
    stack<int> minValueSt;

    MinStack() {

    }

    void push(int val) {
        int minValue = getMin();
        if (val <= minValue)
            minValueSt.push(val);
        st.push(val);

    }

    void pop() {
        int minValue = getMin();
        if (st.top() == minValue)
            minValueSt.pop();
        st.pop();
    }

    int top() {
        return st.top();
    }

    int getMin() {
        if (minValueSt.empty())
            return INT_MAX;
        return minValueSt.top();
    }
};





// Using Two Vector as stack to keep track of element and minValue.
class MinStack {

public:

    vector<int> st;
    vector<int> minValueSt;

    MinStack() {

    }

    void push(int val) {
        int minValue = getMin();
        if (val <= minValue)
            minValueSt.push_back(val);
        st.push_back(val);

    }

    void pop() {
        int minValue = getMin();
        if (st.back() == minValue)
            minValueSt.pop_back();
        st.pop_back();
    }

    int top() {
        return st.back();
    }

    int getMin() {
        if (minValueSt.empty())
            return INT_MAX;
        return minValueSt.back();
    }
};


// Using one Stack

class MinStack {

private:

    long min;
    stack<long> st;

public:
    MinStack() {}

    void push(int val) {

        if (st.empty()) {
            st.push(0);             // st is empty, that time diff is 0
            min = val;              // first element is minimum
        } else {
            st.push(val - min);         // push the diff, diff < 0 => val is new minimum, diff > 0 => val is greater than current minimum
            if (val < min) min = val;   // new minimum found, keep track of it
        }
    }

    void pop() {
        if (st.empty()) return;

        long pop = st.top();
        st.pop();

        // diff < 0 => popping the minimum of stack, so you need to get previous minimum by reversing operation,
        if (pop < 0) min = min - pop;
    }

    int top() {

        long top = st.top();

        // diff > 0 => top of stack is top + minimum
        // diff < 0 => top of stack is minimum
        return (top > 0) ? (top + min) : (int)min;
    }

    int getMin() {
        return (int)min;
    }
};