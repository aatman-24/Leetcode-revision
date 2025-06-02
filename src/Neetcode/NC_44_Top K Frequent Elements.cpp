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

Problem: NC_44_Top K Frequent Elements
Topic: Hashing
Link: https://neetcode.io/problems/top-k-elements-in-list

================================================================================
                                Problem Summary
================================================================================

Given an integer array `nums` and an integer `k`, return the `k` most frequent elements.
You may return the answer in **any order**.

================================================================================
                                Intuition & Explanation
================================================================================

We need a way to:
1. Count how many times each number appears.
2. Efficiently retrieve the `k` elements with the highest frequency.

### 1. Hashing + Sorting:
- Use a hash map to count frequencies: `freqMap[num] = count`.
- Store pairs `{frequency, number}` in a list.
- Sort the list in descending order of frequency.
- Return the top `k` elements.

### 2. Hashing + Min Heap:
- Use a hash map for frequency count.
- Use a min heap (priority queue) to keep track of top `k` elements.
- For each entry in the frequency map:
  - Push into heap.
  - If heap size exceeds `k`, pop the smallest.
- After processing, heap contains top `k` frequent elements.

### 3. Hashing + Bucket Sort:
- Maximum possible frequency is `n` (length of input array).
- Create a list of buckets where `bucket[i]` holds elements that appeared `i` times.
- Populate the buckets using the frequency map.
- Iterate from the end of the bucket array and collect elements until `k` are found.

✅ This method avoids sorting or heap and achieves optimal time complexity.

================================================================================
                          Approach & Time/Space Complexity
================================================================================

Let N = size of input array, K = number of top elements

🔹 Hashing + Sorting:
- Time Complexity: O(N) for frequency map + O(N log N) for sorting
- Space Complexity: O(N)

🔹 Hashing + Min Heap:
- Time Complexity: O(N) for frequency map + O(N log K) for heap operations
- Space Complexity: O(N)

🔹 Hashing + Bucket Sort:
- Time Complexity: O(N)
- Space Complexity: O(N)

*/

// Hashing + MinHeap
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {

        // countMap
        unordered_map<int, int> mp;

        // count freq
        for (int num : nums) mp[num]++;

        // minHeap ? => we want to eliminate pq.top() if it has less frequency so...
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        for (auto it : mp) {

            int num = it.first;
            int freq = it.second;

            pq.push({freq, num});

            if (pq.size() > k) {
                pq.pop();
            }
        }


        // put the result into the array.
        vector<int> ans;
        while (!pq.empty()) {
            ans.push(pq.top().second);
            pq.pop();
        }

        return ans;

    }
};


// Hashing + Bucket Sort
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {

        // countMap
        unordered_map<int, int> mp;

        // add the freq
        for (int num : nums) mp[num]++;

        // declare the buckets
        int N = num.size() + 1;

        // going to store all the numbers, which have same size...so used vector<int> container
        vector<int> buckets[N];

        // place the number at right bucket
        for (auto it : mp) {
            int size = it.second;
            int num = it.first;
            buckets[size].push_back(num);
        }

        vector<int> ans;

        for (int i = N - 1; i >= 0; i--) {

            // skip the empty bucket
            if (buckets[i].size() == 0) continue;

            for (int num : buckets[i]) {

                ans.push_back(num);

                // store top kth elements only
                if (ans.size() == k)
                    return ans;

            }

        }

        return ans;

    }
};
