
### Perform In-place Sort to Remove Duplicate Numbers:

Whenever we need to remove the duplicate number from the array and no-extra space allowed that time

Think about using Two Pointer approach. 

We can place one pointer on the front side of an array, and use other pointers to check an element got repeated, where to place the next non-repeated element. 

Remember, we can't swap the element with rare side elements of an array. 

The Idea is that. 

If we overlap the duplicate elements which reside on the front side of an array, it doesn't affect anything on non-visited elements. So we overlap those
while maintaining the orders. 

[1, 2, 2, 3, 4] -> [1, 2, 3, 4]


