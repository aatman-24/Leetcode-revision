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

Question : 1670. Design Front Middle Back Queue
Topic : Deque, Doubley Linked List
Problems : https://leetcode.com/problems/design-front-middle-back-queue/description/

==============================> Explanation <=============================================

Given that, we have to perform the push() and pop() operation from front, middle and back position.

It is clear that we have to use something which can allow all operations from front and back. (queue, linkedlist).

Also, we have to perform at the middle as well. (which we need to design)

Idea is that,

We already have DS which can allow to perform operations from front and back side. For the middle position need to build.

1) Brute Force:
- Every time we calculate the mid position(N/2).

push_middle: Pop the element from the back and add into the stack. Add new_element at the back of
queue() and again add those popped_elements into the queue.

pop_middle: same as push_middle... we remove the element after adding N/2 elements into the stack, add again add those.

Issue with this problem is that, we have to perform push and pop operations for N/2 elements.

2) To resolve this issue we can use two dequeue and create the middle of it.

q1: [front.....middle] q2:[middle+1...back]  (case: 1)  [we try to add one extra element into q1 compare to q2 because middle is in q1] (#case-1)
q2: [front.....middle-1] q2:[middle...back]  (case: 2)  [we try to add one extra element into q2 compare to q1 because middle is in q2] (#case-2)

#case-1(middle is in q1)
pushFront -> add into q1 from front, a2b()(if overload)
pushBack -> add into q2 from back, b2a()(if overload)
popFront -> remove from q1 at front, b2a()(if underload)
popBack -> remove from q2 at back, if(q2 is empty, remove from q1) a2b()(if underload)
---
pushMiddle -> both queue have same size, add at the end of q1, otherwise perform a2b() then add at the end of q1
popMiddle -> remove from q1 back, b2a()(if underload)


#case-2(middle is in q2)
pushFront -> add into q1 from front, a2b()(if overload)
pushBack -> add into q2 from back, b2a()(if overload)
popFront -> remove from q1 at front,  if(q1 is empty, remove from q2 front) b2a()(if underload)
popBack -> remove from q2 at back, a2b()(if underload)
---
pushMiddle -> both queue have same size, add at the front of q2, otherwise perform b2a() then add at the front of q2.
==> rathar than checking two conditions, add at the back of q1 and perform a2b()(handle if it is underload/overload)

popMiddle -> remove from q1 back, b2a()(if underload)
=> remove from q2 front, a2b()(if underload)


==============================> Approach and Time Complexity <============================

N = s.size()

2) Stack
Time: O(1) each operation take o(1).
Space: O(N)

*/


// #case-1(middle is in a)
class FrontMiddleBackQueue {

    deque<int> a, b;

    void a2b(deque<int> &a, deque<int> &b) {
        if (a.size() <= b.size() + 1) return;
        b.push_front(a.back());
        a.pop_back();
    }

    void b2a(deque<int> &a, deque<int> &b) {
        if (b.size() <= a.size()) return;
        a.push_back(b.front());
        b.pop_front();
    }

    bool isEmpty() {
        return a.empty() && b.empty();
    }

public:

    FrontMiddleBackQueue() {

    }

    void pushFront(int val) {
        a.push_front(val);
        a2b(a, b);
    }

    void pushMiddle(int val) {
        if (a.size() == b.size()) {
            a.push_back(val);
            return;
        }
        b.push_front(a.back()); a.pop_back();
        a.push_back(val);
    }

    void pushBack(int val) {
        b.push_back(val);
        b2a(a, b);
    }

    int popFront() {
        if (isEmpty())
            return -1;

        int popped_element = a.front();
        a.pop_front();
        b2a(a, b);
        return popped_element;
    }

    int popMiddle() {
        if (isEmpty())
            return -1;

        int popped_element = a.back();
        a.pop_back();
        b2a(a, b);
        return popped_element;
    }

    int popBack() {
        if (isEmpty())
            return -1;

        int popped_element;
        if (!b.empty()) {
            popped_element = b.back();
            b.pop_back();
            a2b(a, b);
        } else {
            popped_element = a.back();
            a.pop_back();
            a2b(a, b);
        }

        return popped_element;
    }
};

/**
 * Your FrontMiddleBackQueue object will be instantiated and called as such:
 * FrontMiddleBackQueue* obj = new FrontMiddleBackQueue();
 * obj->pushFront(val);
 * obj->pushMiddle(val);
 * obj->pushBack(val);
 * int param_4 = obj->popFront();
 * int param_5 = obj->popMiddle();
 * int param_6 = obj->popBack();
 */

