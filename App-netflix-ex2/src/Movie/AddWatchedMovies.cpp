#include "AddWatchedMovies.h"
#include "../Commands/IInput.h"
#include "../Storage_Logic/IDataStorage.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

// constructor
AddWatchedMovies::AddWatchedMovies(IDataStorage* storage) : dataStorage(storage) {}

// add movies function
void AddWatchedMovies::addMoviesToUser(int userID, const vector<int>& moviesID) {
    dataStorage->addWatchedMovies(userID, moviesID);
}

//this func check the input and executing AddWatchedMovies in case it good 
string AddWatchedMovies::InputCheck(const vector<string>& convertedInput) {
    
    // checking if all added movies and user are numeric and if the input size is valid
    if (!isFullyNumeric(convertedInput) || convertedInput.size() < 3) {
        // Invalid input, ignore entire input
        return ""; 
    }

    // Convert user ID to integer for addMoviesToUser function
    int userID = stoi(convertedInput[1]);

    // Convert movie IDs to integers vector for addMoviesToUser function
    vector<int> movieIDs;
    for (size_t i = 2; i < convertedInput.size(); i++) {
        movieIDs.push_back(stoi(convertedInput[i]));
    }

    // Add movies to user if all validations pass
    addMoviesToUser(userID, movieIDs);
    return "";
}

// Helper function to check if all strings (except the first one) in the vector are valid integers (only digits)
bool AddWatchedMovies::isFullyNumeric(const vector<string>& convertedInput) {

    //loop akips the first string in the vector ("add")
    for (size_t i = 1; i < convertedInput.size(); i++) {

        //initialize a string with the current string in the vector
        const string& str = convertedInput[i];

        //checkin if the string is empty
        if (str.empty()) return false;

        //isterating over the string and checking if all the chars are digits
        for (char c : str) {
            if (!isdigit(c)) {
                //false if the char is not a digit
                return false;
            }
        }
    }
    //return true if all the strings are digits
    return true;
}

//print the menu format
void AddWatchedMovies::printMenuFormat(){
    cout << "add [userid] [movieid1] [movieid2]…\n";
}
