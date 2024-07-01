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

Question : 350. Intersection of Two Arrays II
Topic : Two Pointer, Hashing
Problems : https://leetcode.com/problems/intersection-of-two-arrays-ii/description/

==============================> Explanation <=============================================

1) Brute Force: For each of element in nums1, calculate the count of that element, do the same for the nums2, add min(count1, count2) if both are positive.
Calculate Count take = O(N) + O(M)
Do for each element = O(N^2) + O(M^2)

2) Two HashMap:
- Instead of calculating count for each time we can use two hashmap to do that in linear time. Then we can iterate over the map and perform same logic.
Check the code!!

3) One Hashmap:
- Instead of having two hashmap, we can have single hashmap, we can reduce the count once the element got visited. Check the code!!

4) Sorting + Two Pointer:
- sort the both array and use two pointers. When comparing elements, if one pointer left behind(points to less value compare to second pointer) increase that.
got match.. add it as answer!!



✔️ Follow-up Question 1: What if the given array is already sorted? How would you optimize your algorithm?
Approach 4 is the best choice since we skip the cost of sorting.
So time complexity is O(M+N) and the space complexity is O(1).


✔️ Follow-up Question 2: What if nums1's size is small compared to nums2's size? Which algorithm is better?
Approach 1 is the best choice.
Time complexity is O(M+N) and the space complexity is O(M), where M is length of nums1, N is length of nums2.


✔️ Follow-up Question 3: What if elements of nums2 are stored on disk, and the memory is limited such that you cannot load all elements into the memory at once?
If nums1 fits into the memory, we can use Approach 1 which stores all elements of nums1 in the HashMap. Then, we can sequentially load and process nums2.
If neither nums1 nor nums2 fits into the memory, we split the numeric range into numeric sub-ranges that fit into the memory.
We modify Approach 1 to count only elements which belong to the given numeric sub-range.
We process each numeric sub-ranges one by one, util we process all numeric sub-ranges.
For example:
Input constraint:
1 <= nums1.length, nums2.length <= 10^10.
0 <= nums1[i], nums2[i] < 10^5
Our memory can store up to 1000 elements.
Then we split numeric range into numeric sub-ranges [0...999], [1000...1999], ..., [99000...99999], then call Approach 1 to process 100 numeric sub-ranges

==============================> Approach and Time Complexity <============================

N = nums1.size(), M = nums2.size()

1) Brute Force:
Time: O(N^2) + O(M^2)
Space: O(1)

2) HashMap:
Time: O(N) + O(M)
Space: O(N+M)

3) Single Hashmap:
Time: O(N) + O(M)
Space: O(N), N < M

4) Sorting + Two Pointer
Time: O(NlogN) + O(MlogM) + O(N+M)
Space: O(1)


*/




class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {

        unordered_map<int, int> mp1, mp2;

        for (int num : nums1) {
            mp1[num]++;
        }

        for (int num : nums) {
            mp2[num]++;
        }

        vector<int> intersection;

        for (auto it : mp1) {

            int element = mp1.first;
            int frequency = mp2.second;

            if (mp2.find(element) != mp2.end()) {

                int minimum_time_repetition = min(frequency, mp2[element]);

                while (minimum_time_repetition > 0) {
                    intersection.push_back(element);
                    minimum_time_repetition--;
                }

            }
        }

        return intersection;
    }
};


class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {

        unordered_map<int, int> mp;

        // put one of the array into map. We can optimize by putting smaller array into hashmap by comparing size.
        for (int num : nums1) {
            mp[num]++;
        }

        vector<int> intersection;

        for (int num : nums2) {

            // element found in num1 and num2(mp) have more than 0 element.
            if (mp.find(num) != mp.end() && mp[num] > 0) {
                intersection.push_back(num);
                mp[num]--;
            }
        }

        return intersection;
    }
};


class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {

        unordered_map<int, int> mp;

        // put one of the array into map. We can optimize by putting smaller array into hashmap by comparing size.
        for (int num : nums1) {
            mp[num]++;
        }

        vector<int> intersection;

        for (int num : nums2) {

            // element found in num1 and num2(mp) have more than 0 element.
            if (mp.find(num) != mp.end() && mp[num] > 0) {
                intersection.push_back(num);
                mp[num]--;
            }
        }

        return intersection;
    }
};


class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {

        vector<int> intersection;
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());

        int i = 0, j = 0, N = nums1.size(), M = nums2.size();
        while (i < N && j < M) {

            // both points to same element, then add it as answer.
            if (nums1[i] == nums2[j]) {
                intersection.push_back(nums1[i]);
                i++; j++;
            }

            // whichever pointer is left behind, increase that.
            else if (nums1[i] < nums2[j]) {
                i++;
            }
            else {
                j++;
            }
        }

        return intersection;
    }
};