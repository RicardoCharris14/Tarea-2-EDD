#ifndef USER
#define USER

#include <string>
#include <iostream>

class user{
public:
    using string = std::string;
private:
    string university;
    long long user_ID;
    string username;
    int numberTweets;
    int friendsCount;
    int followersCount;
    string createdAt;
public:
    user(string, long long, string, int, int, int, string);
    long long getID();
    string getUsername();
    void printData();
};

user::user(string university, long long user_ID, string username, int numberTweets,
            int friendsCount, int followersCount, string createdAt) : university(university),
             user_ID(user_ID), username(username), numberTweets(numberTweets), friendsCount(friendsCount),
              followersCount(followersCount), createdAt(createdAt) {}

long long user::getID(){
    return user_ID;
}

std::string user::getUsername(){
    return username;
}

void user::printData(){
    std::cout <<std::endl
              << "University: " << university << std::endl 
              << "User ID: " << user_ID << std::endl 
              << "username: " << username << std::endl 
              << "Number of tweets: " << numberTweets << std::endl 
              << "Friends count: " << friendsCount << std::endl 
              << "Followers Count: " << followersCount << std::endl 
              << "Created at: " << createdAt << "\n\n";
}

#endif
