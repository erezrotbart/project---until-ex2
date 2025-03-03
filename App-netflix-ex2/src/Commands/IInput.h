// IInput.h
#ifndef IINPUT_H
#define IINPUT_H
#include <vector>
#include <string>
using namespace std;


class IInput {
public:
    virtual ~IInput() {}
    virtual string InputCheck(const vector<string>& convertedInput) = 0;
};

#endif // IINPUT_H