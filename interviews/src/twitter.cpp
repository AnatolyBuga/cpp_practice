#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <string>
#include <stack>
#include <set>

std::ostream& operator<<(std::ostream& os, const std::vector<int>& vec)
{
    os << "[";
    for (int i = 0; i < vec.size(); i++) {
        if (i == vec.size() - 1)
            os << vec[i];
        else
            os << vec[i] << ", ";
    }
    return os << "]";
}

const int N = 10;

class Twitter {
    
public:
    
    std::unordered_map<int, std::stack<int>> user_tweet_map; //
    std::unordered_map<int, std::unordered_set<int>> user_following_map; // u1 follows u2, u3
    
    // Registers a user to the system. Each call to this function will be made with a unique userId.
    void register_user(int user_id) {
       if (user_tweet_map.find(user_id) == user_tweet_map.end()){
           
           std::stack<int> empty_stack;
           user_tweet_map[user_id] = empty_stack;
           
           std::unordered_set<int> empty_set;
           user_following_map[user_id] = empty_set;
           
       }
    }
    
    // Composes a new tweet with ID tweet_id by the user userId. Each call to this function will be made with a unique tweet_id.
    // Each next tweet_id will be larger than any previous one.
    void post_tweet(int user_id, int tweet_id) {
        user_tweet_map[user_id].push(tweet_id);
    }
    
    // The user with ID follower_id started following the user with ID followee_id. Both userIds are guaranteed to exist.
    void follow(int follower_id, int followee_id) {
        user_following_map[follower_id].insert(followee_id);
    }
    
    // The user with ID follower_id started unfollowing the user with ID followee_id. Both userIds are guaranteed to exist.
    void unfollow(int follower_id, int followee_id) {
        user_following_map[follower_id].erase(followee_id);
    }
    
    // Retrieves the N most recent tweet IDs in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user themself. Tweets must be ordered from most recent to least recent.
    std::vector<int> get_news_feed(int user_id, int num_tweets) {
        
        
        std::set<int> all_tweets_from_followees;
        
        auto followees = user_following_map[user_id];
        for(int followee: followees){
            auto tweetss_from_followee = user_tweet_map[followee];
            while (!tweetss_from_followee.empty()) {
                all_tweets_from_followees.insert( tweetss_from_followee.top() );
            }
        }
        
        auto tweetss_from_self = user_tweet_map[user_id];
        
        // TEMP
        // std::vector<int> elements;
        // while(!tweetss_from_self.empty()){
        //     elements.push_back(tweetss_from_self.top());
        //     tweetss_from_self.pop();
        // }
        // std::cout << elements << std::endl;
        // //
        
        while (!tweetss_from_self.empty()) {
                all_tweets_from_followees.insert( tweetss_from_self.top() );
            }
        
        
        int count = 0;               
        std::vector<int> last_n_tweets;
        for (auto i = std::rbegin(all_tweets_from_followees); i != std::rend(all_tweets_from_followees) && count < N; i++){
            last_n_tweets.push_back(*i);
        };
        
        return last_n_tweets;
    }
};


int main()
{
    Twitter twitter;        
    twitter.register_user(1);
    twitter.post_tweet(1, 5); // User 1 posts a new tweet (id = 5).
    
    std::cout << twitter.get_news_feed(1, 10) << "\n"; // [5]
    
    // twitter.register_user(2);
    // twitter.follow(1, 2);    // User 1 follows user 2.
    // twitter.post_tweet(2, 6); // User 2 posts a new tweet (id = 6).
    
    // std::cout << twitter.get_news_feed(1, 10) << "\n"; // [6,5]
    
    // twitter.unfollow(1, 2);  // User 1 unfollows user 2.
    
    // std::cout << twitter.get_news_feed(1, 10) << "\n"; // [5]
    
    return 0;
}