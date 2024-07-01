
### Handle duplicate in sorted array Approach:

We can use the extra O(N) space for map to store the last index of the element. 

[-1, 0, 1, 1, 1, 1, 2]

map = -1(0), 0(1), 1(4), 2(5)

so when we visit "1" first time that time rather than moving to the next element, we use the map to find the last element index and jump next to that. 
