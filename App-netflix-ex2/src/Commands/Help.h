#ifndef HELP_H
#define HELP_H

#include "../Storage_Logic/IDataStorage.h"
#include "IInput.h"
#include <vector>
#include <string>
#include "ICommand.h"
#include "../IMenuFormat.h"


using namespace std;
class Help : public IInput , public ICommand, public IMenuFormat {
public:
    string InputCheck(const vector<string>& convertedInput) override;
    void Execute() override;
    string getHelp();
    void printMenuFormat() override;
};

#endif
