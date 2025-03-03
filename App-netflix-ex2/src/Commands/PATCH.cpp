#include "PATCH.h"
#include <string>
#include <vector>

PATCH::PATCH(IDataStorage* storage) : dataStorage(storage), addWatchedMovies(storage) {}

std::string PATCH::InputCheck(const std::vector<std::string>& convertedInput) {
    // checking if all added movies and user are numeric and if the input size is valid
    if (!isFullyNumeric(convertedInput) || convertedInput.size() < 3) {
        // Invalid input, ignore entire input
        return "400 Bad Request";
    }

    // Convert user ID to integer for addMoviesToUser function
    int userID = std::stoi(convertedInput[1]);

    // Check if user already exists
    if (!dataStorage->userExists(userID)) {
        return "404 Not Found";
    }

    // Convert movie IDs to integers vector for addMoviesToUser function
    std::vector<int> movieIDs;
    for (size_t i = 2; i < convertedInput.size(); i++) {
        movieIDs.push_back(std::stoi(convertedInput[i]));
    }

    // Add movies to user if all validations pass
    addWatchedMovies.addMoviesToUser(userID, movieIDs);
    return "204 No Content";
}

bool PATCH::isFullyNumeric(const std::vector<std::string>& convertedInput) {
    // loop skips the first string in the vector ("PATCH")
    for (size_t i = 1; i < convertedInput.size(); i++) {
        // initialize a string with the current string in the vector
        const std::string& str = convertedInput[i];

        // check if the string is empty
        if (str.empty()) return false;

        // iterating over the string and checking if all the chars are digits
        for (char c : str) {
            if (!isdigit(c)) {
                // false if the char is not a digit
                return false;
            }
        }
    }
    // return true if all the strings are digits
    return true;
}