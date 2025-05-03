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

Question : 264. Ugly Number II
Topic : Heap, PQ
Problems : https://leetcode.com/problems/ugly-number-ii/description/?envType=problem-list-v2&envId=heap-priority-queue

==============================> Explanation <=============================================


In this question we have to use this prime number to generate the nth minimum number
into the sequence: 2, 3, 5

t2 t3 t5 (respetive power of 2, 3 and 5)
0 0 0 => 1
1 0 0 => 2
0 1 0 => 3
2 0 0 => 4
0 0 1 => 5

Basically, we start with 0 power of all three which result into => 1, so we put that into result array.

After that, each time we try to increase the power of each previously generated result by this prime nubmers.

so we need to keep track of pointers for each prime number.....

Dry run:

0 0 0 => 1 [ arr = [1] ]

next,

arr[0] * 2, arr[0] * 3, arr[0] * 5 => arr[0] * 2 => 2....  => [ arr = [1, 2] and t1 = 1]

arr[1] * 2, arr[0] * 3, arr[0] * 5 => arr[0] * 3 => 3....  => [ arr = [1, 2, 3] and t2 = 1]


==============================> Approach and Time Complexity <============================

1) Two Pointer
Time: O(N)
Space: O(N)

*/

class Solution {
public:
    int nthUglyNumber(int n) {

        if (n <= 1)
            return n;

        // array for storing the result
        vector<int> arr(n);

        // base case
        arr[0] = 1;

        // we start with 0th element from array...
        int t2 = 0, t3 = 0, t5 = 0;


        for (int i = 1; i < n; i++) {

            // t2, t3, and t5 are pointers which points to smallest generated number output previosuly.
            // basically each prime needs to be multiply with smallest generated output, so we can have next number.

            int nextMinimum = min(2 * arr[t2], min(3 * arr[t3], 5 * arr[t5]));

            // put the next min number into the result array.
            arr[i] = nextMinimum;

            if (nextMinimum == 2 * arr[t2]) {
                t2++;
            }
            if (nextMinimum == 3 * arr[t3]) {
                t3++;
            }
            if (nextMinimum == 5 * arr[t5]) {
                t5++;
            }

        }

        return arr[n - 1];

    }
};


class Solution {
public:
    int nthUglyNumber(int n) {
        if (n <= 0) return false; // get rid of corner cases
        if (n == 1) return true; // base case
        int t2 = 0, t3 = 0, t5 = 0; //pointers for 2, 3, 5
        vector<int> k(n);
        k[0] = 1;
        for (int i  = 1; i < n ; i ++)
        {
            k[i] = min(k[t2] * 2, min(k[t3] * 3, k[t5] * 5));
            if (k[i] == k[t2] * 2) t2++;
            if (k[i] == k[t3] * 3) t3++;
            if (k[i] == k[t5] * 5) t5++;
        }
        return k[n - 1];
    }
};