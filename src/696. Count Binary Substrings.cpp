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

Question : 696. Count Binary Substrings
Topic : Two Pointer
Problems : https://leetcode.com/problems/count-binary-substrings/description/

==============================> Explanation <=============================================

Idea is that,

We divide the given string in form of two group.
- previous_group
- current_group
current_group is counting '1' then last group is '0'..or vice versa..

Now.... If previous_grp_size >= current_group => it means there is one subgroup formed, which has size of min(previous_grp_size, current_grup)

for example...

    string s = "00011"

    previous_grp = 000
    current_grp = 1 => subgroup = "01"
    current_grp = 11 => subgroup = "0011"

    so we consider all such groups.....

We swap subgroups when new character encounterd which is not the current group part.....

==============================> Approach and Time Complexity <============================

1) Two Pointer
Time: O(N)
Space: O(N)

*/


class Solution {
public:
    int countBinarySubstrings(string s) {

        int prev_grp_size = 0;
        int cur_grp_size = 1;
        int count = 0;

        for (int i = 1; i < s.size(); i++) {
            if (s[i] == s[i - 1]) cur_grp_size++;
            else {
                prev_grp_size = cur_grp_size;
                cur_grp_size = 1;
            }
            if (prev_grp_size >= cur_grp_size) count++;
        }
        return count;
    }
};