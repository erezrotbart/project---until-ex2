#include "DELETE.h"
#include "../Movie/GetWatchedMovies.h" 
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Constructor
DELETE::DELETE(IDataStorage* storage) : dataStorage(storage) {}

// InputCheck function
string DELETE::InputCheck(const vector<string>& convertedInput) {
    // Check if all inputs are numeric and if the input size is valid
    if (!isFullyNumeric(convertedInput) || convertedInput.size() < 3) {
        return "400 Bad Request";
    }

    // Convert user ID to integer
    int userID = stoi(convertedInput[1]);

    // Convert movie IDs to integers vector
    vector<int> movieIDs;
    for (size_t i = 2; i < convertedInput.size(); i++) {
        movieIDs.push_back(stoi(convertedInput[i]));
    }

    // Check if user exists
    if (!dataStorage->userExists(userID)) {
        return "404 Not Found";
    }

    // Check if all movies exist for the user
    GetWatchedMovies getWatchedMovies(dataStorage);
    std::set<int> watchedMovies = getWatchedMovies.getMoviesFromUser(userID);
    for (int movieID : movieIDs) {
        if (watchedMovies.find(movieID) == watchedMovies.end()) {
            return "404 Not Found";
        }
    }

    // Delete movies
    dataStorage->deleteWatchedMovies(userID, movieIDs);
    return "204 No Content";
}

// Helper function to check if all strings (except the first one) in the vector are valid integers (only digits)
bool DELETE::isFullyNumeric(const vector<string>& convertedInput) {
    for (size_t i = 1; i < convertedInput.size(); i++) {
        const string& str = convertedInput[i];
        if (str.empty()) return false;
        for (char c : str) {
            if (!isdigit(c)) {
                return false;
            }
        }
    }
    return true;
}