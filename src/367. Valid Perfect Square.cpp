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

Question : 367. Valid Perfect Square
Topic : Binary Search
Problems : https://leetcode.com/problems/valid-perfect-square/description/

==============================> Explanation <=============================================

Standard Binary Search Algorithm.

#1 Standard Binary Search: Using this we find the num such that, num * num == target. And it is obvious num is
between [1, target]. Check the code!!

#2 Approach: All the perfect square are summation of odd number from (1+3+5....).
For ex: 4 => 1 + 3
        9 => 1 + 3 + 5
        16 => 1 + 3  + 5 + 7
We can use this approach, we subtract all odd numbers until it become zero or negative, if it become zero then it is perfect number.


==============================> Approach and Time Complexity <============================

1) Binary Search
Time: O(N)
Space: O(N)

 */


class Solution {
public:
    bool isPerfectSquare(int num) {
        long long lh = 0, rh = num;
        while (lh <= rh) {
            long long mid = (lh + rh) >> 1;
            long long square = mid * mid;
            if (square == num)
                return true;
            else if (square < num) {
                lh = mid + 1;
            }
            else {
                rh = mid - 1;
            }
        }
        return false;
    }
};


class Solution {
public:
    bool isPerfectSquare(int num) {
        int odd = 1;
        while (num > 0) {
            num -= odd;
            odd += 2;
        }
        return num == 0;
    }
};