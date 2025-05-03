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

Question : NC_6_Design_Twitter
Topic : Heap, PQ
Problems : https://neetcode.io/problems/design-twitter-feed

==============================> Explanation <=============================================

1) Brute Force: Here, what we do..... if we need to fetch the newsFeed for X user... then we iterate over all
the following of X users... and collect all the posts from all the following...put it into the array...
sort that based on decesding order of "time"... and pick the first 10...

Time: Suppose on average.... 1 User is follwing total "M" user... and each user post around "N" post.....

To collect all post take: O(M*N) time, + sorting them take: O(M*N*log(MN)) + O(10) to pick first 10...


2) Priority Queue: In Brute force... we are collecting all posts and then we are picking first 10..instead of what we can do...
we take the latest post of each following and put it into the maxHeap.... maxHeap.top() return the post which is most recent from
all the users..so we add it into the answer... and we put the second latest post of that user into the maxHeap for consideration...
so this way we pick 10 posts..without going through all the posts

Time: Suppose on average.... 1 User is follwing total "M" user... and each user post around "N" post.....

Time: O(M)(to pick latest post from each user) + O(10*log(M))

==============================> Approach and Time Complexity <============================

1) PQ
Time: O(MLogM)
Space: O(N)

*/


// Base code
class Twitter {
public:

    int timer;

    // store all users posts
    unordered_map<int, vector<pair<int, int>>> postsMap; // u -> {{t1, p1}, {t2, p2}}

    // store all followers for user
    unordered_map<int, unordered_set<int>> followMap; // u -> {u1, u2, u3}

    Twitter() {
        timer = 0;
    }

    // using the "timer" to determine the order of tweet.
    void postTweet(int userId, int tweetId) {
        postsMap[userId].push_back({timer++, tweetId});
    }

    // this return top 10 posts, check both brute force approach and optimize using the pq.
    vector<int> getNewsFeed(int userId) {

    }

    // simple
    void follow(int followerId, int followeeId) {
        if (followMap.count(followerId)) {
            followMap[followerId].push_back(followeeId);
        }
    }

    // simple
    void unfollow(int followerId, int followeeId) {
        if (followMap.count(followerId) && followMap[followerId].count(followeeId)) {
            followMap[followerId].remove(followeeId);
        }
    }
};


// Brute force
class Twitter {
public:

    int timer;
    unordered_map<int, vector<pair<int, int>>> postsMap; // u -> {{t1, p1}, {t2, p2}}
    unordered_map<int, unordered_set<int>> followMap; // u -> {u1, u2, u3}

    Twitter() {
        timer = 0;
    }

    void postTweet(int userId, int tweetId) {
        postsMap[userId].push_back({timer++, tweetId});
    }

    // this return top 10 posts
    vector<int> getNewsFeed(int userId) {






        // user can see own posts as well...
        followMap[userId].insert(userId);

        vector<pair<int, int>> posts;

        // iterate thorough all the following of userId
        for (int followingId : followMap[userId]) {

            // get the post
            vector<pair<int, int>> userPosts = postsMap[followingId];

            posts.insert(posts.end(), userPosts.begin(), userPosts.end());
        }

        auto compare = [](const pair<int, int> p1, const pair<int, int> p2) {
            return p1.first > p2.first;
        };

        // sort the posts on ascending order of the time
        sort(posts.begin(), posts.end(), compare);

        // take the last 10 posts...
        vector<int> newsFeedPosts;
        for (int i = 0; i < min(10, (int)posts.size()); i++) {
            newsFeedPosts.push_back(posts[i].second);
        }

        return newsFeedPosts;

    }

    void follow(int followerId, int followeeId) {
        if (followMap.count(followerId)) {
            followMap[followerId].insert(followeeId);
        }
    }

    void unfollow(int followerId, int followeeId) {
        if (followMap.count(followerId) && followMap[followerId].count(followeeId)) {
            followMap[followerId].erase(followeeId);
        }
    }
};



// Using Priority Queue
class Twitter {
public:

    int timer;
    unordered_map<int, vector<pair<int, int>>> postsMap; // u -> {{t1, p1}, {t2, p2}}
    unordered_map<int, unordered_set<int>> followMap; // u -> {u1, u2, u3}

    Twitter() {
        timer = 0;
    }

    void postTweet(int userId, int tweetId) {
        postsMap[userId].push_back({timer++, tweetId});
    }

    // this return top 10 posts
    vector<int> getNewsFeed(int userId) {

        // user can see own posts as well...
        followMap[userId].insert(userId);

        auto compare = [](const vector<int> &a, const vector<int> &b) {
            return a[0] < b[0];
        };

        // maxHeap.... with timer as key.....
        priority_queue<vector<int>, vector<vector<int>>, decltype(compare)> pq(compare); // {timer, userId, postId, lastIndex}

        // iterate thorough all the following of userId, and add the last post for that user.
        for (int followingId : followMap[userId]) {

            if (postsMap.count(followingId)) {

                vector<pair<int, int>> userPosts = postsMap[followingId];

                int lastIndex = userPosts.size() - 1;

                pq.push({userPosts[lastIndex].first, followingId, userPosts[lastIndex].second, lastIndex});

            }

        }

        vector<int> newsFeedPosts;

        // now, we start to remove one post line by line...
        while (!pq.empty() && newsFeedPosts.size() < 10) {

            vector<int> recentPost = pq.top(); pq.pop();

            int timer = recentPost[0];
            int followingId = recentPost[1];
            int postId = recentPost[2];
            int nextIndex = recentPost[3] - 1;

            // Added the post
            newsFeedPosts.push_back(postId);

            if (nextIndex >= 0) {

                pair<int, int> nextRecentPost = postsMap[followingId][nextIndex];

                pq.push({nextRecentPost.first, followingId, nextRecentPost.second, nextIndex});

            }

        }

        return newsFeedPosts;

    }

    void follow(int followerId, int followeeId) {
        if (followerId != followeeId) {
            followMap[followerId].insert(followeeId);
        }
    }

    void unfollow(int followerId, int followeeId) {
        if (followMap.count(followerId) && followMap[followerId].count(followeeId)) {
            followMap[followerId].erase(followeeId);
        }
    }
};
