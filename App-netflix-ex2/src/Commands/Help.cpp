#include "Help.h"
#include <iostream>
#include <vector>
#include <string>
#include "../Movie/AddWatchedMovies.h"


using namespace std;

//InputCheck
string Help::InputCheck(const vector<string>& convertedInput) {
    
   // Checking if the input is exactly "help"
    if (convertedInput.size() != 1 || convertedInput[0] != "help") {
        return "400 Bad Request";
    }
    // this->Execute();
    return this -> getHelp();

}
// Execute
void Help::Execute() {

    cout << "DELETE, arguments: [userid] [movieid]\n";
    cout << "GET, arguments: [userid] [movieid]\n";
    cout << "PATCH, arguments: [userid] [movieid]\n";
    cout << "POST, arguments: [userid] [movieid]\n";
    cout << "help\n";
}

void  Help::printMenuFormat() {
     cout << "help\n";
}
string Help::getHelp(){
    return "DELETE, arguments: [userid] [movieid]\nGET, arguments: [userid] [movieid]\nPATCH, arguments: [userid] [movieid]\nPOST, arguments: [userid] [movieid]\nhelp";
}