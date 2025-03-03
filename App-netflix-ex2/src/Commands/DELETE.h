#ifndef DELETE_H
#define DELETE_H

#include "IInput.h"
#include "../Storage_Logic/IDataStorage.h"
#include <vector>
#include <string>

class DELETE : public IInput {
public:
    DELETE(IDataStorage* storage);
    std::string InputCheck(const std::vector<std::string>& convertedInput) override;

private:
    IDataStorage* dataStorage;
    bool isFullyNumeric(const std::vector<std::string>& convertedInput);
};

#endif // DELETE_H