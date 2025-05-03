### Prefix Sum Intuition

- To get sorted array without changing the original array, we need to get prefix sum array. 

- During prefix sum, we got curSum % k = n, n got repeted two times for any i and j position that means sum[i+1, j] % k == 0.. that's why we again
  got the same value.

- Prefix sum array is always used with map to get the subarray. 

- Whenever given find sub-array of size k, and also given Target T in any form, you can think of prefix sum concept. 

- Many time it is used with sliding window as well. 