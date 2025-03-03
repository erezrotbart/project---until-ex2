// how to use:
// #include "GetWatchedMovies.h"
// FileDataStorage fileStorage("filename.txt");
// GetWatchedMovies Getter(&fileStorage);
// std::set<int> movies=Getter.getMoviesFromUser(4);
// movies will hold a set of movies watched by the user of id 4



#ifndef GET_WATCHED_MOVIES_H
#define GET_WATCHED_MOVIES_H
#include "../Storage_Logic/IDataStorage.h"

class GetWatchedMovies {
private:
    IDataStorage* dataStorage;

public:
    //constructor
    explicit GetWatchedMovies(IDataStorage* storage);
    //get movies function
    std::set<int> getMoviesFromUser(int userID);
};

#endif
