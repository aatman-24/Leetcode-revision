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

Question : NC_1_Kth Largest Element in a Stream
Topic : Heap, PQ
Problems : https://neetcode.io/problems/kth-largest-integer-in-a-stream

==============================> Explanation <=============================================

Why to use minHeap ?
- We need to keep the heap size fixed of K elements. It means that... heap.top() size points to kth largest element... because
all other elements in the heap are greater than that.
- Add whenever we add the new element, we pop out smallest number from heap, to maintain that property(fixed size k).
- If we have asked smallest elements then I need to use maxHeap...(st.top() points to kth smallest element).


==============================> Approach and Time Complexity <============================

1) PQ
Time: O(NLogK)
Space: O(K)

*/


class KthLargest {

private:

    int maxSize;

    // min heap
    priority_queue<int, vector<int>, greater<int>> pq;

    int insertNewElementAndReturnKthLargest(int num) {
        pq.push(num);

        // size more than k, need to pop out element.
        if (pq.size() > maxSize) {
            pq.pop();
        }

        // return kth largest, which is point to top of heap.
        return pq.top();
    }

public:


    KthLargest(int k, vector<int>& nums) {
        maxSize = k;
        for (int num : nums) {
            insertNewElementAndReturnKthLargest(num);
        }
    }

    int add(int val) {
        return insertNewElementAndReturnKthLargest(val);
    }
};
