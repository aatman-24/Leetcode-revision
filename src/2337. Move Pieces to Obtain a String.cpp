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

Question : 2337. Move Pieces to Obtain a String
Topic : Two Pointer
Problems : https://leetcode.com/problems/move-pieces-to-obtain-a-string/description/

==============================> Explanation <=============================================

First, it is very clear that if "_RL_" is there or "L__R" is there.... R cannot move ride side or L cannot move left side.
It means on left side of string should contain the "L", and right side of string should contain the "R".
What I mean is that => "LLLLL......|...R...RRRRR" => Once the R started, L cannot come in string.

Common observation from both approach is that,

Case-1:
S: _ _ L
T: L _ _
This is valid condition, and verdict is that.... in Target String "L" comes first which match with
Source string "L" which comes later.

Case-2:
S: R _ _
T: _ _ R
This is valid condition, and verdict is that.... in Target String "R" comes later which match with
Source string "R" which already visited.


Approach-1:
In this approach, we used this observation. We iterate over both string, and ignore the empty characters(only match L and R)..
first both string matched character need to the same. (equal no of L and R, because once R started, L should not be present on right side).
targetCh == 'L', Case-1 => which indicate => targetIndex <= sourceIndex, for valid scenario.
targetCh == 'R', Case-2 => which indicate => sourceIndex <= targetIndex, for valid scenario.
We use this logic...check the code...


Approach-2:
Using the same observation, but here we use the count variable to keep track of count for L and R.
for source, we increment the count.
for target, we decrement the count.
Based on Case-1: targetChar == 'L' => lCount <= 0 (because we get L first in target string) (valid scenario)
Based on Case-2: targetChar == 'R' => rCount >= 0 (because we get R first in source string) (valid scenario)
Also we need to check two conditions,
L match over when.... source[i] == "L"...during this time rCount == 0 (valid scenario)
R match over when.... target[j] == "R"...during this time lCount == 0 (valid scenario)
Because we know... if I split string in two parts.... left side contains only "L" and right side contains only "R"....
so once R pop up in matching... L should not come after that....
Check the code...



==============================> Approach and Time Complexity <============================

1) Two Pointer
Time: O(N)
Space: O(N)

*/




class Solution {
public:

    bool canChange(string source, string target) {

        // source Index
        int i = 0;

        // target Index
        int j = 0;

        int N = source.size();

        while (i < N || j < N) {

            while (i < N && source[i] == '_') i++;
            while (j < N && target[j] == '_') j++;

            // if one of string reach end of string, then other also needs to be reached.
            if (i == N || j == N)
                return i == N && j == N;

            // both string char should be same..... (matched)
            if (source[i] != target[j])
                return false;

            // case-1
            if (target[j] == 'L') {
                if (!(j <= i))          // check above description
                    return false;
            }

            // case-2
            else {
                if (!(i <= j))          // check above description
                    return false;
            }

            i++; j++;
        }

        return true;

    }
};


// approach-2
class Solution {
public:

    bool canChange(string source, string target) {

        int i = 0;

        int N = source.size();

        int lCount = 0, rCount = 0;

        while (i < N) {

            if (source[i] == 'L') { lCount++; if (rCount != 0) return false;} // match finish here
            if (target[i] == 'L') { lCount--; }

            if (source[i] == 'R') { rCount++; }
            if (target[i] == 'R') { rCount--; if (lCount != 0) return false; } // match finish there

            if (lCount > 0 || rCount < 0) return false; // indicate case like: _RL_

            i++;

        }

        return lCount == 0 && rCount == 0;
    }
};

