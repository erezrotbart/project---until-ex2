#ifndef PATCH_H
#define PATCH_H

#include "../Storage_Logic/IDataStorage.h"
#include "../Movie/AddWatchedMovies.h"
#include <vector>
#include <string>

class PATCH : public IInput   {
public:
    PATCH(IDataStorage* storage);
    std::string InputCheck(const std::vector<std::string>& input) override;

private:
    IDataStorage* dataStorage;
    AddWatchedMovies addWatchedMovies;
    bool isFullyNumeric(const std::vector<std::string>& convertedInput);
};

#endif // PATCH_H