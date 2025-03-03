#include "POST.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

POST::POST(IDataStorage* storage) : dataStorage(storage) {}

string POST::InputCheck(const vector<string>& convertedInput) {
    // number of argemnets must be at least 3
    if (convertedInput.size() < 3) {
        return "400 Bad Request";
    }

    // the user id is the first argument 
    int userID;
    // check if the user id is a integer if not return a bad request
    try{
        userID = stoi(convertedInput[1]);
    } catch (invalid_argument& e){
        return "400 Bad Request";
    }

    // check if the user exists if so return 400 Bad Request
    if(dataStorage->userExists(userID)){
        return "400 Bad Request";
    }

    // create a verctor for the user watched movies
    vector<int> movieIDs;

    for (size_t i = 2; i < convertedInput.size(); i++) {
        // check if the movie id is a integer and if so add it to the vector of watched movies by the user
        try{
            movieIDs.push_back(stoi(convertedInput[i]));
        }
        catch (invalid_argument& e){
            return "400 Bad Request";
        }
    }


    dataStorage->addWatchedMovies(userID, movieIDs);
    return "201 Created";
}
