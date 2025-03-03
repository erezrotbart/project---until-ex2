#include "User/user.h"
#include "Movie/movie.h"
#include "Movie/AddWatchedMovies.h"
#include "Movie/GetWatchedMovies.h"
#include "Storage_Logic/FileDataStorage.h"
#include "App.h"
#include "Commands/IInput.h"
#include <iostream>
#include <map>
#include <string>
#include "Commands/Help.h"
#include "Commands/recommended.h"

// setToString function
string setToString(const set<int>& s) {
    ostringstream oss;
    oss << "{";
    for (auto it = s.begin(); it != s.end(); ++it) {
        if (it != s.begin()) oss << ", "; // Add a comma separator
        oss << *it;
    }
    oss << "}";
    return oss.str();
}

int main() {
    const string filename = "../data/data.txt";
    FileDataStorage fileStorage(filename);
    AddWatchedMovies admin(&fileStorage);

    // defining map of options of the program
    map<string, IInput*> options;
    options["add"] = new AddWatchedMovies(&fileStorage);
    options["help"] = new Help;
    options["recommend"] = new recommended(&fileStorage); 
    
    //running netflix
    App app(options);
    app.Run();

    // Clean up to avoid memory leaks
    delete options["add"];
    delete options["help"];
    options["recommend"]; 

    return 0;
}