### Intuition behind the Sliding Window Algorithm

### Sliding Window Technique

To check whether given question can be solved using this method... first need to check below things:
1) Whatever is answer can be found as one of the windows.
2) Can we make multiple windows by breaking problem into subprogram? 
3) How can we shrink and expand a window?
4) We are able to validate all windows that are possible to find answer.

Remember, always try with pen & paper before jumping to code.... Check shirking and expanding condition for window...

### Template of code always looks like this:

##### Template 1

count = 0 (some condition)
begin = 0
end = N
while (end < N) {
    
    // Shrink the window.. if current window is not valid..from begin pointer

    // Expand the window by adding end 

    // Check if window is valid.... then look for answer

}


##### Template 2

count = 0 (some condition)
begin = 0
for(int end = 0; end < N; end++) {

    // Shrink the window.. if current window is not valid..from begin pointer
    
    // Expand the window by adding end

    // Check if window is valid.... then look for answer
}

