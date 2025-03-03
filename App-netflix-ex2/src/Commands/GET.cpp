#include "GET.h"
#include "recommended.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Constructor: Create a new recommended instance using the provided storage
GET::GET(IDataStorage* storage) {
    recommendCommand = new recommended(storage);
}

// InputCheck function
string GET::InputCheck(const vector<string>& convertedInput) {
    // Call the recommend function return what it returns
    string output = recommendCommand->InputCheck(convertedInput);
    return output;
}
