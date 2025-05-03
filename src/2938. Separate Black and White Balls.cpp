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

Question : 2938. Separate Black and White Balls
Topic : Two Pointer
Problems : https://leetcode.com/problems/separate-black-and-white-balls/description/

==============================> Explanation <=============================================

You don't get the idea directly, but it is easy one...

Idea is that..... if string = "1110" => it means that last zero need to cross all "1" => swap_required = 3
                  if string = "11100" => it means that last two zero needs to cross all "1" => swap_required = 3 + 3 = 6
                  if string = "01100" => it menas that last two zero needs to cross all "1" => swap_required = 2 + 2 = 4

It means, we iterate over all the ballons one at a time...if it is "white(0)" ballon... we need to place that infront of
"1".... so all the black ballons it has that time...needs to be swapped with that...so we keep track of count of black("1")
as well.

==============================> Approach and Time Complexity <============================

1) Two Pointer
Time: O(N)
Space: O(N)

*/




class Solution {
public:


    long long minimumSteps(string s) {

        long long cnt = 0;
        long long  black = 0;
        long long  total_swap_required = 0;

        for (char ch : s) {

            // black
            if (ch == '1') {
                black++;
            }

            // white: this white needs to cross all the black on left side
            else {
                total_swap_required += black;
            }

        }

        return total_swap_required;
    }
};