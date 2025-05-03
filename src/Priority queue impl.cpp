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

Question : Priority queue impl
Topic : Heap
Problems : PQ

==============================> Explanation <=============================================

Priority Queue
---
We use the heap = [] (array implementation)
Insert: Add element at the end of the heap, then perform the heapifyUp() from that position.
Remove(n): Search the n into the heap, if found it... swap with last element in the heap... and perform heapDown() from that index.
Pop(): Replace the last element with first element, and perform heapifyDown(0) from 0th index.

heapifyUp(index) => we compare heap[index] and its parent(heap[index-1/2]), until child < parent.
heapifyDown(index) => we compare current elements and its childresn(left and right).... we replace the parent with smallest child.


==============================> Approach and Time Complexity <============================

1) Two Pointer
Time: O(N)
Space: O(N)

*/



class MinHeap {
private:
    vector<int> heap;

    // Heapify up (used after inserting an element)
    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index] < heap[parent]) {
                swap(heap[index], heap[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    // Heapify down (used after removing the root)
    void heapifyDown(int index) {
        int size = heap.size();
        while (true) {
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;
            int smallest = index;

            if (leftChild < size && heap[leftChild] < heap[smallest]) {
                smallest = leftChild;
            }
            if (rightChild < size && heap[rightChild] < heap[smallest]) {
                smallest = rightChild;
            }
            if (smallest == index) break;

            swap(heap[index], heap[smallest]);
            index = smallest;
        }
    }

public:
    // Insert a value into the heap
    void insert(int value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    // Remove a specific value from the heap
    void remove(int value) {
        int size = heap.size();
        for (int i = 0; i < size; i++) {
            if (heap[i] == value) {
                heap[i] = heap[size - 1];  // Replace with last element
                heap.pop_back();  // Remove last element
                heapifyDown(i);
                return;
            }
        }
        cout << "Value not found in heap.\n";
    }

    // Pop (Extract Min)
    int pop() {
        if (heap.empty()) {
            cout << "Heap is empty!\n";
            return -1;
        }
        int minValue = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
        return minValue;
    }

    // Heapify a given array into a heap
    void heapify(vector<int>& arr) {
        heap = arr;
        for (int i = (heap.size() / 2) - 1; i >= 0; i--) {
            heapifyDown(i);
        }
    }

    // Display heap elements
    void display() {
        cout << "Heap: ";
        for (int val : heap) {
            cout << val << " ";
        }
        cout << "\n";
    }

    // Get the top element
    int top() {
        return heap.empty() ? -1 : heap[0];
    }

    // Check if the heap is empty
    bool isEmpty() {
        return heap.empty();
    }
};

int main() {
    MinHeap pq;

    pq.insert(10);
    pq.insert(5);
    pq.insert(20);
    pq.insert(15);

    pq.display();  // Output: Heap: 5 10 20 15

    cout << "Pop: " << pq.pop() << "\n";  // Output: 5
    pq.display();  // Output: Heap: 10 15 20

    pq.remove(15);
    pq.display();  // Output: Heap: 10 20

    return 0;
}