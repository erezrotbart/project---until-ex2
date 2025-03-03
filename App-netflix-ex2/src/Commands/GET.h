#ifndef GET_H
#define GET_H

#include "../Storage_Logic/IDataStorage.h"
#include "recommended.h"
#include "IInput.h"
#include <vector>
#include <string>

// GET class definition
class GET : public IInput {
private:
    recommended* recommendCommand; // Owned recommended instance

public:
    // Constructor
    explicit GET(IDataStorage* storage);

    // InputCheck override
    std::string InputCheck(const std::vector<std::string>& convertedInput) override;
};

#endif // GET_H
