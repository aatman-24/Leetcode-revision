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

Question : 347. Top K Frequent Elements
Topic : Heap, PQ
Problems : https://leetcode.com/problems/top-k-frequent-elements/description/?envType=problem-list-v2&envId=heap-priority-queue

==============================> Explanation <=============================================

Approach-1:
We can use the priority queue with <freq,num> and then we can pop up first "k" elements out of queue.


Approach-2: (Using Bucket Sorts)
First we calculate the frequency.... then we create the buckets....
- bucket[2] means..we put all element whose freq is 2 into this bucket....

And later we start from the end of the buckets(means from high frequency elements)... and if the bucket is not empty then
we consider that element..... until we get the k elements which we needed.

==============================> Approach and Time Complexity <============================

1) Two Pointer
Time: O(N)
Space: O(N)

*/


// Using Priority Queue....
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {

        // num -> Freq
        unordered_map<int, int> count;
        for (auto n : nums)
            count[n]++;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        for (auto it : count) {
            pq.push({it.second, it.first});
            if (pq.size() > k) pq.pop();
        }

        vector<int> ans;
        while (!pq.empty()) {
            ans.push_back(pq.top().second); pq.pop();
        }

        return ans;
    }
};


// Using Bucket Sort
class Solution {
public:

    vector<int> topKFrequent(vector<int>& nums, int k) {

        // count the frequency....
        unordered_map<int, int> mp;
        for (int num : nums) {
            mp[num]++;
        }

        // create the buckets
        vector<int> bucket[nums.size() + 1];

        // set the frequency...
        for (auto [num, freq] : mp) {
            bucket[freq].push_back(num);
        }

        vector<int> ans;
        for (int i = nums.size(); i >= 0; i--) {
            if (bucket[i].size() > 0) {
                for (auto num : bucket[i]) {
                    ans.push_back(num);
                    k--;
                    if (k == 0)
                        return ans;
                }
            }
        }

        return ans;
    }
};