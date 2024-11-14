### Backtracking Short Notes

----



#### 37.Sudoku Solver




```c
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


/*
Time: O(9 * (9^N^2))
Space: O(N^2) (stack space)

Explanation:

Each node can have maximum 9 children(to test out number is valid or not) => Breadth = 9
Depth => In the worst case... we tried out all the cell of board in terms of depth(decision) which is O(N^2) => depth = O(N^2) (because it is decision based tree(true/falsse)...suppose when we find out
our solution(each N^2 block return true, that path) that time we made the right decision for each of block...so recursion tree length go upto O(N^2)).
Each node processing time => isValid() => O(9)

Formula => processing_time_for_each_node * (breadth^depth) => O(9) * O(9^(N^2))
Space => O(N^2) (maximum_depth)(stack space)
*/

```

### 

### 78 Subsets





```c
// 78: Generate all the subsets (Recursive)
class Solution {
public:

    // store all the subsets.
    vector<vector<int>> allSubsets;

    void subsetsHelper(vector<int>& nums, int index, vector<int> curSubset) {

        // Base condition
        if (index == nums.size()) {
            allSubsets.push_back(curSubset);
            return;
        }

        // Don't take it
        subsetsHelper(nums, index + 1, curSubset);

        // Take it
        curSubset.push_back(nums[index]);
        subsetsHelper(nums, index + 1, curSubset);
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> curSubset;
        subsetsHelper(nums, 0, curSubset);
        return allSubsets;
    }
};



// 78: 2nd Approach: Generate all the subsets (Backtracking) (Right approach)
class Solution {
public:

    // store all the subsets.
    vector<vector<int>> allSubsets;

    void subsetsHelper(vector<int>& nums, int startFrom, vector<int> curSubset) {

        // Add curSubset as one of the set.
        allSubsets.push_back(curSubset);

        for (int i = startFrom; i < nums.size(); i++) {
            curSubset.push_back(nums[i]);           // add curr element
            subsetsHelper(nums, i + 1, curSubset);  // Create all subset with curr element nums[index] in the set.
            curSubset.pop_back();                   // remove nums[i] (backtrack).. and form all subsets without it.
        }
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> curr;
        subsetsHelper(nums, 0, curr);
        return allSubsets;
    }
};
```

### 

### 90 Subsets II

```c
class Solution {
public:

    vector<vector<int>> allSubsets;

    void helper(vector<int> &nums, int startFrom, vector<int> curSubset) {

        // Add the curSubset
        allSubsets.push_back(curSubset);

        for (int i = startFrom; i < nums.size(); i++) {

            // To handle the case for duplicate. (We don't new node with that..because all subset is already visited, when we explore nums[i-1] skipping nums[i])
            if (abs(i - startFrom) > 0 && nums[i] == nums[i - 1]) continue;

            curSubset.push_back(nums[i]);

            helper(nums, i + 1, curSubset);

            curSubset.pop_back(); // backtrack

        }

    }

    vector<vector<int>> subsetsWithDup(vector<int>& nums) {

        // sorting is required, to handle the case for duplicate set.
        sort(nums.begin(), nums.end());

        vector<int> curSubset;

        helper(nums, 0, curSubset);

        return allSubsets;
    }
};
```



### 6000 Subset Sums

```c
// Recursion solution
class Solution {
public:

    // to hold the result.
    vector<int> ans;

    void subsetSums(vector<int> arr, int curSum, int index) {

        // Base conditions, reach at the end of the arr. So whatever element we selected(added in curSum) is one of the combination to form subset.
        if (index == arr.size()) {
            ans.push_back(curSum);
            return;
        }

        subsetSums(arr, curSum + arr[index], index + 1);    // take it
        subsetSums(arr, curSum, index + 1);                 // don't take it.
    }

    vector<int> subsetSums(vector<int> arr, int n) {
        subsetSums(arr, 0, 0);
        return ans;
    }
};


// Backtracking solution.
class Solution {
public:

    // to hold the result.
    vector<int> ans;

    void subsetSums(vector<int> arr, int curSum, int startFrom) {

        ans.push_back(curSum);

        for (int i = startFrom; i < arr.size(); i++) {
            curSum += arr[i];
            subsetSums(arr, curSum, i + 1);
            curSum -= arr[i];       // backtracking...
        }
    }

    vector<int> subsetSums(vector<int> arr, int n) {
        subsetSums(arr, 0, 0);
        return ans;
    }
};
```



### 39 Combination Sum

```c
class Solution {
public:

    // store the answer.
    vector<vector<int>> ans;

    void helper(vector<int> &nums, int startIndex, int curSum, int target, vector<int> curSet) {

        // base condition
        if (curSum == target) {
            ans.push_back(curSet);
            return;
        }

        // base condition
        if (curSum > target)
            return;

        // iterative over the all elements from (startIndex, N)
        for (int i = startIndex; i < nums.size(); i++) {

            curSum += nums[i];
            curSet.push_back(nums[i]);

            // check here.. we can choose the same element again nums[i] (NOTE: we can't chose previous nums[i-1], nums[i-2] elements, otherwise we get duplicate set issue (1, 2, 3) => (3, 2, 1))
            helper(nums, i, curSum, target, curSet);

            // backtrack.
            curSum -= nums[i];
            curSet.pop_back();
        }
    }

    vector<vector<int>> combinationSum(vector<int>& nums, int target) {
        vector<int> curSet;
        sort(nums.begin(), nums.end());
        helper(nums, 0, 0, target, curSet);
        return ans;
    }
};

```

### 

### 40 Combination Sum II

```c
class Solution {
public:

    // store the answer.
    vector<vector<int>> ans;

    void helper(vector<int> &nums, int startIndex, int curSum, int target, vector<int> curSet) {

        // base condition
        if (curSum == target) {
            ans.push_back(curSet);
            return;
        }

        // base condition
        if (curSum > target)
            return;

        // iterative over the all elements from (startIndex, N)
        for (int i = startIndex; i < nums.size(); i++) {

            // How to avoid duplicate set when nums have duplicate number.
            // We don't start with fresh node at level-1 if duplicated.
            // What I mean ?
            // arr = [1, 2, 2, 4, 5]....first_2 visit we alread made set with [first_2, 2(skip), 4, 5]
            // then we skip for [2_second, 4, 5]... at same level first_2 in recursion tree.
            if (abs(i - startIndex) > 0 && nums[i] == nums[i - 1]) continue;

            curSum += nums[i];
            curSet.push_back(nums[i]);

            // check here.. we can choose the same element again nums[i] (NOTE: we can't chose previous nums[i-1], nums[i-2] elements, otherwise we get duplicate set issue (1, 2, 3) => (3, 2, 1))
            helper(nums, i + 1, curSum, target, curSet);

            // backtrack.
            curSum -= nums[i];
            curSet.pop_back();
        }
    }

    vector<vector<int>> combinationSum2(vector<int>& nums, int target) {
        vector<int> curSet;
        sort(nums.begin(), nums.end());
        helper(nums, 0, 0, target, curSet);
        return ans;
    }
};
```



### 216 Combination Sum III

```c
class Solution {
public:

    // Given that, [1-9] numbers can be used for single time only.
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    // To store the result.
    vector<vector<int>> combinations;

    void helper(int startIndex, int curSum, int target, int count, int k, vector<int> curCombination) {

        // selected required numbers and sum of them is equal to target, choose the curCombination. (Base condition)
        if (count == k && curSum == target) {
            combinations.push_back(curCombination);
            return;
        }

        // Base condition... In case we are holding more element then required || curSum > target.
        // We don't find required result exploring more elements with curCombination.
        if (count > k || curSum > target)
            return;

        for (int i = startIndex; i < arr.size(); i++) {

            // Add it
            curCombination.push_back(arr[i]);
            curSum += arr[i];
            count++;

            helper(i + 1, curSum, target, count, k, curCombination);

            // Backtracking (Skip it)
            count--;
            curSum -= arr[i];
            curCombination.pop_back();

        }
    }

    vector<vector<int>> combinationSum3(int k, int n) {
        int curSum = 0, count = 0;
        vector<int> curCombination;
        helper(0, curSum, n, count, k, curCombination);
        return combinations;
    }
};

```



### 131 Palindrome Partitioning

```c
class Solution {
public:

    // store the result.
    vector<vector<string>> ans;

    // Will take O(len(s)) to check.
    bool isPalindrome(string s, int start, int end) {
        while (start <= end) {
            if (s[start] != s[end]) {
                return false;
            }
            start++; end--;
        }
        return true;
    }

    void helper(string s, int startIndex, vector<string> palindromeSubset) {

        // If reached here, it means we are able to parition the string "s" into palindrome subset.
        // Reason is that, we are moving to (i+1) index only if found palindrome substr from (startIndex, i)
        // Reaching here... indicate found set of palindrome substrings from (0, s.size())
        if (startIndex >= s.size()) {
            ans.push_back(palindromeSubset)
            return;
        }

        for (int i = startIndex; i < s.size(); i++) {

            //  check (startIndex, i) length substr is palindrome or not.
            if (isPalindrome(s, startIndex, i)) {

                // yes, get substr
                string substr = s.substr(startIndex, (i - startIndex + 1));

                // put in set
                palindromeSubset.push_back(substr);

                // find palindromeSubset for remaining (i+1, s.size()) string
                helper(s, i + 1, palindromeSubset);

                // bactrack
                palindromeSubset.pop_back();
            }
        }
    }

    vector<vector<string>> partition(string s) {
        vector<string> palindromeSubset;
        helper(s, 0, palindromeSubset);
        return ans;
    }
};
```






