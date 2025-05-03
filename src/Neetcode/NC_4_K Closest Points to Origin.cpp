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

Question : NC_4_K Closest Points to Origin
Topic : Heap, PQ
Problems : https://neetcode.io/problems/k-closest-points-to-origin

==============================> Explanation <=============================================

Approach-1: Use Priority Queue
Idea is that, we can use the maxHeap to get the smallest kth elements. Again I'm repeating...
Why maxHeap when we need kth smallest elements => when we need to pop out element it should be maximum
out of all elements which is characteristic of maxHeap....


Apporach-2: QuickSort_Partition Method
What we need is kth closest points.... right ? So if we use the partition method it's also give us result...

Because, when we return pivotIndex(from left all are lessers and right all are greater), when it is equals to K... it means
our closest points are all left points..

Used same template: NC_3_Kth Largest Element in an Array


Note: This partition method can be used, when you need (kth smallest | kth largest, all element which are less than k but order is not imp)


==============================> Approach and Time Complexity <============================

1) PQ
Time: O(NLogN)
Space: O(N)

*/


// Apporach-1: Priority Queue Solution
class Solution {
private:
    // Return squared Euclidean distance
    int getDistance(const vector<int>& point) {
        return point[0] * point[0] + point[1] * point[1];
    }

    // Custom comparator as a struct (this is imp, why to solve this question)
    struct Compare {
        bool operator()(const vector<int>& a, const vector<int>& b) {
            int distA = a[0] * a[0] + a[1] * a[1];
            int distB = b[0] * b[0] + b[1] * b[1];
            return distA < distB; // max-heap -> largest distance on top
        }
    };

public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        priority_queue<vector<int>, vector<vector<int>>, Compare> pq;

        for (const auto& point : points) {
            pq.push(point);
            if (pq.size() > k) {
                pq.pop();  // remove the farthest point
            }
        }

        vector<vector<int>> closest;
        while (!pq.empty()) {
            closest.push_back(pq.top());
            pq.pop();
        }

        return closest;
    }
};



// Approach-2: Using Quicksort_parition method
class Solution {

private:

    // Return squared Euclidean distance
    int getDistance(const vector<int>& point) {
        return point[0] * point[0] + point[1] * point[1];
    }

public:

    int partition(vector<vector<int>> &points, int left, int right) {
        int pIndex = left;
        int pDistance = getDistance(points[left]);
        int l = left + 1;
        int r = right;
        while (l <= r) {
            while (l <= r && (getDistance(points[l])) <= pDistance) l++;
            while (l <= r && pDistance <= getDistance(points[r])) r--;
            if (!(l <= r)) break;
            swap(points[l], points[r]);
        }
        swap(points[pIndex], points[r]);
        return r;
    }

    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        int left = 0, right = points.size() - 1;
        while (left <= right) {
            int pIndex = partition(points, left, right);
            if (pIndex == k) {
                break;
            }
            if (pIndex < k) {
                left = pIndex + 1;
            }
            else {
                right = pIndex - 1;
            }
        }

        vector<vector<int>> closest;
        int index = 0;
        while (index < k) {
            closest.push_back(points[index++]);
        }


        return closest;
    }
};
