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

Question : 540. Single Element in a Sorted Array
Topic : BS
Problems : https://leetcode.com/problems/single-element-in-a-sorted-array/description/

==============================> Explanation <=============================================

You know the solution of it in linear search, but we want O(logN) for this.

Given that, array is already sorted, you should get the idea about BS.

#1: Which I come up with is,

index => 0 1 2 3 4 5 6 7 8
arr   => 1 1 2 3 3 4 4 8 8

Suppose, for given range(lh, rh) we have some mid element.

We check whether mid is single element, arr[mid-1] != arr[mid] != arr[mid+1] => arr[mid] is that element.

After that one of below scenario happen,

    1) arr[mid-1] == arr[mid]

        we want in this array: [lf....mid] + [mid+1...rh]
        left side of array holds even number of elements => if it does not contain that single element.
        So based on that we decide, which side we need to explore and which one need to skip.

        leftSideTotalElements % 2 == 0,
            we move to right side subarray, lf = mid + 1,
        else
            we move to left side subarray, rh = mid - 2  (we know arr[mid-1] == arr[mid], so we can skip those entry)


    2) arr[mid] == arr[mid+1]

        we want in this array: [lf....mid-1] + [mid, mid+1...rh]
        right side of array holds even number of elements => if it does not contain that single element.
        So based on that we decide, which side we need to explore and which one need to skip.

        rightSideTotalElements % 2 == 0,
            we move to left side subarray, rh = mid - 1,
        else
            we move to right side subarray, rh = mid + 2  (we know arr[mid] == arr[mid+2], so we can skip those entry)

And at the end, both arr[lh] and arr[rh] points to that single element. How I know that ?

Given, 1 <= N < anyting..

N = 1 => we return that.

N != 2..... we have only one single element.

N = 3 => try in (1,1,2) (1,2,2).... and it works.


#2: Simple approach....

index => 0 1 2 3
arr   => 1 1 2 3

If array contain all the element two times, you see starting of pair is always at even index. We can use that logic here for to decide
which side we need to move...

so Idea is that, we always move our "mid" to even index to use this logic.

mid%2 == 1, mid--

1) Move Right Side.

index => 0 1 2 3 4 5 6 7 8
arr   => 1 1 2 2 3 3 4 8 8


arr[mid] == arr[mid+1](arr[4] == arr[5]), it means that (lh, mid+1) all elements in pair, so we move to right side.

lh = mid + 2

2) Move Left Side


index => 0 1 2 3 4 5 6 7 8
arr   => 1 1 2 3 3 4 4 8 8

arr[mid] != arr[mid+1](arr[4] != arr[5]), it means that there is single number in [lh, mid] range. Because, we are moving mid to always to even index
and still it cannot have pair then it is only possible if (lh, mid) contain single element. So we check that range and skip right part.

rh = mid;

==============================> Approach and Time Complexity <============================


1) Binary Search
Time: O(logN)
Space: O(logN)


 */



class Solution {
public:
    int singleNonDuplicate(vector<int>& arr) {

        // If there is only one element, then it is our answer.
        if (arr.size() == 1)
            return arr[0];

        int lh = 0, rh = arr.size() - 1;
        while (lh < rh) {

            int mid = (lh + rh) >> 1;

            if (arr[mid - 1] != arr[mid] && arr[mid] != arr[mid + 1])
                return arr[mid];

            if (arr[mid - 1] == arr[mid]) {

                int numOfElementsOnLeft = mid - lh + 1;

                if (numOfElementsOnLeft % 2 == 0) {
                    lh = mid + 1;
                }
                else {
                    rh = mid - 2;
                }


            }
            else {  // arr[mid] == arr[mid+1]

                int numOfElementsOnRight = rh - mid + 1;


                if (numOfElementsOnRight % 2 == 0) {
                    rh = mid - 1;
                }
                else {
                    lh = mid + 2;
                }

            }

        }

        return arr[lh];
    }
};



// #2



class Solution {
public:
    int singleNonDuplicate(vector<int>& arr) {

        // If there is only one element, then it is our answer.
        if (arr.size() == 1)
            return arr[0];

        int lh = 0, rh = arr.size() - 1;
        while (lh < rh) {

            int mid = (lh + rh) >> 1;

            if (mid % 2 != 0)
                mid--;

            if (arr[mid] == arr[mid + 1]) { // move right side, (lh, mid+1) can't have single element.
                lh = mid + 2;
            }
            else {
                rh = mid;                   // (lh, mid) contains that single element.
            }
        }

        return arr[lh];     // both arr[lh] and arr[rh] hold answer.
    }
};