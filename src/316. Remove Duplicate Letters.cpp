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

Question : 316. Remove Duplicate Letters
Topic : Stack, Mono-stack
Problems : https://leetcode.com/problems/remove-duplicate-letters/description/

==============================> Explanation <=============================================

Idea is that,

- We use one mono increasing stack to add characters, but if any character which reside on top of stack and it is last occurance, we
don't remove it, no matter the order in stack(we have to try to get lexo order, doesn't mean we have to return in lexo order only!!)

- We use memory by counting the frequency of character. so we decide while maintaining lexo order, can we remove st.top() ?
Yes: (if that character will appear again in array)
No: (if it is last occurance)

- Apart from that, we need to maintain visited map, so we don't add visited character again.

Remember,

- Due to lexo order, mono stack comes into the picture.


==============================> Approach and Time Complexity <============================

N = s.size()

2) Mono incresing stack
Time: O(N)
Space: O(N)


*/

class Solution {
public:
    string removeDuplicateLetters(string s) {

        int visited[26] = {0}; // keep track of whether it is visited or not
        int count[26] = {0};  // keep track of s[i] count

        // we are counting the frequency of character, so we can use this memory.
        // This is used to decide to remove last unique character from stack or not.
        // If it is last and not visited, I need to add that.
        for (char ch : s) {
            count[ch - 'a']++;
        }

        // lexo increasing order, with counting logic.
        stack<char> st;

        for (int i = 0; i < s.size(); i++) {

            // decrease count
            count[s[i] - 'a']--;

            // already visited, skip it. It's already in stack.
            if (visited[s[i] - 'a']) continue;


            // First, we need to check st.top() is the last unique character or not. If yes, we don't remove.
            // If it is not, then we can add later occurance which we will find later parts of array.
            // Because we have unique character s[i] which is not visited yet, and it's order is less compare to st.top().
            // So we remove st.top() and (again add next occurance which is left).

            // Increasing mono stack.
            while (!st.empty() && count[st.top() - 'a'] != 0 && st.top() > s[i]) {
                visited[st.top() - 'a'] = 0;    // unmark position
                st.pop();
            }

            visited[s[i] - 'a'] = 1;
            st.push(s[i]);

        }

        // remove all characteers and build string
        string ans = "";
        while (!st.empty()) {
            ans += st.top();
            st.pop();
        }

        // current ans is in reverse order due to added in stack, make that reverse
        reverse(ans.begin(), ans.end());

        return ans;


    }
};