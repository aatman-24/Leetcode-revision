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
================================ Description ================================

📝 Problem: NC_16_Hand of Straights
🔗 Link: https://neetcode.io/problems/hand-of-straights
🧠 Topic: Greedy

=============================== Explanation ===============================

🎯 **Goal**: Check if it's possible to rearrange the given hand of cards into groups of `groupSize` consecutive cards.

🧩 **Core Idea**:
If we can find the smallest (first) element of a group, we can check if the next `groupSize - 1` consecutive elements exist to form a valid group.

---

🔍 **Brute Force Approach**:
- Use a frequency map to track the count of each element.
- Sort the array to always start with the smallest available element.
- For each element with non-zero frequency, try to form a group of `groupSize` consecutive numbers.
- Decrease frequency accordingly.

---

⏳ **Priority Queue Optimization**:
- Instead of sorting the entire array, use a min-heap (priority queue) to always access the smallest element.
- Sync the heap with the frequency map: if frequency drops to zero, ensure it's removed from the heap.
- Prevent outdated top elements from interfering by checking consistency with the frequency map.

---

🔢 **Hashing Approach**:
- Use a frequency map.
- For each number, backtrack to find the earliest possible group start.
- Form groups starting from that point.
- Ensures all elements (especially those with higher frequency) are covered properly.

===================== Approach Summary & Time Complexity ====================

1️⃣ Greedy with Sorting
⏱ Time: O(N log N + N * groupSize)
📦 Space: O(N)

2️⃣ Greedy with Min-Heap (Priority Queue)
⏱ Time: O(N log N + N * groupSize)
📦 Space: O(N)

3️⃣ Hashing
⏱ Time: O(N * groupSize)
📦 Space: O(N)

=========================================================================
*/

// Brute-Force approach
class Solution {
public:

	bool isNStraightHand(vector<int>& arr, int groupSize) {

		int N = arr.size();

		if (N % groupSize != 0) return false;

		// sort the array
		sort(arr.begin(), arr.end());

		// create the freq map...
		unordered_map<int, int> mp;
		for (int num : arr) {
			mp[num]++;
		}

		// check for each num
		for (int num : arr) {

			// num's freq > 0... it means all the numbers in this group must be
			// available
			if (mp[num] > 0) {

				// check all memeber of group is available
				for (int i = num; i < num + groupSize; i++) {

					// group mem not found,
					if (mp[i] == 0)
						return false;

					// visited elemens, so reduce freq
					mp[i] -= 1;
				}

			}

		}

		return true;
	}
};

// Priority Queue
class Solution {
public:

	bool isNStraightHand(vector<int>& arr, int groupSize) {

		int N = arr.size();

		if (N % groupSize != 0) return false;

		// create the freq map...
		unordered_map<int, int> mp;
		for (int num : arr) {
			mp[num]++;
		}

		// min heap
		priority_queue<int, vector<int>, greater<int>> pq;

		// fill with unique element of map.
		for (auto it : mp) {
			pq.push(it.first);
		}

		// check for each num
		while (!pq.empty()) {

			// first element
			int num = pq.top();

			// num's freq > 0... it means all the numbers in this group should be available
			while (mp[num] > 0) {

				// check all memeber of group is available or not
				for (int i = num; i < num + groupSize; i++) {

					// group member not found,
					if (mp[i] == 0)
						return false;

					// visited elemens, so reduce freq
					mp[i] -= 1;

					// edge case, specific condition: sync of pq && freqMap
					// need to drop this number from pq, so it won't be picked up as minimum next time
					if (mp[i] == 0)  {

						int poppedEle = pq.top();

						// what happened, is that..... there is "num" < i then pq.top() = num....
						// in that case next time again mp[num] > 0, so we again start with "num" as first element
						// but the current num "i" freq is already 0 => so we don't able to form the group.
						// that's why current i needs to be on top of pq....
						if (poppedEle != i)
							return false;

						pq.pop();
					}

				}

			}

		}

		return true;
	}
};

// Hashing
class Solution {
public:
	bool isNStraightHand(vector<int>& arr, int groupSize) {

		if (arr.size() % groupSize != 0) return false;

		unordered_map<int, int> count;
		for (int num : arr) count[num]++;

		for (int num : arr) {
			int start = num;

			// backtrack to get the first element
			while (count[start - 1] > 0) start--;

			// so make sure, we start with each of the backtracked elements
			// because sum element have more freq
			// for ex: 4 2 3 2 1 => 2 have freq = 2..... so we need to check for that
			while (start <= num) {
				while (count[start] > 0) {
					for (int i = start; i < start + groupSize; i++) {
						if (count[i] == 0) return false;
						count[i]--;
					}
				}
				start++;
			}
		}
		return true;
	}
};