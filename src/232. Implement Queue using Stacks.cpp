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

Question : 232. Implement Queue using Stacks
Topic : Stack
Problems : https://leetcode.com/problems/implement-queue-using-stacks/description/

==============================> Explanation <=============================================

Idea is that,

we use two stack.

push -> add into the pushed stack. so order of element is [last_added - first_added]
pop -> manage one other stack, which role is to pop element out of it. so if it is empty we transfer element from s1 -> s2...
so order is s2 is [first_added - last_added], if it is not empty we remove st.top() out of it.

==============================> Approach and Time Complexity <============================

N = s.size()

2) Stack
Time: O(1) each operation take o(1).
Space: O(N)

*/


class MyQueue {
public:

    // manage two stack.
    stack<int> pushed;
    stack<int> popped;

    MyQueue() {

    }

    // Take O(1). Every time we push new element into the pushed stack.
    void push(int x) {
        pushed.push(x);
    }

    // Take O(1)* Amortized. If popped stack have elements remove from it, otherwise transfer elements from pushed -> popped, and then remove it.
    int pop() {

        if (empty())
            return -1;

        if (popped.empty()) {
            while (!pushed.empty()) {
                popped.push(pushed.top());
                pushed.pop();
            }
        }

        int num = popped.top(); popped.pop();
        return num;
    }

    // Simliar to pop()
    int peek() {

        if (empty())
            return -1;

        if (popped.empty()) {
            while (!pushed.empty()) {
                popped.push(pushed.top());
                pushed.pop();
            }
        }

        return popped.top();
    }

    bool empty() {
        return popped.empty() && pushed.empty();
    }
};
/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */