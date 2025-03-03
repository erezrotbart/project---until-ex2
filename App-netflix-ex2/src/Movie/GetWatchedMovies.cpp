#include "GetWatchedMovies.h"

// constructor
GetWatchedMovies::GetWatchedMovies(IDataStorage* storage) : dataStorage(storage) {}

// get movies function
std::set<int> GetWatchedMovies::getMoviesFromUser(int userID) {
    return dataStorage->getWatchedMovies(userID);
}