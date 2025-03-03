#ifndef USER_H
#define USER_H
#include <string>
#include <set>
using namespace std;
class User {
private:
    const int userID;
    set<int> movies; 

public:
    // Constructor
    explicit User(int userID);

    // Getters
    int getUserID() const;
    const set<int>& getMovies() const;

    // Modifier
    void addMovie(int movieID);
    
    // Overload operators for comparison
    bool operator<(const User& other) const;
};


#endif
