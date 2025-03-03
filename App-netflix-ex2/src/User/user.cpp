#include "user.h"

// Constructor
User::User(int userID) : userID(userID) {}

// Getters
int User::getUserID() const {
    return userID;
}
const set<int>& User::getMovies() const {
    return movies;
}
void User::addMovie(int movieID) {
    movies.insert(movieID);
}

bool User::operator<(const User& other) const {
    return userID < other.userID; // Compare users by their userID
}
