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

Question :  622. Design Circular Queue
Topic : Queue
Problems : https://leetcode.com/problems/design-circular-queue/description/

==============================> Explanation <=============================================

To design circular array,
- we have front and rear pointer, front is used to delete and rear is used to insert. (As usual in queue)
- only thing different is that, Last position N - 1 again points to first poistion 0.

To avoid managing the front and rear pointer when they hits exterme points, we can use the % opereator.

Operation:

front => points to front element of queue. We delete element on front and increase the pointer.
Edge case: if first element added into the queue,
    make front poitner points to that.

rear => points to last added element, so when we add new element, we increase the pointer and add it.

push() => increase the rear and add it.

pop() =>  just increase the front pointer

    edge case:
    - if rear==front, it queue have 1 element and both rear and front points to same element, so after deleting it we need
    make rear=front=-1.

front() => return element at front
rear() => return element at rear
isEmpty() => (front == -1 && rear == -1)
full() => check if, rear + 1 == front. It means we want to add new element at rear+1, but this position is already occupied with front of element.



==============================> Approach and Time Complexity <============================

N = s.size()

2) Stack
Time: O(1) each operation take o(1).
Space: O(N)

*/


class MyCircularQueue {
public:

    int front = -1, rear = -1, N;
    vector<int> arr;

    MyCircularQueue(int k) {
        N = k;
        arr.assign(N, 0);
    }

    bool enQueue(int value) {
        if (isFull()) {
            return false;
        }
        rear = (rear + 1) % N;      // increase rear
        arr[rear] = value;          // put rear on it
        if (front == -1)            // if front == -1, then increase front because front points to the front of queue
            front = (front + 1) % N;
        return true;
    }

    bool deQueue() {
        if (isEmpty()) {
            return false;
        }
        if (front == rear) {    // front and rear points to same, means last element it is in queue
            front = -1;
            rear = -1;
        }
        else {
            front = (front + 1) % N;
        }
        return true;
    }

    int Front() {
        if (isEmpty())
            return -1;
        return arr[front];
    }

    int Rear() {
        if (isEmpty())
            return -1;
        return arr[rear];
    }

    bool isEmpty() {
        return front == -1 && rear == -1;
    }

    bool isFull() {
        return front == (rear + 1) % N;
    }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */