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

Question : 3000. K-th element of two Arrays
Topic : BS
Problems : https://www.geeksforgeeks.org/problems/k-th-element-of-two-sorted-array1317/1

==============================> Explanation <=============================================

Standard Median of sorted Array.

Here Instead of getting median element (n1+n2)/2, Here we need to find kth element after merging. Same concept.

1) BruteForce: Add into one array, and then return it. O(N) for merge botha array.

2) Counter: Use counter while adding element into single array. Take O(K) time.

3) Binary Search:

arr1 -> holds elements in sorted order
arr2 -> holds elements in sorted order

Given that, need to find kth element after merge.

merge array looks like => [ k,...N - k] elements

we will find the boundary|cut from both arrays whose left side elements = k elements.

Our task is to find how many element contribute to that group. If we find that, and take maximum of last two elements then it will be the kth element.


What is difference in this and median of two sorted array ?

1) Here we need think for left part which contains k elements in total, not N/2.

So if we are taking A elemets form arr1, then we need to take remaining (K - A) elements from array-2.

2) low and high also got changed. Which indicate the how many element we are picking up from the array-1.

for median we, low = 0, high = n1.. because it can be any elements from (0 -> n1) can become median because n1 < n2.

But here it is little bit change, we need to find kth elements.

Ex: arr1 = [3, 4, 5]
    arr2 = [1, 2, 7, 8]

    If k = 1 -> arr2[0]
       k = 2 -> arr2[1]
       k = 3 -> arr1[1]
       k = 6 -> arr1[2]

It is not always we find kth element from arr1. when K = 6 and even standard algorithm got disturbed.

mid1 -> 1
mid2 -> 5 but as you can see arr2 doesn't hold the 5 elements, so there could be misjustification when we compare l1, l2, r1 and r2.

Case2: k < n1
arr1 = [3, 4, 5, 10, 11, 20]
arr2 = [1, 2, 7, 8, 12, 13, 14, 21]

k=2(2nd element),
mid1 = 3, mid2 = k - mid1 = 2 - 3 = -1....
What we are doing wrong is here, mid1 is referring the 3 elements while we need sorting upto 2 elements only. That's wrong.

high should be upto k only when k < n1.

low and high referce to boundary where we can find our kth element.

low => max(0, n2-k). Why (n2-k) because, if n2-k >= 0, it means atleast those element must be added without any comparsion in merge of both array.
high => min(k, n1), incase k < n1... then we try to find boudnary from (0, k) only.


==============================> Approach and Time Complexity <============================


1) Binary Search
Time: O(logN)
Space: O(logN)


 */



int kthElement(vector<int>& arr1, vector<int>& arr2, int k) {

    if (arr2.size() < arr1.size())
        return kthElement(arr2, arr1, k);

    int n1 = arr1.size(), n2 = arr2.size();




    int low = max(0, k - n2), high = min(k, n1);





    while (low <= high) {           // I'm picking up elements from arr1 only. We can select 0th or n1 element from that.

        int cut1 = (low + high) >> 1;      // taken cut1 from array-1.
        int cut2 = (k - cut1);

        int left1 = (cut1 <= 0) ? INT_MIN : arr1[cut1 - 1];
        int left2 = (cut2 <= 0) ? INT_MIN : arr2[cut2 - 1];

        int right1 = (cut1 < n1) ? arr1[cut1] : INT_MAX;            // CUT1==N1 can be possible because high is n1.
        int right2 = (cut2 < n2) ? arr2[cut2] : INT_MAX;

        if (left1 <= right2 && left2 <= right1) {
            return max(left1, left2);
        }
        else if (left1 > right2) {
            high = cut1 - 1;
        }
        else {
            low = cut1 + 1;
        }

    }

    return -1;

}