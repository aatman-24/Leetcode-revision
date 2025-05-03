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

Question : 986. Interval List Intersections
Topic : Greedy = Interval-Scheduling
Problems : https://leetcode.com/problems/interval-list-intersections/description/
==============================> Explanation <=============================================

Pattern: 56. Merge Intervals

We have to find intersections of two Range List.

We have to use two pointer apporach, to compare the two range from both the list, and
if there is overlapping it means we can have intersection of such ranges. But which pointer
to move once comparsion is done, is depend on which range got over first.

How to find intersection of two range ??
[1, 5], [3, 6] => intersection_min = max(1, 3) && intersection_max = min(5, 6) => [3, 5]

Check the code!!

==============================> Approach and Time Complexity <============================

1) Greedy
Time: O(N)
Space: O(1)

 */



class Solution {
public:

    bool isOverlapping(vector<int> range1, vector<int> range2) {

        if (range2[0] < range1[0])
            return isOverlapping(range2, range1);

        if (range1[0] <= range2[0] && range2[0] <= range1[1])
            return true;

        return false;
    }

    vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList, vector<vector<int>>& secondList) {

        vector<vector<int>> intersection;
        int i = 0, M = firstList.size();
        int j = 0, N = secondList.size();

        while (i < M && j < N) {

            // checking overlapping
            if (isOverlapping(firstList[i], secondList[j])) {

                // getting intersection
                int xx = max(firstList[i][0], secondList[j][0]);
                int yy = min(firstList[i][1], secondList[j][1]);
                intersection.push_back({xx, yy});
            }

            // move pointer, whichever range have ending first....
            if (firstList[i][1] < secondList[j][1]) {
                i++;
            }
            else {
                j++;
            }
        }

        return intersection;

    }
};