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

Question : 238. Product of Array Except Self
Topic : PrefixSum
Problems : https://leetcode.com/problems/product-of-array-except-self/description/

==============================> Explanation <=============================================

1) Brute Force:
- For each i, I can do multiplication of left side array and right side array and put it at ans[i]. Take: O(N^2), O(1) space.

2) I can precalculate the all product multiplication and for each i, peform, ans[i] = productOfArray/arr[i], but the problem is that arr[i]=0, then it won't work.

3) Using prefixProduct and suffixProduct we can precompute it. ans[i] = prefixProduct[i-1] * prefixProduct[i+1], Take: O(N), O(N)

4) Instead of using extra space for O(N), we can do it runtime.
Edge case: [0, 1, 3, 5, 0]... ans[0] => product of arr[1->N]. So it is not matter what arr[0] contains for ans[0]. Similar to arr[N-1].
Check the code!!


==============================> Approach and Time Complexity <============================

N = s.size()

1) Brute Force
Time: O(N^2)
Space: O(1)

2) prefixProduct && suffixProduct
Time: O(N)
Space: O(N)

3) Dynamic prefixProduct & prefixProduct
Time: O(N)
Space: O(1)


*/



class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {

        int N = nums.size();

        vector<int> productOfPrefix(N, 0), productOfSuffix(N, 0);
        productOfPrefix[0] = nums[0];
        productOfSuffix[N - 1] = nums[N - 1];

        for (int i = 1; i < N; i++) {
            productOfPrefix[i] = productOfPrefix[i - 1] * nums[i];
        }

        for (int j = N - 2; j >= 0; j--) {
            productOfSuffix[j] = productOfSuffix[j + 1] * nums[j];
        }

        vector<int> productOfArray(N, 0);
        for (int i = 0; i < N; i++) {

            int product = 1;

            if (i - 1 >= 0)
                product *= productOfPrefix[i - 1];

            if (i + 1 < N)
                product *= productOfSuffix[i + 1];

            productOfArray[i] = product;
        }

        return productOfArray;
    }
};



class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {

        int N = nums.size();

        int curProduct = 1;
        vector<int> productOfArray(N, 1);

        for (int i = 0; i < N; i++) {
            productOfArray[i] *= curProduct;
            curProduct *= nums[i];      // keep track of product till nums[i-1] from left end. It is used for next ans[i+1]
        }

        curProduct = 1;
        for (int i = N - 1; i >= 0; i--) {
            productOfArray[i] *= curProduct;
            curProduct *= nums[i];     // keep track of product till nums[i+1] from right end. It is used for ans[i-1]
        }

        return productOfArray;
    }
};