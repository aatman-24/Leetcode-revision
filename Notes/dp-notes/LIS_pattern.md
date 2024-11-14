### Dynamic programming, Pattern = LIS (Longest increasing  sub sequence)

----

### [300. Longest Increasing Subsequence](https://leetcode.com/problems/longest-increasing-subsequence/)

```c

/* Intuition:

Top-down Approach,

    Two para which are changing.... (i, prev_index)

    prev_index = -1... so we need to shift it by +1.. so we can create memo table...

    prev_index + offset... indexing will be this way...

Bottom-up:

    On bottom up, to manage the prev_index==-1, we are shifting the entire jth column to (j+1)th column for dp table. Due to that,
    whenever we using jth index in dp table(dp[i][j]) that time we need to offset it by +1. (dp[i][j] -> dp[i][j+offset]).

    And one more point is that... we have pairs in this format (i, prev_index(<i))... so second for loop start at (i-1).

    Check the code!!

Bottom-up with space optimization:

    We can reduce one dimesion by using prev and curr, 1D dp table.

Bottom-up without using DP: (Go with this directly)

    We can get LIS_Length using 2 for loops in O(N^2) time, which is equivalent to DP-Bottom-up.

    Idea is that,

        each lis[i] = 1... (each ith element have LIS of length 1)

        One loop goes from (i = 0 -> 1)

            inside loop (we check from 0 -> j)

                nums[j] < nums[i]... it means (seq which was added at nums[j] can be extend by nums[i]) so that way...we choose longest seq for dp[i]....

        Check the code!!

Printing LIS:

    To print LIS,#Bottom-up without using DP this approach is very easy... we just need to keep track of prev element using other array. (check the code)

Binary Search LIS:

    Idea comes from the, #Bottom-up without using DP...

    Where we use the two for loops, to get LIS length...

    We can replace inner one using binary_search.

    For that, understand the concept, form here: https://takeuforward.org/data-structure/longest-increasing-subsequence-binary-search-dp-43/

    - We keep track of increasing order array. Where we either update oen of element if (cur_num < last_element) or add cur_num as back of array.

    - Idea is that, We try to get the LIS at each element as tail of it.

        First of all => LIS = 1, Each element can be consider as LIS of itself.

        Then we check,

            nums[i] <= last_element_of_increasing_order,

                It means nums[i]... can replace some greater number from the increasing order (It is not increasing the length)

                This time, we LIS remain same because we are justing replacing (just greater than "nums[i]" with nums[i](most optimal choice)) (3, 4), nums[i] == 1...we replace "3" not 4.

                Externally, we are creating a new lis_order... but due to ask is "length_of_lis"... we can do within single array.

            nums[i] > last_element_of_increasing_order,

                Add nums[i] in increasing order...

        At the end, increasing order array's size is maxLis.

*/


// Recursive solution
class Solution {
public:

    int LIS(int i, int prev_index, vector<int> &nums) {

        if(i >= nums.size())
            return 0;   

        int lengthOfLIS;

        // you can take nums[i] in LIS, so you have two choice to take it or don't take it.
        if(prev_index == -1 || nums[prev_index] < nums[i]) {

            // // take it
            // 1 + LIS(i+1, i, nums);

            // // don't take it
            // LIS(i+1, prev_index, nums);

            lengthOfLIS = max(1 + LIS(i+1, i, nums), LIS(i+1, prev_index, nums));
        }
        else {
            lengthOfLIS = LIS(i+1, prev_index, nums);
        }

        return lengthOfLIS;
    }


    int lengthOfLIS(vector<int>& nums) {

        return LIS(0, -1, nums);        
    }
};


// Top-down
// 1 <= nums.length <= 2500
class Solution {
public:

    int t[2502][2502];

    int OFFSET = 1;

    int LIS(int i, int prev_index, vector<int> &nums) {

        if(i >= nums.size())
            return 0;   

        if(t[i][prev_index+OFFSET] != -1)
            return t[i][prev_index+OFFSET];

        int lengthOfLIS;

        // you can take nums[i] in LIS, so you have two choice to take it or don't take it.
        if(prev_index == -1 || nums[prev_index] < nums[i]) {

            // // take it
            // 1 + LIS(i+1, i, nums);

            // // don't take it
            // LIS(i+1, prev_index, nums);

            lengthOfLIS = max(1 + LIS(i+1, i, nums), LIS(i+1, prev_index, nums));
        }
        else {
            lengthOfLIS = LIS(i+1, prev_index, nums);
        }

        return t[i][prev_index+OFFSET] = lengthOfLIS;
    }


    int lengthOfLIS(vector<int>& nums) {
        memset(t, -1, sizeof(t));
        return LIS(0, -1, nums);        
    }
};


// Bottom-up
// 1 <= nums.length <= 2500
class Solution {
public:

    int OFFSET = 1;

    int lengthOfLIS(vector<int>& nums) {
        int m = nums.size();
        vector<vector<int>> dp(m+1, vector<int>(m+1, 0));

        // base case (covered during initialization)
        // dp[m][j] = 0;

        for(int i = m-1; i >= 0; i--) {

            for(int prev_index = i-1; prev_index >= -1; prev_index--) {

                int lengthOfLIS;

                // you can take nums[i] in LIS, so you have two choice to take it or don't take it.
                if(prev_index == -1 || nums[prev_index] < nums[i]) {

                    // // take it
                    // 1 + LIS(i+1, i, nums);

                    // // don't take it
                    // LIS(i+1, prev_index, nums);

                    lengthOfLIS = max(1 + dp[i+1][i+OFFSET], dp[i+1][prev_index+OFFSET]);
                }
                else {
                    lengthOfLIS = dp[i+1][prev_index+OFFSET];
                }

                dp[i][prev_index+OFFSET] = lengthOfLIS;

            }
        }

        return dp[0][-1+OFFSET];
    }
};

// Bottom-up Space Optimization
class Solution {
public:

    int OFFSET = 1;

    int lengthOfLIS(vector<int>& nums) {
        int m = nums.size();

        vector<int> prev(m+1, 0), cur(m+1, 0);
        // base case dp[m][j] = 0, covered. 

        for(int i = m-1; i >= 0; i--) {

            for(int prev_index = i-1; prev_index >= -1; prev_index--) {

                int lengthOfLIS;

                // you can take nums[i] in LIS, so you have two choice to take it or don't take it.
                if(prev_index == -1 || nums[prev_index] < nums[i]) {

                    // // take it
                    // 1 + LIS(i+1, i, nums);

                    // // don't take it
                    // LIS(i+1, prev_index, nums);

                    lengthOfLIS = max(1 + prev[i+OFFSET], prev[prev_index+OFFSET]);
                }
                else {
                    lengthOfLIS = prev[prev_index+OFFSET];
                }

                cur[prev_index+OFFSET] = lengthOfLIS;
            }

            swap(prev, cur);
        }

        return prev[-1+OFFSET];
    }
};


// Bottom-up Withou Using DP
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int m = nums.size();
        vector<int> lis(m, 1);
        int maxLis = 1; // keep track of maxLis Length
        for(int i = 1; i < m; i++) {
            for(int j = i - 1; j >= 0; j--) {
                if(nums[j] < nums[i] && (1 + lis[j]) > lis[i]) {
                    lis[i] = 1 + lis[j];
                } 
            }
            maxLis = max(maxLis, lis[i]);   // update after computing lis[i], we are considering ith element as end of lis so taking its length. 
        }
        return maxLis;
    }
};

// Bottom-up Without Using DP (Printing LIS)
class Solution {
public:
    vector<int> longestIncreasingSubsequence(int m, vector<int>& nums) {
        vector<int> lis(m, 1), prev(m, 0);
        int maxLis = 1; // keep track of maxLis Length
        for(int i = 0; i < m; i++) {
            prev[i] = i;    // setting prev element as itself. 
            for(int j = 0; j < i; j++) {        // for lexo order we need to check from (0 , j) else (j --> i) is also fine.
                if(nums[j] < nums[i] && (1 + lis[j]) > lis[i]) {
                    lis[i] = 1 + lis[j];
                    prev[i] = j;        // indicate... ith element previous element is at jth index. 
                } 
            }
            maxLis = max(maxLis, lis[i]);   // update after computing lis[i], we are considering ith element as end of lis so taking its length. 
        }

        // find the index, which have maxLis so we can start from that. 
        int index = 0;
        while(lis[index] != maxLis) {
            index++;
        }

        vector<int> lisOrder;

        // Until we don't reach to last element keep doing that..
        while(prev[index] != index) {
            lisOrder.push_back(nums[index]);
            index = prev[index];
        }

        // Add last prev[index] == index... element (because that is last number which is also part of LIS)
        lisOrder.push_back(nums[index]);

        reverse(lisOrder.begin(), lisOrder.end());

        return lisOrder;
    }
};

// LIS using the Binary Search, O(NlogN)
class Solution {


    // Return index of element which is equal to "target" or just greater than "target".
    int lower_bound(vector<int>& arr, int num) {

        int low = 0, high = arr.size() - 1;

        while (low <= high) {

            int mid = (low + high) >> 1;

            if (arr[mid] == num) {
                return mid;
            } else if (num < arr[mid]) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        return low;
    }

public:
    int lengthOfLIS(vector<int>& nums) {

        int m = nums.size();

        // Keep track of increasing order. 
        vector<int> incOrder;

        incOrder.push_back(nums[0]); // base case, add first element... as we know atleast LIS=1 is possible with any single number

        for (int i = 1; i < m; i++) {

            // if nums[i] <= last_element of incOrder.. it means it can swap one of greater number than it. 
            if (nums[i] <= incOrder.back()) {
                int replaceAt = lower_bound(incOrder, nums[i]);
                incOrder[replaceAt] = nums[i];
            } else {        // nums[i] > last_elememt.... then nums[i] extend the lis by ending at nums[i]
                incOrder.push_back(nums[i]);
            }
        }
        return incOrder.size(); // size of incOrder will be length of LIS. Note: lncOrder is not LIS order it is just increasing order. 
    }
}; 
```

### 1_GFG_LIS_Print Longest Increasing Subsequence

```c

/* Intuition:


Bottom-up without using DP:

    We can get LIS_Length using 2 for loops in O(N^2) time, which is equivalent to DP-Bottom-up.

    Idea is that,

        each lis[i] = 1... (each ith element have LIS of length 1)

        One loop goes from (i = 0 -> 1)

            inside loop (we check from 0 -> j)

                nums[j] < nums[i]... it means (seq which was added at nums[j] can be extend by nums[i]) so that way...we choose longest seq for dp[i]....

        Check the code!!

Printing LIS:

    To print LIS,#Bottom-up without using DP this approach is very easy... we just need to keep track of prev element using other array. (check the code)

*/

// Bottom-up Without Using DP
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int m = nums.size();
        vector<int> lis(m, 1);
        int maxLis = 1; // keep track of maxLis Length
        for (int i = 1; i < m; i++) {
            for (int j = i - 1; j >= 0; j--) {
                if (nums[j] < nums[i] && (1 + lis[j]) > lis[i]) {
                    lis[i] = 1 + lis[j];
                }
            }
            maxLis = max(maxLis, lis[i]);   // update after computing lis[i], we are considering ith element as end of lis so taking its length.
        }
        return maxLis;
    }
};

// Bottom-up Without Using DP (Printing LIS)
class Solution {
public:
    vector<int> longestIncreasingSubsequence(int m, vector<int>& nums) {
        vector<int> lis(m, 1), prev(m, 0);
        int maxLis = 1; // keep track of maxLis Length
        for (int i = 0; i < m; i++) {
            prev[i] = i;    // setting prev element as itself.
            for (int j = 0; j < i; j++) {       // for lexo order we need to check from (0 , j) else (j --> i) is also fine.
                if (nums[j] < nums[i] && (1 + lis[j]) > lis[i]) {
                    lis[i] = 1 + lis[j];
                    prev[i] = j;        // indicate... ith element previous element is at jth index.
                }
            }
            maxLis = max(maxLis, lis[i]);   // update after computing lis[i], we are considering ith element as end of lis so taking its length.
        }

        // find the index, which have maxLis so we can start from that.
        int index = 0;
        while (lis[index] != maxLis) {
            index++;
        }

        vector<int> lisOrder;

        // Until we don't reach to last element keep doing that..
        while (prev[index] != index) {
            lisOrder.push_back(nums[index]);
            index = prev[index];
        }

        // Add last prev[index] == index... element (because that is last number which is also part of LIS)
        lisOrder.push_back(nums[index]);

        reverse(lisOrder.begin(), lisOrder.end());

        return lisOrder;
    }
};
```

[368. Largest Divisible Subset](https://leetcode.com/problems/largest-divisible-subset/)

```c
/* Intuition: 

Given that, largest divisible subset which is simliar to LIS. 

Because, LIS = nums[j] < nums[i] and follow transitive property. Here, 

         LDS = nums[i] % nums[j] == 0 && follow transitive property.

Both we need largest subsets. Directly using the Bottom-up approach(quite easy).

---

Here, we need to find largest divisible subset of given set, such that every elements
in that set is divisible by other elements of set or vice versa. Which is possible, there is transitive property
exist in set. What I mean is that,

- If given numbers is A -> B -> C, if B % A == 0 and C % B == 0 then, automatic C % A == 0(which no need to check).
 (Transitive Property)

- So we sort the array, so i < j then nums[i] < nums[j] and nums[i] could become divisor.

- And we use LIS logic.... dp[i] = dp[j] + 1 if(nums[i] % nums[j] == 0)

- But Here problem is that we also need that subset not only size.. so we use dfs logic of keeping previous
elements...(from which is best for current i) and lastly we derive that subset see below code..

1) Choise Diagram: if(nums[i] % nums[j] == 0) then we can expand the nums[j] series but we look all the
                    possible divisor which gives maxlen subset. (0 < =j <= i-1).

2) Base Case: every number is divisible by itself. minimum value of dp[i] = 1.

3) Recurrance Relation:
        for(int j = i - 1; j >= 0; j--)
        	if(nums[i] % nums[j] == 0)
	            dp[i] = max(dp[i], dp[j]+1)


*/

class Solution {
public:

    vector<int> largestDivisibleSubset(vector<int>& nums) {

        int N = nums.size();

        // DP Table
        // Each element divisible by itself, make 1 length subset
        // previous of each element can be -1.
        vector<int> dp(N, 1), pre(N, -1);

        // Sort array, so we can form the transitive relation n1 < n2 < n3
        // n3 % n2 == 0 && n2 % n1 == 0 => n3 % n1 == 0.
        sort(nums.begin(), nums.end());

        // Atleast each element is divisible by itself
        int maxSubsetLIS = 1;

        for (int i = 1; i < N; i++) {

            // keep track of previous element for forming the path.
            int prev = -1;

            for (int j = i - 1; j >= 0; j--) {
                if (nums[i] % nums[j] == 0 && (dp[i] < dp[j] + 1)) {
                    dp[i] = 1 + dp[j];
                    prev = j;
                }
            }

            // keep track of maximum LIS (which we will use to get first element)
            maxSubsetLIS = max(maxSubsetLIS, dp[i]);

            pre[i] = prev;
        }

        // Find the subset using DFS Traversal in reverse manner
        vector<int> largestSubset;
        int index = 0;
        for (int i = 0; i < N; i++) {
            if (dp[i] == maxSubsetLIS) {
                index = i;
                break;
            }
        }

        while (index != -1) {
            largestSubset.push_back(nums[index]);
            index = pre[index];
        }

        // (doesn't require)
        reverse(largestSubset.begin(), largestSubset.end());

        return largestSubset;
    }
};
```

[1048. Longest String Chain](https://leetcode.com/problems/longest-string-chain/)

```c
// Direct Applying LIS Time: (N^2*L)
/* Intution: 
    Bottom-up is quite easy, applied directly that one. Just check the isPredecessor() logic.
    Apart from that it is same as LIS. We have sorted the given words in terms of length, because
    we want predecessor(less length) words are visited first.
    Time: O(N^2) * O(16)(for comparsion of two string)

---

Given words of different length we need to make longest chain by connecting
predecessor of words. Predecessor is word, which has 1 character less/missing from next string, but
order of characters should be maintained.

Basically, they ask to create longest chain by following this predecessor logic, which is
very similar to LIS logic.

LIS => nums[j] < nums[i] && (1 + lis[j] < lis[i])
Here => isPrdecessor(nums[j], nums[i]) && (1 + lis[j] < lis[i])

Basically, we try to extend all chain which was ended at "jth" index, by joining "ith" index.

#1: Standard LIS
Bottom-up is quite easy, applied directly that one. Just check the isPredecessor() logic.
Apart from that it is same as LIS. We have sorted the given words in terms of length, because
we want predecessor(less length) words are visited first.
Time: O(N^2) * O(16)(for comparsion of two string)


#2: Tricking LIS
Instead of directly joining the two string with Predecessor logic. One thing we can do is,
We can sort the given words in terms of length.

Order of visiting words be like: 1_length_word |2_len_word |3_len_word

And we also know that.... 1_len_word can be predecessor of 2_len_word only...

So we can apply that logic.

There is word = ac

There is next word of length 3 = bac => b + ac(above word)

"ac" is predecessor of "bac".

So, what we do is, we elimiate the one of single character from string "s".
And check whatever string left is already visited or not, if "yes" then that
string is predecessor of this "s". We don't know which character we need to drop
so we drop one by one and check by doing that.... we can get predecessor by O(16),
instead of O(N).

Also maintain one map which is LIS. Which tell which last added string and its length of chain.

Time => O(N*16)


*/
class Solution {
public:

        static bool compartor(string a, string b) {
            return a.size() < b.size():
        }

        // Check if string "b" can be predecssor of string "a".
        // Logic is that: If both string length is differ by 1...
        // Will compare each character one by one, allow one mismatch, if second mismatch encounter return false.
        bool isPredecessor(string a, string b) {

        // check size first, must be differ by "1".
        if (a.size() - b.size() != 1) return false;

        // check relative position.
        int i = 0, j = 0;

        bool allowoneMismatch = true;

        while (i < a.size()) {

            if (a[i] == b[j]) {
                i++; j++;
            }
            else if (allowoneMismatch) {
                i++;
                allowoneMismatch = false;
            }
            else {
                return false;
            }
        }

        return true;
    }

    int longestStrChain(vector<string>& words) {

        int N = words.size();

        vector<int> lis(N, 1);

        sort(words.begin(), words.end(), compartor);

        int maxChain = 1;

        for (int i = 1; i < N; i++) {

            for (int j = i - 1; j >= 0; j--) {

                if (isPredecessor(words[i], words[j]) && (1 + lis[j] > lis[i])) {
                    lis[i] = 1 + lis[j];
                }

                maxChain = max(maxChain, lis[i]);
            }
        }

        return maxChain;
    }
};


// Applying LIS in different way, so we can reduce that mathching alogrithm.
/* Intution: 
   Idea is that, (L-1) length words will be visited first, compare to L length words. 
   So when we visit the L length words, we can make it to (L-1) length word by drooping one of its characer,
   and then we can find in alreday visited (L-1) words map, to find it as predecessor, If we get it 
   then we extend that chain by updating LIS_map. 
*/
class Solution {
public:

    static bool compartor(string a, string b) {
        return a.size() < b.size();
    }

    int longestStrChain(vector<string>& words) {

        int N = words.size();

        unordered_map<string, int> dp;

        sort(words.begin(), words.end(), compartor);

        int maxChain = 1;

        for (string w : words) {

            // Each word can create atleast 1 size of chain. (base case)
            dp[w] = 1;

            for (int i = 0; i < w.length(); i++) {

                // break the word, by removing "ith" character, so we can check in map
                // if such predecessor is already visited or not, if yes, then we can extend it more.
                string pre = w.substr(0, i) + w.substr(i + 1);

                // found predecessor, extend it.
                if (dp.count(pre)) {
                    dp[w] = max(dp[w], dp[pre] + 1);
                }

            }

            maxChain = max(maxChain, dp[w]);
        }

        return maxChain;
    }
};
```

[673. Number of Longest Increasing Subsequence](https://leetcode.com/problems/number-of-longest-increasing-subsequence/)

```c
/* Intution:

This is LIS Pattern that we know, but in this question ask is, return number of LIS. 

So we just not need to track maxLIS but its count as well. 

Simple idea is that, 

    1 3 5 4 7
    LIS ending at 3 => 1 3
    LIS ending at 5 => 1 3 5
    LIS ending at 4 => 1 3 4
    LIS ending at 7 => 1 3 5 7 | 1 3 4 7

    If we notice, LIS ending at 7.... is considering all the LIS of length 3. 

    LIS => 3 + 1 => 4 
    LIS_Count => 1 + 1 => 2

    So there is slight change standard LIS, 

        The way we are calculating LIS will remain same, only change is there...

        1 + lis[j] == lis[i] => indicate that... lis[i] is already updated with this length,
        but there are subsequence which are ending at jth also can have same length lis[i]. 

        So we need to consider its count.

        For example: 

            LIS ending at 7 = 1 3 4 7

            But it can also extend the "LIS ending at 5 => 1 3 5"

            So we only update the count of maxLIS. 

    So it is obvious that, we need 2D array dp[N][2]... to keep track of LIS and LISCount. 


    // Got bigger length LIS
    dp[i][0] = 1 + dp[j][0]
    dp[i][1] = dp[j][1] (can extend all subseq which are ending at dp[j])    

    // Got same length LIS
    dp[i][1] += dp[j][1] (only update count)

*/
class Solution {
public:

    int findNumberOfLIS(vector<int>& nums) {

        int N = nums.size();

        // dp table store, dp[0][0] => maxLIS, dp[0][1] => maxLISCount
        // First Index[0], it store the length of longest LIS
        // Second Index[1], it store the number of longest LIS
        vector<vector<int>> dp(N, vector<int>(2, 1));

        int maxLIS = 1;

        for(int i = 1; i < N; i++) {

            for(int j = i - 1; j >= 0; j--) {

                if(nums[j] < nums[i] && (1 + dp[j][0] >= dp[i][0])) {

                    // Found Bigger LIS
                    if(1 + dp[j][0] > dp[i][0]) {
                        dp[i][0] = 1 + dp[j][0];    // Update LIS Length
                        dp[i][1] = dp[j][1];        // Same number of LIS, ended at jth index we can extend it
                    }

                    // Got other LIS whose length is also same as lis[i]
                    // So we can increase the count of LIS, which are ending at jth index
                    // and can be extended of same length. 
                    else {
                        dp[i][1] += dp[j][1];
                    }
                }
            } 

            maxLIS = max(maxLIS, dp[i][0]);         
        }

        // Count all LIS which have largest LIS
        int count = 0;
        for(int i = 0; i < N; i++) {
            // Consider all chain, which have maxLIS. 
            if(dp[i][0] == maxLIS) {
                count += dp[i][1];     
            }
        }
        return count;
    }
};
```

#### 2_GFG_Longest_Bitonic_subsequence

```c
/* Intution:

    We need subseq which is increasing and decreasing from center point. And center point can be any of nums[i].

    For increasing subsequence we can use LIS Algorithm.

    For decreasing subsequence as well, we can use LIS(LDS) algorithm, but twist is that. We have to find LDS from behind.

    Because,

    First_part_increassing + nums[i] + Second_Part_Decreasing

    LIS: 1 3 5 7
    LDS: 7 2 1

    Also given that, both part should be present to consider it as Bitonic. So we don't consider nums[i] length
    when we compute nums[i]...that's why I initialized with "0"... and Later during computation we will add that.

    Check the code!!

*/


class Solution {
public:
    int LongestBitonicSequence(int N, vector<int> &nums) {

        // Initialize with "0", not considering length of number itself.
        vector<int> lis(N, 0), lds(N, 0);

        // Find LIS
        for (int i = 1; i < N; i++) {
            for (int j = i - 1; j >= 0; j--) {
                if ((nums[j] < nums[i]) && (1 + lis[j] > lis[i])) {
                    lis[i] = 1 + lis[j];
                }
            }
        }

        // Find LDS
        for (int i = N - 2; i >= 0; i--) {
            for (int j = i + 1; j < N; j++) {
                if ((nums[j] < nums[i]) && (1 + lds[j] > lds[i])) {
                    lds[i] = 1 + lds[j];
                }
            }
        }

        // get MaxBitonicSub Length
        int maxBitonicSub = 0;
        for (int i = 0; i < N; i++) {
            if (lis[i] > 0 && lds[i] > 0) {
                maxBitonicSub = max(maxBitonicSub, lis[i] + lds[i] + 1);    // +1 (nums[i], should be present atleast one time)
            }
        }

        return maxBitonicSub;
    }
};
```
