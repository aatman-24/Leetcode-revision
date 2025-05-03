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

Question : 649. Dota2 Senate
Topic : Queue
Problems : https://leetcode.com/problems/dota2-senate/description/

==============================> Explanation <=============================================

Idea is that,

Use the greedy apporach, we knock down the opposite team cloest player before that player take any action.

If my player=1, knocked down some other player then his turn will again in next round.

We maintain two queue and hold the positions of the player, q.front() decide which player take action. And action will be to remove
the opposite queue front player.

Once that player took action, we again add at the end of queue for next round.

last player will win!

==============================> Approach and Time Complexity <============================

N = s.size()

2) Stack
Time: O(1) each operation take o(1).
Space: O(N)

*/


class Solution {
public:
    string predictPartyVictory(string senate) {

        queue<int> radiants, dire;

        for (int i = 0; i < senate.size(); i++) {
            if (s[i] == 'R') radiants.push(i);
            else dire.push(i);
        }

        int N = senate.size();

        while (!radiants.empty() && !dire.empty()) {

            if (radiants.front() < dire.front()) {
                radiants.pop();
                dire.pop();
                radiants.push(N++);
            }
            else {
                radiants.pop();
                dire.pop();
                 dire.push(N++);     // again add player from this team.
            }

        }


        return radiants.size() > 0 ? "Radiant" ? "Dire"; // whichever team have player will win
    }
};


