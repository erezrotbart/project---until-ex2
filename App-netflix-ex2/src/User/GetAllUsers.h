#ifndef GET_ALL_USERS_H
#define GET_ALL_USERS_H

#include "../Storage_Logic/IDataStorage.h"
#include "user.h"
#include <set>
#include <string>

class GetAllUsers {
private:
    IDataStorage* dataStorage;

public:
    // Constructor
    explicit GetAllUsers(IDataStorage* storage);

    // Method to retrieve all users
    std::set<User> getAllUsers() const;
};

#endif