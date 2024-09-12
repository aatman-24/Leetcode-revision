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

Question : 950. Reveal Cards In Increasing Order
Topic : Queue
Problems : https://leetcode.com/problems/reveal-cards-in-increasing-order/description/

==============================> Explanation <=============================================

Return an ordering of the deck that would reveal the cards in increasing order.

That mean we have to return the deck which reveal the cards in increasing order with given rule(take it first, add the second at the end of deck).

Required orders of cards: [2, 3, 5, 7, 11, 13, 17]

Now, we have to arrange the deck such that it gives the orders of cards in above orders when we play the game.

So Idea is that,

Based on rule given in question we can get the idea it is queue question,

We need position for each deck element, that gives gurantee the orders of deck.

we know the revealed deck element orders => [2, 3, 5, 7, 11, 13, 17],

Why not simulate the game in reverse manner ?

- Suppose, first element which reveal is 2 right ? And we know user will start from left -> right..[0 -> N]

arr[0] = 2...

next....

arr[?] = 3....

That "?"(which mean which next position will reveal), "1" or "2" ?
[As given in rule, once you pick up the top of card("0"), you need to put the next card at the end of queue(next pos will go at the end of queue)]
Answer: 1 go at the end of queue, and next position is 2.

arr[2] = 3....

So we are adding the next pos at the end of queue and again assign the next element of deck to right position.

Check the code!!

# Input: deck = [17,13,11,2,3,5,7]


==============================> Approach and Time Complexity <============================

N = s.size()

2) Stack
Time: O(1) each operation take o(1).
Space: O(N)

*/


class Solution {
public:
    vector<int> deckRevealedIncreasing(vector<int>& deck) {

        int N = deck.size();

        // reveals the position of cards.
        queue<int> q;
        for (int i = 0; i < N; i++) q.push(i);      // we start from left -> right, to pick up the cards from deck. [0 -> N]

        sort(deck.begin(), deck.end());             // elements of deck. we know revealed cards orders.
        int deckElementPos = 0;

        vector<int> revealOrders(N, 0);

        // our task is to assign the deck[i] to revealed position.
        while (!q.empty()) {

            // position which is revealed
            int revealOrder = q.front(); q.pop();
            revealOrders[revealOrder] = deck[deckElementPos++];

            // This position will not reveal now, as given in game we need to add this position at the end of queue.
            if (!q.empty()) {
                int nextOrder = q.front();
                q.push(nextOrder);  // add this nextOrder at the end of queue, so that we can assign right to it.
                q.pop();
            }

        }

        return revealOrders;
    }
};



