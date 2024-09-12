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

Question : 402. Remove K Digits
Topic : Stack, Mono-stack
Problems : https://leetcode.com/problems/remove-k-digits/description/

==============================> Explanation <=============================================

Parent: 496. Next Greater Element I.

1) Mono Decreasing stack:

Approach:

- Idea is that,

Suppose there are

x1 x2 x3 x4 elements into the array.

and (x1 < x2 < x3) > x4.

So for each of the x1, x2 and x3, next lesser element is x4.

We manage one mono increasing stack, and anytime we get st.top() > nums[i]... It means nums[i] is just lesser element for st.top().

So stack holds all the elements which doesn't have the next lesser element at moment(that's why it is mono decreasing stack)

That's logic.

Need Greater element (st.top() < nums[i]), use Decreasing Stack.
Need lesser element (st.top() > nums[i]), use Increasing Stack.
----

So we used above apporach here...

Why ?

Give number is:

1432219, K = 3. I need to delete the 3 digits from this number.

To make it smaller after we removed 3 digits,
- We can't delete the max digits each time. Here If we delete: 9, 4, 3 => 1221, Actual answer is: 1219(min_num)

What we need to focus is smaller elements from (left -> right) that's how we can get smaller elements.

To get the smaller elements on the left side of new number we can use the mono increasing stack....

1 4 3 2 2 1 9

any time from left end side, we get st.top() > nums[i], It means that nums[i] is better choice compare to st.top() to reside on left side of number.
And for that we need to remove st.top() out of the number.

Here,

st: 1
st: 1 4
st: 1 4 3  4 > 3
st: 1 3, k = 2
st: 1 3 2
st: 1 3 2, 3 > 2
st: 1 2, k = 1
st: 1 2 2
st: 1 2 2 1, 2 > 1
st: 1 2 1, k = 0
st: 1 2 1 [9 (remaining numbers after k = 0)]
Answer is : 1 2 1 9

Edge case:

What if st.top() == nums[i], can we pop out st.top() in that case ?
- No. Because we don't know what is after these numbers, if that number is less than nums[i], then obviosuly nums[i] got deleted, but in case it is
greater than nums[i] then those forseen number needs to be deleted.

Ex: 559, 551, K = 1... then smallest is 51(decided on the 1 to remvoe second 5), not 59(decied on second 5 to remove first 5).

There are three edge cases:

1) num: 1234, k = 2, we need to delete the number from the end if it is increasing order of digit.
2) num: 10054, k = 1: ans=00054..... we need to delete this zero on prefix side.
3) num: 10005, k = 2: ans="0" not "".

==============================> Approach and Time Complexity <============================

N = s.size()

1) Mono incresing stack
Time: O(N)
Space: O(N)


*/


class Solution {
public:
    string removeKdigits(string num, int k) {

        // delete entire number.
        if (num.size() <= k)
            return "0";

        stack<int> st;
        for (char ch : num) {
            int digit = ch - '0';
            while (!st.empty() && k > 0 && st.top() > digit) {      // digit is lesser number so He can take place of st.top() to be reside on left side.
                st.pop();
                k--;
            }
            st.push(digit);
        }

        // st: [1, 2, 3, 4] num=1234, .... k = 2, in that case we need to delete the number from the end, because digits are in increasing order.
        while (k > 0 && !st.empty()) {
            st.pop(); k--;
        }

        // number build up. Add current number in reverse format.
        string ans = "";
        while (!st.empty()) {
            ans += to_string(st.top());
            st.pop();
        }

        // reverse the number
        reverse(ans.begin(), ans.end());

        // remove unecessary zero on prefix side.
        int idx = 0;
        while (idx < ans.size() && ans[idx] == '0') {
            idx++;
        }

        // If all num are deleted, return "0" not "".
        if (idx == ans.size())
            return "0";

        // otherwise remove those zeros.
        return ans.substr(idx, ans.size());
    }
};


// Better code in writting

class Solution {

public:
    string removeKdigits(string num, int k) {
        if (num.length() <= k) return "0"; // num=112 and k >= 3 (remove all) ans = "0".
        stack<char> st;
        st.push(num[0]);


        // Here we check the top of stack if the st.top() > nums[i] then pop the stack top element
        // bcz this element increase the value of number.
        // if st.top() <= nums[i] then push the nums[i] into the stack.This process run until k == 0 or i == num.length()[1,2,3,4]
        // if (k == 0) add reamining element into the stack.
        // if(k != 0) then pop the kth element from the stack.
        // ans last reverse the stack element and remove the leading zero if exist.

        int i = 1;
        while (i < num.length() && k > 0) {

            if (!st.empty() && st.top() > num[i]) {
                st.pop();
                k--;
            }
            else {
                st.push(num[i]);
                i++;
            }
            if (k == 0) break;

        }

        for (int rem = i; rem < num.length(); rem++) st.push(num[rem]);

        // k != 0 remove the element from the top of stack.
        while (k != 0) {
            st.pop(); k--;
        }

        // pop all element and store into the tmp_result.
        string resWithLeadingZero = "";
        while (!st.empty()) {
            resWithLeadingZero += st.top();
            st.pop();
        }

        // reverse the tmp-result string.
        reverse(resWithLeadingZero.begin(), resWithLeadingZero.end());

        // remove leading zero.
        string res = "";
        int start = 0;
        int n = resWithLeadingZero.length();
        while (start < n && resWithLeadingZero[start] == '0') start++;

        while (start < n) {
            res += resWithLeadingZero[start];
            start++;
        }

        // if all element is removed we return "0".
        if (res.length() == 0) res = "0";

        return res;
    }
};