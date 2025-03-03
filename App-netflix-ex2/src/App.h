#ifndef APP_H
#define APP_H

#include <string>
#include <vector>
#include <map>
#include "Commands/ICommand.h"
#include "Commands/IInput.h"
#include "Commands/recommended.h"
using namespace std;

class App {
    
private:
    map<string, IInput*> inputMap;

public:
    App(const map<string, IInput*>& inputMap);
    void Run();
    string handleCommand(const string& input);
    bool IsValidInput(const string& input, const vector<string>& convertedInput);
    vector<string> parseInput(const string& input);
};

#endif // APP_H