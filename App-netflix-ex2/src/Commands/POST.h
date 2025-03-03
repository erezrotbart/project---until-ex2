#ifndef POST_H
#define POST_H

#include "../Storage_Logic/IDataStorage.h"
#include "IInput.h"
#include <vector>
#include <string>

class POST : public IInput {
private:
    IDataStorage* dataStorage;

public:
    explicit POST(IDataStorage* storage);
    std::string InputCheck(const std::vector<std::string>& convertedInput) override;
};

#endif