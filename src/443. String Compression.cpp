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

Question : 443. String Compression
Topic : Two Pointer
Problems : https://leetcode.com/problems/string-compression/description/

==============================> Explanation <=============================================

Very clear, just applied brute force apporach, used two pointer to determine the size of
group... and based on that...compressed string derived...

==============================> Approach and Time Complexity <============================

1) Two Pointer
Time: O(N^2) (Because...adding someting in string take O(N^2) time....)
Space: O(N)

*/




class Solution {
public:
    int compress(vector<char>& chars) {

        // store the compressed string
        string s = "";

        int begin = 0;
        while (end < chars.size()) {

            // begin points to first element of group
            // end points to next group first element or end of string
            while (end < chars.size() && chars[begin] == chars[end]) end++;

            // get size of grp
            int grp_size = (end - begin);
            s += chars[begin];

            // if size more than > 1.... add the length of grp size as well.
            s += (grp_size > 1) ? to_string(grp_size) : "";

            being = end;
        }

        // replace the output string in chars[] array
        int idx = 0;
        for (auto ch : s) {
            chars[idx++] = ch;
        }

        // return size of compressed string
        return s.size();
    }
};