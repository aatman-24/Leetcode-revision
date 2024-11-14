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

Question : 37. Sudoku Solver
Topic : Backtracking
Problems : https://leetcode.com/problems/sudoku-solver/description/
==============================> Explanation <=============================================

We are applying the brute force approach to solve sudoku.

Each empty box can contain the (1-9) digit, so we will try out one by one.. and if any of them is valid..then we jump to next empty block...
incase if any of the forward call deny(return false)...then we need to change that num..(backtrack and jump to next valid number search)(check in code)..
and jump to next empty block... in case it won't work then we backtrack(by unsetting that number).

Why forward call deny(return false) ?
=> Because previously we selected "num" which was valid based on that state of board but in future those decision won't lead to solve entire sudoku.
So we need to backtrack and change that "num" to next valid number.

==============================> Approach and Time Complexity <============================

1) Backtracking
Time: O(9 * (9^N^2))
Space: O(N^2) (stack space)

Each node can have maximum 9 children(to test out number is valid or not) => Breadth = 9
Depth => In the worst case... we tried out all the cell of board in terms of depth(decision) which is O(N^2) => depth = O(N^2) (because it is decision based tree(true/falsse)...suppose when we find out
our solution(each N^2 block return true, that path) that time we made the right decision for each of block...so recursion tree length go upto O(N^2)).
Each node processing time => isValid() => O(9)

Formula => processing_time_for_each_node * (breadth^depth) => O(9) * O(9^(N^2))
Space => O(N^2) (maximum_depth)(stack space)

 */




class Solution {
public:


    bool isValid(vector<vector<char>> &board, int row, int col, char num) {

        for (char i = 0; i < 9; i++) {

            // check row contain same digit
            if (board[i][col] == num)
                return false;

            // check col contain same digit
            if (board[row][i] == num)
                return false;

            // check [row][col] of 3*3 sub-matrix contain same digit

            // Identify Sub-Matrix:

            // 1.Calculate the starting point of the 3x3 sub-matrix using:
            // row_start = (row // 3) * 3
            // col_start = (col // 3) * 3
            // This pinpoints the top-left corner of the relevant sub-matrix.

            // 2.Map 1D Range to 3x3 Grid:
            // Convert index i (0-8) to row and column within the sub-matrix:
            // row_offset = i // 3
            // col_offset = i % 3

            int x = (3 * (row / 3) + i / 3);
            int y = (3 * (col / 3) + i % 3);
            if (board[x][y] == num)
                return false;
        }

        return true;
    }


    bool solve(vector<vector<char>>& board) {

        int N = board.size();

        // check for each [r, c] block...
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                if (board[r][c] == '.') {   // empty block...
                    for (char num = '1'; num <= '9'; num++) {   // try out [1-9] number
                        if (isValid(board, r, c, num)) {    // if "num" is valid...
                            board[r][c] = num;              // set into the board..
                            if (solve(board))               // jump to next block to check our decision(to set "num") will solve sudoku or not.
                                return true;
                            board[r][c] = '.';      // (getting false from next block) backtrack.. and try next number.
                        }
                    }
                    return false;       // Indicate that for empty block... none of (1-9) works.. so we need to return false.
                }
            }
        }
        return true;  // when all the empty box are filled up and valid, at the end this one triggered.. and algo start to backtrack by returing true for each solve().
    }


    void solveSudoku(vector<vector<char>>& board) {
        solve(board);
    }
};