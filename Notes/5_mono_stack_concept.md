### How you will get the idea about when to use mono stack or not ?

Usually, In a problem it is given that, 

1) Maintain the order in increasing/decreasing order strictly. 
2) Find just next greater/lesser element. 
3) Find a left and right boundary for an element. (Boundary means element less than or greater than a current element).

---

### Snippet of code for both mono stacks for all conditions. 

Mono Increasing Stack((x1 < x2 < x3) > x4):

1) You want to find a smaller left_boundary, go for increasing stack. 
2) You want to find a smaller right_boundary, go for increasing stack.

   while(!st.empty() && st.top() >= arr[i]) {

        // Order of stack: Increasing. 

        // #case-1: x2 is lesser element than x3. So when I visit the x3, that time I update the left_smaller_boundary[x3] = x2(st.top() during that time).
        // #case-2: x4 is lesser element than x3. So when I visit the x4, that time I update the left_smaller_boundary[st.top()] = x4.
        // Ex: 1 4 7 10.... arr[i] = 5... need to remove 10 and 7.
        
        // Are you able to spot difference?
        // For ith element, st.top() become left smaller boundary.
        // For st.top() element, ith element becomes right smaller boundary.
   }



Mono Increasing Stack((x1 > x2 > x3) < x4):

3) You want to find a greater left_boundary, go for decreasing stack.
4You want to find a greater right_boundary, go for decreasing stack.

    while(!st.empty() && st.top() <= arr[i]) {  

        // Order of stack: Decreasing. 

        // #case-3: x2 is greater element than x3. So when I visit the x3, that time I update the left_greater_boundary[x3] = x2(st.top() during that time).
        // #case-4: x4 is greater element than x3. So when I visit the x4, that time I update the left_smaller_boundary[st.top()] = x4.
        // Ex: 1 4 7 10.... arr[i] = 5... need to remove 10 and 7.
        
        // Are you able to spot difference?
        // For ith element, st.top() become left greater boundary.
        // For st.top() element, ith element becomes right greater boundary.
    }


## Conclusion:

    Decide-1: You want lesser or greater element ?
    
        Lesser -> Increasing Stack.
        Greater -> Decreasing Stack
        
    Decide-2: From left side or right side ?
    
        From left side: left_boundary[i] = st.top();
        From right side: right_boundary[st.top()] = i;
