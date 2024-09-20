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

Question : 8001. Allocate Books
Topic : BS
Problems : https://www.interviewbit.com/problems/allocate-books/

==============================> Explanation <=============================================

Variation: Min-Max, Max-Min

It's not easy to come up with binary search, you need remember this variation, no matter what!

Given that you need to find minimum of maximum allocation.

We need to allocate the book to given no of students(M) such that, whoever holding the maximum pages during allocation, needs to be minimum in all possibilities.

Here, "you apply the binary search on maximum pages which can be allowed". And if it is allow then you try to decresae it, if it is not allow you try to increase that threshold. Simple!

###But problem is how you determine given maximum page can be allowed or not ?
For that, you try to allocate as much as possible to the student from start, and see how many students we got with given allocation barrier.

If we are getting more students it means => allocation is lesser then it should => we increase allocation barrier
If we are getting less students it measn => allocation is more than it should => decresae allocation
If we are getting equal amonunt of student => it means current allocation can be our answer but still we look minimum right => decrease allocatino.

Let's directly talk about the search-space.

max_pages_allowed => 1, then no student can hold any book.
max_pages_allowed => min(arr), only one student can hold that book no other student can do.
max_pages_allowed => max(arr), now each student have atleast one book. This can be our minimum.
max_pages_allowed => sum(arr), then only one student hold all the books. This can be our maximum.

Our answer reside within [lh, rh] and we need to find using binary seach. Our mid will be the max_pages_allowed(allocation) and then
we decide which one of half we can skip.

Edge case: At the end lh hold the minimum allocation. So that is our answer. But we can also change the code to match our style.#2

Check the code!

==============================> Approach and Time Complexity <============================


1) Binary Search
Time: O(logN)
Space: O(logN)


 */



int getNoOfStudentWithGivenAllocation(vector<int> &arr, int maxAllocation) {

    // keep track of how many student got allocated with keeping barrier as maxAllocation.
    int noOfStudent = 1;

    // cur student holding this number of pages.
    int pages = 0;

    for (int num : arr) {

        if (pages + num <= maxAllocation) {
            pages += num;
        }
        else {
            pages = num;
            noOfStudent++;      // new student
        }

    }

    return noOfStudent;
}

int books(vector<int> arr, int n1, int requiredStudent) {

    int lh = *max_element(arr.begin(), arr.end());          // max of arr.
    int rh = accumulate(arr.begin(), arr.end(), 0);         // sum of entire arr.

    while (lh <= rh) {

        int maxAllocation = (lh + rh) >> 1;

        int noOfStudent = getNoOfStudentWithGivenAllocation(arr, maxAllocation);

        // allocation is less that's why more students we are getting, we need to increase the allocation to decrease the student.
        if (noOfStudent > requiredStudent) {
            lh = maxAllocation + 1;
        }
        else {
            rh = maxAllocation - 1;
        }

    }

    return lh;   // At the end lh hold the answer.
}


// #2
int books(vector<int> arr, int n1, int requiredStudent) {

    int lh = *max_element(arr.begin(), arr.end());          // max of arr.
    int rh = accumulate(arr.begin(), arr.end(), 0);         // sum of entire arr.
    int minimumAllocation = rh;

    while (lh < rh) {

        int maxAllocation = (lh + rh) >> 1;

        int noOfStudent = getNoOfStudentWithGivenAllocation(arr, maxAllocation);

        if (noOfStudent == requiredStudent) {
            minimumAllocation = min(minimumAllocation, maxAllocation);      // maxAllocation can be our answer, but will still looking for min allocaiton.
        }

        // allocation is less that's why more students we are getting, we need to increase the allocation to decrease the student.
        if (noOfStudent > requiredStudent) {
            lh = maxAllocation + 1;
        }
        else {                          // noOfStudent > requiredStudent || noOfStudent == requiredStudent(looking for min allocation)
            rh = maxAllocation - 1;
        }

    }

    return minimumAllocation;   // At the end lh hold the answer.
}
