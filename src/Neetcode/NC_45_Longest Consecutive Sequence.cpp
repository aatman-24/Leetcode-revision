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

Problem: NC_45_Longest Consecutive Sequence
Topic: Hashing
Link: https://neetcode.io/problems/longest-consecutive-sequence

================================================================================
                                Problem Summary
================================================================================

Given an unsorted array of integers `nums`, return the length of the longest consecutive elements sequence.
The solution must run in **O(n)** time.

================================================================================
                                Intuition & Explanation
================================================================================

We are required to find the **longest sequence of consecutive numbers** that can be formed from the array.

### ✅ Approach 1: Hashing (O(N) Time)
- Step 1: Insert all elements into a hash set for O(1) lookup.
- Step 2: For each number, only start a sequence if `num - 1` is **not** present in the set.
  - This ensures `num` is the start of a potential sequence.
- Step 3: Keep expanding the sequence from `num` while `num + 1`, `num + 2`, ... exist in the set.
- Track the maximum length of such sequences.

👉 This avoids redundant checks and gives an efficient solution.

### ⚠️ Avoid Starting Sequence Midway:
- If `num - 1` exists, `num` is part of some longer sequence that we have already checked.

---

### 🔁 Approach 2: Sorting (O(N log N) Time)
- Sort the array.
- Traverse the array and count the length of consecutive increasing elements.
- Handle duplicates by skipping `nums[i] == nums[i-1]`.
- Reset the count when a gap is found (i.e., `nums[i] != nums[i-1] + 1`).

✅ Simpler to implement, but not optimal due to sorting.

================================================================================
                          Approach & Time/Space Complexity
================================================================================

Let N be the size of the input array.

🔹 Approach: Hashing
Time Complexity: O(N)
Space Complexity: O(N)

🔹 Approach: Sorting
Time Complexity: O(N log N)
Space Complexity: O(1) or O(N) depending on sorting method used

*/



// Hashing
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {

        unordered_map<int, int> mp;

        // scan first time, and make entry for all available number
        for (int num : nums) mp[num] = 1;

        int maxi = 0;

        for (int num : nums) {

            // if "num-1" is present then "num" cannont be head, so we won't start and ignore,
            // as we know when "num" comes that time it got visited.
            if (mp.count(num - 1))
                continue;

            // if num is not visited yet, it means it is head of new sequence
            int longest = 1;

            while (mp.count(num + 1)) {
                num = num + 1;
                longest++;
            }

            maxi = max(maxi, longest);
        }

        return maxi;

    }
};


// Sorting

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if (nums.empty()) return 0;
        sort(nums.begin(), nums.end());

        int res = 0, curr = nums[0], streak = 0, i = 0;

        while (i < nums.size()) {
            if (curr != nums[i]) {
                curr = nums[i];
                streak = 0;
            }
            while (i < nums.size() && nums[i] == curr) {
                i++;
            }
            streak++;
            curr++;
            res = max(res, streak);
        }
        return res;
    }
};