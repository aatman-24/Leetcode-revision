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

Question : 239. Sliding Window Maximum
Topic : Queue, Monotonic Queue
Problems : https://leetcode.com/problems/sliding-window-maximum/description/

==============================> Explanation <=============================================

1) Brute Force using priority_queue(max_heap): (Wrong Apporach)

Idea is that, we can manage the one PQ for given window of K elements. Each time pq.top() give the maximum element. But the issue is that
we have to validate the window when it's size increased more than K. For that, we need to remove element from PQ. PQ doesn't give pre-built method
so I write it down that function.

removeElement() => Time: O(K), Space: O(K)(to store all the elemetns of window in worst case)
maxSlidingWindow()
Time: O(N) * O(K)(removeElement) => O(N*K) => O(N^2) (Give, K = N)
Space: O(K)

2) Brute Force directly:
- For each i from (0 -> N-K), I can iterate over next K element and find them maximum. which take similar time.
Time: O(N) * O(K)(removeElement) => O(N*K) => O(N^2) (Give, K = N)
Space: O(1)

3) Monotonic Increasing Deque:

- Idea is that, We have to maintain one dequeue in increasing order,

    left -> have maximum elements, right -> have minimum elements

    We only allow to add elements from the right end.

    Inutition behind this apporach is that,

        arr: 1 3 -1 -3

    window => [1], DQ=[1]
    window => [1, 3], DQ=[3], once greater element in queue compare to previous elements, those elements can't be maximum of window so we remove those.
    window => [1, 3, -1], DQ=[3, -1], we allow upocoming elements who is less than curr_max, because once curr_max got out of window, someone need to become maximum.

    So those are two are reasons we allow increasing order in deque only.

- Before adding new element in window, we validate window by removeing element who got out of window which can be done on deque.

Check the code!!


==============================> Approach and Time Complexity <============================

N = s.size()

1) Brute Force using priority_queue
Time: O(N*K) = O(N^2)
Space: O(K)

2) Brute Force directly
Time: O(N*K) = O(N^2)
Space: O(1)

3) Monotonic Increasing Deque
Time: O(N)
Space: O(K)

*/



class Solution {
public:

    void removeElement(priority_queue<int> &maxPQ, int element) {
        vector<int> poppedElements;
        while (true) {
            int poppedElement = maxPQ.top(); maxPQ.pop();
            if (poppedElement == element)
                break;
            poppedElements.push_back(poppedElement);
        }
        for (int num : poppedElements)
            maxPQ.push(num);

    }

    vector<int> maxSlidingWindow(vector<int>& nums, int K) {

        priority_queue<int> maxPQ;
        vector<int> max_sliding_window;
        int begin = 0, end = 0, N = nums.size();
        int max_of_window = INT_MIN;

        for (int end = 0; end < N; end++) {

            // Adjust window
            if (end - begin + 1 > K) {
                removeElement(maxPQ, nums[begin]);
                begin++;
            }

            maxPQ.push(nums[end]);

            if (maxPQ.size() >= K) {
                max_sliding_window.push_back(maxPQ.top());
            }
        }

        return max_sliding_window;
    }
};





class Solution {
public:

    vector<int> maxSlidingWindow(vector<int>& nums, int K) {

        // monotonic increasing deque
        deque<int> dq;
        vector<int> max_of_sliding_window;
        int N = nums.size();

        // Add first K elements(create window of K)
        for (int i = 0; i < K; i++) {

            // Maintain Increasing order of Queue, so remove smaller elements from the end before adding large number.
            // Why (nums[dq.back()] == nums[i]) equal as well ? Because same number with higher index will have more priority. That's because value is same and greater index it can reside on deque more than previous one.
            while (!dq.empty() && nums[dq.back()] <= nums[i]) {
                dq.pop_back();
            }

            // add the index, instead of number because using index we can validate the window by size.
            dq.push_back(i);
        }

        // add maximum of first window
        max_of_sliding_window.push_back(nums[dq.front()]);

        for (int j = K; j < N; j++) {

            // pop out invalid elements out of window. If front() holds index which is out of window for current j, remove it.
            while (!dq.empty() && (j - dq.front() >= K)) {
                dq.pop_front();
            }

            // Addition of nums[i]

            // 1. Add it at right place, maintain the order of deque.
            while (!dq.empty() && nums[dq.back()] <= nums[j] ) {
                dq.pop_back();
            }
            // 2. Add it.
            dq.push_back(j);

            max_of_sliding_window.push_back(nums[dq.front()]);
        }

        return max_of_sliding_window;
    }
};