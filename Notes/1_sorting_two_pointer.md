
### What is this Sorting + Two Pointer Approach:

Basically, this approach is used when you are given unsorted array(i, j) 
and you need to find two elements A & B whose sum is near to given target.

When we sort the array, we are making the array in increasing order. So left side we find smaller elements and
 on the right side larger elements. 

During each iteration, we reduce that (i, j) range either by removing a left or right element from that range. And intuition is that, 
if A[right] is not the best candidate for given matching criteria then A[right+1] is also not because A[right] < A[right+1].
Same for A[left]. 

This approach is not for finding the closest sum... It can be used anywhere in which we have to reduce the time complexity of O(N^2) to O(NLogN), and match
that condition to remove extreme(left, right) based on some condition. 

Two Sum.

Operation is => Sum => Which follow given below 

Basic fundamental of this approach. A[i-1], A[i].... A[j], A[j+1]...
For given operation, A[i] is not the best candidate then A[i-1] is also not, even it is worse than A[i].
For given operation, A[j] is not the best candidate then A[j+1] is also not, even it is worse than A[j]. 

With this approach we reduce the size of subarray until we find the best candidate. 
