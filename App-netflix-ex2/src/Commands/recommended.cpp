#include "recommended.h"
#include "../User/GetAllUsers.h"
#include <sstream>

// constructor
recommended::recommended(IDataStorage* storage) : dataStorage(storage) {}

// recommend function
std::string recommended::recommend(int userID, int movieID) {
    std::set<int> userMovies = dataStorage->getWatchedMovies(userID);
    std::set<int> alluserIDs = AllUserIDs(dataStorage);
    std::map<int, int> userIdRelevance = calculateUserRelevance(alluserIDs, userMovies, userID, movieID);
    std::map<int, int> movieIdRelevance = calculateMovieRelevance(userIdRelevance, userMovies, movieID);
    std::vector<std::pair<int, int>> sortedRecommendations = sortRecommendations(movieIdRelevance);
    // printTopRecommendations(sortedRecommendations);
    return getTopRecommendationsAsString(sortedRecommendations);
}

// InputCheck function
std::string recommended::InputCheck(const vector<string>& convertedInput) {

    // checking if all added movies and user are numeric and if the input size is valid
    if (convertedInput.size() != 3 || !isFullyNumeric(convertedInput)) {
        // Invalid input, ignore entire input
        return "400 Bad Request"; 
    }
    // Convert user ID to integer for recommend function
    int userID = stoi(convertedInput[1]);

    // Check if the user exists in the system
    if (!IsUserExists(userID, AllUserIDs(dataStorage))) {
        // User does not exist, ignore input
        return "404 Not Found";
    }

    // Convert movie ID to integer for recommend function
    int movieID = stoi(convertedInput[2]);

    // Check if the movie exists in the system
    if (!IsMovieExists(movieID, AllUserIDs(dataStorage))) {
        // Movie does not exist, ignore input
        std::string output = "200 Ok\n\n";
        output+="";
        return output;
    }

    // Call the recommend function if all validations pass
    std::string output = "200 Ok\n\n";
    output+=recommend(userID, movieID);

    return output;
}

//checking if the user exists in the system
bool recommended::IsUserExists(int userID, const std::set<int>& allUserIDs) {
    return allUserIDs.find(userID) != allUserIDs.end();
}

//checking if the movie exists in the system
bool recommended::IsMovieExists(int movieID, const std::set<int>& allUserIDs) {
    for (const auto& userID : allUserIDs) {
        std::set<int> userMovies = dataStorage->getWatchedMovies(userID);
        if (userMovies.find(movieID) != userMovies.end()) {
            return true;
        }
    }
    return false;
}

// Helper function to check if all strings (except the first one) in the vector are valid integers (only digits)
bool recommended::isFullyNumeric(const vector<string>& convertedInput) {
    // Loop skips the first string in the vector ("recommend")
    for (size_t i = 1; i < convertedInput.size(); i++) {
        // Initialize a string with the current string in the vector
        const string& str = convertedInput[i];

        // Check if the string is empty
        if (str.empty()) return false;

        // Iterating over the string and checking if all the chars are digits
        for (char c : str) {
            if (!isdigit(c)) {
                // False if the char is not a digit
                return false;
            }
        }
    }
    // Return true if all the strings are digits
    return true;
}

// Other methods
std::set<int> recommended::AllUserIDs(IDataStorage* storage) {
    GetAllUsers getAllUsers(storage);
    std::set<User> allUsers = getAllUsers.getAllUsers();
    std::set<int> allUserIDs;
    for (const User& user : allUsers) {
        allUserIDs.insert(user.getUserID());
    }
    return allUserIDs;       
}

std::map<int, int> recommended::calculateUserRelevance(const std::set<int>& allUserIDs,
const std::set<int>& userMovies, int userID, int movieID) const {
    std::map<int, int> userIdRelevance; 
    for (const auto& otherUserID : allUserIDs) {
        if (otherUserID == userID) {
            continue;
        }
        std::set<int> otherUserMovies = dataStorage->getWatchedMovies(otherUserID);
        if (otherUserMovies.count(movieID)) {
            std::set<int> intersection;
            set_intersection(userMovies.begin(), userMovies.end(), otherUserMovies.begin(), otherUserMovies.end(),
                std::inserter(intersection, intersection.begin()));
            int commonMovies = intersection.size();
            userIdRelevance[otherUserID] = commonMovies;
        }
    }
    return userIdRelevance;
}

std::map<int, int> recommended::calculateMovieRelevance(
const std::map<int, int>& userIdRelevance, const std::set<int>& userMovies, int movieID) const {
    std::map<int, int> movieIdRelevance;
    for (const auto& [similarUserID, similarityScore] : userIdRelevance) {
        std::set<int> similarUserMovies = dataStorage->getWatchedMovies(similarUserID);
        for (int movie : similarUserMovies) {
            if (userMovies.count(movie) == 0 && movie != movieID) {
                movieIdRelevance[movie] += similarityScore;
            }
        }
    }
    return movieIdRelevance;
}

std::vector<std::pair<int, int>> recommended::sortRecommendations(const std::map<int, int>& movieIdRelevance) const {
    std::vector<std::pair<int, int>> sortedRecommendations(movieIdRelevance.begin(), movieIdRelevance.end());
    std::sort(sortedRecommendations.begin(), sortedRecommendations.end(),
            [](const auto& a, const auto& b) {
                return a.second > b.second || (a.second == b.second && a.first < b.first);
            });
    return sortedRecommendations;
}

void recommended::printTopRecommendations(const std::vector<std::pair<int, int>>& sortedRecommendations) const {
    for (size_t i = 0; i < std::min(sortedRecommendations.size(), size_t(10)); ++i) {
        std::cout << sortedRecommendations[i].first << " ";
    }
    std::cout << std::endl;
}

//returns the top recommendation as a string
std::string recommended::getTopRecommendationsAsString(const std::vector<std::pair<int, int>>& sortedRecommendations) const {
    std::ostringstream oss;
    for (size_t i = 0; i < std::min(sortedRecommendations.size(), size_t(10)); ++i) {
        oss << sortedRecommendations[i].first;
        if (i < std::min(sortedRecommendations.size(), size_t(10)) - 1) {
            oss << " "; // Add a space between IDs
        }
    }
    return oss.str();
}