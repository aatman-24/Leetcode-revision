#### DP Series: MCM Pattern

---

###### 1_dp_gfg_Matrix Chain Multiplication

```c

/* Intuition:


Standard question.

Given the arr[] = {10, 20, 30, 40}

M1 = 10 X 20
M2 = 20 X 30
M3 = 30 X 40

We need to find minimum multiplication cost.

Ex: M1 * (M2 * M3) || (M1 * M2) * M3

For multiplying matrix we need atleast two matrix, for single matrix cost will be zero. (base case)

What we will do is, we try to make cut at every ith index starting from 1th index.

suppose we are making cut at kth index = {i....k...j}

cost = cost(i, k) + cost(k, j) + multiplication_cost(i, k, j)...

multiplication_cost = M1 * M2 => A[i-1] * A[K] * A[J]...considering(M1 = i-1 * K, M2 = K * j dimensions)

we are not sure what combination is best for (i..k) range so we again apply recursion there to find minimum cost.

Check, recursive and top-down approach...

Bottom-up approach: When we see mcm(1, 4) this calls to mcm(2, 4) | mcm(3, 4).... get idea from top-down.

In Bottom-up, we need to start i = N - 1 -> 0.... so when we compute mcm(1, 4) that time we have result of mcm(2, 4) and mcm(3, 4)

*/

// Top-down
int t[101][101];

int mcm(int arr[], int i, int j) {

    // base condition
    if (i == j || i > j)
        return 0;

    if (t[i][j] != -1)
        return t[i][j];

    int minCost = INT_MAX;
    // M1 = (i-1, i), M2 = (k, j)
    for (int k = i; k <= j - 1; k++) {
        int cost = mcm(arr, i, k) + mcm(arr, k + 1, j) + arr[i - 1] * arr[k] * arr[j];
        minCost = min(minCost, cost);
    }

    return t[i][j] = minCost;
}


int matrixMultiplication(int N, int arr[]) {
    memset(t, -1, sizeof(t));
    return mcm(arr, 1, N - 1);
}
```

```c
// Bottom-up
int matrixMultiplication(int N, int arr[]) {

    vector<vector<int>> dp(N + 1, vector<int>(N + 1, 0));

    // base condition
    // dp[0][0] = dp[1][1] = dp[2][2] = 0; (covered during initalization)


    // Started with i = N-1, because if you see top-down approach.... it will
    // first solve (4, 5) and then (0, 4) because (0,4) needs (4, 5) as intermidatory result.
    for (int i = N - 1; i >= 0; i--) {
        for (int j = i + 1; j < N; j++) {   // j = i+1, because i < j
            int minCost = INT_MAX;
            for (int k = i; k <= j - 1; k++) {
                int cost = dp[i][k] + dp[k + 1][j] + arr[i - 1] * arr[k] * arr[j];
                minCost = min(minCost, cost);
            }
            dp[i][j] = minCost;
        }
    }

    return dp[1][N - 1];
}
```

[1547. Minimum Cost to Cut a Stick](https://leetcode.com/problems/minimum-cost-to-cut-a-stick/)

```c
/* Intuition:

How cost will be calcualted ?

suppose you are cutting 5 length rod... from ith point...

cost = remaining_cost_left_side + remaining_cost_right_side + 5(length of cost)

In short, whatever length rod you are cutting is direct cost.


Recursion:

In this, I am managing total 4 parameters.
rod_begin, rod_end => to calculate direct cost (length of rod)
i, j => which keep track of which cut we have applied in which range.

So based on which order we are making cuts...cost will be different..because if we make cut on 7th length rod and 3 length rod => direct cost can be 7 or 3...

Recurssion Relation is straightforward:

	minCost(begin, end, i, j) =>

		k: i -> j

			minCost(begin, cuts[k], i, k-1) + minCost(cuts[k], end, k+1, j) + (end - begin)(direct cost)

See how I changed begin & end...

	If I am making cut at cuts[k].... then left rod... end = cuts[k], and for
	right rod... begin=cuts[k]..

Top-Down Approach with managing begin & end pointers:

	Here, we just applied memorization apporach. Nothing else.

Bottom-up Approach with managing begin & end pointers:

	This one I tried, but I was not able to manage the begin & end boundary in this approach.


So I come up with one trick is that...

	we will push 0 and N... into the cuts[]... so we don't have to manage the boundary, edge cases.

	Because, if cuts[] = {10}.... only given then getting the left & right boundary which is 0 & N during
	counting rod length become diffcult...

	instead of we push cuts[] = {0, 10, 20}.... we can count it by "cuts[j] - cuts[i]". Only this is that
	we will iterate the k between (i, j)... indicate cutting between (i, j)...which is right & easy...

	Because ultimately...we are finding minCost of (0, N) length rod...applying given cuts[]....

*/


// Recursion Solution
class Solution {
public:

    int minCost(vector<int> &cuts, int begin, int end, int i, int j) {

        if(i > j) return 0;

        int minimumCost = INT_MAX;
        for(int k = i; k <= j; k++) {
            int cost = minCost(cuts, begin, cuts[k], i, k - 1) + minCost(cuts, cuts[k], end, k + 1, j) + abs(begin-end);
            minimumCost = min(minimumCost, cost);
        }

        return minimumCost;
    }


    int minCost(int n, vector<int>& cuts) {
        sort(cuts.begin(), cuts.end());
        return minCost(cuts, 0, n, 0, cuts.size() - 1);
    }
};

// Top-down Approach, managing the boundary separately...
class Solution {
public:

    int t[101][101];

    int minCost(vector<int> &cuts, int begin, int end, int i, int j) {

        if(i > j) return 0;

        if(t[i][j] != -1)
            return t[i][j];

        int minimumCost = INT_MAX;
        for(int k = i; k <= j; k++) {
            int cost = minCost(cuts, begin, cuts[k], i, k - 1) + minCost(cuts, cuts[k], end, k + 1, j) + abs(begin-end);
            minimumCost = min(minimumCost, cost);
        }

        return t[i][j] = minimumCost;
    }


    int minCost(int n, vector<int>& cuts) {
        memset(t, -1, sizeof(t));
        sort(cuts.begin(), cuts.end());
        return minCost(cuts, 0, n, 0, cuts.size() - 1);
    }
};

// Top-down Approach (With Boundary Addition)
class Solution {
public:

    int t[103][103];

    int minCost(vector<int> &cuts, int i, int j) {

        if(i > j) return 0;

        if(t[i][j] != -1)
            return t[i][j];

        int minimumCost = INT_MAX;
        for(int k = i+1; k < j; k++) {
            int cost = minCost(cuts, i, k) + minCost(cuts, k, j) + abs(cuts[i]-cuts[j]);
            minimumCost = min(minimumCost, cost);
        }

        // (i, j) is irrelveant... keeping as "0" only, otherwise above cost calculation given out of range for int. 
        return t[i][j] = minimumCost == INT_MAX ? 0 : minimumCost;
    }


    int minCost(int n, vector<int>& cuts) {
        memset(t, -1, sizeof(t));
        cuts.push_back(0);
        cuts.push_back(n);
        sort(cuts.begin(), cuts.end());
        return minCost(cuts, 0, cuts.size()-1);
    }
};



// Bottom-up with boundary Addition
class Solution {
public:
    int minCost(int n, vector<int>& cuts) {

        // Adding,(0, N) to form the boundary. 
        cuts.push_back(0);
        cuts.push_back(n);

        sort(cuts.begin(), cuts.end());

        int m = cuts.size();

        vector<vector<int>> dp(m, vector<int>(m, 0));

        for(int i = m - 1; i >= 0; i--) {
            for(int j = i + 1; j < m; j++) {
                int minimumCost = INT_MAX;
                for(int k = i+1; k < j; k++) {
                    int cost = dp[i][k] + dp[k][j] + abs(cuts[i] - cuts[j]); 
                    minimumCost = min(cost, minimumCost);
                }
                // don't confuse with this... I'm keeping dp[i][j] as "0" only, not assiging INT_MAX because (i, j) is irrevalnt
                // (i, j) subproblem can't be solution of any other range...
                // and during cost calcualtion given out of range for int. 
                dp[i][j] = minimumCost == INT_MAX ? 0: minimumCost;            
            }
        }

        return dp[0][m-1];
    }
};
```

[312. Burst Balloons](https://leetcode.com/problems/burst-balloons/)

```c

/* Intuition:

1) Brute Force: So we know that, when we burst ballon that ballon got eliminated... and later we can choose any of remaining ballon to burst...
In short... whatever is optimium solution...those ballon got bursted in some orders..right... so what if we try all orders(permutation) and
see which one give maximum cost. (permuation...checking O(N))

2) DP:

This question is crazy!!.... Remember the trick of this question....

Basically...we are following the MCM pattern....but there is one problem....

Question is that, for given ballons[].... we have to burst all ballons such that cost will be maximum.

if we burst kth ballon =>

	direct cost = ballons[k-1] * ballons[k] * ballons[k+1] (incase out of bound, use the 1 as cost)

so what I thought is that....

	I can burst any of the ballons from given range (i, j) and then calculate cost for (i, k-1) and (i, k+1)... make sense(following MCM pattern....)

	But problem is that....

		we burst kth ballon... new array will look like....

			before: [i, i+1...k-1, k, k+1,....j]

			after:  [i, i+1...k-1, k+1...j]		(see k ballon got bursted)

		And next time when we burst k-1 ballon that time... A[k+1] is considered in direct costing... which is different than MCM pattern.

		In MCM, what we are doing is that when we make cut(choose) kth element... (i, k-1) and (k+1, j) is independent recursion subproblem. So we will resolve that
		and choose optimum costing from both range...

		But here...That's not the case... if we burst kth ballon.... formed this subproblems (i, k-1) and (k+1, j).. and these are dependent on each other... during calculation of costing..
		So those independent calculation won't work here(wait before coming to final verdict!!!)

		Ex: arr[] = {1, 3, 4, 2}... k=3 bursting... arr[] = {1, 4, 2}...1 & 4 become neighbors of each other..so we again choose 4 for bursting... costing of "1"(left element)
		will be added.

		Ex2: arr[] = {1, 2, 3, 4, 5}....

			burst: 3...cost = 2 * 3 * 4, arr[] = {1, 2, 4, 5}
			burst: 4...cost = 2 * 4 * 5, arr[] = {1, 2, 5}
			burst: 5....cost = 2 * 5 * 1, arr[] = {1, 2}

			See.... 2 is repeating many times...which was not case in MCM...... (Hope you understand)

			Not, Go through this: https://leetcode.com/problems/burst-balloons/solutions/892552/for-those-who-are-not-able-to-understand-any-solution-with-diagram


How to solve then ? If we can't we apply the MCM pattern then how to solve this ?

Issue is that, if we burst kth ballon A[k-1] * A[k] * A[k+1] is direct cost... and both side subproblems cannot be resovled independently...right...

We will apply MCM... but instead of bursting kth ballon first in (i, j) range we will burst at last... because if we do that way....

	(i, k-1) k (k+1, j)

	then (i, k-1) && (k+1, j) is not dependent on each other.. because when we burst kth ballon.... already (i, k-1) && (k+1, j) all ballons are bursted...

	Then...question is how we will compute direct cost ?

	Easy: If I'm saying that... (i, k-1) && (k+1, j) already bursted....it means

		cost = A[i-1] * A[k] * A[j+1]

		because (i-1) and (j+1) is next neighbors of k.....

	Hope you get it!!

At high level if you think...from (0, m-1) range we will select kth element which will be burst at last...then in subproblems (i, k-1) & (k+1, j)... we again pick up kth element
to burst at last.... this chaining will continue until there is one ballon left(base case)... which will be added as direct cost(because after that subproblems become invalid...)

Boundary Related Issue:

If we divide the subproblem this way,

	k = i -> j,

		(i, k-1), k, (k+1, j)

	when k = i

		first subproblem => (i, i-1) (which is invalid, i < j)

	For recursive solution, it is handled in base case..but facing issue in bottom-up approach to manging boundary....


Instead,

If we divide the subproblem this way,

	k = i+1 -> j-1,

		(i, k), k, (k, j)

	when k = i + 1,

		first subproblem => (i, i+1)...which is valid.

	But see when I'm referring the subproblem range as (i, j).... that time ith and jth index is not considered in range...they are outsider...

	so cost caluation also will be changed from,

			A[i-1] * A[k] * A[j+1],

	To,

			A[i] * A[k] * A[j] (because i and j which are not part of range, will become neighbors after ballon got bursted)...



*/



// Top-down (Boundary Apporach-2)
class Solution {
public:

int t[302][302];

    int maxCoins(vector<int>& nums, int i, int j) {

        if(i > j) return 0;

        if(t[i][j] != -1)
            return t[i][j];

        int maxCost = 0;

        for(int k = i+1; k < j; k++) {            // (i, j) is exclusive boundary...

            // direct cost
            int cost = nums[k];

            // range: (i, k), k, (k, j)            // (i, k) & (k, j) is exclusive boundary..they are not added in that range...

            // kth is last ballon we are bursting in range(i, j), indicate we have already bursted [i+1 k-1] & [k+1, j-1] ballons. 
            // so adjancent element of kth element are ith and jth, which are still left to burst. That's why we are taking those to calculate direct cost. 
            if(i >= 0)
                cost *= nums[i];

            if(j < nums.size())
                cost *= nums[j];

            cost += maxCoins(nums, i, k) + maxCoins(nums, k, j);

            maxCost = max(maxCost, cost);
        }
        return t[i][j] = maxCost;
    }

    int maxCoins(vector<int>& nums) {

        memset(t, -1, sizeof(t));

        // using boundary nums {1, nums, 1}... to avoid handling edge case. 
        // Because when we burst 0th & last ballon we need to handle that case...better to use boundary array. 
        vector<int> numsWithBoundary = {1};
        for(int num: nums) {
            numsWithBoundary.push_back(num);
        }
        numsWithBoundary.push_back(1);

        int m = numsWithBoundary.size();

        return maxCoins(numsWithBoundary, 0, m-1);    // (i, j) is exclusive boundary
    }
};

// Bottom-up approach (Boundary Apporach-2)
class Solution {
public:

    int maxCoins(vector<int>& nums) {

        vector<int> numsWithBoundary = {1};
        for(int num: nums) {
            numsWithBoundary.push_back(num);
        }
        numsWithBoundary.push_back(1);

        int m = numsWithBoundary.size();

        // dp table
        vector<vector<int>> dp(m+1, vector<int>(m+1, 0));

        for(int i = m - 1; i >= 0; i--) {                // (i, j) is exclusive boundary... (k will be choose between them)...dp[i][j] = dp[i][k] + dp[k][j] + direct_cost
            for(int j = i + 1; j <= m - 1; j++) {
                int maxCost = 0;
                for(int k = i + 1; k < j; k++) {
                    int cost = numsWithBoundary[k];
                    if(i >= 0)
                        cost *= numsWithBoundary[i];
                    if(j < m)
                        cost *= numsWithBoundary[j];
                    cost += dp[i][k] + dp[k][j];
                    maxCost = max(maxCost, cost);
                } 
                dp[i][j] = maxCost;
            }
        }

        return dp[0][m-1];
    }
};



// Bottom-up (MCM Pattern Template)
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        //including the nums[-1] and nums[n]
        int n = nums.size() + 2;        
        vector<vector<int>> dp(n, vector<int>(n));
        vector<int> new_nums(n, 1);
        int i = 1;
        for(auto num : nums) {
            new_nums[i++] = num;
        }
        for(int len = 2; len <= n; len++) {                 // start with small range length of 2...
            //iterate from interval length from 2 to n
            for(int i = 0; i <= n - len; i++) {                // (i, i+len-1) (exclusive boundary)
                int j = i + len - 1;
                //select between left and right boundary (i, j)
                for(int k = i + 1; k < j; k++) {                 // (i, j) work as boundary of range... exclusive
                    dp[i][j] = max(dp[i][j], dp[i][k] + dp[k][j] + new_nums[i] * new_nums[k] * new_nums[j]);
                }
            }
        }
        return dp[0][n - 1];
    }
};
```

[132. Palindrome Partitioning II](https://leetcode.com/problems/palindrome-partitioning-ii/)

```c
/* Intuition:


Brute Force: We can apply recursion to check (i, j) is Palindrome and if yes then we can check (i+1, j)...
And keep track of minimum cut. Which is done in #1 Solution.

DP(MCM): On the brute force, applied the memorziation to avoid duplicate computation of subproblems.

But problem is that, DP(MCM) take O(N^3) Time... Given N = 2000.. we are getting TLE. Main issue is that,
In other MCM Problem we don't need to check whether(i, j) satisfy some condition, but here we need to check s[i..j]
is Palindrome which costing us O(N) time... leads to O(N^3).

There are 2 Specific solution of this question, both are following MCM pattern(but twisted way)...

#1: We try to find minCut and Palindrome substr, both at same time rathar than checking every time.
Idea is that,

		For s[i...j] substr....if s[i] == s[j] && s[i+1...j-1] (insider substr) is also palindrome,

		It menas s[i..j] is also palindrome.

		minimum cutting is required from (0, j) => minCut[i-1] + 1

		Cuts are => {0, i-1}, {i, j]}

Problems, here is that...we are chekcing for each(i, j) substr through loops which can be optimized.

#2: We put "ith" character as center of Palindrome and try to increase as much as its length so we get bigger
Palindrome so cuts will be reduced. That way we don't need to check for each (i, j) range...once range of substr
stopped widening due to mismatch of (s[i], s[j]) we don't check for (i-1, j+1)..


*/


// Specific solution - 1

class Solution {
public:
    /* Intuition:

        For s[i...j] substr....if s[i] == s[j] && s[i+1...j-1] inside string is also palindrome,

        minimum cutting is from (0, j) => minCut[i-1] + 1

        Cuts are => {0, i-1}, {i, j]}

        Again, when we have longer substr of k length(0, k) that time we will use this computed result from (0, j) to get minCuts.

        See how subproblems order got resolved...

            (4, 4) => (3, 4) => (2, 4) => (1, 4)

            (5, 5) => (4, 5)(here we check (3, 4) is palindrome or not) => (3, 5) => (2, 5) => (1, 5)
    */
    int minCut(string s) {

        int N = s.size();

        if (N <= 1)
            return 0;

        // Taking every s[i...j] as not palindrome.
        vector<vector<int>> isPalindrome(N, vector<int>(N, 0));

        // minCuts require for s[0...j], will be stored dp[j+1].
        vector<int> dp(N + 1, 0);

        // Worst case, ith length string require (i-1) cuts, with single digit as pal
        for (int i = 0; i <= N; i++)
            dp[i] = i - 1;

        for (int j = 1; j < N; j++) {
            for (int i = j; i >= 0; i--) {

                // characters are matchings..
                // 1) (i, i) || (i-1, j) with s[i-1] == s[j]
                // 2) s[i] == s[j] && s[i+1...j-1] is pal
                if ((s[i] == s[j]) && ((j - i < 2) || isPalindrome[i + 1][j - 1])) {
                    isPalindrome[i][j] = 1;
                    dp[j + 1] = min(dp[j + 1], 1 + dp[i]);
                }
            }
        }

        return dp[N];
    }
};


// Specific solution - 2: Manancher-like solutiion


class Solution {
public:

    /* Intuition:

        With this solution, we are not checking every (i, j) as palindrome, but we try to increase the length
        of palindrome from the center as much as we can.

        Similar to #1 Specific solution.

        But in this, we consider (ith) character as center of palindrome and increase the length.

        we check, (i-1, i, i+1), (i-2, i-1, i, i+1, i+2)... this way

        And again for this substr [(i-2, i-1, i, i+1, i+2)], we need intermidate result of [(i-1, i, i+1)].

        As we are using centric apporach, we need to check for both even and odd length substr at mid.

        Apart from that, Recurrent Relation remain same but twisted with new indexes,

            Recurrent Relation:

                minCut[j] = min(minCut[j], 1 + minCut[i]]

    */
    int minCut(string s) {

        int N = s.size();

        if (N <= 1)
            return 0;

        // minCuts require from (0, j) will be stored dp[j+1] location...
        vector<int> dp(N + 1, 0);

        // Worst case, ith length string require (i-1) cuts
        for (int i = 0; i <= N; i++)
            dp[i] = i - 1;


        for (int i = 1; i < N; i++) {

            // Odd length center
            for (int j = 0; (i - j) >= 0 && (i + j) < N && s[i - j] == s[i + j]; j++) {
                dp[i + j + 1] = min(dp[i + j + 1], 1 + dp[i - j]);
            }

            // Even length center.. [a,b,b,a]... we are checking form 2nd "b"... for i = 2..first comparision will be (0, 3)
            for (int j = 0; (i - j - 1) >= 0 && (i + j) < N && s[i - j - 1] == s[i + j]; j++) {
                dp[i + j + 1] = min(dp[i + j + 1], 1 + dp[i - j - 1]);
            }
        }

        return dp[N];
    }
};
```

#### MCM_5_Boolean Evaluation

```c
/* Intution

    It is very obvious that, we have to divide string into two parts, and find how many ways
    left and right expression can return true and do aggregation. We can divide string at each
    operator. 

    If operator is reside at kth location => count(i, k-1) + count(k+1, j)

    count(i, j) return total count of ways expression can resolved to true. 

    What if experssion return false ? => We ignore that...right ? NOOOOO

    See,

    OR
    T T => T
    T F => T (see this one)
    F T => T (see this one)
    F F => F

    One of experssion is returning false, still the overall experssion can be resolved to true. 

    Same goes for AND & XOR. So we have to consider that as well......

    So basically, third dimension comes into picture, let's call it "isTrue"..

    count(i, j, isTrue=1) => return total number of ways experssion can be resolved to True
    count(i, j, isTrue=0) => return total number of ways experssion can be resolved to False

    So now we know how to resolve experssion as true/false, and how to count all the ways.

    Let's see Base case, 

    i > j => return 0. (out of bound)
    i == j, isTrue = 1, => return (int) exp[i] == 'T'; (if last charater is = T and isTrue = 1, then only we return 1, else 0)
    i == j, isTrue = 0, => return (int) exp[j] == 'F'; (same as above, but vice versa).
*/
int getNumberOfWaysBasedOnOperator(char oper, int lt, int rt, int lf, int rf, int resolvedAsTrue) {

    /* OR
        T T => T
        T F => T
        F T => T
        F F => F
    */
    if(oper == '|') {
        if(resolvedAsTrue)
            return lt * rt + lt * rf + lf * rt;
        else
            return lf * rf;
    }


    /* AND
        T T => T
        T F => F
        F T => F
        F F => F
    */
    if(oper == '&') {
        if(resolvedAsTrue)
            return lt * rt;
        else
            return lt * rf + lf * rt + lf * rf; 
    }

    /* XOR
        T T => F
        T F => T
        F T => T
        F F => F
    */

    if(oper == '^') {
        if(resolvedAsTrue) 
            return lt * rf + lf * rt;
        else
            return lt * rt + lf * rf;
    }

}

int evaluateExp(string &exp, int i, int j, int isTrue) {

    // base case

    // out of bound
    if(i > j) return 0;

    if(i == j) {
        if(isTrue) return exp[i] == 'T';
        else return exp[i] == 'F';
    }

    int count = 0;

    // with increment of 2, k now only point to operator in experssion.
    // jth point to last oprand, so we stop k at last operator. 
    for(int k = i + 1; k < j; k += 2) {

        int leftExpTrue = evaluateExp(exp, i, k-1, 1);
        int rightExpTrue = evaluateExp(exp, k+1, j, 1);
        int leftExpFalse = evaluateExp(exp, i, k-1, 0);
        int rightExpFalse = evaluateExp(exp, k+1, j, 0);

        count += getNumberOfWaysBasedOnOperator(exp[k], leftExpTrue, rightExpTrue, leftExpFalse, rightExpFalse, isTrue);
    }

    return count;
}

int evaluateExp(string &exp) {

    // Given isTrue = 1, because we want to resolve all exp as True.
    return evaluateExp(exp, 0, exp.size() - 1, 1);

}
```

#### 1043_Partition Array for Maximum Sum

```c
// #1: Brute-Force(Recursive)
/* Intuition
=> Given that choose k elements, I can choose (0, k) elements from "start" index, and remaining elements I can do same thing recursively.
Recurrent Relation:
    cut = start => cut <= start + k && cut < end
        solve(start, cut) + solve(cut+1, end)
    Base case: Whenever we have subarray whose length is < K...that time we can get the cost by choosing maximum of that range and replace with all other elements.
    => maxii * (len_of_array)
Time => O(N*K)(For each subarray division) * O(K)(To get maximum of k size subarray).
*/
class Solution {
public:

    int maxElement(vector<int> &arr, int start, int end) {
        int maxiii = 0;
        for (int i = start; i <= end; i++) {
            maxiii = max(maxiii, arr[i]);
        }
        return maxiii;
    }

    int maxSumAfterPartitioning(vector<int>& arr, int start, int end, int k) {

        // // base case: Out of bound.
        if (start > end) return 0;

        if ((abs(end - start) < k)) {
            int maxi = maxElement(arr, start, end);
            return maxi * (end - start + 1);
        }

        int maxCost = 0;

        for (int cut = start; cut < min(start + k, end); cut++) {

            maxCost = max(maxCost, maxSumAfterPartitioning(arr, start, cut, k) + maxSumAfterPartitioning(arr, cut + 1, end, k));
        }

        return maxCost;
    }

    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        return maxSumAfterPartitioning(arr, 0, arr.size() - 1, k);
    }
};


// Memo-Optimization
/* Intuition
=> Instead of choosing maximum element separately, we are doing in-place during for loop. A little change in recurrent relation as well.
Check the code!!
Recurrent Relation:
    cut = start => cut <= start + k && cut < end
        directCost = max(start...cut) * (cut+1)(times)  (because here we are considering cut=start, k = 0... that's why added +1 offset)
        directCost + solve(cut+1, end)
Time => O(N*K)
*/
class Solution {
public:

    int t[501][501];

    int maxSumAfterPartitioning(vector<int>& arr, int i, int j, int k) {

        // // base case: Out of bound.
        if (i > j) return 0;

        if (t[i][j] != -1)
            return t[i][j];

        int maxCost = 0;
        int maxii = 0;
        for (int cut = 0; cut < k && i + cut <= j; cut++) {
            maxii = max(maxii, arr[i + cut]);
            int directCost = maxii * (cut + 1);
            maxCost = max(maxCost, directCost + maxSumAfterPartitioning(arr, i + cut + 1, j, k));
        }

        return t[i][j] = maxCost;
    }

    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        memset(t, -1, sizeof(t));
        return maxSumAfterPartitioning(arr, 0, arr.size() - 1, k);
    }
};

// 2D-1D DP
// Memo-Optimization
/* Intuition
=> Now If I observe the solution well, I can see the jth index is not contributing into the equation... because we don't have left_subproblem,
only right_subproblem is present...so j = N - 1 for each of right subproblem.
We can reduce the 2D DP => 1D DP... by replacing j = N - 1.
*/
class Solution {
public:

    int t[501][501];

    int maxSumAfterPartitioning(vector<int>& arr, int i, int k) {

        // // base case: Out of bound.
        if (i > arr.size() - 1) return 0;

        if (t[i] != -1)
            return t[i];

        int maxCost = 0;
        int maxii = 0;
        for (int cut = 0; cut < k && i + cut <= arr.size() - 1; cut++) {
            maxii = max(maxii, arr[i + cut]);
            int directCost = maxii * (cut + 1);
            maxCost = max(maxCost, directCost + maxSumAfterPartitioning(arr, i + cut + 1, k));
        }

        return t[i] = maxCost;
    }

    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        memset(t, -1, sizeof(t));
        return maxSumAfterPartitioning(arr, 0, k);
    }
};



// Bottom-up: Converted Top-down into bottom-up.
class Solution {
public:

    int maxSumAfterPartitioning(vector<int>& arr, int k) {

        int N = arr.size();

        vector<vector<int>> dp(N + 1, 0);

        // base case
        // (i > j) return 0. make sure in for loop that won't happen.

        for (int i = N - 1; i >= 0; i--) {
            int maxCost = 0;
            int maxii = 0;
            for (int cut = 0; cut < k && i + cut < N; cut++) {      // at which index I can make cut... (here cut = cutIndex)
                maxii = max(maxii, arr[i + cut]);
                int directCost = maxii * (cut + 1);                 // cut+1, because I'm starting from cut = 0... i + cut = ith element.. indicate 1 element
                maxCost = max(maxCost, directCost + dp[i + cut + 1]);
            }

            dp[i] = maxCost;
        }

        return dp[0];
    }
};



// Reverse Bottom-Up.
class Solution {
public:

    int maxSumAfterPartitioning(vector<int>& arr, int start, int k) {

        // Out of Index
        if (start < 0)
            return 0;

        int maxCost = 0;
        int maxii = 0;

        for (int cut = 1; cut <= k && start - cut >= 0; cut++) {    // Here cut means (0, K)

            maxii = max(maxii, arr[start - cut]);

            int directCost = maxii * cut;

            maxCost = max(maxCost, directCost + maxSumAfterPartitioning(arr, start - cut, k));
        }

        return maxCost;
    }

    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        return maxSumAfterPartitioning(arr, arr.size(), k);
    }
};
```
