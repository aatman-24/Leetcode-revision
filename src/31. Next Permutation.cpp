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

Question :  31. Next Permutation
Topic : Two Pointer
Problems : https://leetcode.com/problems/next-permutation/submissions/1299536400/

==============================> Explanation <=============================================

What is next permuataion ?
- For given number, there are many large number but smallest of that is next permuation.

Apporach behind to get next permuataion is, need to swap two numbers from right end side so that we get greater element. (not smallest greater, next permuataion)

- find, ith index from right side such that, arr[i] < arr[i+1]...if we swap that arr[i] with any number which is greater than it(not only arr[i+1]), we most probably get
large number than current one.

But whom we swap ?
- yes, arr[i+1] is greater than arr[i], but it is not confirmed that arr[i+1] is just smallest greater than it. We have to find that...

Range: [0....i...N] -> [0...i](don't need to make any change in this)
       (i, i+1..N) -> [(i+1)....N] -> is in decreasing order... that's why we get arr[i] < arr[i+1] at ith index...

We have to find number from that range which is greater than arr[i]. So we can have minimal greater on the ith index.

ex:
ith index we have 2
right side ragne: [6 4 3 1]

good to swap 2 with (6, 4, 3) but for getting minimal greater we have to choose 3. (We can't allow to have greater element on left side of number when we have choice for minimal)

swapped:
3 | 6 4 2 1

now, we can make it more minimal by reversing right side array(making it in ascending order)
3 | 6 4 2 1 -> 3 | 1 2 4 6

Edge case:

If sequence is already greatest -> we have to reverse all the sequence (to make it smallest)

==============================> Approach and Time Complexity <============================

N = nums.size()

1) Brute Force:
Time: O(N!) * O(N)(To compare)(Generate all permutation keep track of current, next one is answer).
Space: O(N!)

2)
Time: O(N)(Overall)
Space: O(1)


*/


class Solution {
public:

    void reverseSuffix(vector<int> &nums, int begin, int end) {
        while (begin < end) {
            swap(nums[begin++], nums[end--]);
        }
    }

    void swap(int &a, int &b) {
        int tmp = a;
        a = b;
        b = tmp;
    }

    void nextPermutation(vector<int>& nums) {
        int N = nums.size();
        if (N <= 1)
            return nums;

        // find the ith position such that, arr[i] < arr[i+1]
        int i;
        for (i = N - 2; i >= 0; i--) {
            if (nums[i] < nums[i + 1])
                break;
        }

        // edge case, reverse all array.
        if (i == -1) {
            reverseSuffix(nums, i + 1, N - 1);
        }
        else {

            // find greater number which is just close(large) to arr[i]
            int j;
            for (j = N - 1; j >= 0; j--) {
                if (nums[j] > nums[i])
                    break;
            }
            swap(nums[i], nums[j]);
            reverseSuffix(nums, i + 1, N - 1);
        }

    }
};