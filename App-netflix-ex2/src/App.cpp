#include "App.h"
#include "Movie/AddWatchedMovies.h"
#include "Storage_Logic/FileDataStorage.h"
#include "Commands/IInput.h"
#include "Commands/Help.h"
#include <iostream>
#include <sstream>
#include "Commands/ICommand.h"
#include <vector>
#include <map>

using namespace std;
//constructor
App::App(const map<string, IInput*>& inputMap) : inputMap(inputMap) {}

// function to run the program
void App::Run() {
    string input;
    
    // Run the program until the user decides exit terminal
    while (true) {
        // getting input from this user
        getline(cin, input);

        /* 
        
          adding the following lines help to run tests for the program because the progrma will not exit
          when the user types "exit" in the terminal.

          add this lines to the code to make the test work:
           if (input == "exit") {
            break;
        }

        */

        // Convert string input to vector for easy checking
        vector<string> convertedInput = parseInput(input);

        // Check if the input is valid and contains a command.
        if (!IsValidInput(input, convertedInput)) {
            continue;
        }
        
        //send the input to the input check function and execute a good command.
        string output=inputMap[convertedInput[0]]->InputCheck(convertedInput);

        if (!output.empty()) { // Only print non-empty output
            cout << output << "\n";
        }
    }
}
//handles a single command as oppose to handling a whole run
string App::handleCommand(const string& input) {
    // Convert string input to vector for easy checking
    vector<string> convertedInput = parseInput(input);
    // Check if the input is valid and contains a command.
    if (!IsValidInput(input, convertedInput)) {
        return "400 Bad Request";
    }
    //send the input to the input check function and execute a good command.
    string output=inputMap[convertedInput[0]]->InputCheck(convertedInput);
    return output;
}
// function to convert string to vector
vector<string> App::parseInput(const string& input) {
    
    // vector to store the converted input
    vector<string> convertedInput;
    stringstream inputstream(input);

    // word to store the input for each iteration
    string word;

    // Check if there are leading spaces in the input - not allowed in the task
    if (input.find_first_not_of(' ') != 0) {
        // Return an empty vector if there are leading spaces
        return convertedInput;
    }
    
    //passing any word until space to the vector
    while (inputstream >> word) {
        convertedInput.push_back(word);
    }
    
    //return the converted input
    return convertedInput;
}

// first input check for the program
bool App::IsValidInput(const string& input, const vector<string>& convertedInput) {
    if (convertedInput.empty()) {
        return false;
    }

    // Check if the input contains a tab character
    if (input.find('\t') != string::npos) {
        return false;
    }

    // Check if the input contains a valid command using map<string, IInput*> iterator
    if (inputMap.find(convertedInput[0]) == inputMap.end()) {
        return false;
    }
    
    //if the method passes all the checks return true
    return true;
}