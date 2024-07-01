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

Question :  80. Remove Duplicates from Sorted Array II
Topic : Two Pointer
Problems : https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/description/

==============================> Explanation <=============================================

- Intuition behind this solution is that,

Can't peform anything on rare side of array, otherwise we lost those elements.

So It is obvious we need to think from front side only.

We can use three pointer and keep track of how many times element got visited, where to place the element, how to identify we are visiting same element.

What I am sure is that, each time we need to store the element at kth location if it is viable(not visited more than 2 times).

Check the code.


#2 Solution: Here we keep track of count for number, how many time it got visited. As array is sorted, so if number is visited more than 2 times,
then it previous index have same number so we can avoid that ith(pointer) and instead use the coutner to keep track of frequency.


==============================> Approach and Time Complexity <============================

N = nums.size()

1) Two Pointer
Time: O(N)
Space: O(1)


*/

class Solution {
public:
    int removeDuplicates(vector<int>& arr) {

        int N = arr.size();
        if (N <= 2)
            return N;

        // i -> first_element_in_pair
        // j -> runner, second_element_in_pair | new_element
        // k -> where to place visited element
        int i = 0, j = 0, k = -1;

        while (j < N) {

            // ele are same
            if (arr[i] == arr[j]) {

                // dist is more than 2 (ele repetead more than 2 times)
                if ((j - i) >= 2) {

                    // visit next element
                    j++;
                    continue;
                }

                // dist is less than 2, we put same element second time in array.
                arr[++k] = arr[j];
            }
            else {

                // ele are diff, first time new element got visited.
                arr[++k] = arr[j];

                //  keep track of the new element.
                i = j;
            }

            j++;
        }

        return k + 1;
    }
};



class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if (n <= 2) return n;

        int writeIndex = 1;
        int count = 1;

        for (int i = 1; i < n; ++i) {

            // previous and current element are same.
            if (nums[i] == nums[i - 1]) {

                // visited same element less than 2 times, we store it in writeIndex. else not.
                if (count < 2) {
                    nums[writeIndex++] = nums[i];
                    count++;
                }
            } else {
                // got new element.
                nums[writeIndex++] = nums[i];
                count = 1;
            }
        }

        return writeIndex;
    }
};


// https://github.com/aatman-24/DSA/blob/main/LeetCode/Medium/80.%20Remove%20Duplicates%20from%20Sorted%20Array%20II.cpp
class Solution {

public:

    int removeDuplicates(vector<int>& nums) {

        int N = nums.size();

        if (N <= 2)
            return N;

        // point to first duplicate.
        int prev = INT_MIN;

        // point to second duplicate.
        int curr = 0;

        // find next element.
        int next = 1;

        while (next < N) {

            // (new number || (first == second duplicate found, next is new number))
            if (nums[curr] != nums[next] || (nums[curr] == nums[next] && prev != nums[next])) {

                curr++;

                // keep track of previous.
                prev = nums[curr - 1];

                // placed new number
                nums[curr] = nums[next];
            }
            next++;
        }

        // increment by 1, because we start curr with zero.
        return curr + 1;

    }
};