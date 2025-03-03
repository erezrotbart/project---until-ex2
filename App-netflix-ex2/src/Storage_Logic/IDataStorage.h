#ifndef I_DATA_STORAGE_H
#define I_DATA_STORAGE_H

#include <vector>
#include <set>
#include <unordered_map>

class IDataStorage {
public:

    // check if user exists
    virtual bool userExists(int userID) const = 0;

    // get user watched movies
    virtual std::set<int> getWatchedMovies(int userID) const = 0;

    // add movies to user watch list
    virtual void addWatchedMovies(int userID, const std::vector<int>& moviesID) = 0;

    // Retrieve all user data (user ID mapped to their watched movies)
    virtual std::unordered_map<int, std::set<int>> getAllUserData() const = 0;

    //delete watched movies from user watch list
    virtual void deleteWatchedMovies(int userID, const std::vector<int>& movieIDs) = 0;
};

#endif