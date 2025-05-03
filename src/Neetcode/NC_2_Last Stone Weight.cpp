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

Question : NC_2_Last Stone Weight
Topic : Heap, PQ
Problems : https://neetcode.io/problems/last-stone-weight

==============================> Explanation <=============================================

Idea is that, we can push the all elements into the maxHeap..so when we need most weighted elements,
we can get it O(1)(to access) + O(logN)(heapify). Again we push the remaining weight into the PQ.

==============================> Approach and Time Complexity <============================

1) PQ
Time: O(NLogN)
Space: O(N)

*/



class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {

        // max heap
        priority_queue<int, vector<int>> pq;

        for (int weight : stones) {
            pq.push(weight);
        }

        while (pq.size() > 1) {
            int w1 = pq.top(); pq.pop();
            int w2 = pq.top(); pq.pop();
            if (w1 == w2) continue;
            pq.push(abs(w1 - w2));
        }

        return pq.size() == 1 ? pq.top() : 0;
    }
};
