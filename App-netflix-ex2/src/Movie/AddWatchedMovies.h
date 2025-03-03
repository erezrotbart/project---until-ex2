#ifndef ADD_WATCHED_MOVIES_H
#define ADD_WATCHED_MOVIES_H

#include "../Storage_Logic/IDataStorage.h"
#include "../Commands/IInput.h"
#include <vector>
#include <string>
#include "../IMenuFormat.h"

using namespace std;

class AddWatchedMovies : public IInput, public IMenuFormat {
private:
    IDataStorage* dataStorage;
    string InputCheck(const vector<string>& convertedInput) override;
    void printMenuFormat() override;
    bool isFullyNumeric(const vector<string>& convertedInput);

public:
    //constructor
    explicit AddWatchedMovies(IDataStorage* storage); 
    //add movie function
    void addMoviesToUser(int userID, const vector<int>& moviesID);
};

#endif
