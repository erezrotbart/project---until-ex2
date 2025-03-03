#include "GetAllUsers.h"
#include <fstream>
#include <sstream>

// Constructor
GetAllUsers::GetAllUsers(IDataStorage* storage) : dataStorage(storage) {}

// Method to retrieve all users
std::set<User> GetAllUsers::getAllUsers() const {
    std::set<User> users;

    // Use IDataStorage to retrieve all user data
    auto allData = dataStorage->getAllUserData(); 

    // Iterate through the data and create User objects
    for (const auto& [userID, movies] : allData) {
        User user(userID);
        for (int movieID : movies) {
            user.addMovie(movieID);
        }
        users.insert(user);
    }

    return users;
}
